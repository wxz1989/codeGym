Init()
{
	echo -e "Hey Gorgeous!!!...how are you today??? Hope you are great as usuual and full of life with loads of smiles :) Be calm and have patience i will be with you shortly"
	sleep 5s
	echo -e "Hey...I am back...with a small a questionare for you. Are you game for it???"
	StartQuestionare
}
StartQuestionare()
{
	sleep 3s
	echo -e "Enter your choise (y/n):"
	read command
	echo -e "Your options [$command]"
	echo -e "Processing...,this may take a while"
	sleep 5s
	echo -e "Hold on...doing last minute touchups... be there with me :)"
	sleep 3s
	if [ "$command" == "y" || "$command" == "Y"]; 
	then
		start
	else
		stop
	fi
}

ShowProcessing()
{
	echo -e "Param #1 is $1"
}
start()
{
   echo -e "You choose the best options, welcome onboard :)"
   echo  -e "Loading data...give me a moment `sleep 5s` \npersonify engine is trying to understand your character... 'sleep 5s`"
  echo -e "awww... our servers are sayign that you are in in love..."   
echo -e "I envy you...`sleep 3s` \nSo lucky you are... `sleep 3s` \nSo who is the guy???"
	
   echo -e "Name first letter of the person you love"
   read lou
	if [ $low == "Rakesh" || $lou == "rakesh"];
	then
		echo -e "Our servers suggested the same name...you are in heaven now...!!!"
	else
		echo -e "INCORRECT...`sleep 3s` \nSystem says that your love interest has name starting with R `sleep 3s` \nReinitiating the process"
		StartQuestionare		
   echo $lou > ~/Downloads/rakesh.txt
   echo -e "just aa few words why do you like him"
   read reasons
   echo $reasons > ~/Downloads/reasons.txt
   echo -e "Would like you spend the rest of your life with him(y/n)???"
   read answer
   echo $answer > ~/Downloads/answer.txt

   if [ "$answer" == "y" ];
   then
	echo -e "Bravo~~~he would make you happy,  be happier"
   else
	echo -e "Seriously???, do you need more time to think???"
	echo -e "Take all the time you need, but say YES"
	Init
   fi
}
stop()
{
   echo -e "Sad that you have choosen this, best wishes for your future. Do well!! :( "
}

echo -e “Welcome~~~, utilize this opportunity well!!!”
Init
