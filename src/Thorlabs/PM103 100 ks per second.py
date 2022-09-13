from datetime import datetime
from ctypes import cdll,c_long, c_ulong, c_uint16, c_uint32,byref,create_string_buffer,c_bool,c_char_p,c_int,c_int16,c_double,c_float, sizeof, c_voidp
from TLPM import TLPM
import time
import csv


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
#resourceName = create_string_buffer(b"COM1::115200")
#print(c_char_p(resourceName.raw).value)
tlPM.open(resourceName, c_bool(True), c_bool(False))
 
time.sleep(1)

tlPM.resetFastArrayMeasurement()

tlPM.confCurrentFastArrayMeasurement()
 
dataSize = 200 
timeStamps = (c_uint32 * dataSize)()
data = (c_float * dataSize)()

returnSize = c_uint16(0)
tlPM.getNextFastArrayMeasurement(byref(returnSize), timeStamps, data)

with open("CurrentData.csv", "w") as txt_file:
	for i in range(returnSize.value):
		txt_file.write(str(timeStamps[i]) + ";" + "{:.5e}".format(data[i]) + "\n")
 
tlPM.close()
print('End program')
