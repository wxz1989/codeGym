import RPi.GPIO as GPIO
import time

LDR_INPUT = 18
LDR_OUTPUT = 4

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

GPIO.setup(LDR_INPUT, GPIO.IN)
GPIO.setup(LDR_OUTPUT, GPIO.OUT)
GPIO.output(LDR_OUTPUT, GPIO.LOW)
#counter  = 0

try :
	while True:
		light = GPIO.input(LDR_INPUT)
#		counter +=1
		#print "Light intensity is: " , light
		if light == 1:
			print "Good Night"
			GPIO.output(LDR_OUTPUT, GPIO.HIGH)
			time.sleep(5)
		else:
#			counter += 1 
			print "Good Day!"
			GPIO.output(LDR_OUTPUT, GPIO.LOW)
			time.sleep(5)
except KeyboardInterrupt:
	print "Terminated by user"
	GPIO.cleanup()
