# Multiple-Client-Server-Program-in-C-using-fork
A simple tcp client server application that describes the communication between the client and a server. The server is a simple echo sever that can handle multiple client using fork.

An echo server is a server that send back the same message that the client has send the server. 
Like:

Client send - abc<br/>
Server recv - abc

# Registro de terremotos - Ejemplo de uso de sockets en C

## Descripción

Este programa hace uso de sockets para comunicar dos procesos, uno de ellos es el servidor y el otro es el cliente. El servidor se encarga de recibir los datos enviados por el cliente y los almacena en un archivo de texto.

## Compilación

Para compilar el programa se debe ejecutar el siguiente comando:

```bash
bash build.sh
```

El cual compilará el programa y creará los ejecutables `Servidor` y `Cliente`, en la carpeta `build/bin`.
