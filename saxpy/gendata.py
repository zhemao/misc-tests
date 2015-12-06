import random
import sys

def print_data(typ, name, data):
    size = len(data)
    print("#define {}_SIZE {}".format(name.upper(), size))
    print("{} {}_data[{}] = {{".format(typ, name.lower(), size))
    print("\t" + ",".join(str(d) for d in data))
    print("};")

def saxpy_gendata(ysize, xsize):
    a = random.random() * 1000.0
    y = [random.random() * 1000.0 for i in range(0, ysize)]
    x = [random.random() * 1000.0 for i in range(0, xsize)]
    print("float a_data = {};".format(a))
    print_data("float", "x", x)
    print_data("float", "y", y)

def print_guard(name):
    print("#ifndef __{}_DATASET_H__".format(name))
    print("#define __{}_DATASET_H__".format(name))

def print_end(name):
    print("#endif // __{}_DATASET_H__".format(name))

def main():
    print_guard("saxpy")

    ysize = int(sys.argv[1])
    xsize = int(sys.argv[2])
    saxpy_gendata(ysize, xsize)

    print_end("saxpy")

main()
