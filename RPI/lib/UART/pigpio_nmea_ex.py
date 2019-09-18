#!/usr/bin/python
import sys
import time
import difflib
import pigpio
RX=18
RX1=23
try:
    pi = pigpio.pi()
    pi.set_mode(RX, pigpio.INPUT)
    pi.bb_serial_read_open(RX, 9600, 8)
    pi.bb_serial_read_open(RX1, 9600,8)
    print "DATA - SOFTWARE SERIAL:"
    while 1:
      (count, data) = pi.bb_serial_read(RX)
      if count:
        print data
      (count,data) = pi.bb_serial_read(RX1)
      if count:
        print data
      time.sleep(1)
except:
    pi.bb_serial_read_close(RX)
    pi.bb_serial_read_close(RX1)
    pi.stop()
