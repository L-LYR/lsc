#!/usr/bin/python3
import sys


class Node:
    def __init__(self, text, level):
        self.text = text
        self.level = level
        self.children = []

    def addChild(self, node):
        self.children.append(node)

    def empty(self):
        return len(self.children) == 0

    def __str__(self):
        return self.text


def splitAt(s):
    i = s.find(' ')
    return (int(s[:i]), s[i+1:-1])


def AST(td, ts, d):
    n = Node(ts[0], d)
    st = [i for i, x in enumerate(td) if x == d+1]
    for i in range(len(st)-1):
        n.addChild(AST(td[st[i]:st[i+1]], ts[st[i]:st[i+1]], d+1))
    if len(st) > 0:
        n.addChild(AST(td[st[-1]:], ts[st[-1]:], d+1))
    return n


def printAST(node, indent, final, file):
    line = "".join(indent[:node.level])
    line += "└─" if final else "├─"
    print(line+node.text, file=file)
    if node.empty():
        return
    for i, n in enumerate(node.children):
        indent.append("  " if final else "│ ")
        printAST(n, indent, i == len(node.children)-1, file)
        del indent[-1]


def beautifyAST(lines, outfile):
    data = list(map(splitAt, lines))
    depth = [t[0] for t in data]
    strs = [t[1] for t in data]
    print("AST", file=outfile)
    printAST(AST(depth, strs, 1), [], True, outfile)


if __name__ == "__main__":
    if len(sys.argv) != 2:
        raise Exception("No input file!")
    file = open(sys.argv[1], "r+")
    lines = file.readlines()
    file.seek(0)
    beautifyAST(lines, file)
    file.close()
