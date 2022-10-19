#!/usr/bin/env python3

import datetime
import subprocess
import sys

import serial
import numpy as np
import os.path
from config import Settings

testType = "test"
iterations = 1
ntests = 10

schemeList = ["ntruhps2048677", "ntruhrss701", "ntruhps4096821",
              "ntrulpr653", "ntrulpr761", "ntrulpr857",
              "sntrup653", "sntrup761", "sntrup857"]
impleList = ["", "_1440", "_1536"]
cpu = "m4f"


def getBinary(scheme, impl):
    return f"bin/crypto_kem_{scheme}_{impl}_{testType}.bin"

def getFlash(binary):
    return f"st-flash --reset write {binary} 0x8000000"

def makeAll():
    subprocess.check_call(f"make clean", shell=True)
    subprocess.check_call(f"make -j8 ITERATIONS={iterations}", shell=True)


def test(scheme, impl):
    binary = getBinary(scheme, impl)

    if os.path.isfile(binary):
        print(f"test {binary}")
    else:
        print(f"skip {binary}")
        return None

    try:
        subprocess.check_call(getFlash(binary), shell=True)
    except:
        print("st-flash failed --> retry")
        return test(scheme, impl)

    with serial.Serial(Settings.SERIAL_DEVICE, Settings.BAUD_RATE, timeout=10) as dev:
        log = b""

        while True:
            device_output = dev.read()
            if device_output == b'':
                print("timeout --> retry")
                return test(scheme, impl)
            sys.stdout.buffer.write(device_output)
            sys.stdout.flush()
            log += device_output
            if device_output == b'#':
                break

    log = log.decode(errors="ignore")
    assert log.count("ERROR") == 0 and log.count("OK") == ntests


makeAll()

for scheme in schemeList:
    for imple in impleList:
        test(scheme, cpu + imple)


