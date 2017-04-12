#!/usr/bin/env python

import cgi
import csv
import cgitb
cgitb.enable()

#Get the values of the inventory and the URL from the form
form = cgi.FieldStorage()

inventory = form.getvalue('inventory')
URL = form.getvalue('URL')
URL_temp = "http://www.cs.mcgill.ca/~mxiong4/cgi-bin"

#Open the csv file to get occupancy status of the room
f1 = open('./resources.csv',"rb")
reader = csv.reader(f1)
for row in reader:
        mana = row[0]
        gold = row[1]
        occupied = row[2]
f1.close()

#If the room is occupied
#Generate a new html page that says that it is occupied and display a return button
if occupied == '1':
	print "Content-Type: text/html\n\n"
        print "<br><br><br>"
        print "<body style=background-color:powderblue;>"
        print "<h1><center><big><b>The room is currently occupied</b> </big></center></h1>"
	print "<center><form action="
	print URL_temp + "/room.cgi"
	print " method=post style=display:inline;> <input type=hidden name=command value=refresh><input type=hidden name=inventory value="
	print inventory
	print "> <input type=submit value=Return></form>"
	print "</center></body>"

#If the room is not occupied
#Generate a new html page that says that the person can proceed the teleporting and display a proceed button
else:
	print "Content-Type: text/html\n\n"
	print "<br><br><br>"
        print "<body style=background-color:powderblue;>"
        print "<h1><center><big><b>You are now teleporting to the next room!</b> </big></center></h1>"
	print "<center><form action="
	#Run previous room's success.py
	print URL_temp + "/success.py"
	#Pass the URL of YOUR room and player inventory through hidden values
	print " method=post style=display:inline;><input type=hidden name=URL value="
	print "www.cs.mcgill.ca/~mxiong4/cgi-bin>"
	print "<input type=hidden name=inventory value="
	print inventory
	print "> <input type=submit value=Proceed></form>"
	print "</center></body>"

print "<h2>Hello %s %s</h2>" %(URL, inventory)
