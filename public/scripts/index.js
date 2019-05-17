var socket = io();

$(".actionbutton").each(function(index){
	$(this).click(function(){
		socket.emit('binaryaction',$(this).attr('id'));
	});
});

var joystick	= new VirtualJoystick({
    container	: document.getElementById('container'),
    mouseSupport	: true,
    deadzoneX : 20,
    deadzoneY : 20,
    motorAmp : 3,
});
var lastm1 = 0;
var lastm2 = 0;
setInterval(function(){
    var m1 = joystick.motorLeft();
	var m2 = joystick.motorRight();
	if(m1!=lastm1 || m2!=lastm2){
		lastm1=m1;
		lastm2=m2;
		sendMotorSignal(Math.floor(lastm1),Math.floor(-lastm2));
	} 
}, 1/20 * 1000);


//When making a log message for this make sure to include one of the status_msgs in the string and a 0 for false, 1 for true
function checkStatus(msg){
	status_msgs = ["armloaded","armback","armlatched","armpulleyrelease"]
	status_msgs.forEach(function(smsg){
		if(msg.indexOf(smsg)!=-1){
			document.getElementById(smsg).style.color = msg.indexOf("0")!=-1 ? "red" : "blue";
		}
	});
}

//------

function sendMotorSignal(left,right){
	//console.log(`L:${left}, R:${right}`);
	var str = `ML${left}R${right}`;
	socket.emit('binaryaction',str)
}

socket.emit('getlatestlog');

socket.on('logmessage',function(message){
	var msgbox = $('#logmessages');
	msgbox.val(msgbox.val() + message);
	if(msgbox.length)
		msgbox.scrollTop(msgbox[0].scrollHeight - msgbox.height());
	checkStatus(message);
});
socket.on('ultrasonicstatus',function(sensordata){
	console.log(sensordata);
});
