
var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);
var port = process.env.PORT || 5000




//Because Heroku doesn't like websockets?
//https://github.com/nodejs/node/wiki/Socket.IO-and-Heroku
// io.set('transports', ['xhr-polling']);
// io.set('polling duration', 10);



//Backup plan: HTTP Requests
app.get("/devices/:deviceData", function(req, res){
	
	var num = req.params.deviceData;

	console.log("Received Device Request. We get this: " + num)

	res.send("7");

});



app.get('/', function(req, res){
  res.sendfile('index.html');
});

app.get('/next', function(req, res){
	console.log("Next request, sending")
	res.send("Moving on!");
});

io.on('connection', function(socket){
  console.log('a user connected');
  io.emit("connectionMessage", "Sendthis!");

  socket.on('connection', function (data) {
    	console.log(data);   });
  socket.on('atime', function (data) {
	  	sendTime();
    	console.log(data);
    });
});

http.listen(port, function(){
  console.log('listening on' +  port);
});