#code to delete folders containing no files...


if [ ! -d "$1" ]
then
	echo "Directory doesn not exist"
	exit 1
fi

input="yes"
var=-1
dirCount=-1

#important line which pull the no of files and folders in a given folder...
#dirCount=$(ls -lR "$1" | grep ^d | wc -l)
dirCount=$(find "$1" -type d -maxdepth 1 | wc -l)
(( dirCount-- ))
var=$(ls -F "$1" | grep -v / | wc -l)
echo "Directory count is [$dirCount]"
echo "File count in" "$1" "is [$var]"
var=$(( $dirCount + $var ))
echo "Total files/folder count in" "$1" "is [$var]"

if [ $var -ge 1 ]
then
	echo "Delete all this file/folders?"
	read input
	if [ "$input" == "yes" -o "$input" == "y" ]
	then
		echo "Files/Folders are there and you choose to delete it, sure about it???"
		confirm="no"
		read confirm
		if [ "$confirm" == "yes" -o "$confirm" == "y" ]
		then
			rm -rf "$1"
		else
			echo "$1" "has files and it's not deleted!!!"
		fi
	else
		echo "Not to deleting this folder/files"
	fi
else
	echo "No files found in this folder...deleting it...is that okay???"
	read input
	if [ "$input" == "yes" -o "$input" == "y" ]
	then
		rm -rf "$1"
	else
		echo "Not to deleting this folder/file"
	fi
fi

echo "Completed!!!"
