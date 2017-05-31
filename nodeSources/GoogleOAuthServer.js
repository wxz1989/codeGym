var http = require('http');
var express = require('express');
var Session = require('express-session');
var google = require('googleapis');
//var opn = require('opn');
var openUrl = require('openurl');

var plus = google.plus('v1');
var OAuth2 = google.auth.OAuth2;


const ClientId = "947156970260-36nhr0l2nbvlbl723m5ehjolubi9vnub.apps.googleusercontent.com";
const ClientSecret = "S0c4a5YlTENZvHtLrUqO7iCo";
const RedirectionUrl = "http://localhost:8080/oauthCallback";

var weekday = new Array(7);
weekday[0] =  "Sunday";
weekday[1] = "Monday";
weekday[2] = "Tuesday";
weekday[3] = "Wednesday";
weekday[4] = "Thursday";
weekday[5] = "Friday";
weekday[6] = "Saturday";

function getDaysBetweenDates(d0, d1) {

  var msPerDay = 8.64e7;

  // Copy dates so don't mess them up
  var x0 = new Date(d0);
  var x1 = new Date(d1);

  // Set to noon - avoid DST errors
  x0.setHours(12,0,0);
  x1.setHours(12,0,0);

  // Round to remove daylight saving errors
  return Math.round( (x1 - x0) / msPerDay );
}

var app = express();
app.use(Session({
	secret: 'rakesh-secret-19830622226',
	resave: true,
	saveUninitialized: true
}));

function getOAuthClient () {
	return new OAuth2(ClientId ,  ClientSecret, RedirectionUrl);
}

function getAuthUrl () {
	var oauth2Client = getOAuthClient();
	// generate a url that asks permissions for Google+ and Google Calendar scopes
	var scopes = [
	'https://www.googleapis.com/auth/plus.me',
	'https://www.googleapis.com/auth/calendar',
	'https://www.googleapis.com/auth/calendar.readonly'
	];

	var url = oauth2Client.generateAuthUrl({
		access_type: 'offline',
		scope: scopes // If you only need one scope you can pass it as string
	});

	return url;
}

app.use("/oauthCallback", function (req, res) {
	var oauth2Client = getOAuthClient();
	var session = req.session;
	var code = req.query.code;
	oauth2Client.getToken(code, function(err, tokens) {
	  // Now tokens contains an access_token and an optional refresh_token. Save them.
	  if(!err) {
	  	oauth2Client.setCredentials(tokens);
	  	session["tokens"]=tokens;
	  	res.send("Login successful!!" + "Token:[" + JSON.stringify(tokens) + "]"+ " Sessions:[" + JSON.stringify(session) + "]");
		//&lt;a href="/details"&gt;Go to details page&lt;/a&gt;      

		//console.log("Tokens Sending to list Function:" + JSON.stringify(session["tokens"]));
		listEvents(oauth2Client);
	}
	else{
		res.send("Login failed!");
		return;
	}

});

	//console.log("*************Saved Token:" + "Session:" + JSON.stringify(session) +  "Strigified Tokens:[" + JSON.stringify(session["tokens"]) + "] **********************");
	//listEvents(session["tokens"]);
});

app.use("/details", function (req, res) {
	var oauth2Client = getOAuthClient();
	oauth2Client.setCredentials(req.session["tokens"]);

	var p = new Promise(function (resolve, reject) {
		plus.people.get({ userId: 'me', auth: oauth2Client }, function(err, response) {
			resolve(response || err);
		});
	}).then(function (data) {
		/*res.send(`
			&lt;img src=${data.image.url} /&gt;
			&lt;h3&gt;Hello ${data.displayName}&lt;/h3&gt;
			`);*/
		console.log("Hello " + data.displayName);
		})
});

app.use("/", function (req, res) {
	var url = getAuthUrl();
	res.send("Authentication using google oAuth!" + "URL:[" + url + "]");
	openUrl.open(url);
	//opn(url, {app:'chrome'});
	//window.open(url,'mywindow','width=400,height=200')
});

function listEvents(auth) {
	var calendar = google.calendar('v3');
	/*
	calendar.calendars.get({
		auth: auth,
		calendarId: 'en-gb.indian%23holiday%40group.v.calendar.google.com',
		//timeMin: (new Date("2017-01-01")).toISOString(),
		//timeMax: (new Date("2017-12-31")).toISOString(),
		//maxResults: 10,
		//singleEvents: true,
		//orderBy: 'startTime'
	}, function(err, response) {
		console.log("Function calledback");
		if (err) {
			console.log('The API returned an error: ' + err);
			return;
		}
		console.log(JSON.stringify(response));
	});
	*/
	calendar.events.list({
		auth: auth,
		calendarId: 'en-gb.indian%23holiday%40group.v.calendar.google.com',
		timeMin: (new Date("2017-01-01")).toISOString(),
		timeMax: (new Date("2017-12-31")).toISOString(),
		//maxResults: 10,
		//singleEvents: true,
		//orderBy: 'startTime'
	}, function(err, response) {
		if (err) {
			console.log('The API returned an error: ' + err);
			return;
		}
		var start;
		var prev;
		var events = response.items;
		if (events.length == 0) {
			console.log('No Holidays found.');
		} else {
			console.log("Upcoming [" +  events.length + "] Holidays");
			for (var i = 0; i < events.length; i++) {

				var event = events[i];
				prev = start;
				var start = event.start.dateTime || event.start.date;

				//Check to remove all Sundays and Saturdays for computing leave list
				//if(new Date(start).getDay() == 0 || new Date(start).getDay() == 6 ){
				//	continue;
				//}
				//else
				{ 
					console.log('%s [%s] Diff[%d] - %s', start, weekday[new Date(start).getDay()],getDaysBetweenDates(new Date(prev), new Date(start)), event.summary);				
				}
			}
		}
	});
}


var port = 8080;
var server = http.createServer(app);
server.listen(port);
server.on('listening', function () {
	console.log("listening to "+ port);
});
