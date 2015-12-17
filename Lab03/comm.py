#!/usr/bin/python

"""
Implements the comm command in linux

It also adds the -u option for unsorted text files

Written by Connor Kenny (using the work cited below).
Used randline.py as an outline and some of the code is reused.
"""
"""
Output lines selected randomly from a file

Copyright 2005, 2007 Paul Eggert.
Copyright 2010 Darrell Benjamin Carbajal.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Please see <http://www.gnu.org/licenses/> for a copy of the license.

$Id: randline.py,v 1.4 2010/04/05 20:04:43 eggert Exp $
"""

import random, sys, locale, string
from optparse import OptionParser

one, two, three = False, False, False
printed1, printed2 = False, False

class comm:
    def __init__(self, file1, file2):
        if file1 == "-":
            f1 = sys.stdin
        else:
            f1 = open(file1)
        if file2 == "-":
            f2 = sys.stdin
        else:
            f2 = open(file2)
        self.lines1 = f1.readlines()
        self.lines2 = f2.readlines()
        f1.close()
        f2.close()
        
    def compareSorted(self):
        locale.setlocale(locale.LC_COLLATE, '')
        i = 0
        j = 0
        l1 = self.lines1
        l2 = self.lines2
        error = False
        happened = False
        while (i < len(l1)) and (j < len(l2)):
            if not error and i > 0 and l1[i] < l1[i-1]:
                error = True
            if not error and j > 0 and l2[j] < l2[j-1]:
                error = True
            if not happened and error:
                print("Error - Unsorted file(s)")
                happened = True
            if l1[i] < l2[j]:
                printCol(l1[i], 1)
                i += 1
            elif l1[i] > l2[j]:
                printCol(l2[j], 2)
                j += 1
            else:
                printCol(l1[i], 3)
                i += 1
                j += 1
        global printed1
        global printed2
        while i < len(l1):
            printCol(l1[i], 1)
            i += 1
        if printed1:
            print("")
        while j < len(l2):
            printCol(l2[j], 2)
            j += 1
        if printed2:
            print("")
                    
    def compareUnsorted(self):
        locale.setlocale(locale.LC_COLLATE, '')
        l1 = self.lines1
        l2 = self.lines2
        j = 0
        inBoth = []
        printed =  False
        for line1 in l1:
            for line2 in l2:
                j += 1
                if line1 == line2:
                    printCol(line1, 3)
                    printed = True
                    inBoth.append(j-1)
                    break
            if not printed:
                printCol(line1, 1)
            j = 0
            printed = False
        if printed1:
            print("")
        while j < len(l2):
            if j not in inBoth:
                printCol(l2[j], 2)
            j += 1
        if not two:
            print("")
def printCol(s, col):
    global printed1
    global printed2
    if col == 1:
        if one:
            return
        printed1 = True
    elif col == 2:
        if two:
            return
        if not one:
            sys.stdout.write("\t")
        printed2 = True
    elif col == 3:
        if three:
            return
        if not one:
            sys.stdout.write("\t")
        if not two:
            sys.stdout.write("\t")
    sys.stdout.write("%s" % s)
    
def main():
    version_msg = "%prog 1.0"
    usage_msg = """%prog [OPTIONS] FILE1 FILE2

Implement the comm command - Compare two files line by line"""

    parser = OptionParser(version=version_msg,
                          usage=usage_msg)
    parser.add_option("-1",
                      action="store_true", dest="one", default=False,
                      help="allow for suppression of first column")
    parser.add_option("-2",
                      action="store_true", dest="two", default=False,
                      help="allow for suppression of second column")
    parser.add_option("-3",
                      action="store_true", dest="three", default=False,
                      help="allow for suppression of thrid column")
    parser.add_option("-u", "--unsorted",
                      action="store_true", dest="unsorted",
                      help="allow for unsorted files to be compared")
    options, args = parser.parse_args(sys.argv[1:])

    # Save these options for the other functions to use
    global one
    global two
    global three
    one = options.one
    two = options.two
    three = options.three

    if len(args) != 2:
        parser.error("wrong number of operands")

    try:
        generator = comm(args[0], args[1])
        if options.unsorted:
            generator.compareUnsorted()
        else:
            generator.compareSorted()
    except IOError as err:
        errno, strerror = err.args
        parser.error("I/O error({0}): {1}".
                     format(errno, strerror))

if __name__ == "__main__":
    main()
