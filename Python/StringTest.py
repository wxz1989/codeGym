#!/usr/bin/python

print "Hello Koding World!"

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
