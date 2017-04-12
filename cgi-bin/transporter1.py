#!/usr/bin/env python
import cgi
import csv
mana = 0
gold = 0
occupied = 0

#Process parameters

form = cgi.FieldStorage() 
print form
#inventory = form["inventory"].value
URL = form["URL"].value
print URL

#reading the file
f1 = open('./resources.csv',"rb")
reader = csv.reader(f1)
for row in reader:
        mana = row[0]
        gold = row[1]
        occupied = row[2]
f1.close()

'''if occupied == 1:
        print
	print "%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10
        print "<html>"
        print "<br><br><br>"
        print "<body style=background-color:powderblue;>"
        print "<h1><center><big><b>The room is currently occupied</b> </big></center></h1>"
	print "<center><form action=p4.cgi method=post style=display:inline;> <input type=hidden name=command value=refresh><input type=hidden name=inventory value="
	print inventory
	print "> <input type=submit value=Return></form>"
	print "</center></body></html>"

#writting the file
with open('./try2.csv', "wb") as csv_file:
        writer = csv.writer(csv_file, delimiter=',')
        writer.writerow(['34','4','1'])
'''
print "Content-Type: text/html\n\n"
print
print "<h1>Hello World!</h1>"

