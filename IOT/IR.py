import RPi.GPIO as GPIO
GPIO.setmode(GPIO.BOARD)

GPIO.setup(5,GPIO.IN)
GPIO.setup(12,GPIO.OUT)
# pin 5 is connected to ir sensor output and pin 12 is connected to led

while True:
    var = GPIO.input(5)
    print(var)
    
    if(var==1):
        GPIO.output(12,True)
    else:
        GPIO.output(12,False)
GPIO.cleanup()    
