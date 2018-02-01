#!/usr/bin/env python
import serial
from serial import SerialException
import time
from time import sleep

FORWARD = 'Move Forward'
REVESRE = 'Move Back'
LEFT = 'Move Left'
RIGHT = 'Move Right'
STOP = 'Stop'

ONE_REVOLUTION = 16
STEPS_PER_REVOLUTION = 400

#The that will be used to control the stepper motors
nav_arduino = serial.Serial()  
nav_arduino.port = "COM5" 
# nav_arduino.port = "/dev/ttyACM1"
nav_arduino.baudrate = 9600

#distance -> cm
def number_of_steps(distance):
    return distance / ONE_REVOLUTION * STEPS_PER_REVOLUTION 

def get_directions():
    return '111'

def arduino_msg(direction, distance=None):
    if distance is None: 
        if direction == LEFT or direction == RIGHT:
            #Add the number of steps it takes to turn 90 degrees
            return direction + ',' + str(number_of_steps(0))
        return direction
    return direction + ',' + str(number_of_steps(distance))

def main():
    order = []
    directions = list(get_directions())
    
    try:   
        nav_arduino.open()
        nav_arduino.flushInput() #flush input buffer, discarding all its contents
        ############
        # Direction to A
        ############
        if directions[0] == '1':
            order.extend([{'direction': FORWARD, 'distance': 23},
                          {'direction': RIGHT, 'distance': None},
                          {'direction': FORWARD, 'distance': 37},
                          {'direction': STOP, 'distance': None}])
        else:
            order.extend([{'direction': FORWARD, 'distance': 23},
                          {'direction': LEFT, 'distance': None},
                          {'direction': FORWARD, 'distance': 37},
                          {'direction': STOP, 'distance': None}])

        ############
        # Direction to B
        ############
        if directions[1] == '1':
            order.extend([{'direction': LEFT, 'distance': None},
                          {'direction': LEFT, 'distance': None},
                          {'direction': FORWARD, 'distance': 37},
                          {'direction': RIGHT, 'distance': None},
                          {'direction': FORWARD, 'distance': 163},
                          {'direction': RIGHT, 'distance': None},
                          {'direction': LEFT, 'distance': None},
                          {'direction': LEFT, 'distance': None},
                          {'direction': FORWARD, 'distance': 37},
                          {'direction': STOP, 'distance': None}])
        else:
            order.extend([{'direction': RIGHT, 'distance': None},
                          {'direction': RIGHT, 'distance': None},
                          {'direction': FORWARD, 'distance': 37},
                          {'direction': RIGHT, 'distance': None},
                          {'direction': FORWARD, 'distance': 163},
                          {'direction': LEFT, 'distance': None},
                          {'direction': RIGHT, 'distance': None},
                          {'direction': RIGHT, 'distance': None},
                          {'direction': FORWARD, 'distance': 37},
                          {'direction': STOP, 'distance': None}])

        ############
        # Direction to C
        ############
        if directions[2] == '1':
            order.extend([{'direction': LEFT, 'distance': None},
                          {'direction': LEFT, 'distance': None},
                          {'direction': FORWARD, 'distance': 37},
                          {'direction': RIGHT, 'distance': None},
                          {'direction': FORWARD, 'distance': 163},
                          {'direction': RIGHT, 'distance': None},
                          {'direction': LEFT, 'distance': None},
                          {'direction': LEFT, 'distance': None},
                          {'direction': FORWARD, 'distance': 37},
                          {'direction': STOP, 'distance': None}])       
        else:
            order.extend([{'direction': RIGHT, 'distance': None},
                          {'direction': RIGHT, 'distance': None},
                          {'direction': FORWARD, 'distance': 37},
                          {'direction': RIGHT, 'distance': None},
                          {'direction': FORWARD, 'distance': 163},
                          {'direction': LEFT, 'distance': None},
                          {'direction': RIGHT, 'distance': None},
                          {'direction': RIGHT, 'distance': None},
                          {'direction': FORWARD, 'distance': 37},
                          {'direction': STOP, 'distance': None}])

        for o in order:
            # sleep(2)           
            nav_arduino.write(arduino_msg(o['direction'], o['distance']).encode())
            # sleep(2)
            print(arduino_msg(o['direction'], o['distance']))
            # nav_arduino.flushInput() #flush input buffer, discarding all its contents
            #nav_arduino.flushOutput()#flush output buffer, aborting current output
            while str(nav_arduino.read()) == 'Z':
                break


        nav_arduino.flushOutput()#flush output buffer, aborting current output
        nav_arduino.close()
    except SerialException as e:
        print((e))

if __name__ == '__main__':
    main()