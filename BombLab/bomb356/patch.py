import sys

if len(sys.argv) < 2:
    print "Usage: %s <file>" % sys.argv[0]
    sys.exit(1)

fname = sys.argv[1]
data = None

with open(fname, "rb") as f:
    data = f.read()

def find_all(a_str, sub):
    start = 0
    while True:
        start = a_str.find(sub, start)
        if start == -1: return
        yield start
        start += len(sub)

data = data.replace("zhan4854", "A" * len("zhan4854"))

with open(fname, "wb") as f:
    f.write(data)
