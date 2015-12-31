import matplotlib.pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages
import re

LINE_REGEX = re.compile(r"time\[(\d+)\] = (\d+)")

def parse_file(fname):
    with open(fname) as f:
        res = []
        for line in f:
            m = LINE_REGEX.match(line.strip())
            if m:
                groups = m.groups()
                n = int(groups[0])
                cycles = int(groups[1])
                res.append((n, cycles))
        return tuple(zip(*res))

n_channels = [1, 2, 4]

def main():
    pp = PdfPages("results/plot.pdf")
    print("opened PDF file")
    plt.figure()
    plt.clf()

    for nchan in n_channels:
        n, cycles = parse_file("results/{}channels.txt".format(nchan))
        plt.plot(n, cycles)

    pp.savefig()
    pp.close()

main()
