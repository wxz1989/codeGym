import RPi.GPIO as GPIO
import time

PIR_INPUT = 4
PIR_OUTPUT = 23

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

GPIO.setup(PIR_INPUT, GPIO.IN)
GPIO.setup(PIR_OUTPUT, GPIO.OUT)

GPIO.output(PIR_OUTPUT, GPIO.LOW)

try :
	while True:
		detected = GPIO.input(PIR_INPUT)
		if detected==1:
			print "Motion Detected"
			GPIO.output(PIR_OUTPUT, GPIO.HIGH)
			time.sleep(0.1)
		else:
			print "Nothing"
			GPIO.output(PIR_OUTPUT, GPIO.LOW)
			time.sleep(0.1)
except KeyboardInterrupt:
	print "Terminated by user"
	GPIO.cleanup()
