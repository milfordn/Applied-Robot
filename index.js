var express = require("express");

var serialport = require("serialport");
var Readline = require('@serialport/parser-readline');
var port = new serialport('/dev/ttyACM0', {baudRate: 115200});
var parser = port.pipe(new Readline({delimiter:'\n'}));

var app = require("express")(),
	http = require("http").Server(app),
	io = require("socket.io")(http);

const listenport = 15421;
http.listen(listenport,function(){
	console.log("Server running on port "+this.address().listenport);
});

app.get('/', function(req, res){
	    res.sendFile(__dirname + '/public/index.html' );
});

app.use(express.static('public'));

io.on('connection',function(socket){
	socket.on('binaryaction',function(data){
		port.write(data,function(err){
			if(err)
				console.log("Error writing to serial: "+err.message);
			console.log("Wrote to serial: "+data);
		});
	});
	socket.on('getlatestlog',function(){
		io.sockets.emit('logmessage',lastLog);
	});
});
var lastLog = ""
port.on('open',function(){
	console.log("Serial port opened!");
});
parser.on('data',function(data){
	lastLog = data;
	io.sockets.emit('logmessage',lastLog);
	console.log("M: "+lastLog);
});

start_ultrasonic();

function start_ultrasonic(){
	var pyscript = 'ultrasonic.py'
	var spawn = require('child_process').spawn,
		py = spawn('python3',[pyscript]);

	console.log("Launching ultrasonic");
	py.stdout.on('data',function(data){
		var strdata = data.toString();
		sensordata_str = strdata.split(',');
		sensordata = []
		sensordata_str.forEach(function(data_str){
			sensordata.push(parseFloat(data_str));	
		});
		react_ultrasonic(sensordata);
	});
	py.stderr.on('data',function(data){
		var strdata = data.toString();
		console.log("stderr: " +strdata);
	});
}

//Because ultrasonic sensors are notoriously noisy, we add some tolerance.
var obstacle = false;
const tolerance = 3; //We need to get to the tolerance point of the binary value (obstacle|clear) in a row.
var in_a_row = 0;
function react_ultrasonic(sensordata){
	var clear = true; //This is a boolean value that will only be true if all the sensors have nothing in proximity.
	sensordata.forEach(function(sdata,index){
		if(sdata < 20){ //If any sensor reads proximity obstacle
			if(!obstacle && in_a_row >= tolerance){ //If we havent sensed an obstacale, Then we will try to write there is an obstacle, but only if we have reached the tolerance point.
				port.write('o',function(err){
					if(err) console.log("Error writing to serial: "+err.message);
				});
				obstacle = true; //Toggle that there was a obstacle in the most recent report. We don't want to bombard the serial communications.
			}
			//No matter what, if there is a proximity, add 1 to the number in a row.
			in_a_row+=1;
			if(in_a_row >=tolerance)
				in_a_row = tolerance
			clear = false; //Any proximity will trigger this
		}
	});
	//If no proximity was detected, then take 1 away from the values in a row. Once this reaches 0, trigger say there is no obstacle.
	if(clear){ 
		in_a_row-=1
		if(in_a_row <= 0)
			in_a_row=0;
	}
	if(in_a_row <= 0 && obstacle){ //If we are surely clear and there was an obstacle before, then we toggle.
		obstacle = false;
		port.write('c',function(err){
			if(err) console.log("Error writing to serial: "+err.message);
		});
	}
	io.sockets.emit('ultrasonicstatus',sensordata);
}
