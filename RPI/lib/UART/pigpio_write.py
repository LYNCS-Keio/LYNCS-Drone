#!/usr/bin/python
import sys
import time
import difflib
import pigpio
TX0=18
try:
    pi = pigpio.pi()
    pi.set_mode(TX0, pigpio.OUTPUT)
    pi.set_mode(TX1, pigpio.OUTPUT)
    h1 = pi.serial_open("/dev/ttyS0", 9600)
    print "DATA - SOFTWARE SERIAL:"
    while 1:
      pi.serial_write(h1,"hello")
      time.sleep(1)
except:
    pi.serial_close(TX0)
    pi.stop()
