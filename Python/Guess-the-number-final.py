# Testing template for "Guess the number"

###################################################
# Student should add code for "Guess the number" here


# template for "Guess the number" mini-project
# input will come from buttons and an input field
# all output for the game will be printed in the console


import simplegui
import random
import math

comp_guess = 0
player_guess = 0
maxRange = 0
guess_count = 0
allowed_guess = 0
current_game = -1

# helper function to start and restart the game
def new_game():
    # initialize global variables used in your code here
    global player_guess
    global comp_guess
    global player_guess 
    global maxRange
    global allowed_guess
    
    comp_guess = 0
    player_guess = 0
    #maxRange = 0
   
    allowed_guess = int (math.log(maxRange, 2)) + 1
    guessCount = allowed_guess
    
    inputField.set_text("")
    
# define event handlers for control panel
def range100():
    # button that changes the range to [0,100) and starts a new game 
    # remove this when you add your code    
    global maxRange
    global allowed_guess
    global comp_guess
    global guess_count
    global current_game 
    maxRange = 100
    
    current_game = 0
    comp_guess = random.randrange(0, maxRange);
    allowed_guess = int (math.log(maxRange, 2)) + 1
    guess_count = allowed_guess

    print "New game. Range is from 0 to ", str(maxRange)
    print "Number of remaining guesses is ", str(allowed_guess)
    print	""

def range1000():
    # button that changes the range to [0,1000) and starts a new game     
    global maxRange   
    global allowed_guess
    global comp_guess
    global guess_count
    global current_game 
    current_game = 1
    maxRange = 1000
    
    comp_guess = random.randrange(0, maxRange);
    allowed_guess = int (math.log(maxRange, 2)) + 1
    guess_count = allowed_guess

    print "New game. Range is from 0 to ", str(maxRange)
    print "Number of remaining guesses is ", str(allowed_guess)
    print	""
    
def input_guess(guess):
    # main game logic goes here	
    global guess_count
    global player_guess
    # remove this when you add your code
    
    # check if the given input guess is withing the specified rnage limit, 
    # else show and error message
    if ( int(guess) >=0 and int(guess)< maxRange):
        player_guess = int(guess)
    else:
        print "Guess out of range"
        player_guess = -1

    print "Guess was", str(player_guess) 

    if ( guess_count > 0 ):
        guess_count -= 1
        print "Number of remaining guesses is ", str(guess_count)
    else:
        print "You ran out of guesses.  The number was ", str(comp_guess) 
        print "" 
        new_game()
        if ( current_game == 0):
            range100()
        else:
            range1000()
            
    if ( player_guess < comp_guess):
        print "Higher!"
    elif (player_guess == comp_guess):
        print "Correct!"
        new_game()
        print "" 
        if ( current_game == 0):
            range100()
        else:
            range1000()
    else:
        print "Lower!"

# create frame
frame = simplegui.create_frame("Guess the number!", 200, 200)
# register event handlers for control elements and start frame
buttonRange1 = frame.add_button("Range is [0, 100)", range100 ,200)
buttonRange2 =frame.add_button("Range is [0, 1000)", range1000 ,200)
inputField = frame.add_input("Enter a guess:", input_guess, 200)

frame.start()

# call new_game 
new_game()

"""
###################################################
# Start our test #1 - assume global variable secret_number
# is the the "secret number" - change name if necessary


secret_number = 74	
input_guess("50")
input_guess("75")
input_guess("62")
input_guess("68")
input_guess("71")
input_guess("73")
input_guess("74")

###################################################
# Output from test #1
#New game. Range is from 0 to 100
#Number of remaining guesses is 7
#
#Guess was 50
#Number of remaining guesses is 6
#Higher!
#
#Guess was 75
#Number of remaining guesses is 5
#Lower!
#
#Guess was 62
#Number of remaining guesses is 4
#Higher!
#
#Guess was 68
#Number of remaining guesses is 3
#Higher!
#
#Guess was 71
#Number of remaining guesses is 2
#Higher!
#
#Guess was 73
#Number of remaining guesses is 1
#Higher!
#
#Guess was 74
#Number of remaining guesses is 0
#Correct!
#
#New game. Range is from 0 to 100
#Number of remaining guesses is 7

###################################################
# Start our test #2 - assume global variable secret_number
# is the the "secret number" - change name if necessary

#range1000()
#secret_number = 375	
#input_guess("500")
#input_guess("250")
#input_guess("375")

###################################################
# Output from test #2
#New game. Range is from 0 to 100
#Number of remaining guesses is 7
#
#New game. Range is from 0 to 1000
#Number of remaining guesses is 10
#
#Guess was 500
#Number of remaining guesses is 9
#Lower!
#
#Guess was 250
#Number of remaining guesses is 8
#Higher!
#
#Guess was 375
#Number of remaining guesses is 7
#Correct!
#
#New game. Range is from 0 to 1000
#Number of remaining guesses is 10



###################################################
# Start our test #3 - assume global variable secret_number
# is the the "secret number" - change name if necessary

#secret_number = 28	
#input_guess("50")
#input_guess("50")
#input_guess("50")
#input_guess("50")
#input_guess("50")
#input_guess("50")
#input_guess("50")

###################################################
# Output from test #3
#New game. Range is from 0 to 100
#Number of remaining guesses is 7
#
#Guess was 50
#Number of remaining guesses is 6
#Lower!
#
#Guess was 50
#Number of remaining guesses is 5
#Lower!
#
#Guess was 50
#Number of remaining guesses is 4
#Lower!
#
#Guess was 50
#Number of remaining guesses is 3
#Lower!
#
#Guess was 50
#Number of remaining guesses is 2
#Lower!
#
#Guess was 50
#Number of remaining guesses is 1
#Lower!
#
#Guess was 50
#Number of remaining guesses is 0
#You ran out of guesses.  The number was 28
#
#New game. Range is from 0 to 100
#Number of remaining guesses is 7
"""