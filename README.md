# Proyecto de Comunicación Cliente-Servidor en C++<br>
<br>
Este proyecto es un ejemplo de comunicación básica entre un servidor y un cliente en C++ utilizando la biblioteca Winsock en Windows. El servidor escucha conexiones entrantes de clientes, establece la comunicación y envía la fecha y hora al cliente. El cliente se conecta al servidor, recibe la fecha y hora y la muestra en pantalla.
<br>
Para el servidor:<br>
Usa el siguiente comando para compilar el servidor:

```bash
g++ server.cpp -o server -lws2_32
```

<br>
Para el cliente:<br>
Usa el siguiente comando para compilar el cliente:

```bash
g++ client.cpp -o client -lws2_32
```

<br>
Ejecución<br>
Inicia el servidor ejecutando el archivo server:

```bash
./server
```
<br>
El servidor comenzará a escuchar conexiones en el puerto 9000.
<br>
Inicia el cliente ejecutando el archivo client:

```bash
./client
```
<br>
El cliente se conectará al servidor y mostrará la fecha y hora recibidas.
