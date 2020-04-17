/* Client UDP */

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>


int main(int argc, char* argv[])
{	
	int n, somma;
	struct sockaddr_in server;
	
	
	if(argc < 3)
	{
		printf("Uso: ./somma_client IP_dest Porta_dest\n");
		return 0;
	}
	
	
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd < 0)
	{
		printf("Errore nell'apertura della connessione ... esco!\n");
		return -1;
	}
	
	
	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	inet_pton(AF_INET, argv[1], &(server.sin_addr));
	server.sin_port = htons(atoi(argv[2]));
	
	
	printf("++++++ Programma di rete per fare le somme ++++++\n\n");
	
	
	printf("Quanti numeri vuoi sommare? ");
	scanf("%d", &n);
	int buffer[n];
	
	
	printf("Inserisci i tuoi numeri:\n");
	for(int i=0; i<n; i++)
		scanf("%d", &buffer[i]);
	
	
	sendto(sockfd, &n, sizeof(int), 0, (struct sockaddr *) &server, sizeof(server));
	sendto(sockfd, buffer, n*sizeof(int), 0, (struct sockaddr *) &server, sizeof(server));
	
	
	recvfrom(sockfd, &somma, sizeof(int), 0, NULL, NULL);
	printf("La somma e': %d\n", somma);
	printf("Buon lavoro... esco!\n");
}
