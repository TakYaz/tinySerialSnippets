import serial
import random
import time

DEVICE_NAME = "/dev/tty.usbmodem1411"
BAUDRATE_FOR_DEVICE = 115200
HEADER = "H"

def wait_for_message(ser):
    """
    so ugly code.
    I should change to use async/await as soon as possible.
    """
    while ser.in_waiting < 1:
        time.sleep(1) # so ugly! should use async/await
        print("wait for a message")

def get_int_from_serial(bit_num):
    ser = serial.Serial(DEVICE_NAME, BAUDRATE_FOR_DEVICE)
    time.sleep(7); # so ugly! wait to connect

    # variables
    checker = random.randint(0, 2**bit_num - 1)
    upper_checker = 2**bit_num
    checker_message = HEADER + str(checker) + ","
    upper_checker_message = HEADER + str(upper_checker) + ","

    # test commoncase
    # Arduino will return the dicimal number in the message
    ser.write(checker_message.encode(encoding='utf_8'))
    ser.flushOutput()
    wait_for_message(ser)
    ret = ser.readline()
    print(checker_message, "->", ret)
    assert ret == (str(checker) + "\r\n").encode(encoding='utf_8'), \
        "error: commoncase"

    # test edgecase
    # int overflow will occur
    ser.write(upper_checker_message.encode(encoding='utf_8'))
    ser.flushOutput()
    wait_for_message(ser)
    ret = ser.readline()
    print(upper_checker_message, "->", ret)
    assert ret != (str(checker) + "\r\n").encode(encoding='utf_8'), \
        "error: edgecase (with too long message, \
        I expect Arduino serial buffer overflow)"

    ser.close()

if __name__ == '__main__':
    get_int_from_serial(16)
