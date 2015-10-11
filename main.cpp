#include "ClientHandler.h"

void noop() {};

int main(int argc, char** argv) {
	int port = 8007;
	std::string hostname = "127.0.0.1";

	// Handle the server-client connection and send some json
	ClientHandler handler(hostname, port);
	if(handler.connected()) 
		while(handler.sendMessage());

	return 0;
}
