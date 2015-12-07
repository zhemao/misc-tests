import os
import subprocess
import shutil

SIZE_STEP=1000
DATA_SIZE=20000

def build_test(prefetch, size):
    with open("test-settings.h", "w") as f:
        if prefetch:
            f.write("#define PREFETCH\n")
        f.write("#define TEST_SIZE {}\n".format(size))

    testname = "tests/saxpy-test-{}-{}.hex".format(
            "prefetch" if prefetch else "noprefetch", size)

    subprocess.call(["make", "saxpy-test.hex"])
    shutil.copyfile("saxpy-test.hex", testname)

def main():
    if not os.path.isdir("tests"):
        os.mkdir("tests")
    for size in range(SIZE_STEP, DATA_SIZE + 1, SIZE_STEP):
        build_test(False, size)
        build_test(True, size)

main()
