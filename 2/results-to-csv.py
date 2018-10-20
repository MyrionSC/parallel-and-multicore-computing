#!/usr/bin/env python3

import sys
import pandas as pd

data = {}

args = sys.argv[1:]
with open(args[0], "r") as file:
    for line in file:
        content = line.split(" ")
        if len(content) == 3:
            name, result, time = content # we don't care too much about the results
            if name in data:
                data[name] += [float(time)]
            else:
                data[name] = [float(time)]

# shitty hack to make pandas handle jagged arrays
s = [pd.Series(data=value, name=key) for key, value in data.items()]
df = pd.concat(s, axis=1)

# write to file
df.to_csv(args[0][:-4] + "-sheetformat.csv", sep="\t")


print(df)
print("\nprinted output to file " + args[0][:-4] + "-sheetformat.csv")
