import os
import subprocess
import sys
import csv
import re

SIZE_STEP=1000
DATA_SIZE=20000

def run_test(config, prefetch, size):
    testname = "{}/tests/saxpy-test-{}-{}.hex".format(
            os.getcwd(), "prefetch" if prefetch else "noprefetch", size)
    emulator = "./emulator-Top-{}".format(config)
    command = [emulator, "+dramsim", "+cycle-count", "+loadmem={}".format(testname)]
    emulator_dir = os.path.abspath("../../emulator")
    p = subprocess.Popen(command,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            cwd=emulator_dir)
    _, output = p.communicate()
    matches = re.findall(r"\d+", output)
    if not matches:
        print("Could not find number in output '{}'".format(output))
    return int(matches[0])

def main():
    config = sys.argv[1]
    writer = csv.writer(sys.stdout)

    for size in range(SIZE_STEP, DATA_SIZE + 1, SIZE_STEP):
        npf_time = run_test(config, False, size)
        pf_time = run_test(config, True, size)
        writer.writerow([size, npf_time, pf_time])

main()
