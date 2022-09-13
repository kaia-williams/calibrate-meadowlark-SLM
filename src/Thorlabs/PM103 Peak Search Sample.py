from datetime import datetime
from ctypes import cdll,c_long, c_ulong, c_uint32,byref,create_string_buffer,c_bool,c_char_p,c_int,c_int16,c_double, sizeof, c_voidp
from TLPM import TLPM
import time


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

tlPM.setFreqMode(1)

tlPM.writeRaw(c_char_p("ABORT".encode('utf-8')))
tlPM.writeRaw(c_char_p("CONF:CURR".encode('utf-8')))
tlPM.writeRaw(c_char_p("ABORT".encode('utf-8')))
tlPM.writeRaw(c_char_p("INIT".encode('utf-8')))

#Start autoset

tlPM.startPeakDetector()
time.sleep(1)

isRunning = c_bool(True)
while isRunning.value:
	tlPM.isPeakDetectorRunning(byref(isRunning))
 
count = 0
response = create_string_buffer(256)
while count < 10: 
	regValue = c_int16()
	tlPM.readRegister(4, byref(regValue))
	if (regValue.value & 512) != 0:
		tlPM.writeRaw(c_char_p("FETC?".encode('utf-8')))
		retCount = c_uint32()
		tlPM.readRaw(response, 256, byref(retCount))
		print(c_char_p(response.raw).value)
		tlPM.writeRaw(c_char_p("ABORT".encode('utf-8')))
		tlPM.writeRaw(c_char_p("INIT".encode('utf-8')))
	count+=1
	time.sleep(1)

tlPM.setFreqMode(0)

tlPM.close()
print('End program')
