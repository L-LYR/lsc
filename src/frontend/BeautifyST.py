#!/usr/bin/python3

import prettytable as pt
import sys
import pandas as pd
import io

keys = [
    "ID",
    "Declaration Location",
    "Offset",
    "Definition Location"
]


def beautifyST(lines, outfile):
    print(lines[0], end="", file=outfile)
    if lines[1] == "empty":
        print(lines[1], end="\n\n", file=outfile)
        return
    print(file=outfile)
    csv = io.StringIO("\n".join(lines[1:]))
    df = pd.read_csv(csv, delimiter=";")

    curKey = []
    for key in keys:
        if key in df:
            df[key] = pd.to_numeric(df[key])
            curKey.append(key)

    df = df.sort_values(by=curKey)

    tb = pt.from_csv(io.StringIO(df.to_csv(index=False)))
    tb.align = "r"
    print(tb, file=outfile, end="\n\n")


if __name__ == "__main__":
    if len(sys.argv) < 2:
        raise Exception("No input file!")

    file = open(sys.argv[1], "r+")
    lines = [""]
    lines.extend(file.read().splitlines())
    file.seek(0)
    while len(lines) > 1:
        if lines[0] == "":
            j = lines.index("", 1)
            curLines = lines[1:j]
            lines = lines[j:]
            beautifyST(curLines, file)
    file.close()
