#include "common.h"
#include "auth.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <mysql.h>

#define PORT 8888
#define BUFSIZE 2000	/*定义接收缓冲区大小*/





int main(int argc, char *argv[])
{
	INT32 sockFd;
	struct sockaddr_in serverAddr;
	struct sockaddr_in clientAddr;
	INT8 recvBuf[BUFSIZE];	/*接收缓冲区*/
	INT32 addrLen;
	INT32 recvSize;	/*接收到的报文大小*/

	userInfo *pUserInfo;
//	MYSQL *conn;
//	connectSQL(&conn);
	connectSQL(&connection);
//	authentication("hello", "111");
	authentication("hello", "202cb962ac59075b964b07152d234b70");
	
	/*套接字*/
	sockFd = socket(AF_INET, SOCK_DGRAM, 0);

	/*初始化套接字*/
	bzero(&serverAddr, sizeof(struct sockaddr_in));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	/*绑定端口*/
	bind(sockFd, (struct sockaddr *)(&serverAddr), sizeof(struct sockaddr));

	/*开始接收数据*/
	while (1)
	{
		addrLen = sizeof(struct sockaddr);
		bzero(recvBuf, sizeof(recvBuf));
		
		recvSize = recvfrom(sockFd, recvBuf, BUFSIZE, 0, (struct sockaddr *)(&clientAddr), &addrLen);
		recvBuf[recvSize] = 0;
		printf("recv: %s\n", recvBuf);
		
		INT8 retValue;
		INT8 code;
		deserialized(recvBuf, pUserInfo);
		retValue = authentication(pUserInfo->name, pUserINfo->password);
		if (retValue == '0')
		{
			code = 3;
		}
		else
		{
			code = 2;
		}
		
		pktcontent pcontent;
		pcontent.type = '3';
		pcontent.lengthItem = 3;
		pcontent.value[0] = retValue;
		
		bzero(recvBuf, sizeof(recvBuf));
		INT16 pkgLen = serverSerialized(recvBuf, &pcontent);

		/*返送回客户端*/
		sendto(sockFd, recvBuf, pkgLen, 0, (struct sockaddr *)(&clientAddr), addrLen);
	}
	close(sockFd);
	mysql_close(connection);

	return 0;
}
