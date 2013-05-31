// ClientTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <time.h>
#pragma comment(lib, "ws2_32.lib")

#define SERVER_PORT 8087 //侦听端口


int _tmain(int argc, _TCHAR* argv[])
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int ret;
	SOCKET sClient; //连接套接字
	struct sockaddr_in saServer; //服务器地址信息
	char *ptr;
	BOOL fSuccess = TRUE;

	//WinSock初始化
	wVersionRequested = MAKEWORD(2, 2); //希望使用的WinSock DLL的版本
	ret = WSAStartup(wVersionRequested, &wsaData);	//加载套接字库
	if(ret!=0)
	{
		printf("WSAStartup() failed!\n");
		//return 0;
	}
	//确认WinSock DLL支持版本2.2
	if(LOBYTE(wsaData.wVersion)!=2 || HIBYTE(wsaData.wVersion)!=2)
	{
		WSACleanup();	//释放为该程序分配的资源，终止对winsock动态库的使用
		printf("Invalid WinSock version!\n");
		//return 0;
	}

	//创建Socket,使用TCP协议
	sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sClient == INVALID_SOCKET)
	{
		WSACleanup();
		printf("socket() failed!\n");
		//return 0;
	}

	//构建服务器地址信息
	saServer.sin_family = AF_INET; //地址家族
	saServer.sin_port = htons(SERVER_PORT); //注意转化为网络节序
	saServer.sin_addr.S_un.S_addr = inet_addr("192.168.133.133");

	//连接服务器
	ret = connect(sClient, (struct sockaddr *)&saServer, sizeof(saServer));
	if (ret == SOCKET_ERROR)
	{
		printf("connect() failed!\n");
		closesocket(sClient); //关闭套接字
		WSACleanup();
		//return 0;
	}
	while(1)
	{
	   ret = send (sClient, "123", 5, 0);
	if (ret == SOCKET_ERROR)
	{
		printf("send() failed!\n");
	}
	else
		printf("client info has been sent!");
	char recvBuf[100];
	recv(sClient,recvBuf,100,0);
	printf("%s\n",recvBuf);
	Sleep(1000);
	}
	closesocket(sClient); //关闭套接字
	WSACleanup();
	getchar();
	//return 0;
}

