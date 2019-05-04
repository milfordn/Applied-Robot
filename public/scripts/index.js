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
    motorAmp : 2,
});
var lastm1 = 0;
var lastm2 = 0;
setInterval(function(){
    var m1 = joystick.motorLeft();
	var m2 = joystick.motorRight();
	if(m1!=lastm1 || m2!=lastm2){
		lastm1=m1;
		lastm2=m2;
		sendMotorSignal(lastm1,lastm2);
	} 
}, 1/30 * 1000);



//------

function sendMotorSignal(left,right){
	//console.log(`L:${left}, R:${right}`);
	var str = `ml${left}r${right}`;
	socket.emit('binaryaction',str)
}

socket.emit('getlatestlog');

socket.on('logmessage',function(message){
	var msgbox = $('#logmessages');
	msgbox.val(msgbox.val() + message);
	if(msgbox.length)
		msgbox.scrollTop(msgbox[0].scrollHeight - msgbox.height());
});
socket.on('ultrasonicstatus',function(sensordata){
	console.log(sensordata);
});
