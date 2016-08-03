#!/usr/bin/python2.7

# FLORIPASAT 
# Parser from uG mission to fsat frame 
# Created by Mario Baldini <mario.baldini@gmail.com>
# 2016-08-01
import sys

if len(sys.argv) <= 1:
    print 'Insuficient arguments! Usage: python2.7', sys.argv[0], ' ug-fsat-3byte.csv'
    quit()

file = open(str(sys.argv[1]), "r")

file_content = file.read()
lines = file_content.split('\n')

tokens = []
for line in lines: 

    for token in line.split(','):
        # print token + ",",

        token_int = int(token)

        token_byte1 = token_int & 0xFF0000
        token_byte2 = token_int & 0x00FF00
        token_byte3 = token_int & 0x0000FF

        print token_byte1,token_byte2,token_byte3,


    print 


file.close()

