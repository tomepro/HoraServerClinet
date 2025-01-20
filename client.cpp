#include <iostream>
#include <winsock2.h>
#include <ctime>

#pragma comment(lib, "ws2_32.lib") // Para vincular la biblioteca de Winsock

using namespace std;

int main() {
    // Inicializacion de Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "Error al inicializar Winsock" << endl;
        return 1;
    }

    // Crear un socket
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        cerr << "Error al crear el socket" << endl;
        WSACleanup();
        return 1;
    }

    // Definir la direccion del servidor
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(9000); // Puerto del servidor
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Direccion del servidor, en mi caso (localhost)

    // Conectar al servidor
    if (connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cerr << "No se puede conectar al servidor" << endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    cout << "Conexion establecida con el servidor." << endl;

    // Recibir los datos del servidor
    char buffer[1024];
    int bytesReceived = recv(sock, buffer, sizeof(buffer), 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0'; // Asegurarse de que el buffer termine con un null
        cout << "Hora y fecha recibidas: " << buffer << endl;
    } else {
        cerr << "Error al recibir datos del servidor" << endl;
    }

    // Cerrar el socket
    closesocket(sock);
    WSACleanup();

    return 0;
}
