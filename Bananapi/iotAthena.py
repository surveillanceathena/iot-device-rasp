import ctypes
import pylibi2c
import time
import datetime

from firebase import firebase

# Open i2c device @/dev/i2c-0, addr 0x50, 16bits internal address
i2c = pylibi2c.I2CDevice('/dev/i2c-1', 0x08, iaddr_bytes=2)

# Set delay
i2c.delay = 10

# Set page_bytes
i2c.page_bytes = 16

# Set flags
i2c.flags = pylibi2c.I2C_M_IGNORE_NAK

# Python3
buf = bytes(256)

firebase = firebase.FirebaseApplication('https://surveillaceathenaiot.firebaseio.com/', None)
#firebase = firebase.FirebaseApplication('https://35.201.97.85/', None)

while True:

    data = i2c.ioctl_read(0x0,8)
    
    if data != '99999999':
        
        now = datetime.datetime.now()
        date = now.strftime("%Y-%m-%d %H:%M:%S")
        firebase.put('/sensores','S'+str(data[:4]),str(data[4:8]) + ' - '+date+']')        
        print '['+ date +'] sensor: S' + data[:4] + ' value:' + data[4:8] 
    
    time.sleep( 2 )
