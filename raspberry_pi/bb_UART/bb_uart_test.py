import pigpio

pi = pigpio.pi()
try:
    pi.bb_serial_read_close(17)
    status = pi.bb_serial_read_open(17, 9600)
    while True:
        count = 1
        text = ""
        while count:
            count, data = pi.bb_serial_read(17)
            if count:
                text += data
            time.sleep(0.01)
        print(text)

finally:
    pi.bb_serial_read_close(17)
