import serial
import random
import time

DEVICE_NAME = "/dev/tty.usbmodem1411"
BAUDRATE_FOR_DEVICE = 115200
HEADER = "H"

def get_int_from_serial():
    ser = serial.Serial(DEVICE_NAME, BAUDRATE_FOR_DEVICE)
    checker = random.randint(0, 10**64 - 1)
    upper_checker = 10**64
    checker_message = HEADER + str(checker) + ","
    upper_checker_message = HEADER + str(upper_checker) + ","
    ser.write(checker_message.encode(encoding='utf_8'))
    time.sleep(1)
    ret = ser.readline()
    print(checker_message, "->", ret)
    assert ret == (str(checker) + "\r\n").encode(encoding='utf_8'), \
        "error: commoncase"
    ser.write(upper_checker_message.encode(encoding='utf_8'))
    time.sleep(1)
    ret = ser.readline()
    print(upper_checker_message, "->", ret)
    assert ret != (str(checker) + "\r\n").encode(encoding='utf_8'), \
        "error: edgecase (with too long message, \
        I expect Arduino serial buffer overflow)"
    ser.close()

if __name__ == '__main__':
    get_int_from_serial()
