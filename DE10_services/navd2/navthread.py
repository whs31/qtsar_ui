#!/usr/bin/python
# -*- coding: utf-8 -*-

import time
from decimal import *
import socket
import struct
from datetime import datetime
import threading

class NavThread(threading.Thread):
    def __init__(self, t=False):
        threading.Thread.__init__(self)
        self.testMode = t
        self.lat = 0.0
        self.lon = 0.0
        self.elv = 0.0
        self.speed = 0.0
        self.running = True
        
        

    def run(self):
        print "Enter to nav thread"
        if(self.testMode):
            self.test()
        else:
            work()
        
    def test(self):
        self.lat = 100.0
        self.lon = 200.0
        self.elv = 300.0
        self.speed = 400.0
        
        while(1):
            self.lat += 0.1
            self.lon += 0.1
            self.elv += 0.1
            self.speed += 0.1
            
            time.sleep(1)
        
        
            
    def work(self):
        import GPTelemetry_pb2
        MCAST_GRP = '229.10.12.90'
        MCAST_PORT = 31290


        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
        sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        sock.bind((MCAST_GRP, MCAST_PORT))
        mreq = struct.pack("4sl", socket.inet_aton(MCAST_GRP), socket.INADDR_ANY)

        sock.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, mreq)

        tel = GPTelemetry_pb2.Telemetry()

        while(self.running):
            try:
                data, addr = sock.recvfrom(1024)
            except socket.error, e:
                print "Exception", e
                   
            p_magic = struct.unpack("BBB", data[0:3])
            p_len = int(struct.unpack("B", data[3])[0] )
            p_crc_proto = struct.unpack("B", data[4])
            p_crc_header = struct.unpack("B", data[5])
            
            #p_data = struct.unpack("s", data[6:6+p_len])
            p_data = data[6:6+p_len];
            
            
            tel.ParseFromString(p_data);
            
            unix_time = int(tel.unix_time) + (3*60*60)
            self.speed = tel.gps_speed
            air_speed = tel.air_speed
            self.lat = tel.lat
            self.lon = tel.lon
            self.elv = tel.alt_gps
            dir = tel.gps_course
            fix = 99
            sats = 777
            
            date_str = datetime.utcfromtimestamp(unix_time).strftime('%Y-%m-%dT%H:%M:%S')
            

        sock.close()
        
        
    def stop(self):
        self.running = False 

