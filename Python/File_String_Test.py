#!/usr/bin/python

import math
import random
import time

print "Hello Koding World!"


print "***************************"
print "*******Array and List Functions**********"
array= [ 1, 2, 3, 4, 5, 6];

print array
array.sort()
print array
array.sort(reverse = True)
print array

print array[len(array) -1 ]

TwoDArray = ["C++", "Java", "Python", "SQLite"]
print TwoDArray
print range(len(TwoDArray))

for names in TwoDArray:
    print names, ":", len(names)
    
else:
    print "Name list empty"
    print len(TwoDArray)
    
for index in range(len(TwoDArray)):
    print TwoDArray[index], len(TwoDArray[index])
    
    
list = [1, 5, 3, 7, 8, 4, 9]

print "Min Member of the list:", min(list)
print "Max member of the list:", max(list)
    
print "***************************"


print "***************************"
print "*******String Functions*********"
testString = "Rakesh Dineshbhai Gajjar"

print testString
print testString[:6]
print testString[7:17]
print testString[18:]

index =  testString.find("Gajjar")
print "Found Index:", index 
print "Find Result:", testString.find("Gajjar")
replacedString =  testString.replace("Gajjar", "Suthar");
print "Replaced String:", replacedString
print "Original String :", testString

#testString.replace(index, "Suthar")

print str(testString[:6]) ,"is learning ", str(TwoDArray[2]),  "and" , str(TwoDArray[3]) , "right now!!!"

print testString[:-1]
print testString[-1:]

#Tupples and Disctionaties

print "Tuple and Disctionaties Example"
tup1 = ('physics', 'chemistry', 1997, 2000);
tup2 = (1, 2, 3, 4, 5, 6, 7 );

testTuple  = ('Rakesh',  7790832, 'Gajjar')
print testTuple
print tup1, tup2


print "Dictionaries"
dict1 = {'Alice': '2341', 'Beth': '9102', 'Cecil': '3258', 'TestDictElement' : 1234}

dict2 =  {"Swara" : "Aestranaut", "Rakesh" : 7790832, "Pradip" : 12345 , "Nishant" : 2425, "Prakash": "RakhadPatti" , "Aarav" : "Bigg Doctor" }

print dict1 , "\n", dict2 

print dict1["Alice"]

key1 = "Nishant"
key2 = "Prakash"

if ( dict2.has_key(key1)):
    print "Key Found, delete it"
    del dict2[key1];
else:
    print "Key ", key1, "not found"
    
if ( dict2.has_key(key2)):
    print "Key Found, delete it"
    del dict2[key2];
else:
    print "Key ", key2, "not found"
    
#Loop using for construct
print "Loop using for construct"
for items in dict2:
    print "Keys:", items, "Values", dict2.get(items)
    

print "Dictory Range and Length", len(dict2), range(len(dict2))

print "Loop using the index variable"
#Loop using index 
for index in range(len(dict2)):
    print "Keys:", dict2.keys()[index], "Values", dict2.values()[index]
    
    
print "Loop the tuple list returned"
dictTup = dict2.items()

for pairs in dictTup:
    print "Traverse Typle"
    for ite  in pairs:
        print "Tuppe Item:", ite 
    else:
        print "No more typle items found!!!"
else:
    "Pair type is empty now"
    
for index in range(len(dictTup)):
    print dictTup[index]
else:
    "Pair type is empty now"
    
print "Dictionary Tuple", dict2.items()

print "After Deletion", dict2

print "*********************"
print "**Clearn Dictironary Contnet**"
dict2.clear()
print dict2
print "*********************"


print "*********************"
print "**Time Functions**"
print "Current Time" , time.time()

print "Local Time" , time.localtime(time.time())
print "Printable Time" , time.asctime(time.localtime(time.time()))

print "CPU Clock Speed" , time.clock()

print "GMT Time" , time.asctime(time.gmtime(time.time()))

name = "Rakesh"
age = 31
print "My Name is %s and age is %d " %  ( name , age )


def ChangeName(name):
    print "Original Name:", name
    name += " Gajjar"
    #name = "Name Changed"
    return


MyName = "Rakesh"
print "Before Calling Function:", MyName
ChangeName(MyName)
print "After Calling Function:", MyName


SumOfNaturalNumbers = lambda arg1 : ((arg1*(arg1+1))/2)
print "Using lambda function:", SumOfNaturalNumbers (10)

print "Using Default Arguments"
def DefaultArgs(name, age = 35):
    print "Name:", name
    print "Age:", age
    return

DefaultArgs("Rakesh", 31)
DefaultArgs("Pradip")
DefaultArgs("Pankaj ", 65)
DefaultArgs("Vipul")
    
    
#content = dir (math)
#for names in content:
#print "Names Supported in Math:", names

print "Global Names:", globals()
print "Local Names:", locals()

"""
print "Raw Input from Concole:"
str = raw_input("Enter your input: ");
print "Received input is : ", str

fp = open ("IoTest.txt", "ab+")
print fp.name, fp.closed, fp.mode

fileContent = fp.read();
print "Reading current content of file:", fileContent

print "Content being appended to file is: ", str
fp.write(str);


fp.close()
"""


