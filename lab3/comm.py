#!/usr/bin/python

import string, sys, locale
from argparse import ArgumentParser

class comm:
    def __init__(self, file1, file2):
        if (file1 == "-" and file2 == "-"):
            print("Both files can't be stdin!")
            exit()
        elif (file1 == "-"):
            f1 = sys.stdin
            f2 = open(file2,'r')
        elif (file2 == "-"):
            f2 = sys.stdin
            f1 = open(file1,'r')
        else:
            f1 = open(file1,'r')
            f2 = open(file2,'r')

        self.lines1 = f1.readlines()
        self.lines2 = f2.readlines()

        self.col1 = []
        self.col2 = []
        self.col3 = []

        f1.close()
        f2.close()
    
    def compare(self, arg4):
        if arg4:
            for i in range(len(self.lines1)):
                for j in range(len(self.lines2)):
                    if (self.lines1[i] == self.lines2[j]):
                        self.col3.append(self.lines1[i])
                        self.col1.append("\t")
                        self.col2.append("\t")
                        del self.lines2[j]
                        match = True
                        break
                    else:
                        match = False
                if match == False: # there was nothing similar
                    self.col1.append(self.lines1[i])
                    self.col2.append("")
                    self.col3.append("")
            for i in range(len(self.lines2)): # additional spaces
                self.col2.append(self.lines2[i])
                self.col1.append("\t")
                self.col3.append("")
                
        else:
            i,j = 0,0
            while i in range(len(self.lines1)) and j in range(len(self.lines2)):
                if self.lines1[i] == self.lines2[j]:
                    self.col3.append(self.lines1[i])
                    self.col1.append("\t")
                    self.col2.append("\t")
                    i += 1
                    j += 1
                elif self.lines1[i] < self.lines2[j]:
                    self.col1.append(self.lines1[i])
                    self.col2.append("")
                    self.col3.append("")
                    i += 1
                else:
                    self.col2.append(self.lines2[j])
                    self.col1.append("\t")
                    self.col3.append("")
                    j += 1
        
    def printThat(self, arg1, arg2, arg3):
        if arg1 == True:
            self.col1 = ['']*len(self.col1)
        if arg2 == True:
            self.col2 = ['']*len(self.col2)
        if arg3 == True:
            self.col3 = ['']*len(self.col3)
        
        combined = []
        for i in range(len(self.col1)):
            add = self.col1[i] + self.col2[i] + self.col3[i]
            if (add != '' and add != '\t' and add != '\t\t'):
                combined.append(add)
                
        for i in range(len(combined)):
            print(combined[i],end="")
        


def main():
    descr = "Compare sorted files FILE1 and FILE2 line by line. \
                When FILE1 or FILE2 (not both) is -, read standard input."
    parser = ArgumentParser(description=descr)
    parser.add_argument('-1', dest="no_c1", action='store_true',
                    help = "suppress cloumn 1 (lines unique to FILE1)")
    parser.add_argument('-2', dest = "no_c2", action = 'store_true',
                    help = "suppress cloumn 2 (lines unique to FILE2)")
    parser.add_argument('-3', dest = "no_c3", action = 'store_true',
                    help = "suppress cloumn 3 (lines that apear in both files)")
    parser.add_argument('-u', dest = "no_sort", action = 'store_true',
                    help = "work with unsorted files")
    parser.add_argument('filename', nargs='+',
                    help = "this is a file")
 
    args = parser.parse_args()
    
    try:
        no_c1 = bool(args.no_c1)
    except:
        parser.error("invalid argument for -1: {0}".
                     format(args.no_c1))
    try:
        no_c2 = bool(args.no_c2)
    except:
        parser.error("invalid argument for -2: {0}".
                     format(args.no_c2))
    try:
        no_c3 = bool(args.no_c3)
    except:
        parser.error("invalid argument for -3: {0}".
                     format(args.no_c3))
    try:
        no_sort = bool(args.no_sort)
    except:
        parser.error("invalid argument for -u --unsorted: {0}".
                     format(args.no_sort))
        
    arg_vars = vars(args)
    if len(arg_vars['filename']) != 2:
        parser.error("wrong number of args")
    try:
        i_file1 = arg_vars['filename'][0]
        i_file2 = arg_vars['filename'][1]
    
        comm_obj = comm(i_file1, i_file2)
        comm_obj.compare(args.no_sort)
        comm_obj.printThat(no_c1,no_c2,no_c3)
    except IOError as err:
        errno = err.errno
        strerr = err.strerror
        parser.error("I/O error ({0}): {1}".
                                    format(errno,strerr))
    
if __name__ == "__main__":
    main()
