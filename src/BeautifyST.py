#!/usr/bin/python3

import prettytable as pt
import sys
import pandas as pd
import io

first_key = "Declaration Location"
second_key = "Offset"


def beautifyST(lines, outfile):
    print(lines[0], end="", file=outfile)
    if lines[1] == "Empty Scope":
        print(lines[1], end="\n\n", file=outfile)
        return
    print(file=outfile)
    csv = io.StringIO("\n".join(lines[1:]))
    df = pd.read_csv(csv, delimiter=";")
    df[first_key] = pd.to_numeric(df[first_key])
    df[second_key] = pd.to_numeric(df[second_key])
    df = df.sort_values(by=[first_key, second_key])
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
