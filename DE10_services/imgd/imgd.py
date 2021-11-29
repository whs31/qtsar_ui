#!/usr/bin/python3
# -*- coding: utf-8 -*-
import os
import sys
import errno
import socket

FIFO = '/tmp/imgd.pipe'
LOCKFILE = "/tmp/imgd.lock"
CONFIG = 'imgd.cfg'


# Defines
NOFILE = -1

class Daemon():
    
    
    def __init__(self):
        from threading import Thread
        
        print("startDaemon", os.getpid())
        #self.daemonize()
        
        self.cfg = self.parseCfg(CONFIG)
        self.clent_addr = None
        self.client = None
        self.sock = None
        
        self.createLockfile();
        Thread(target = self.io).start()
        
        ip = self.cfg['server']['ip']
        port = self.cfg['server']['port']
        
        self.sock = self.createServer(ip, port)
        try:
            self.bufferSize = int(self.cfg['server']['bufferSize'])
        except:
            self.bufferSize = 1024
        
        while(1):
            print("Wait for client...")
            try:
                self.client, self.clent_addr = self.sock.accept()
            except OSError as oe: 
                if oe.errno == 22:
                    print("Accept aborted")
                    continue
                else:
                    raise
            
            print("Client Connected", self.clent_addr)
            
            while(1):
                try:
                    data = self.client.recv(1024)
                except:
                    data = ''
                if(len(data) == 0):
                    self.clent_addr = None
                    self.client = None
                    print('Client disconnected')
                    break
                else:
                    self.send(data.decode("utf-8"))
    
    def daemonize(self):
        try:
            pid = os.fork()
            if pid > 0:
                # exit first parent
                sys.exit(0)
        except OSError as err:
            sys.stderr.write('_Fork #1 failed: {0}\n'.format(err))
            sys.exit(1)
        # decouple from parent environment
        os.chdir('/')
        os.setsid()
        os.umask(0)
        # do second fork
        try:
            pid = os.fork()
            if pid > 0:
                # exit from second parent
                sys.exit(0)
        except OSError as err:
            sys.stderr.write('_Fork #2 failed: {0}\n'.format(err))
            sys.exit(1)
        # redirect standard file descriptors
        sys.stdout.flush()
        sys.stderr.flush()
        si = open(os.devnull, 'r')
        so = open(os.devnull, 'w')
        se = open(os.devnull, 'w')
        os.dup2(si.fileno(), sys.stdin.fileno())
        os.dup2(so.fileno(), sys.stdout.fileno())
        os.dup2(se.fileno(), sys.stderr.fileno())

    def parseCfg(self, path):
        import configparser
        config = configparser.ConfigParser()
        config.read(path)
        
        return config
        
    def createLockfile(self):
        lockfile = open(LOCKFILE, "w")
        lockfile.write( str(os.getpid()) )
        lockfile.close()
        
    def createServer(self, ip, port):
        port = int(port)
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        
        server_address = (ip, port)
        
        sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        sock.bind(server_address)
        sock.listen(1)
        return sock

    def status(self):
        status = []
        
        status.append( "Daemon pid: {}".format(os.getpid()) )
        ip, port = self.sock.getsockname()
        status.append( "Server at {}:{} ".format(ip, port) )
        status.append( "Client: {}".format(self.clent_addr) )
        status.append( "Buffer size: {}".format(self.bufferSize) )
        
        return "\n".join(map(str, status))
        
    def send(self, path):
    
        import time
        if(self.client):
			
            try:
                img = open(path, 'rb');
            except:
                self.client.send( NOFILE.to_bytes( 4 , byteorder='little' , signed=True ) );
                return "file {} not found!".format(path)
            
            fileSize = os.stat(path).st_size 
            self.client.send(fileSize.to_bytes(4, 'little'))
            
            chunk = img.read(self.bufferSize)
            sended = 0;
            while(chunk):
            
                # NEED TEST. Buggy part
                try:
                    sended += self.client.send(chunk)
                except:
                    img.close()
                    return 'Error. Connection reset by peer.'
                chunk = img.read(self.bufferSize)
                
                #TEST
                time.sleep(1.1)
            
            #self.sock.shutdown(socket.SHUT_WR)
            return "{} bytes sended".format(sended)
        else:
            return "Client is not connected"
    
    def fifoPrint(self, data):
        with open(FIFO, 'w') as fifo:
            fifo.write(data)
            fifo.close()
            
    def changeIP(self, data):
        ip, port = data.split(":")
        
        try:
            self.sock.shutdown(socket.SHUT_RD)
            self.sock.close()
        except:
            pass
            
        self.sock = self.createServer(ip, port)

        return 'Setting server {}:{}'.format(ip, port)

    
    def io(self):
        import shlex
        try:
            os.mkfifo(FIFO)
        except OSError as oe: 
            if oe.errno != errno.EEXIST:
                raise
        response = ''
        while(1):
            with open(FIFO) as fifo:
                data = fifo.read()
                
            data = shlex.split(data)
            
            
            if(data[0] == 'status'):
                response = self.status();
            elif(data[0] == 'send'):
                response = self.send(data[1])
            elif(data[0] == 'server'):
                response = self.changeIP(data[1])
            else:
                response = "Command not found"
            
            self.fifoPrint(response)

    
def command(pid, cmd):
    with open(FIFO, 'w') as fifo:
        data = fifo.write(cmd)
        fifo.close()
    import time

    with open(FIFO) as fifo:
        data = fifo.read()
        print(data)

def checkPID(pid):
    if(pid == None):
        return False
    pid = int(pid)
    
    try:
        os.kill(pid, 0)
    except OSError as e:
        if(e.errno == 3):
            return False
        else:
            return True
    else:
        return True
        
def main(cmd):
    
    pid = None
    try:
        lockfile = open(LOCKFILE, "r")
        pid = lockfile.read()
        lockfile.close()
    except:
        print("Have no lockfile")
        pass
    
    if(cmd == "'stop' "):
        print("kill", pid)
        
        try:
            os.kill(int(pid), 9)
        except:
            pass
        
        try:
            os.remove(FIFO)
            os.remove(LOCKFILE)
        except:
            pass
        
        exit(0)
        
            
    
    if(checkPID(pid)):
        command(pid, cmd)
    else:
        d = Daemon()
        
        

if __name__ == "__main__":
    cmd = ''
    if(len(sys.argv) == 1):
        cmd = 'status'
    else:
        #print(sys.argv) 
        #cmd = ' '.join( map(str, sys.argv[1:]) )
        for c in sys.argv[1:]:
            cmd += "'{}' ".format(c)
    main(cmd)
