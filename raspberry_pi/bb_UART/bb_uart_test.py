import pigpio

pi = pigpio.pi()
try:
    status = pi.bb_serial_read_open(17, 9600)
    while True:
        count, data = pi.bb_serial_read(17)
        print(data, end="")

finally:
    pi.bb_serial_read_close(17)
