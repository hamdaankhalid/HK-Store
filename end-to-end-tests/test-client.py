import socket

class Client:
    def __init__(self, host, port):
        self.HOST = host
        self.PORT = port
        self.ENDIANESS = 'little'

    def set_request(self):
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((self.HOST, self.PORT))
            
            key_size = (3).to_bytes(4,self.ENDIANESS)
            val_size = (5).to_bytes(4,self.ENDIANESS)

            request = b"SET " + key_size + b" " + val_size + b" cat spark"

            print(request)

            s.sendall(request)
            data = s.recv(1024)

        print(f"Received {data!r}")

    def get_request(self):
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((self.HOST, self.PORT))
            
            key_size = (3).to_bytes(4,self.ENDIANESS)

            request = b"GET " + key_size + b" " + b"cat"

            print(request)

            s.sendall(request)
            data = s.recv(1024)

        print(f"Received {data!r}")

    def del_request(self):
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((self.HOST, self.PORT))
            
            key_size = (3).to_bytes(4,self.ENDIANESS)

            request = b"DEL " + key_size + b" " + b"cat"

            print(request)

            s.sendall(request)
            data = s.recv(1024)

        print(f"Received {data!r}")

def main():
    c = Client("127.0.0.1", 3000)
    c.set_request()
    c.get_request()
    c.del_request()

main()
