#!/usr/bin/env python
import cgi
form = cgi.FieldStorage()
print form
if form.has_key("inventory"):
	print form["inventory"]
else:
	print "Content-type: text/html"
