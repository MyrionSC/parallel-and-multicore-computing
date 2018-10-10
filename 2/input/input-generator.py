#!/usr/bin/env python3

import random
import sys

if len(sys.argv) > 1:
    n = int(sys.argv[1])
else:
    print("argument 1 must be number of nodes in TSP graph")
    exit()

adjMatrix = [[0 for y in range(n)] for x in range(n)]

for i in range(0, n):
    for j in range(0, n):
        if i != j and adjMatrix[i][j] == 0:
            if random.random() < 0.3:
                adjMatrix[i][j] = adjMatrix[j][i] = random.randint(10, 100)

# for row in adjMatrix:
#    print(row)


#adjMatrix = [[0, 4, 0, 0, 0, 0, 0, 8, 0],
#             [4, 0, 8, 0, 0, 0, 0, 11, 0],
#             [0, 8, 0, 7, 0, 4, 0, 0, 2],
#             [0, 0, 7, 0, 9, 14, 0, 0, 0],
#             [0, 0, 0, 9, 0, 10, 0, 0, 0],
#             [0, 0, 4, 14, 10, 0, 2, 0, 0],
#             [0, 0, 0, 0, 0, 2, 0, 1, 6],
#             [8, 11, 0, 0, 0, 0, 1, 0, 7],
#             [0, 0, 2, 0, 0, 0, 6, 7, 0]]
#n = 9

f = open(str(n) + ".txt", "w+")
f.write(str(n) + "\n")
for i in range(0, n):
    for j in range(0, n):
        f.write(str(i) + " " + str(j) + " " + str(adjMatrix[i][j]) + "\n")

print("data saved to file: " + str(n) + ".txt")
