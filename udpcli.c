#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define  SERV_PORT	22222
#define  MAXLINE	80

void process(FILE *fp, int sockfd, const struct sockaddr *pservaddr, 
             socklen_t servlen);


int
main(int argc, char **argv)
{
	int			sockfd;
	struct sockaddr_in	servaddr;

	if (argc != 2) {
		printf("usage: udpcli <IPaddress>\n");
		exit (0);
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	process(stdin, sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	exit(0);
}

void
process(FILE *fp, int sockfd, const struct sockaddr *pservaddr, socklen_t servlen)
{
        char                    sendline[MAXLINE];
        char   string1[MAXLINE], string2[MAXLINE];

        while (fgets(sendline, MAXLINE, fp) != NULL) {

                sendto(sockfd, sendline, strlen(sendline), 0, 
                                                pservaddr, servlen);

        }

}
