#include <iostream>

using namespace std;

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>

#pragma comment(lib, "ws2_32")

int main()
{
	WSAData wsaData;
	int Result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (Result != 0)
	{
		cout << "Error" << endl;
		exit(-1);
	}

	SOCKET ServerSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ServerSocket == INVALID_SOCKET)
	{
		cout << "Socket Error" << endl;
		cout << "Socket Error Number : " <<  GetLastError() << endl;
		exit(-1);
	}
	SOCKADDR_IN ServerSock;
	memset(&ServerSock, 0, sizeof(SOCKADDR_IN));
	ServerSock.sin_family = AF_INET;
	ServerSock.sin_port = htons(5001);
	ServerSock.sin_addr.s_addr = INADDR_ANY;

	Result = bind(ServerSocket, (SOCKADDR*)&ServerSock, sizeof(ServerSock));
	if (Result == SOCKET_ERROR)
	{
		cout << "bind Error" << endl;
		cout << "Socket Error Number : " << GetLastError() << endl;
		exit(-1);
	}

	Result = listen(ServerSocket, 5);
	if (Result == SOCKET_ERROR)
	{
		cout << "listen Error" << endl;
		cout << "Socket Error Number : " << GetLastError() << endl;
		exit(-1);
	}

	while (true)
	{
		SOCKADDR_IN ClientSock;
		memset(&ClientSock, 0, sizeof(SOCKADDR_IN));
		int ClientSockLength = sizeof(ClientSock);

		SOCKET ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientSock, &ClientSockLength);
		if (ClientSocket == INVALID_SOCKET)
		{
			cout << "accept Error" << endl;
			cout << "Socket Error Number : " << GetLastError() << endl;
			exit(-1);
		}

		char Message[] = "show me the money";

		int SendByte = send(ClientSocket, Message, (int)strlen(Message), 0);
		if (SendByte <= 0)
		{
			cout << "send Error" << endl;
			cout << "Socket Error Number : " << GetLastError() << endl;
			exit(-1);
		}

		char Buffer[1024] = { 0, };

		int RecvByte = recv(ClientSocket, Buffer, sizeof(Buffer), 0);
		if (RecvByte <= 0)
		{
			cout << "recv Error" << endl;
			cout << "Socket Error Number : " << GetLastError() << endl;
			exit(-1);
		}

		cout << "client send : " << Buffer << endl;


		closesocket(ClientSocket);
	}
	closesocket(ServerSocket);

	WSACleanup();

	return 0;
}

