var http = require('http');
var port = 8080;
var hostName = "localhost";

function handleRequest(request, response){
	console.log(request.headers);
	response.writeHead(200, {'Content-Type': 'text/html'});
	response.end("<h1>Hello World!</h1>");
}

var server = http.createServer(handleRequest);
server.listen(port, hostName, function(){  
	console.log('Server running at http://${hostName}:${port}/'); 
})
