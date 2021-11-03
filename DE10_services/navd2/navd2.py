#!/usr/bin/python
# -*- coding: utf-8 -*-

import socket
import navthread
import sys
import os
import struct

localIP     = "127.0.0.1"
localPort   = 9955
bufferSize  = 1024

UDPServerSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
UDPServerSocket.bind((localIP, localPort))

print("UDP server up and listening")

nt = navthread.NavThread(True)
nt.start()

while(1):

    try:
        bytesAddressPair = UDPServerSocket.recvfrom(bufferSize)
    except KeyboardInterrupt:
        #nt.exit()
        UDPServerSocket.close()
        os.kill(0, 9)

    message = bytesAddressPair[0]
    address = bytesAddressPair[1]
    print 'Recv:', message

    #data = str.encode( '{} {} {} {}'.format(nt.lat, nt.lon, nt.speed, nt.elv) )
    data = struct.pack('ddff', nt.lat, nt.lon, nt.speed, nt.elv)

    UDPServerSocket.sendto(data, address)



