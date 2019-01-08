#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SERV_PORT 23456
#define MAXLINE 80

void process(FILE *FP, int sockfd);

int
main(int argc, char **argv)
{
	int	sockfd;
	struct sockaddr_in	servaddr;

	if (argc != 2) {
		printf("usage: tcpcli <IPaddress>");
		exit (0);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	process(stdin, sockfd);		/* do it all */

	exit(0);
}

void process(FILE *fp, int sockfd)
{
        char  sendline[MAXLINE];
        char  string1[MAXLINE], string2[MAXLINE];

        while (fgets(sendline, MAXLINE, fp) != NULL)
	 {

                write(sockfd, sendline, sizeof(sendline));

            if (read(sockfd, string2, sizeof(string2)) == 0) 		      	{
                printf("Client: server terminated prematurely");
			exit (0);
		}

                printf("Server says %s\n", string2);
        }
}
