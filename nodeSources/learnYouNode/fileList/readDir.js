#!/usr/local/bin/ node 

var fs = require('fs')
var path = require('path')
/*function declaration of a Displaying Utitlity
var DisplayContent = function (message){ console.log("File Listing utility:" + message)}
*/
/*Function declaration of a fileListing utitliy*/
var fileList = function (dirPath, extention){
  if ( dirPath == null ){
    if (process.argv[2] == null ) { return }
    dirPath = process.argv[2]
  }
  if ( extention == null ){
    if( process.argv[3] == null ){ return }
    extention = process.argv[3]
  }

  fs.readdir(dirPath, function(err, fileList){
    if(err){ console.log(err)}
    else{
      for (index in fileList) {
          var extName = path.extname(fileList[index])
          var indexOf = extName.lastIndexOf('.')
          if ( (extName.slice(indexOf+1, extName.length)) == extention){ console.log(fileList[index]) }
      }
    }
  })
}
//module.exports.Display=DisplayContent
module.exports.list=fileList

fileList(process.argv[2], process.argv[3])
