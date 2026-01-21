#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char message[50];
    
    char ip[20];
    int port;

   
    while (1) {
        printf("introduce la IP del servidor: ");
        scanf("%s", ip);
        if (inet_addr(ip) == INADDR_NONE) {
            printf("IP no valida. intenta de nuevo.\n");
        } else {
            break;
        }
    }
    
    while (1) {
        printf("introduce el puerto del servidor: ");
        if (scanf("%d", &port) != 1 || port < 1 || port > 65535) {
            printf("puerto no válido. Intenta de nuevo.\n");
            while (getchar() != '\n'); 
        } else {
            break;
        }
    }

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    srand(time(NULL));

    while (1) {
        int tipo;
        int medida;
        char tipoMedida[20];

        printf("seleccione el tipo que quiere (1 = Temp | 2 = luz | 3 = salir): ");
        scanf("%d", &tipo);

        if (tipo == 1) {
            medida = (rand() % 16 + 15);
            strcpy(tipoMedida, "temperatura");
        } else if (tipo == 2) {
            medida = (rand() % 201 + 100);
            strcpy(tipoMedida, "luz");
        } else if (tipo == 3) {
            printf("cerrando\n");
            break;
        } else {
            printf("error\n");
            continue;
        }

        sprintf(message, "%s:%d", tipoMedida, medida);
        sendto(sock, message, strlen(message), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));

        printf("sensor envio: %s\n", message);
    }

    close(sock);
    return 0;
}

