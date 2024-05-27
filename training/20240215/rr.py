# read prior information
from random import randint as rnd
line = input().split()
N = int(line[0])
M = int(line[1])
eps = float(line[2])
fields = []
for _ in range(M):
    line = input().split()
    ps = []
    for i in range(int(line[0])):
        ps.append((int(line[2*i+1]), int(line[2*i+2])))
    fields.append(ps)

# drill every square
has_oil = []
for _ in range(rnd(10, 20)):
    x = rnd(1, N)
    y = rnd(1, M)
    print("q 1 {} {}".format(x, y))
    resp = input()
    if resp != "0":
        has_oil.append((x, y))

print("a {} {}".format(len(has_oil), ' '.join(
    map(lambda x: "{} {}".format(x[0], x[1]), has_oil))))
resp = input()
assert resp == "1"
