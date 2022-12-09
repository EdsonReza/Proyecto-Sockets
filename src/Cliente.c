
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include "Plot.h"
#include "tools_cliente.h"

#define bzero(b,len) (memset((b), '\0', (len)), (void) 0) 
#define PORT 4444

int redondeo(float n) {
    return (int) n;
}

int main() {
    int op = 0;

    int clientSocket, ret;
    struct sockaddr_in serverAddr;
    char buffer[1024];
    char nameCity[50];
    char message[20];
    float number;
    char userValue[10];
    int time_value;

    char file_vector[15];
    int vec[100];
    char nameCityFile[50];

    char *token;
    time_t t1 = 0;
    time_t *currentTime = &t1;

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        printf("[-]Error en la conexion.\n");
        exit(EXIT_FAILURE);
    } else {
        printf("[+]Cliente creado.\n");

        memset(&serverAddr, '\0', sizeof (serverAddr));
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(PORT);
        serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

        ret = connect(clientSocket, (struct sockaddr *) &serverAddr, sizeof (serverAddr));
        if (ret < 0) {
            printf("[-]Error en la conexion.\n");
            exit(1);
        }
        printf("[+]Conectado al servidor.\n");

        imprimePantallaCapturaCadena("Seleccion de Ciudad", "Nombre de la Ciudad: ", nameCity);
        send(clientSocket, nameCity, strlen(nameCity), 0);

        while (op != 3) {

            op = imprimeMenuIzquierda("Menu Principal",
                    "Introducir dato,"
                    "Solicitar grafica,"
                    "Terminar conexion",
                    ',');

            switch (op) {
                case 1:
                    number = imprimePantallaCapturaNumeroRealPositivo(
                            "Introducir Dato",
                            "Magnitud del sismo en escala de Richter: ")*10;

                    sprintf(userValue, "%d", redondeo(number));

                    time(currentTime);
                    sprintf(message, "%ld", *currentTime);
                    strcat(message, "|");
                    strcat(message, userValue);
                    strcat(message, "|");

                    imprimePantallaMensajeDoble(
                            "Introducir Datos",
                            "Datos enviados",
                            message);

                    send(clientSocket, message, strlen(message), 0);
                    break;
                case 2:
                    int nada = 0;
                    op = imprimeMenuIzquierda(
                            "Solicitud de Grafica",
                            "Por semana,"
                            "Por Mes,"
                            "Volver <--",
                            ',');
                    switch (op) {
                        case 1:
                            strcpy(buffer, "grafica1");
                            break;
                        case 2:
                            strcpy(buffer, "grafica2");
                            break;
                        case 3:
                            break;
                        default:
                            imprimePantallaMensajeDoble(
                                    "Solicitud de Grafica",
                                    "Error de opcion", 
                                    "Intente nuevamente");
                            break;
                    }
                    if (op >= 1 && op <= 2) {
                        send(clientSocket, buffer, strlen(buffer), 0);
                        int j = 0;
                        int bandera = 1;
                        while (bandera == 1) {

                            recv(clientSocket, file_vector, 14, 0);
                            token = strtok(file_vector, "|");
                            token = strtok(NULL, "|");

                            if (strcmp(file_vector, ":exit") == 0) {
                                bandera = 0;
                                break;
                            } else {
                                vec[j] = atoi(token);
                                j++;
                            }
                        }
                        for (int i = 0; i < j; i++) {
                            printf("%d\n", vec[i]);
                        }
                        strcpy(nameCityFile, nameCity);
                        strcat(nameCityFile, ".pgm");

                        generaGrafica(nameCityFile, vec, j);

                        imprimePantallaMensajeDoble(
                                "Solicitud de Grafica",
                                "Grafica creada correctamente, Encuentrela como:",
                                nameCityFile);
                    }else{
                        op = 0;
                    }

                    break;
                case 3:
                    bzero(buffer, sizeof (buffer));
                    strcpy(buffer, ":exit");
                    send(clientSocket, buffer, strlen(buffer), 0);
                    imprimeMensajeSimple("Hasta pronto");
                    break;
                default:
                    imprimePantallaMensajeDoble(
                            "Menu Principal",
                            "Opcion no valida",
                            "Intente nuevamente");
                    break;
            }
        }
    }

    return 0;
}
