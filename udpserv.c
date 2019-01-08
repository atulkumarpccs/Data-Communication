#include <sys/socket.h>
#include <netinet/in.h>

#define SERV_PORT	22222
#define MAXLINE		80

void process(int sockfd, struct sockaddr *pcliaddr, socklen_t clilen);

int
main(int argc, char **argv)
{
	int					sockfd;
	struct sockaddr_in	servaddr, cliaddr;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(SERV_PORT);

	bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	process(sockfd, (struct sockaddr *) &cliaddr, sizeof(cliaddr));
}

void
process(int sockfd, struct sockaddr *pcliaddr, socklen_t clilen)
{
        socklen_t       len;
        char            mesg[MAXLINE];

        for ( ; ; ) {
                len = clilen;
                recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len);
		printf ("Client says: %s", mesg) ;
        }
}
