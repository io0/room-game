#!/usr/bin/env python

import cgi
import csv
import cgitb
cgitb.enable()

form = cgi.FieldStorage()

inventory = form.getvalue('inventory')
URL = form.getvalue('URL')

inventory_list = inventory.split(",")
mana = int(inventory_list[0])
gold = int(inventory_list[1])

#write csv to occupied
f1 = open('./resources.csv',"rb")
reader = csv.reader(f1)
for row in reader:
        mana = row[0]
        gold = row[1]
        occupied = row[2]
f1.close()

with open('./resources.csv', "wb") as csv_file:
        writer = csv.writer(csv_file, delimiter=',')
        writer.writerow([mana,gold,'1'])
#display exit screen
print "Content-Type: text/html\n\n"
print "<br><br><br>"
print "<body style=background-color:powderblue;>"
print "<h1><center><big><b>Sorry to see you leave.</b> </big></center></h1>"
print "<center><form action="
#Run next room's refresh command
print "http://" + URL + "/room.cgi"
#Pass player inventory
print " method=post style=display:inline;><input type=hidden name=command value=refresh><input type=hidden name=inventory value="
print inventory
print "> <input type=submit value=Exit></form>"
print "</center></body>"
