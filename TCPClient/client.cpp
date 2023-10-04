#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>

using namespace std;



#include <WinSock2.h>

#pragma comment(lib, "ws2_32")

int main()
{
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET ServerSocket = socket(PF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN ServerSock;
	ZeroMemory(&ServerSock, 0);
	ServerSock.sin_family = AF_INET;
	ServerSock.sin_addr.s_addr = inet_addr("127.0.0.1");
	ServerSock.sin_port = htons(5001);


	int Result = connect(ServerSocket, (SOCKADDR*)&ServerSock, sizeof(ServerSock));
	if (Result == SOCKET_ERROR)
	{
		cout << "connect Error" << endl;
		cout << "Socket Error Number : " << GetLastError() << endl;
		exit(-1);
	}

	char Buffer[1024] = { 0, };

	int RecvByte = recv(ServerSocket, Buffer, sizeof(Buffer), 0);
	if (RecvByte <= 0)
	{
		cout << "recv Error" << endl;
		cout << "Socket Error Number : " << GetLastError() << endl;
		exit(-1);
	}

	cout << "Recv : " << Buffer << endl;

	char Message[1024] = "give me message";

	int SendByte = send(ServerSocket, Message, (int)strlen(Message), 0);
	if (SendByte <= 0)
	{
		cout << "send Error" << endl;
		cout << "Socket Error Number : " << GetLastError() << endl;
		exit(-1);
	}

	closesocket(ServerSocket);

	WSACleanup();

	return 0;
}
