#include <sys/socket.h>
#include <netinet/in.h>

#define SERV_PORT	23456

void process(int sockfd);


int main(int argc, char **argv)
{
	int	listenfd, connfd;
	pid_t		childpid;
	socklen_t	clilen;
	struct sockaddr_in	cliaddr, servaddr;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(SERV_PORT);

	bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	listen(listenfd, 5);

	for ( ; ; ) {
		clilen = sizeof(cliaddr);
		connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);

		if ( (childpid = fork()) == 0) {	/* child process */
			close(listenfd);	/* close listening socket */
			process(connfd);	/* process the request */
			exit(0);
		}
		close(connfd);			/* parent closes connected socket */
	}
}

void process(int sockfd)
{
        ssize_t                 n;
        char buffer1[80], buffer2[]="Thanks for calling...";

        for ( ; ; ) {
                if ( (n = recv(sockfd, buffer1, sizeof(buffer1),0)) == 0)
                        return;         /* connection closed by other end */
		printf ("Server: Received %s", buffer1);
                send(sockfd, buffer2, sizeof(buffer2),0);
        }

}
