import serial
import threading
import time

ser = serial.Serial('/dev/ttyACM0',115200)
ready = False

def get_serial():
    print('Connecting')
    while(True):
        data = ser.readline()
        print('Message: '+data.decode('utf-8'))

def send_serial():
    while(True):

        signal = input('Action: ')
        if(signal.startswith('int')):
            print('Sending int: {}'.format(signal[3:]))
            ser.write(str.encode('i'+signal[3:]))
        else:
            print('Sending {}'.format(signal))
            ser.write(str.encode(signal))

if __name__ == "__main__":
    try:
        read = threading.Thread(target=get_serial)
        read.start()
        write = threading.Thread(target=send_serial)
        write.start()
    except KeyboardInterrupt:
        exit(1)
