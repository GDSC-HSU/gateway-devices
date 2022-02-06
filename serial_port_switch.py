# import util
import sys
import os
pioPath = ".platformio/penv/lib/python3.9/site-packages
fullPath = os.path.join(os.path.expanduser('~'), pioPath)
print(fullPath)
sys.path.append(os.path.join(os.path.expanduser('~'), pioPath))
import util
util.get_serial_ports()
