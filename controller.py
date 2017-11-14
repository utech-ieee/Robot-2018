import serial
import time

serPort = "/dev/ttyACM0"
baudRate = 9600
ser = serial.Serial(serPort, baudRate)
print "Serial port " + serPort + " opened  Baudrate " + str(baudRate)

send = ""

while send != "q":
	send = raw_input("Send to Duino: ")
	ser.write(str(send));

if send == "q":
	ser.close()