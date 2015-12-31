import sys
import subprocess
import os

max_size = 65536
start_size = 1024

n_channels = [1, 2, 4]

def run_benchmark(nchan, size, f):
    emulator = "./emulator-Top-Benchmark{}ChannelConfig".format(nchan)
    command = [emulator, "+dramsim", "pk", "membw", str(size)]
    print(" ".join(command))
    with open(os.devnull) as devnull:
        subprocess.call(command, stdin=devnull, stdout=f)

def main():
    for nchan in n_channels:
        resultfile = "results/{}channels.txt".format(nchan)
        with open(resultfile, "w") as f:
            size = start_size
            while size <= max_size:
                run_benchmark(nchan, size, f)
                size *= 2

main()
