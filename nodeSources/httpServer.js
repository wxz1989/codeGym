var http = require('http');
const PORT = 8080;


function handleRequest(request, response){
	response.writeHead(200, {'Content-Type': 'text/plain'});
	console.log("Request Headers:"+request.headers);
	console.log("Request httpVersion:"+request.httpVersion );
	console.log("Request Method:"+request.method );
	console.log("Request RawHeaders:"+request.rawHeaders);
	console.log("Request rawTailers:"+request.rawTrailers);
	console.log("Request StatusCode:"+request.statusCode);
	console.log("Request statusMessage:" +request.statusMessage );
	console.log("Request Socket:"+request.socket);
	console.log("Request tailers:"+ request.trailers);
	console.log("Request URL:"+ request.url);

	response.end("Server is up and running [ "+ request.url + " ]");
}

var server = http.createServer(handleRequest);
server.listen(PORT, function(){  console.log("Server is listening on http://localhost:" +  PORT ); })
