var socket = io();

$(".actionbutton").each(function(index){
	$(this).click(function(){
		socket.emit('binaryaction',$(this).attr('id'));
	});
});

/*
var joystick	= new VirtualJoystick({
    container	: document.getElementById('container'),
    mouseSupport	: true,
    motorMax : 255,
    motorMin : 0,
    deadzoneX : 20,
    deadzoneY : 20,
    motorAmp : .7,
});
var lastm1 = 0;
var lastm2 = 0;
setInterval(function(){
    var m1 = joystick.motorLeft();
    var m2 = joystick.motorRight();
    //if(m1!=lastm1 || m2!=lastm2){
	    //lastm1=m1;
	    //lastm2=m2;
	    sendMotorSignal(Math.floor(m1),Math.floor(m2));
	//} 
}, 1/5 * 1000);
*/

//When making a log message for this make sure to include one of the status_msgs in the string and a 0 for false, 1 for true
function checkStatus(msg){
	status_msgs = ["armloaded","armback","armlatched","armpulleyrelease"]
	status_msgs.forEach(function(smsg){
		if(msg.indexOf(smsg)!=-1){
			document.getElementById(smsg).style.color = msg.indexOf("0")!=-1 ? "red" : "blue";
		}
	});
}

var current = [false,false,false,false];
document.addEventListener('keydown',function(event){
    if(event.key == 'w'){ current[0] = true; }
    if(event.key == 'a'){ current[1] = true; }
    if(event.key == 's'){ current[2] = true; }
    if(event.key == 'd'){ current[3] = true; }
});
document.addEventListener('keyup',function(event){
    if(event.key == 'w'){ current[0] = false; }
    if(event.key == 'a'){ current[1] = false; }
    if(event.key == 's'){ current[2] = false; }
    if(event.key == 'd'){ current[3] = false; }
});
setInterval(function(){
    var m1=0;
    var m2=0;
    if(current[0]){ m1=120; m2=120; } 
    if(current[1]){ m1-=60; m2+=60; } 
    if(current[3]){ m1+=60; m2-=60; } 
    if(current[2]){ m1=0; m2=0; }
    m1 = Math.max(Math.min(m1,255),0);
    m2 = Math.max(Math.min(m2,255),0);
    sendMotorSignal(m1,m2);
}, 1/5 * 1000);

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
