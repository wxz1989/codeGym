var testCode= 1;
console.log(testCode);

var person = { firstName: "Rakesh", middleName: "D", lastName: "Gajjar"};
console.log(person);

function addValue(a, b){
	return a + b;
}
console.log(addValue(7,3));


var PrintVar = function(){
	console.log("Function Printing");
}

PrintVar();


console.log(typeof "Rakesh");
console.log(typeof 1);
console.log(typeof 3.14);
console.log(typeof 'Gajjar');


var stringOpe = "Con" + "Cat" + "a" + "nate";

console.log(stringOpe);

SetCallback(function(){
	console.log("Anonymous Function Writtenn for Doing Junk Work");
});

var arrayOfInt = [1, 2, 3, 4, 5];

console.log(arrayOfInt);
console.log(arrayOfInt[2]);
console.log(arrayOfInt[1]);
console.log(arrayOfInt[3]);


console.log("Array of Length:" + arrayOfInt.length);
console.log("Array of Size:" + arrayOfInt.size);


function TEST(){
	console.log("This is going to be a TEST function");
}

TEST();


var test ="test";
console.log(typeof test);
console.log(typeof test.toUpperCase());
console.log(typeof test.toLowerCase());

console.log(test.toUpperCase());
console.log(test.toLowerCase());



function SetCallback(cb){
	var callback = cb;

	callback();
}



var EmpltyVariale = [] ;

EmpltyVariale.push("Rakesh");
EmpltyVariale.push("D");
EmpltyVariale.push("Gajjar");


EmpltyVariale.push("Swara");
EmpltyVariale.push("Rakesh");
EmpltyVariale.push("Gajjar");


console.log(EmpltyVariale);
console.log(EmpltyVariale.join());
console.log(EmpltyVariale.join(""));


var StringMap= {};

StringMap["Rakesh"] = "Samsung";
StringMap["Swara"] = "USA";

StringMap["Pradip"] = "Apple";
StringMap["Chitta"] = "Oracle";


console.log("Rakesh" in StringMap);
console.log(StringMap["Pradip"]);
