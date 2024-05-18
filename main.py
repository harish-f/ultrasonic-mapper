import serial
import time

PORTNAME = "/dev/tty.usbmodem1201"
BAUDRATE = 9600

X_PIXELS = 10
Y_PIXELS = 10
X_ANGLE = 90
Y_ANGLE = 90

results = [[0]*X_PIXELS]*Y_PIXELS

ser = serial.Serial(port=PORTNAME, baudrate=BAUDRATE, timeout=0.1)

time.sleep(3) # to let serial initialise

if not ser:
    print("unable to open establish connection with Arduino")
    exit()


def writeToSerial(x):
    ser.write(bytes(str(x)+'\n', 'utf-8'))
    time.sleep(0.05)

def readFromSerial():
    res = ser.readline().decode('utf-8')
    while not res: res = ser.readline().decode('utf-8')
    return int(res)


# to tell arduino image dimension
writeToSerial(X_PIXELS)
writeToSerial(Y_PIXELS)
writeToSerial(X_ANGLE)
writeToSerial(Y_ANGLE)

if readFromSerial() == X_PIXELS + Y_PIXELS + X_ANGLE + Y_ANGLE:
    print("Successfully initialised communication with Arduino")
else: print("fuck")



for yIndex in range(Y_PIXELS):
    r = []
    for xIndex in range(X_PIXELS):
        distValue = readFromSerial()
        r.append(distValue)
    results[yIndex] = r


csvData = ",".join([str(x) for x in range(X_PIXELS+1)]) + "\n"

for y in range(Y_PIXELS):
    csvData += str(y+1) + "," + ",".join([str(val) for val in results[y]]) + "\n"

with open("data.csv", "w") as csvFile:
    csvFile.write(csvData)
    csvFile.close()

print(csvData)