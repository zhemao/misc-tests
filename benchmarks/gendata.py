import random
import sys

def format_data(int_data, rowsize):
    nrows = int(math.ceil(len(int_data) / float(rowsize)))
    rowstrings = [None] * nrows

    for i in range(0, nrows):
        start = i * rowsize
        finish = min(start + rowsize, len(int_data))
        rowdata = int_data[start : finish]
        rowstrings[i] = "\t" + ",".join(str(i) for i in rowdata)

    return ",\n".join(rowstrings) + "\n"

def main():
    sizes = [int(s) for s in sys.argv[1:]]

    for (idx, size) in enumerate(sizes):
        data = [random.random() * 1000.0 for i in range(0, size)]
        print("#define INPUT{}_SIZE {}".format(idx, size))
        print("float input{}_data[{}] = {{".format(idx, size))
        print("\t" + ",".join(str(f) for f in data))
        print("};")

main()
