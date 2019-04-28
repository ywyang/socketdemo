/*
 * server.c为服务器端代码
*/

#include "config.h"

int main(int argc , char **argv)
{
	//int i;

	if(argc >1)
	{
		if(strcmp(argv[1],"--help")==0)
		{
			printf("USAGE: socketServer [option] value \r\n");
			printf("\r\nOPTIONS:\r\n");
			printf("\tno option use 6000 as default port\r\n");
			printf("\t--help\r\n");
			printf("\t-p value\r\n");
			return 0;
		}
		if(argc ==3)
		{
			if(strcmp(argv[1],"-p")==0)
			{
				PORT=atoi(argv[2]);
				//printf("port is %d",PORT);
			}

		}
	}
//	     printf("Total %d arguments\n", argc);
//    for(i=0; i<argc; i++)
//    {
//        printf("Argument %d = %s\n", i+1, argv[i]);
//    }

	/*声明服务器地址和客户链接地址*/
	struct sockaddr_in servaddr , cliaddr;

	/*声明服务器监听套接字和客户端链接套接字*/
	int listenfd , connfd;
	pid_t childpid;

	/*声明缓冲区*/
	char buf[MAX_LINE];

	socklen_t clilen;

	/*(1) 初始化监听套接字listenfd*/
	if((listenfd = socket(AF_INET , SOCK_STREAM , 0)) < 0)
	{
		perror("socket error");
		exit(1);
	}//if

	/*(2) 设置服务器sockaddr_in结构*/
	bzero(&servaddr , sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); //表明可接受任意IP地址
	servaddr.sin_port = htons(PORT);

	/*(3) 绑定套接字和端口*/
	if(bind(listenfd , (struct sockaddr*)&servaddr , sizeof(servaddr)) < 0)
	{
		perror("bind error");
		exit(1);
	}//if
	else
	{
		printf("Socket start listen at port %d \r\n",PORT);
	}

	/*(4) 监听客户请求*/
	if(listen(listenfd , LISTENQ) < 0)
	{
		perror("listen error");
		exit(1);
	}//if

	/*(5) 接受客户请求*/
	for( ; ; )
	{
		clilen = sizeof(cliaddr);
		if((connfd = accept(listenfd , (struct sockaddr *)&cliaddr , &clilen)) < 0 )
		{
			perror("accept error");
			exit(1);
		}//if

		//新建子进程单独处理链接
		if((childpid = fork()) == 0) 
		{
			close(listenfd);
			//str_echo
			ssize_t n;
			char buff[MAX_LINE];
			while((n = read(connfd , buff , MAX_LINE)) > 0)
			{
				printf("Recive msg by client :%s",buff);
				char writebuff[MAX_LINE]="";
				char readbuff[MAX_LINE]="";
				strncpy(readbuff,buff,strlen(buff)-1);
				sprintf(writebuff , "msg:%s send success\r\n" , readbuff);
				write(connfd , writebuff , strlen(writebuff));
			}
			exit(0);
		}//if
		close(connfd);
	}//for
	
	/*(6) 关闭监听套接字*/
	close(listenfd);
}
