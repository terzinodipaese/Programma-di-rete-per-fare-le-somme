/* Server UDP */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>



int main(int argc, char* argv[])
{
	int sockfd, n, somma; 
	socklen_t len = sizeof(struct sockaddr_in);
	struct sockaddr_in locale, remoto;
	
	somma = 0;
	
	if(argc < 2)
	{
		printf("Uso: ./somma_server listening_port\n");
		return 0;
	}
	
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd < 0)
	{
		printf("Errore nell'apertura della connessione ... esco!");
		return -1;
	}
	
	memset(&locale, 0, sizeof(locale));
	memset(&remoto, 0, sizeof(remoto));
	
	locale.sin_family = AF_INET;
	locale.sin_port = htons(atoi(argv[1]));
	
	bind(sockfd, (struct sockaddr *) &locale, len);
	
	recvfrom(sockfd, &n, sizeof(int), 0, (struct sockaddr *) &remoto, &len);
	printf("Ricevuta richiesta di servizio dalla macchina %s\n", inet_ntoa(remoto.sin_addr));
	printf("%s richiede la somma di %d numeri\n", inet_ntoa(remoto.sin_addr), n);
	
	int buffer[n];
	
	recvfrom(sockfd, buffer, n*sizeof(int), 0, (struct sockaddr *) &remoto, &len);
	
	for(int i=0; i<n; i++)
		somma += buffer[i];
	
	sendto(sockfd, &somma, sizeof(int), 0, (struct sockaddr *) &remoto, sizeof(remoto));
	printf("Fine servizio...\n");
}
