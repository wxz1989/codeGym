var http = require('http');
var fileSystem = require('fs');

console.log(fileSystem.readFileSync('request_table.js').length);

var POSTOption = {
  hostname: 'localhost',
  port: 8080,
  path: '/uploadProfilePicture',
  method: 'POST'
};


var GETOption = {
  hostname: 'localhost',
  port: 8080,
  path: '/getTimelineDetails',
  method: 'GET'
};

var req = http.request(GETOption, function(res) {
  console.log('STATUS: ' + res.statusCode);
  console.log('HEADERS: ' + JSON.stringify(res.headers));
  res.setEncoding('utf8');
  res.on('data', function (chunk) {
    console.log('BODY: ' + chunk);
  });
});

req.on('error', function(e) {
  console.log('problem with request: ' + e.message);
});

// write data to request body
req.write('data\n');
req.write('data\n');
req.end();