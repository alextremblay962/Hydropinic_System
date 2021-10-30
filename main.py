import serial
import json
import io
import  time

ser = serial.Serial("COM24" , 9600, timeout=2)

topic = "hydro/light1"
payload = 1

#data = json.dumps({"topic":topic,"payload":payload})
data = "{\"topic\":\"hydro/light1\",\"payload\":1}"
data = data.encode()

print(data)

ser.write(data)


hello = ser.readline().decode("ascii")
print(hello)