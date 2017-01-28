
module.exports = function (x, y, callback){
	try{
		if ( x< 0 || y < 0 ){
			throw new Error("Length and Breadth should be greater thatn zero");
		} else {
			callback(null, {
				Perimeter: function(){
					return (2*(x+y));
				},
				Area: function(){
					return (x*y);
				}
			});
		}
	}
	catch(error){
		callback(error, null);
	}
}