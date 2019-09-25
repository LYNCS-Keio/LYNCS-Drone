import pigpio

pi = pigpio.pi()
try:
    pi.bb_serial_read_close(17)
    status = pi.bb_serial_read_open(17, 9600)
    while True:
        count, data = pi.bb_serial_read(17)
        while count:
            print(data)

finally:
    pi.bb_serial_read_close(17)
