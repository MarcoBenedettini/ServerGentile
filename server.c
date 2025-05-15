//server
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 5700

int main(int argc, char const* argv[])
{
    int server_fd, new_socket;
    
    struct sockaddr_in address;
    int opt = 1;
    socklen_t addrlen = sizeof(address);
    char buffer[1024] = { 0 };

	char *responses[] = {
        "Sei così carina",
		"Bel messaggio, buona giornata!",
		"Ti ringrazio per avermi scritto!",
		"Grazie, come sei gentile!"
    };
	
	srand(time(NULL));
	int selected_response = rand() % 4;
	
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Aspettando che qualcuno si connetta.......\n\n");

    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
  
    printf("Qualcuno si e' connesso!\n\n");

    ssize_t msg;   
	
    msg = read(new_socket, buffer, 1024 - 1);
    printf("Client 1:\n\t%s\n", buffer);

	send(new_socket, responses[selected_response], strlen(responses[selected_response]), 0);
    printf("Risposta inviata.\n");
  
    close(new_socket);
    close(server_fd);

    return 0;
}
