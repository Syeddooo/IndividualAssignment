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
	int socketDesc, Client1, Client2;
	char buffer [1024];
	struct sockaddr_in serverAdd;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size;
	
	socketDesc = socket(AF_INET, SOCK_STREAM, 0);
	serverAdd.sin_family = AF_INET;
	serverAdd.sin_port = htons(8888);
	serverAdd.sin_addr.s_addr = INADDR_ANY;
	memset(serverAdd.sin_zero, '\0', sizeof serverAdd.sin_zero);
	bind (socketDesc, (struct sockaddr *) &serverAdd, sizeof (serverAdd));
	
	
	if (listen(socketDesc,5)==0)
	{
		puts("\n************** HELLO LADS ***************");
		puts("\n                ~LADS communicating~\n");
	}
	
	else
		
		puts("Error");

	addr_size = sizeof serverStorage;
	Client1 = accept(socketDesc, (struct sockaddr *) &serverStorage, &addr_size);
	Client2 = accept (socketDesc, (struct sockaddr *) &serverStorage, &addr_size);
	
	
	int exit = 0;
	while (exit == 0)
	{
		recv(Client1, buffer , 1024, 0);
		printf ("%s\n  ~~Buddy1 send Budddy2 a message!~~\n", buffer);
		send (Client2, buffer , 1024, 0);
		
		if (compare_strings (buffer,"exit")== 0)
		{
			exit = 1;
		}
		else
		{
			memset (&buffer[0], 0, sizeof (buffer));
			
			recv (Client2, buffer, 1024, 0);
			printf ("%s\n  ~~Buddy2 send Buddy1 a message!~~\n", buffer);
			send (Client1, buffer, 1024, 0);
			
			if (compare_strings (buffer, "exit") == 0)
			{
				exit = 1;
			}
		}
	}
	
	return 0;
}
