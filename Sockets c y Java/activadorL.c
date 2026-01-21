#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int port;
    
    while (1) {
        printf("introduce el puerto para el activador de luz: ");
        if (scanf("%d", &port) != 1 || port < 1 || port > 65535) {
            printf("puerto no valido. Intenta de nuevo.\n");
            while (getchar() != '\n'); 
        } else {
            break; 
        }
    }

    int sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    char buffer[50];
    socklen_t addr_len = sizeof(client_addr);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port); 
    server_addr.sin_addr.s_addr = INADDR_ANY; 

    if (bind(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error al asociar el socket con la direccion");
        close(sock);
        return 1;
    }

    listen(sock, 3);

    printf("actuador de Luz esperando conexiones en puerto %d...\n", port);

    while (1) {
        client_sock = accept(sock, (struct sockaddr*)&client_addr, &addr_len);
        if (client_sock < 0) {
            perror("Error al aceptar la conexion");
            continue;
        }

        int bytes_received = recv(client_sock, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received > 0) {
            buffer[bytes_received] = '\0'; 
            printf("encender luz con intensidad: %s\n", buffer);
        }
        close(client_sock);
    }
    close(sock);
    return 0;
}





