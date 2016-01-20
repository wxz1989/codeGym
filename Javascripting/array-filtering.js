var numbers  = [1,2,3,4,5,6,7,8,9,10];
var filtered = numbers.filter(function evenNumbers(number){
	console.log("Filter number: "+number);
	if( number % 2 == 0 ) {
		console.log("Even Number");
		return 0;
	} else {
		console.log("Odd Number");
		return 1;
	}
});
console.log(filtered);


