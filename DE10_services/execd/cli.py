import socket
import sys

hostname, sld, tld, port = 'www', 'integralist', 'co.uk', 80
target = '{}.{}.{}'.format(hostname, sld, tld)

# create an ipv4 (AF_INET) socket object using the tcp protocol (SOCK_STREAM)
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# connect the client
# client.connect((target, port))
client.connect(('', 5053))

# send some data (in this case a HTTP GET request)
client.send('test')

# receive the response data (4096 is recommended buffer size)

while(1):
    response = client.recv(4096)
    #print response
    sys.stdout.write(response)
