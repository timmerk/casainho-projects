#!/usr/local/bin/python
import string
import sys
import getopt
import re
import os
import os.path

def usage():
  """ Display the usage """
  print "Usage:" + sys.argv[0] + "csvfile"
  print "--help|h : print this information"
  sys.exit(2)

def validateOpts(opts):
  """ Returns option values specified, or the default if none """
  outputFileName = ""
  sepChar = ","
  for option, argval in opts:
    if (option in ("-h", "--help")):
      usage()
  return

def main():
  """ This is how we are called """
  try:
    opts,args = getopt.getopt(sys.argv[1:], "h", ["help"])
  except getopt.GetoptError:
    usage()

  if (len(args) != 1):
    usage()

  inputFileName = args[0]
  try:
    inputFile = open(inputFileName, 'r')
  except IOError:
    print "File not found:", inputFileName, "...aborting"
    sys.exit(-1)

  #Open the file
  f = open(inputFileName, "rU")
  fOutput = open("weight.csv", "w")

  #Replace line by line
  for row in f:
    row = row.replace(',', ';', 1)
    row = row.replace(',', '.', 1)
    row = re.sub('"', '', row)
    fOutput.write(row)

  f.close()
  fOutput.close()

  print "Conversion done."

if __name__ == "__main__":
  main()

