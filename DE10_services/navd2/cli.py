#!/usr/bin/python
# -*- coding: utf-8 -*-

import socket

serverAddressPort   = ("127.0.0.1", 9955)
bufferSize          = 1024

UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

UDPClientSocket.sendto('Test', serverAddressPort)
msgFromServer = UDPClientSocket.recvfrom(bufferSize)

msg = "Message from Server {}".format(msgFromServer[0])

print(msg)
