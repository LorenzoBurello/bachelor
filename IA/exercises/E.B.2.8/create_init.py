out = ""
xMAX = 20
yMAX = 5
blocks = [[(0,20)], [(0, 6), (8, 8), (11, 20)], [(3, 3), (5, 5), (12, 20)], [(12, 12), (14, 14), (16, 18), (20, 20)], [(17, 17)]]
availability = [2, 2, 2, 3, 2, 3, 2, 1, 2, 1, 1, 2, 4, 3, 4, 3, 4, 5, 4, 3, 4]

for y, l in enumerate(blocks):
    for t in l:
        print(t)
        start, stop = t
        for i in range(start, stop+1):
            out = out + f"\t(Block x{i} y{y})\n"

for x, y in enumerate(availability):
    out = out + f"\t(Available x{x} y{y})\n"

for i in range(yMAX):
    out = out + f"\t(AdiacentY y{i} y{i+1})\n"
    out = out + f"\t(AdiacentY y{i+1} y{i})\n"

for i in range(xMAX):
    out = out + f"\t(AdiacentX x{i} x{i+1})\n"
    out = out + f"\t(AdiacentX x{i+1} x{i})\n"

print(out)