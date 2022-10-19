#!/usr/bin/env python3

import datetime
import os.path
import subprocess
import sys
import serial

import numpy as np

from config import Settings

testType = "test"
iterations = 1
ntests = 10
outFileName = "test.txt"

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


def test(scheme, impl, outfile):
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
        return test(scheme, impl, outfile)

    with serial.Serial(Settings.SERIAL_DEVICE, Settings.BAUD_RATE, timeout=10) as dev:
        log = b""

        while True:
            device_output = dev.read()
            if device_output == b'':
                print("timeout --> retry")
                return test(scheme, impl, outfile)
            sys.stdout.buffer.write(device_output)
            sys.stdout.flush()
            log += device_output
            if device_output == b'#':
                break

    log = log.decode(errors="ignore")
    print(f"{scheme}_{impl}".ljust(30, ' '), end = '\t', file = outfile)
    print(str(log.count("ERROR")).rjust(10, ' ') + str(log.count("OK")).rjust(10, ' '), file = outfile, flush = True)

makeAll()

with open(outFileName, "w+") as outfile:

    now = datetime.datetime.now(datetime.timezone.utc)
    print(f"test logs written on {now}; iterations={iterations}\n\n", file=outfile)

    print("Scheme".ljust(32,' ') + "#ERROR".rjust(10, ' ') + "#OK".rjust(10, " "),file=outfile)

    for scheme in schemeList:
        for imple in impleList:
            test(scheme, cpu + imple, outfile)




