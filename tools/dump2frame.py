#!/usr/bin/python2.7

# FLORIPASAT 
# Parser for obdh flash memory dump
# Created by Mario Baldini <mario.baldini@gmail.com>
# 2016-06-22
import sys


if len(sys.argv) <= 1:
    print 'Insuficient arguments! Usage: python2.7', sys.argv[0], ' mem_file_dump.txt'
    quit()

# print "Parsing file:", sys.argv[1]

file = open(str(sys.argv[1]), "r")

file_content = file.read()
lines = file_content.split('\n')

tokens = []
for line in lines: 
    # print line.split(' ')
    for token in line.split(' '):
        tokens.append( token )

# print "Read tokens from file:", tokens

state = None
count = 0

for token in tokens:

    # Frame format to be parsed:
    # {{{BBB..BBB}\n\r    where BB..BB => byte sequence

    if   (state == None) and (token == "7B"):  # 0x7B = {
        state = "SOF1"
        continue
    elif (state == None) and (token != "7B"):
        state = None
        continue


    if   (state == "SOF1") and (token == "7B"):  
        state = "SOF2"
        continue
    elif (state == "SOF1") and (token != "7B"):
        state = None
        continue
        

    if   (state == "SOF2") and (token == "7B"): 
        print "{{{",
        state = "DATA"
        continue
    elif (state == "SOF2") and (token != "7B"):
        state = None
        continue


    if   (state == "DATA") and (token != "7D"):  # 0x7D = }
        print token,
        state = "DATA"
        continue
    elif (state == "DATA") and (token == "7D"):
        state = "EOF1"
        continue


    if   (state == "EOF1") and (token == "0A"):  # 0x0A = \n
        state = "EOF2"
        continue
    elif (state == "EOF1") and (token != "0A"):
        print "7D",token,
        state = "DATA"
        continue


    if   (state == "EOF2") and (token == "0D"):  # 0x0D = \r
        print "}\n\r",
        count = count + 1 
        state = None
        continue
    elif (state == "EOF2") and (token != "0D"):
        print "7D","0A",token, 
        state = "DATA"
        continue



print "Frames read:", count

file.close()

