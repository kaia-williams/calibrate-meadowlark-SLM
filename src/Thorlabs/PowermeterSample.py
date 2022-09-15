from datetime import datetime
from ctypes import (
    c_uint32,
    byref,
    create_string_buffer,
    c_bool,
    c_char_p,
    c_int,
    c_double,
)
from TLPM import TLPM
import time

# type: ignore
# flake8: noqa

tlPM = TLPM()
deviceCount = c_uint32()
tlPM.findRsrc(byref(deviceCount))

print("devices found: " + str(deviceCount.value))

resourceName = create_string_buffer(1024)

for i in range(0, deviceCount.value):
    tlPM.getRsrcName(c_int(i), resourceName)
    print(c_char_p(resourceName.raw).value)
    break

tlPM.close()

tlPM = TLPM()
# resourceName = create_string_buffer(b"COM1::115200")
# print(c_char_p(resourceName.raw).value)
tlPM.open(resourceName, c_bool(True), c_bool(True))

message = create_string_buffer(1024)
tlPM.getCalibrationMsg(message)
print(c_char_p(message.raw).value)

time.sleep(5)

power_measurements = []
times = []
count = 0
while count < 20:
    power = c_double()
    tlPM.measPower(byref(power))
    power_measurements.append(power.value)
    times.append(datetime.now())
    print(power.value)
    count += 1
    time.sleep(1)

tlPM.close()
print("End program")
