import RPi.GPIO as GPIO
import time

LED = 4 
#LED_LOOPBACK = 17
GPIO.setmode(GPIO.BCM)
GPIO.setup(LED, GPIO.OUT)
GPIO.output(LED, False)

#GPIO.setup(LED_LOOPBACK, GPIO.IN)
 
try :
	while True:
		GPIO.output(LED, True)
		#ledState = not GPIO.input(LED_LOOPBACK)	
		time.sleep(1)
		GPIO.output(LED, False)
		time.sleep(1)
except KeyboardInterrupt:
	print "Terminated by user"
	GPIO.cleanup()
