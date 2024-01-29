import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)
#use pin 3,5 to connect to leds

GPIO.setup(3,GPIO.OUT)
GPIO.setup(5,GPIO.OUT)


GPIO.output(3,True)
time.sleep(2)
GPIO.output(3,False)
time.sleep(2)
GPIO.output(5,True)
time.sleep(2)
GPIO.output(5,False)
GPIO.cleanup()
