import serial
import io

ser = serial.Serial("COM24" , 115200, timeout=1)

ser.write(b'hello')

hello = ser.readline()
print(hello)