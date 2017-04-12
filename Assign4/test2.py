#!/usr/bin/python

# Filename: test2.py

import csv

mana = 0
gold = 0
occupied = 0

#reading the file
f1 = open('./try2.csv',"rb")
reader = csv.reader(f1)
for row in reader:
	mana = row[0]
	gold = row[1]
	occupied = row[2]
f1.close()

print (occupied)

if occupied == 1:
	print "the room is occupied"

#writting the file
with open('./try2.csv', "wb") as csv_file:
	writer = csv.writer(csv_file, delimiter=',')
	writer.writerow(['34','4','1'])




