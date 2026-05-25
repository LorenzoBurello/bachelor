nMax = 10

log = ""

for a in range(nMax+1):
    for b in range(nMax+1):
        if a+b < nMax:
            log = log + f"(Sum q{a} q{b} q{a+b})\n"

for a in range(nMax):
    for b in range(a, nMax+1):
        log = log + f"(Le q{a} q{b})\n"
print(log)