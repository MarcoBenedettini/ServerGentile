//client
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 5700
#define IP "192.168.10.125"

int main(int argc, char const* argv[])
{
    int status, valread, client_fd;
    struct sockaddr_in serv_addr;
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    char buffer[1024] = { 0 };

    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
    
    if (inet_pton(AF_INET, IP, &serv_addr.sin_addr)
        <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if ((status = connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)))
        < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    printf("\tConnessione con server avvenuta con successo\n\tBenvenuto nella chat\n\n");
    

    char msg[100];
    fgets(msg, 100, stdin);

    send(client_fd, msg, strlen(msg), 0);
    printf("-- Messaggio inviato --\n\n");
        
    strcpy(msg, "");
	
	read(client_fd, buffer, 1024);
	printf("risposta dal server: %s\n", buffer);

    // closing the connected socket
    close(client_fd);
    return 0;
}
