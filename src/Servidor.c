#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

#define bzero(b, len) (memset((b), '\0', (len)), (void)0) // Crea un buffer de tamaño len y lo llena de 0, actualmente bzero esta obsoleto, un macro lo remplaza por memset

#define PORT 4444

int main()
{
	FILE *archivo;
	int sockfd, ret;
	struct sockaddr_in serverAddr;

	char name[1024];
	char nameFile[1024];
	char t[20];
	char val[20];

	char *token;

	char file_vector[30][15];
	char c;

	int newSocket;
	struct sockaddr_in newAddr;

	socklen_t addr_size;

	char buffer[1024];
	pid_t childpid;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Servidor de Socket creado.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
	if (ret < 0)
	{
		printf("[-]Error en el enlace.\n");
		exit(1);
	}
	printf("[+]Enlazado al puerto %d\n", 4444);

	if (listen(sockfd, 10) == 0)
	{
		printf("[+]Esperando...\n");
	}
	else
	{
		printf("[-]Error en el enlace.\n");
	}

	while (1)
	{
		newSocket = accept(sockfd, (struct sockaddr *)&newAddr, &addr_size);
		if (newSocket < 0)
		{
			exit(1);
		}
		printf("Conexion aceptada de %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));

		if ((childpid = fork()) == 0)
		{
			close(sockfd);
			recv(newSocket, buffer, 1024, 0);
			strcpy(name, buffer);

			strcpy(nameFile, name);
			strcat(nameFile, ".dat");

			printf("%s\n", nameFile);

			bzero(buffer, sizeof(buffer));
			while (1)
			{
				recv(newSocket, buffer, 1024, 0);
				int op = 0;
				if (strcmp(buffer, ":exit") == 0)
				{
					op = 3;
					break;
				}
				else
				{
					if (strcmp(buffer, "grafica1") == 0)
					{
						op = 2;
					}
					else if (strcmp(buffer, "grafica2") == 0)
					{
						op = 4;
					}
					else
					{
						op = 1;
					}
				}
				switch (op)
				{
				case 1:
					archivo = fopen(nameFile, "a");
					strcat(buffer, "\n");
					fputs(buffer, archivo);
					printf("Client[%s]: %s\n", name, buffer);
					bzero(buffer, sizeof(buffer));
					fclose(archivo);
					break;
				case 2:

					FILE *fich;
					if ((fich = fopen(nameFile, "r")) == NULL)
					{
						printf(" Error en la apertura. Es posible que el archivo no exista \n ");
					}
					c = fgetc(fich);
					int contador = 0;
					while (c != EOF)
					{
						for (int i = 0; i < 14; i++)
						{
							file_vector[contador][i] = c;
							c = fgetc(fich);
						}

						contador++;
						c = fgetc(fich);
					}
					for (int i = contador - 1; i >= contador - 7; i--)
					{

						if (i >= 0)
						{
							send(newSocket, file_vector[i], 14, 0);
						}
						else
						{
							break;
						}
					}

					fclose(fich);
					send(newSocket, ":exit", 14, 0);

					break;
				case 3:
					printf("Desconectado de %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
					fclose(archivo);
					close(newSocket);
					break;
				case 4:

					if ((fich = fopen(nameFile, "r")) == NULL)
					{
						printf(" Error en la apertura. Es posible que el archivo no exista \n ");
					}
					c = fgetc(fich);
					contador = 0;
					while (c != EOF)
					{
						for (int i = 0; i < 14; i++)
						{
							file_vector[contador][i] = c;
							c = fgetc(fich);
						}

						contador++;
						c = fgetc(fich);
					}
					for (int i = contador - 1; i >= contador - 30; i--)
					{
						if (i >= 0)
						{
							send(newSocket, file_vector[i], 14, 0);
						}
						else
						{
							break;
						}
					}

					fclose(fich);
					send(newSocket, ":exit", 14, 0);

					break;
				default:
					break;
				}
			}
		}
	}

	return 0;
}