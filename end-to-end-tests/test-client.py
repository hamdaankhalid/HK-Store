import socket

class HkStoreClient:
    def __init__(self, host, port):
        self.HOST = host
        self.PORT = port
        self.ENDIANESS = 'little'

    def set_(self, key, val):
        key_size = (len(key)).to_bytes(4,self.ENDIANESS)
        val_size = (len(val)).to_bytes(4,self.ENDIANESS)
        key_val = f" {key} {val}"
        request = b"SET " + key_size + b" " + val_size + str.encode(key_val)
        self._make_request(request)

    def get_(self, key):
        key_size = (len(key)).to_bytes(4,self.ENDIANESS)
        request = b"GET " + key_size + b" " + str.encode(key)
        self._make_request(request)

    def del_(self, key):
        key_size = (len(key)).to_bytes(4,self.ENDIANESS)
        request = b"DEL " + key_size + b" " + str.encode(key)
        self._make_request(request)

    def all_(self):
        self._make_request(b"ALL")


    def _make_request(self, request):
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((self.HOST, self.PORT))

            print(f"Request: {request}")

            s.sendall(request)
            data = s.recv(1024)

        print(f"Received {data!r}")
        return data


def main():
    c = HkStoreClient("127.0.0.1", 8000)
    c.set_("owner", "hamdaan")
    print("#"*10)
    c.set_("cat", "spark")
    print("#"*10)
    c.set_("O", "1")
    print("#"*10)
    c.get_("owner")
    print("#"*10)
    c.get_("cat")
    print("#"*10)
    c.get_("friend")
    print("#"*10)
    c.get_("O")
    c.all_()

main()
