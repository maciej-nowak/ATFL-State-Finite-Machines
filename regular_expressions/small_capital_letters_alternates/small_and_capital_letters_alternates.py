#!/usr/bin/python2
#-*- coding: utf-8 -*-

import sys
import re

pattern = re.compile(ur"^[^0-9](([A-ZĄĆĘŁŃÓŚŻŹ][a-ząćęłńóśżź])*)|(([a-ząćęłńóśżź][A-ZĄĆĘŁŃÓŚŻŹ])*)[^0-9]$", re.LOCALE|re.UNICODE)
pattern2 = re.compile(ur"^[A-ZĄĆĘŁŃÓŚŻŹ]$", re.LOCALE|re.UNICODE)
pattern3 = re.compile(ur"^[a-ząćęłńóśżź]$", re.LOCALE|re.UNICODE)

for line in sys.stdin:
    length = len(unicode(line, 'utf8'))
    length = length - 1
    if length%2==0:
        match = re.match(pattern, line)
        match2 = True
    else:
        lastChar = line[length-1:length]
        beforeLastChar = line[length-2:length-1]
        line = line[:length-1]
        match = re.match(pattern, line)
        if re.match(pattern2, beforeLastChar) and re.match(pattern3, lastChar):
            match2 = True
        elif re.match(pattern3, beforeLastChar) and re.match(pattern2, lastChar):
            match2 = True
        else:
            match2 = False
    if match and match2:
        print 'true'
    else:
        print 'false'