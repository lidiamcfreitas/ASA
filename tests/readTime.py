import sys

def readvalues(filename):
    """reads input configuration from filename"""
    file = open(filename,"r")
    res = []
    i = 3
    for line in file:
        
        if i%4 == 0:
            x = line[:-1].split("m")
            i = 1
            sys.stdout.write(x[1][:-1] + ",")
        else:
            i += 1

readvalues(sys.argv[1])