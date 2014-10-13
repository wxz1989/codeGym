#code to delete folders containing no files...

input="yes"
var=-1

#important line which pull the no of files and folders in a given folder...
var=$(ls -F $1 | grep -v / | wc -l)	

echo "File count in" $1 "is [" $var "]"

if [ $var -ge 1 ]
then
	echo "Do you want to delete all this file?"
	read input
	if [ "$input" == "yes" -o "$input" == "y" ]
	then
		echo "There are files and you choose to delete it, are you sure about it???"
		confirm="no"
		read confirm
		if [ "$confirm" == "yes" -o "$confirm" == "y" ]
		then
			rm -rf $1
		else
			echo "Congratulations..." $1 "has files and it's not deleted!!!"
		fi
	else
		echo "you choose not to delete this folder/files"
	fi
else
	echo "No files found in this folder...deleting it...is that okay???"
	read input
	if [ "$input" == "yes" -o "$input" == "y" ]
	then
		rm -rf $1
	else
		echo "you choose not to delete this folder"
	fi
fi

echo "Operation successfull"