MAX_MOVES = 10
costs = [1, 2]

log = ""

for n in range(MAX_MOVES+1):
    log = log + f"v{n} "
log = log + "- cost\n"
for cost in costs:
    for n in range(MAX_MOVES-(cost - 1)):
        log = log + f"(ActionCost{cost} v{n} v{n+cost})\n"

print(log)