#!/usr/bin/python3

import re
import sys
from math import *

if len(sys.argv) < 2:
    print("Usage: autoparse.py <filename>")
    exit()

filename = sys.argv[1]
with open(filename, "r") as myfile:
    data = myfile.readlines()

vertices = []
faces = []
normal = []

prog1 = re.compile('^v (-?\d\.\d+) (-?\d\.\d+) (-?\d\.\d+)')
prog2 = re.compile('^f (\d+)\/\d+\/\d+ (\d+)\/\d+\/\d+ (\d+)\/\d+\/(\d+)$')
prog3 = re.compile('^vn (-?\d\.\d+) (-?\d\.\d+) (-?\d\.\d+)')
for string in data:
    result = prog1.match(string)
    if result != None:
        vec = []
        for i in range(1, 4):
            vec.append(float(result.group(i)))
        vertices.append(vec)
    
    result = prog2.match(string)
    if result != None:
        for i in range(1, 5):
            faces.append(int(result.group(i)) - 1)
    
    result = prog3.match(string)
    if result != None:
        n = []
        for i in range(1, 4):
            n.append(float(result.group(i)))
        normal.append(n)
            
print(len(vertices))
for vertex in vertices:
    print("Vec3f(", end="")
    for i in range(len(vertex) - 1):
        print(vertex[i], end="f, ")
    print(vertex[2], end="f),")
    print()

print(len(faces) / 4)
for i in range(0, int(len(faces) / 4)):
    n = normal[faces[i * 4 + 3]]
    for j in range(3):
        print(str(int(faces[i * 4 + j])), end=", ")
    print()
