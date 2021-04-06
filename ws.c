#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include<string.h>
#include <fcntl.h>
 

int listen_fd, comm_fd;

int main()
{
    //char str[100];
    char x;
    char catch = 13;
    char catch2 = 10;
    char prev = 0;
    int count = 0;
    struct sockaddr_in servaddr;
 
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    bzero( &servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    servaddr.sin_port = htons(8080);
 
    bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
 
    listen(listen_fd, 10);
 
    comm_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);
 
    while(1 == read(comm_fd, &x, 1))
    {   

	printf("%c", x);
	if ((x == catch2) && (catch == prev))
	{
		if (count > 7)
		{

			int fd;
			char c;
			fd = open("webpage.html", O_RDONLY);
			char http200[] = "HTTP/1.1 200 OK\r\n Content-Type: text/html\r\n \r\n";
			write(comm_fd, &http200, strlen(http200));
			while( 1 == read(fd, &c, 1))
			{
				write(comm_fd, &c, 1);
			}
			close(fd);
			break;
		}
		count++;
	}
	prev = x;
	


    }
}
