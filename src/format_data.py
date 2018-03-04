#!/bin/python

import subprocess
import sys
import datetime
import datetime
import collections
from operator import itemgetter
import os.path

if not os.path.exists('/tmp/8006'):
    os.makedirs('/tmp/8006')

f = subprocess.run(['grep', '-i', 'failed password', '/var/log/secure'], stdout=subprocess.PIPE)

g = f.stdout.split(b'\n');

x = {}

for line in g[:-1]:
    col = line.split(b' ');
    col = list(filter(None, col))
    col = col[:3] + [col[-4]]
    col = [(int) (datetime.datetime.strptime(b' '.join(col[:3]).decode('ascii'), '%b %d %X').replace(year=2018).timestamp())] + [col[-1].decode('ascii')]

    if (col[1] in x):
        x[col[1]] = x[col[1]] + [col[0]]
    else:
        x[col[1]] = [col[0]]

for ip in x.keys():
    data = x[ip]
    if (os.path.isfile('/tmp/8006/' + ip)):
        #Read file for ban timestamp, and remove older entries
        rec = open('/tmp/8006/' + ip, 'r')

        for line in rec:
            tok = line.split()
            data = [e for e in data if e > int(tok[0])]
            if (int(datetime.datetime.now().timestamp()) > int(tok[1]) and int(tok[1]) != -1):
                r = subprocess.Popen(['iptables', '-L', '-n'], stdout=subprocess.PIPE)
                d = subprocess.Popen(['grep', ip], stdin=r.stdout, stdout=subprocess.PIPE)
                out, err = d.communicate()
                if (out is not None and out):
                    print('U ' + ip)

        rec.close()
    else:
        #Ban this ip
        rec = open('/tmp/8006/' + ip, 'w+')
        rec.write(str(int(datetime.datetime.now().timestamp())) + " " + sys.argv[2] + "\n")
        rec.close()

    if (len(data) >= int(sys.argv[1])):
        print('B ' + ip)

