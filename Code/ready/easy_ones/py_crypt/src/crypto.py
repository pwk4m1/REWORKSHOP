#!/usr/bin/env python2.7
from sys import argv
from Crypto.Cipher import AES

def write_file(x, y):
    f = open(x, "w")
    f.write(y)
    f.close()

def pad(x):
    while (len(x) % 16):
        x += "\x00"
    return x

def main():
    if (len(argv) != 3):
        print "Usage: %s <message> <outfile>" % argv[0]
        return

    print "Encrypting message..."

    msg = pad(argv[1])
    key = "AntherLongString"
    print len(key)
    IV = "reALLYLONGSTRING"
    Aes = AES.new(key, AES.MODE_CBC, IV)
    cipher = Aes.encrypt(msg)
    
    print "Writing cipher to file %s" % argv[2]
    write_file(argv[2], cipher)
    print "Done."

if __name__ == "__main__":
    main()

