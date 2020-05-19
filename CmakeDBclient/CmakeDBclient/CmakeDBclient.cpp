// CmakeDBclient.cpp: определяет точку входа для приложения.
//

#include "CmakeDBclient.h"

using namespace std;

SOCKET podcluchenie;

int main(int argc, char* argv[]) {

	string fname = "adres.txt";
	ifstream input(fname);
	string address_s;
	string port_s;
	getline(input, address_s);

	getline(input, port_s);

	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "oshibka" << std::endl;
		exit(1);
	}
	SOCKADDR_IN addr;
	int razmerada = sizeof(addr);
	//локалхост
	addr.sin_addr.s_addr = inet_addr(address_s.c_str());
	addr.sin_port = htons(stoi(port_s));
	addr.sin_family = AF_INET;

	
	

	//отправляет сообщение на сервер в переменную msg
	char msg1[256];
	while (true) {
		podcluchenie = socket(AF_INET, SOCK_STREAM, NULL);
		std::cout << "vvedite comandu: ";
		std::cin.getline(msg1, sizeof(msg1));
		if (connect(podcluchenie, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
			std::cout << "oshibka podkluchenia k serveru\n";
		}
		else {
			std::cout << "connected\n";
			send(podcluchenie, msg1, sizeof(msg1), NULL);
			Sleep(10);
			closesocket(podcluchenie);
		}
		
	}
	system("pause");
	return 0;
}