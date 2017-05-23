var http = require('http');
var express = require('express');
var Session = require('express-session');
var google = require('googleapis');
var plus = google.plus('v1');
var OAuth2 = google.auth.OAuth2;
const ClientId = "947156970260-36nhr0l2nbvlbl723m5ehjolubi9vnub.apps.googleusercontent.com";
const ClientSecret = "S0c4a5YlTENZvHtLrUqO7iCo";
const RedirectionUrl = "http://localhost:8080/oauthCallback";

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
        }
      else{
        res.send("Login failed!");
      }
    });

    listEvents(session["tokens"]);

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
    })
});

app.use("/", function (req, res) {
    var url = getAuthUrl();
    res.send("Authentication using google oAuth!" + "URL:[" + url + "]");
    //window.open(url,'mywindow','width=400,height=200')
});

function listEvents(auth) {

    console.log("Called Listing Event Functions");
  var calendar = google.calendar('v3');
  calendar.events.list({
    auth: auth,
    calendarId: 'primary',
    timeMin: (new Date()).toISOString(),
    maxResults: 10,
    singleEvents: true,
    orderBy: 'startTime'
  }, function(err, response) {
    if (err) {
      console.log('The API returned an error: ' + err);
      return;
    }
    var events = response.items;
    if (events.length == 0) {
      console.log('No upcoming events found.');
    } else {
      console.log('Upcoming 10 events:');
      for (var i = 0; i < events.length; i++) {
        var event = events[i];
        var start = event.start.dateTime || event.start.date;
        console.log('%s - %s', start, event.summary);
      }
    }
  });

  console.log("Exited Listing Event Functions");
}


var port = 8080;
var server = http.createServer(app);
server.listen(port);
server.on('listening', function () {Exited
    console.log("listening to "+ port);
});
