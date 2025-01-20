#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <ctime>

#pragma comment(lib, "ws2_32.lib")

int main() {
    // Inicializacion de Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Error al inicializar Winsock" << std::endl;
        return 1;
    }

    // Crear el socket para el servidor
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Error al crear el socket" << std::endl;
        WSACleanup();
        return 1;
    }

    // Configuracion de la direccin del servidor
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(9000);

    // Vincular el socket a la direccion
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Error al vincular el socket" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Escuchar conexiones entrantes
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Error al escuchar" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Servidor iniciado. Esperando conexiones en el puerto 9000..." << std::endl;

    while (true) {
        // Aceptar conexiones entrantes
        SOCKET clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Error al aceptar la conexion" << std::endl;
            continue;
        }

        std::cout << "Conexion aceptada. Enviando hora y fecha al cliente..." << std::endl;

        // Obtener la hora y la fecha actuales
        time_t currentTime = time(NULL);
        char* timeStr = ctime(&currentTime);

        // Enviar la hora y la fecha al cliente
        send(clientSocket, timeStr, strlen(timeStr), 0);

        std::cout << "Hora y fecha enviadas: " << timeStr << std::endl;

        // Cerrar el socket del cliente
        closesocket(clientSocket);
    }

    // Cerrar el socket del servidor
    closesocket(serverSocket);

    // Limpiar Winsock
    WSACleanup();

    return 0;
}
