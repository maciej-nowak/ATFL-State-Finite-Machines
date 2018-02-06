#!/usr/bin/python2

import sys
import re

pattern = re.compile(r"^(N(IE{6,}|O{6,})!{3,})$", re.UNICODE)

for line in sys.stdin:
    match = re.match(pattern,line)
    if match:
        print 'true'
    else:
        print 'false'