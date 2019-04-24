import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BCM)

#The set of pins for HC-SR04 sensors. in tuples (trigger,echo)
pinsets = [(23,24)]

for pins in pinsets:
    GPIO.setup(pins[0],GPIO.OUT)
    GPIO.setup(pins[1],GPIO.IN)
print("Ultrasonic active")
try:
    while True:
        output_str = ""
        for pins in pinsets:
            (TRIG,ECHO) = pins
            GPIO.output(TRIG,False)
            time.sleep(.05)

            GPIO.output(TRIG,True)
            time.sleep(0.00001)
            GPIO.output(TRIG,False)

            while(GPIO.input(ECHO) == 0):
                pulse_start = time.time()
            
            while(GPIO.input(ECHO) == 1):
                pulse_end = time.time()

            pulse_dur = pulse_end - pulse_start
            distance = round(pulse_dur*34300/2,1)
            if(not len(output_str) == 0):
                output_str+=','
            output_str+=str(distance)
        print(output_str,flush=True)

except KeyboardInterrupt:
    GPIO.cleanup()
    exit(0)
