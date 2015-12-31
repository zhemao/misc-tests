import random

data_size = 65536
res_size = 4096

X = [int(random.random()*1000.00) for x in range(data_size)]
K = [int(random.random()*data_size) for k in range(res_size)]

result = []

for k in K:
    result.append(X[k])


def print_arr(array_type, array_name, array_sz, pyarr):
    print "{} {}[{}] = ".format(array_type, array_name, array_sz)
    print "{"
    print ", ".join(map(str, pyarr))
    print "};"


print "#define DATA_SIZE {}".format(data_size)
print "#define RES_SIZE {}".format(res_size)

print_arr("int", "input_data_X", "DATA_SIZE", X)
print_arr("int", "input_data_K", "RES_SIZE", K)

print_arr("int", "verify_data", "RES_SIZE", result)

