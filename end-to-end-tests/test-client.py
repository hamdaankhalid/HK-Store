import socket

HOST = "127.0.0.1"  # The server's hostname or IP address
PORT = 3000  # The port used by the server

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    
    key_size = (3).to_bytes(4,'big')
    val_size = (5).to_bytes(4,'big')

    request = b"SET " + key_size + b" " + val_size + b" cat spark"

    print(request)

    s.sendall(request)
    data = s.recv(1024)

print(f"Received {data!r}")
