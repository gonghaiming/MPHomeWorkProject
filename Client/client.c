#include "common.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8888
#define BUFSIZE 2000

INT32 flag = 0;

void *countTime(void* ptr)
{
    while(1)
    {
        sleep(5000);
	if (flag == 0)
		printf("等待超时！\n");
    }
   
    return NULL;
}

int main(int argc, char *argv[])
{
	INT32 threadRe;
	INT32 ret;


 
	INT32 sockFd;
	INT8 sendBuf[BUFSIZE];
	INT8 passWord[BUFSIZE];
	struct sockaddr_in serverAddr;
#if 0
	if(argc != 2)
	{
		printf("未输入服务器地址！");
		return 0;
	}
#endif	

	sockFd = socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&serverAddr, sizeof(struct sockaddr_in));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");


	while(1)
	{
		printf("name:");

		/*清除缓冲区*/
		bzero(&sendBuf, strlen(sendBuf));
		bzero(&md5x, 32);
		bzero(&tmp, 2);
		transNum = 0;
		bzero(&passWord, BUFSIZE);

		fgets(sendBuf, BUFSIZE, stdin);	/*读取用户名*/

		INT32 nameLen = strlen(sendBuf);
		sendBuf[nameLen-1] = '\0';

		fgets(passWord, BUFSIZE, stdin); /*读取密码*/
		INT32 pwdLen = strlen(passWord);
		passWord[pwdLen-1] = '\0';
		

		INT8 hash[33] = {'\0'};
		encrypt(passWord, hash);
	
		pktcontent pcontent[2] = {{'1', nameLen, sendBuf}, {'2', 32, hash}};
		INT16 pktLen = clientSerialized(sendBuf, pcontent);

		sendto(sockFd, sendBuf, pktLen, 0, (struct sockaddr *)(&serverAddr), sizeof(struct sockaddr));
		bzero(sendBuf, BUFSIZE);


		//ret = pthread_create(&threadRe, NULL, countTime, NULL);

		INT32 sendSize;
		INT32 addrLen = sizeof(struct sockaddr);
		sendSize = recvfrom(sockFd, sendBuf, BUFSIZE, 0, (struct sockaddr *)(&serverAddr), &addrLen);
                sendBuf[sendSize] = 0;
		userInfo *pUserInfo;
		deserialized(sendBuf, pUserInfo);
                printf("权限为: %c\n", pUserInfo->previlage);
	}
	
	close(sockFd);
	return 0;
}
