var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);
var path = require('path');
 
// Initialize appication with route / (that means root of the application)
app.get('/', function(req, res){
  console.log("get event called");
  var express=require('express');
  app.use(express.static(path.join(__dirname)));
  res.sendFile(path.join(__dirname, '/ChatApplication', 'index.html'));
});
 
// Register events on socket connection
io.on('connection', function(socket){
  console.log("connection event called");
  socket.on('chatMessage', function(from, msg){
    console.log("chatMessage event received");
    io.emit('chatMessage', from, msg);
  });
  socket.on('notifyUser', function(user){
    console.log("notify event called");
    io.emit('notifyUser', user);
  });
});
 
// Listen application request on port 3000
http.listen(3000, function(){
  console.log("listen event received");
  console.log('listening on *:3000');
});