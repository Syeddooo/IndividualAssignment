#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int compare_strings(char x[], char y[])
{
	int p = 0;
	while (x[p] == y[p])
	{
		if (x[p] == '\0' || y[p] == '\0')
			break;
		p++;
	}
	if (x[p] == '\0' && y[p] == '\0')
		return 0;
	else 
		return -1;
}

int main(int argc, char *argv[])
{
	int clientSocket;
	char buffer [1024];
	struct sockaddr_in serverAdd;
	socklen_t addr_size;
	
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket == -1) {
		puts ("could not create socket");
		return 1;
	}
	serverAdd.sin_family = AF_INET;
	serverAdd.sin_port = htons(8888);
	serverAdd.sin_addr.s_addr = inet_addr("192.168.56.2");
	memset(serverAdd.sin_zero, '\0', sizeof serverAdd.sin_zero);
	addr_size = sizeof serverAdd;
	
	if (connect(clientSocket, (struct sockaddr *) &serverAdd, sizeof(serverAdd)) < 0)
	{
		puts ("BUDDY FAILED TRY AGAIN NEXT TIME");
	}
	else{
		puts("\n**********  Hello Buddy **********");
	}
	
	
	printf ("Buddy 1: ");
	scanf ("%[^\n]s", buffer);
	send (clientSocket, buffer, sizeof buffer -1,0);
	
	int exit = 0; 
	while (exit == 0)
	{
		if (compare_strings (buffer, "exit")== -1)
		{
			memset (&buffer[0], 0, sizeof (buffer));
			
			int receive = recv (clientSocket, buffer, sizeof buffer -1, 0);
			if (receive != 1)
			{
				if (compare_strings (buffer, "exit") == -1)
				{
					printf ("Buddy 2: ");
					printf ("%s\n", buffer);
					
					memset (&buffer[0], 0, sizeof(buffer));
				}
				
				else exit = 1;
			}
			else
			{
				printf("Buddy 1: ");
				scanf(" %[^\n]s", buffer);
				
			
				send (clientSocket, buffer, sizeof buffer -1, 0);
			}
		}
		else exit = 1;
	}
	return 0;
}
