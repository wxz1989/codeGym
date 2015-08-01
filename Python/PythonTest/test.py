#/usr/bin/python

import random
import math


print "Hellow World!"


print "Rakesh Gajjar"[::-1]


name = "Rakesh"
for x in range(len(name)):
    print len(name)
    if ( name[x] == name [len(name-(x+1))]):
        print "Matching"
    else:
        print "Not a palindrome"

    print name[x], name[len(name-(x+1))], x



