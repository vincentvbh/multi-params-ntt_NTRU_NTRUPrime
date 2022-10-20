#!/usr/bin/env python3

import datetime
import os.path
import subprocess
import sys
import serial

import numpy as np

from config import Settings

hbench={}
polybench={}
benchTypes = ["speed","speed168MHz"]
outFileName = "speed.txt"
iterations = 10
testedList = [["keygen", "keypair cycles:"],
              ["encaps", "encaps cycles:"],
              ["decaps", "decaps cycles:"],
              ["NTT", "NTT cycles:"],
              ["NTT_small", "NTT_small cycles:"],
              ["basemul", "basemul cycles:"],
              ["iNTT", "iNTT cycles:"],
              ["final_map","final_map cycles:"]
             ]
# schemeList = ["ntruhps2048677", "sntrup857"]
schemeList = ["ntruhps2048677", "ntruhrss701", "ntruhps4096821",
              "ntrulpr653", "ntrulpr761", "ntrulpr857",
              "sntrup653", "sntrup761", "sntrup857"]
impleList = ["", "_1440", "_1536"]
cpu = "m4f"


def toLog(name, value, k=None):
  if value > 200000:
    value = f"{round(value/1000)}k"
  else:
    value = f"{value}"
  return f"{value}" 

def getBinary(scheme, impl,benchType):
    return f"bin/crypto_kem_{scheme}_{impl}_{benchType}.bin"

def getFlash(binary):
    return f"st-flash --reset write {binary} 0x8000000"

def run_bench(scheme, impl, benchType):
    binary = getBinary(scheme, impl, benchType)

    if os.path.isfile(binary):
        print(f"test {binary}")
    else:
        print(f"skip {binary}")
        return None

    try:
        subprocess.check_call(getFlash(binary), shell=True)
    except:
        print("st-flash failed --> retry")
        return run_bench(scheme, impl, benchType)

    # get serial output and wait for '#'
    with serial.Serial(Settings.SERIAL_DEVICE, Settings.BAUD_RATE, timeout=10) as dev:
        logs = []
        iteration = 0
        log = b""
        while iteration < iterations:
            device_output = dev.read()
            if device_output == b'':
                print("timeout --> retry")
                return run_bench(scheme, impl, benchType)
            sys.stdout.buffer.write(device_output)
            sys.stdout.flush()
            log += device_output
            if device_output == b'#':
                logs.append(log)
                log = b""
                iteration += 1
    return logs


def parseLogSpeed(log, ignoreErrors):
    log = log.decode(errors="ignore")
    if "error" in log.lower() and not ignoreErrors:
        raise Exception("error in scheme. this is very bad.")
    lines = str(log).splitlines()

    def get(lines, key):
        if key in lines:
            return int(lines[1+lines.index(key)])
        else:
            return None

    def cleanNullTerms(d):
        return {
            k:v
            for k, v in d.items()
            if v is not None
        }

    return cleanNullTerms({
            k: get(lines, v)
            for k, v in testedList
    })

def average(results):
    avgs = dict()
    for key in results[0].keys():
        avgs[key] = int(np.array([results[i][key] for i in range(len(results))]).mean())
    return avgs


def bench(scheme, texName, impl, benchType, ignoreErrors=False):
    logs    = run_bench(scheme, impl,benchType)
    if logs == None:
        return None
    results = []

    for log in logs:
        try:
            result = parseLogSpeed(log, ignoreErrors)
        except:
            breakpoint()
            print("parsing log failed -> retry")
            return bench(scheme, texName, impl, benchType)
        results.append(result)

    avgResults = average(results)
    
    if benchType==benchTypes[1]:
        texName+="_168MHz"
    hbench[texName]=[avgResults[testedList[0][0]],avgResults[testedList[1][0]],avgResults[testedList[2][0]]]
    polyb=[]
    for op in testedList[3:]:
        polyb.append(avgResults[op[0]])
    polybench[texName]=polyb

def makeAll():
    subprocess.check_call(f"make clean", shell=True)
    subprocess.check_call(f"make -j8 ITERATIONS={iterations}", shell=True)


makeAll()

with open(outFileName, "w+") as outfile:

    now = datetime.datetime.now(datetime.timezone.utc)
    print(f"{benchTypes[0]} measurements written on {now}; iterations={iterations}\n", file=outfile)


    for scheme in schemeList:
        for imple in impleList:
            for benchType in benchTypes:
                bench(scheme, scheme + cpu + imple, cpu + imple, benchType)
    print("\n"+"Cycle counts for high level operations.".center(60, ' ')+"\n",file=outfile)
    print("\nImplementation".ljust(30,' '),end='\t',file=outfile)
    for op in testedList[0:3]:
        print(f"{op[0]}".rjust(10,' '),end='\t',file=outfile)
    print('', file=outfile, flush=True)
   
    for key, value in hbench.items():
        print(key.ljust(30,' '),end='\t',file=outfile)
        for v in value:
            print(toLog(key,v).rjust(10,' '),end='\t',file=outfile)
        print("", file=outfile, flush=True)
    
    print("\n"+"Performance of polymuls in NTRU and NTRU Prime on Cortex-M4.".center(90, ' ')+"\n",file=outfile)  
    print("\nImplementation".ljust(30,' '),end='\t',file=outfile)
    print('polymul'.rjust(10,' '), end = '\t', file=outfile)
    for op in testedList[3:]:
        print(f"{op[0]}".rjust(10,' '),end='\t',file=outfile)
    print("", file = outfile, flush = True)

    for key, value in polybench.items():
        print(key.ljust(30,' '),end='\t',file=outfile)
        print(str(sum(value)).rjust(10,' '), end = '\t', file=outfile, flush=True)
        for v in value:
            print(toLog(key,v).rjust(10,' '),end='\t',file=outfile)
        print("", file = outfile, flush = True)





