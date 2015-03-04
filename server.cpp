#include <iostream>
#include <winsock2.h>
#include <fstream>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
int main()
{
	WSADATA WsaDat;
	if (WSAStartup(MAKEWORD(2, 2), &WsaDat) != 0)
	{
		std::cout << "WSA Initialization failed!\r\n";
		WSACleanup();
		system("PAUSE");
		return 0;
	}

	SOCKET Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (Socket == INVALID_SOCKET)
	{
		std::cout << "Socket creation failed.\r\n";
		WSACleanup();
		system("PAUSE");
		return 0;
	}

	SOCKADDR_IN serverInf;
	serverInf.sin_family = AF_INET;
	serverInf.sin_addr.s_addr = INADDR_ANY;
	serverInf.sin_port = htons(55554);
	if (bind(Socket, (SOCKADDR*)(&serverInf), sizeof(serverInf)) == SOCKET_ERROR)
	{
		std::cout << "Unable to bind socket!\r\n";
		WSACleanup();
		system("PAUSE");
		return 0;
	}
	listen(Socket, 1);
	SOCKET TempSock = SOCKET_ERROR;
	while (TempSock == SOCKET_ERROR)
	{
		std::cout << "Waiting...\r\n";
		TempSock = accept(Socket, NULL, NULL);
	}
	Socket = TempSock;
	std::cout << "Client successful!\r\n\r\n";
	char buffer1[2024];
	memset(buffer1, 0, 999);
	int inDataLength = recv(Socket, buffer1, 1000, 0);

	ofstream myfile("sample1.txt");
	if (myfile.is_open())
	{
		myfile << buffer1;

		myfile.close();
	}
	else cout << "Unable to open file";
	// Shutdown our socket
	shutdown(Socket, SD_SEND);
	// Close our socket entirely
	closesocket(Socket);
	// Cleanup Winsock
	WSACleanup();
	system("PAUSE");
	return 0;
}