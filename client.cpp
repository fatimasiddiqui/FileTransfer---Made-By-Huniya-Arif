#include <iostream>
#include <fstream>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
int main()
{
	// Initialise Winsock
	WSADATA WsaDat;
	if (WSAStartup(MAKEWORD(2, 2), &WsaDat) != 0)
	{
		std::cout << "Winsock error - Winsock initialization failed\r\n";
		WSACleanup();
		system("PAUSE");
		return 0;
	}

	// Create our socket
	SOCKET Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (Socket == INVALID_SOCKET)
	{
		std::cout << "Winsock error - Socket creation Failed!\r\n";
		WSACleanup();
		system("PAUSE");
		return 0;
	}
	// Resolve IP address for hostname
	struct hostent *host;
	if ((host = gethostbyname("localhost")) == NULL)
	{
		std::cout << "Failed to resolve hostname.\r\n";
		WSACleanup();
		system("PAUSE");
		return 0;
	}
	// Setup our socket address structure
	SOCKADDR_IN SockAddr;
	SockAddr.sin_port = htons(55554);
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);
	// Attempt to connect to server
	if (connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0)
	{
		std::cout << "Failed to establish connection with server\r\n";
		WSACleanup();
		system("PAUSE");
		return 0;
	}
	// Display message from server
	char buffer[1000];
	char filename[256];


	cout << "Please enter the filename:" << endl;
	cin >> filename;
	ifstream file;
	file.open(filename);		//open the file

	if (file.is_open()){
		file.seekg(0, ios::end);
		int size = file.tellg();	//file size! 
		file.seekg(0, ios::beg);		//sets location back to beginning of file

		char* rbuffer = new char[size];
		file.read(rbuffer, size);		//write file to buffer

		int j = send(Socket, rbuffer, strlen(rbuffer), 0);	//send file to server

	}
	// Shutdown our socket
	shutdown(Socket, SD_SEND);
	// Close our socket entirely
	closesocket(Socket);
	// Cleanup Winsock
	WSACleanup();
	system("PAUSE");
	return 0;
}