#!/bin/python

import subprocess;
import datetime;

f = subprocess.run(['grep', '-i', 'failed password', '/home/john/Documents/BCIT/COMP8006/final/network1/web/log/secure'], stdout=subprocess.PIPE)

g = f.stdout.split(b'\n');

for line in g[:-1]:
    col = line.split(b' ');
    col = list(filter(None, col))
    col = col[:3] + [col[-4]]
    col = [(int) (datetime.datetime.strptime(b' '.join(col[:3]).decode('ascii'), '%b %d %X').replace(year=2018).timestamp())] + [col[-1].decode('ascii')]
    print(col)

