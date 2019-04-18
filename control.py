import serial

ser = serial.Serial('/dev/ttyACM0',115200)

if __name__ == "__main__":
    while(True):
        signal = input('Action: ')
        if(signal == 'f'):
            ser.write(str.encode(signal))
