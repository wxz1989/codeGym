var http = require ('http');
var exp = require('express');

var hostName = "localHost";
var portNo = 3000;


var app = exp();

app.use(function(req,res,next){
	console.log(req);

	res.writeHead(200, {'Content-Type': 'text/html'});
	res.end("<html><body><h1>Hello JS World!</h1></body></html>");
});

var server = http.createServer(app);
server.listen(portNo, hostName, function(){  
	console.log('Server running at http://${hostName}:${port}/'); 
})

