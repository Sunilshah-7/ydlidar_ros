import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BCM)
GPIO.setup(8,GPIO.OUT,initial=GPIO.LOW)
if(True):
    GPIO.output(8,GPIO.LOW)
else:
    GPIO.output(8,GPIO.HIGH)
