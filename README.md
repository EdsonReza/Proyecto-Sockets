# Registro de terremotos - Ejemplo de uso de sockets en C

## Descripción

Este programa hace uso de sockets para comunicar dos procesos, uno de ellos es el servidor y el otro es el cliente. El servidor se encarga de recibir los datos enviados por el cliente y los almacena en un archivo de texto.

## Compilación

Para compilar el programa se debe ejecutar el siguiente comando:

```bash
bash build.sh
```

La compilacion requiere de CMake 3.8+ y GCC.

El cual compilará el programa y creará los ejecutables `Servidor` y `Cliente`, en la carpeta `build/bin`.
