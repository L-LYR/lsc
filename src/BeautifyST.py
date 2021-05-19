#!/usr/bin/python3

import prettytable as pt
import sys


def beautifyST(lines, outfile):
    print(lines[0], end="", file=outfile)
    if (lines[1] == "Empty Scope"):
        print(lines[1]+"\n", file=outfile)
        return
    else:
        print(file=outfile)
    tb = pt.PrettyTable()
    tb.field_names = lines[1].split(";")
    for line in lines[2:]:
        tb.add_row(line.split(";"))
    print(tb, "\n", file=outfile, sep="")


if __name__ == "__main__":
    if len(sys.argv) != 2:
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
