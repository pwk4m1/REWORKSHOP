#!/usr/bin/env python2.7
import sys

f = open(sys.argv[1], "r")
code = f.read()
f.close()

code = code.replace("myos", "Nyanix")

with open(sys.argv[1], "w") as phile:
    phile.write(code)


