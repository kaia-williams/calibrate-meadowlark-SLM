from ..Thorlabs.TLPM import TLPM
from ctypes import c_uint32, byref, create_string_buffer, c_bool, c_char_p, c_int
from time import sleep


def find_power_meter(logging: bool = False) -> TLPM:
    # finds all connected power meters and returns an instance of TLPM
    # corresponding to the first one

    # this code is more or less copied from the Power Meter Write Read Raw.py file in the /Thorlabs directory
    device_PowerMeter_static = TLPM()
    deviceCount = c_uint32()
    device_PowerMeter_static.findRsrc(byref(deviceCount))

    if logging:
        print("devices found: " + str(deviceCount.value))

    resourceName = create_string_buffer(1024)

    for i in range(0, deviceCount.value):
        device_PowerMeter_static.getRsrcName(c_int(i), resourceName)
        print(c_char_p(resourceName.raw).value)
        break

    device_PowerMeter_static.close()

    device_PowerMeter_main = TLPM()
    # resourceName = create_string_buffer(b"COM1::115200")
    # print(c_char_p(resourceName.raw).value)
    device_PowerMeter_main.open(resourceName, c_bool(True), c_bool(False))

    sleep(1)

    return device_PowerMeter_main
