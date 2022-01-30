#This code is used to calibrate the 3d model of the sensor
from curses import baudrate
import serial

serial_port = serial.Serial(port = "COM3", baudrate = 9600, bytesize = 8, timeout = 2, stopbits = serial.STOPBITS_ONE)

serial_string = ""
while(True):
    #Wait until there is data in the serial buffer
    if(serial_port.in_waiting > 0):
        #Read data in the buffer until \n
        serial_string = serial_port.readline()
        #Print data
        print(serial_string)

