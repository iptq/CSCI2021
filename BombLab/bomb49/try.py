answers = """
And they have no disregard for human life.
1 2 4 8 16 32
0 u 644
12 3
gamfeg
"""

from subprocess import Popen, PIPE, STDOUT
from itertools import permutations

for a in range(7):
    for b in range(7):
        for c in range(7):
            print a, b, c
            for d in range(7):
                for e in range(7):
                    for f in range(7):
                        p = Popen(['./bomb'], stdout=PIPE, stdin=PIPE, stderr=PIPE)
                        stdout_data = p.communicate(input="%s\n%s %s %s %s %s %s" % (answers, a, b, c, d, e, f))[0]
                        if not(stdout_data.find("BOOM") > 0):
                            print "SHIET", a, b, c, d, e, f