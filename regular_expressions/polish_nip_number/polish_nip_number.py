#!/usr/bin/python2

import sys
import re

pattern = re.compile(r"^([0-9]{3}-[0-9]{2}([0-9]-[0-9]{2}-|-[0-9]{2}-[0-9])[0-9]{2})$", re.UNICODE)

for line in sys.stdin:
    match = re.match(pattern,line)
    if match:
        print 'true'
    else:
        print 'false'
