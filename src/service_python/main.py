import socket

HOST = '127.0.0.1'
PORT = 8080
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((HOST, PORT))

booleano = True
def server_py():
    server.listen()
    print(f"Server running in port: {PORT}")

while booleano:
    server_py()
    client_socket, client_address = server.accept()
    print(f"Connected with C module: {client_address}")
    # Envia uma mensagem ao cliente
    message = "Hello, C module!"
    client_socket.send(message.encode())

        
    
