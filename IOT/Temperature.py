import Adafruit_DHT
import RPi.GPIO as GPIO

GPIO.setmode (GPIO.BCM)
#Using BCM means use GPIO3 Pin to cennect to sensor

while(True):
    humidity,temperature = Adafruit_DHT.read_retry(Adafruit_DHT.DHT11,3)
    print(humidity,temperature)
GPIO.cleanup()   
