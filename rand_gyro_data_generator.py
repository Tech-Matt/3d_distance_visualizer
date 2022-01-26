#This code randomly generate gyroscope x, y, z data 

import serial

serial_port = serial.Serial('/dev/ttyUSB0', 9600) #Opened port at 9600 bd/s
print(serial_port.name)

