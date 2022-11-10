import socket

class Client:
    def __init__(self, host, port):
        self.HOST = host
        self.PORT = port
        self.ENDIANESS = 'little'

    def set_request(self, key, val):
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((self.HOST, self.PORT))
            
            key_size = (len(key)).to_bytes(4,self.ENDIANESS)
            val_size = (len(val)).to_bytes(4,self.ENDIANESS)
            key_val = f" {key} {val}"

            request = b"SET " + key_size + b" " + val_size + str.encode(key_val)

            print(request)

            s.sendall(request)
            data = s.recv(1024)

        print(f"Received {data!r}")

    def get_request(self, key):
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((self.HOST, self.PORT))
            
            key_size = (len(key)).to_bytes(4,self.ENDIANESS)

            request = b"GET " + key_size + b" " + str.encode(key)

            print(request)

            s.sendall(request)
            data = s.recv(1024)

        print(f"Received {data!r}")

    def del_request(self, key):
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((self.HOST, self.PORT))
            
            key_size = (len(key)).to_bytes(4,self.ENDIANESS)

            request = b"DEL " + key_size + b" " + str.encode(key)

            print(request)

            s.sendall(request)
            data = s.recv(1024)

        print(f"Received {data!r}")

    def get_all_keys_request(self):
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((self.HOST, self.PORT))

            request = b"ALL"

            print(request)

            s.sendall(request)
            data = s.recv(1024)

        print(f"Received {data!r}")

def main():
    c = Client("127.0.0.1", 8000)
    c.set_request("owner", "hamdaan")
    print("#"*10)
    c.set_request("cat", "spark")
    print("#"*10)
    c.set_request("O", "1")
    print("#"*10)
    c.get_request("owner")
    print("#"*10)
    c.get_request("cat")
    print("#"*10)
    c.get_request("friend")
    print("#"*10)
    c.get_request("O")
    c.get_all_keys_request()

main()
