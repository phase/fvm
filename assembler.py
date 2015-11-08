#!/usr/bin/env python3
import sys
import re

fileName = ""
try:
    fileName = sys.argv[1]
except:
    print("File not specified")
    exit();

def string2int(str):
    return [ord(c) for c in str].append(0)

f = open(fileName, 'r')
bytecode = ""
lastIndent = 0
indent = 0
routineIndent = 0
for line in f:
    spaceCount = len(line) - len(line.strip(' '))
    indent = int(spaceCount / 4)
    if indent > lastIndent:
        routineIndent += indent - lastIndent
    elif indent < lastIndent:
        routineIndent -= lastIndent - indent
    print("indent " + repr(indent) + " " + repr(spaceCount) + " " + repr(routineIndent))
    
    lastIndent = indent