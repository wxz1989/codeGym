
var network = require('net');
const PORT  = 4000;

var chatServer = network.createServer();

console.log("*****!Chat Server Started!*****");

//list of clients whom server is going to maintain.


chatServer.on('connection', function(client){
	var clientList = [];
	var clientName = client.remoteAddress + ":"  + client.remotePort ;
	console.log(clientName + " connected!");

	client.write("Hi " +clientName);

	clientList.push(client);

	//Once client is connected, go ahead listen for the data.
	client.on('data', function(data){
		console.log(clientName + ":["  + data + "]");
	})

	//Once client is terminated, send cilent a termination message.
	client.on('end', function(){
		console.log(clientName + " terminated!");
		client.end("bbye!!!");
	})
})
chatServer.listen(PORT);
