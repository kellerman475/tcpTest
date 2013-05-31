// ClientTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <time.h>
#pragma comment(lib, "ws2_32.lib")

#define SERVER_PORT 8087 //�����˿�


int _tmain(int argc, _TCHAR* argv[])
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int ret;
	SOCKET sClient; //�����׽���
	struct sockaddr_in saServer; //��������ַ��Ϣ
	char *ptr;
	BOOL fSuccess = TRUE;

	//WinSock��ʼ��
	wVersionRequested = MAKEWORD(2, 2); //ϣ��ʹ�õ�WinSock DLL�İ汾
	ret = WSAStartup(wVersionRequested, &wsaData);	//�����׽��ֿ�
	if(ret!=0)
	{
		printf("WSAStartup() failed!\n");
		//return 0;
	}
	//ȷ��WinSock DLL֧�ְ汾2.2
	if(LOBYTE(wsaData.wVersion)!=2 || HIBYTE(wsaData.wVersion)!=2)
	{
		WSACleanup();	//�ͷ�Ϊ�ó���������Դ����ֹ��winsock��̬���ʹ��
		printf("Invalid WinSock version!\n");
		//return 0;
	}

	//����Socket,ʹ��TCPЭ��
	sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sClient == INVALID_SOCKET)
	{
		WSACleanup();
		printf("socket() failed!\n");
		//return 0;
	}

	//������������ַ��Ϣ
	saServer.sin_family = AF_INET; //��ַ����
	saServer.sin_port = htons(SERVER_PORT); //ע��ת��Ϊ�������
	saServer.sin_addr.S_un.S_addr = inet_addr("192.168.133.133");

	//���ӷ�����
	ret = connect(sClient, (struct sockaddr *)&saServer, sizeof(saServer));
	if (ret == SOCKET_ERROR)
	{
		printf("connect() failed!\n");
		closesocket(sClient); //�ر��׽���
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
	closesocket(sClient); //�ر��׽���
	WSACleanup();
	getchar();
	//return 0;
}

