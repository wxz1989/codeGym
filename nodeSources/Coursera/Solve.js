var argv = require("yargs")
	.usage('Usage: node $0 --l=num --b=num')
    .demand(['l','b'])
    .argv;


var rectModule = require("./rec.js")


function SolveRect(l, b){
	rectModule(l, b, function (error, rectObj){
		if ( error){
			console.log(error);
		} else{
			console.log("Rectangle Perimeter:" + rectObj.Perimeter() + " and Area:"  + rectObj.Area());
		}
	})
}


SolveRect(argv.l,argv.b);