var socket = io();

$(".actionbutton").each(function(index){
	$(this).click(function(){
		socket.emit('binaryaction',$(this).attr('id'));
	});
});

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
