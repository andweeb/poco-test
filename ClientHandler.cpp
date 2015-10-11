#include "ClientHandler.h"

ClientHandler::ClientHandler(std::string h, int p) : 
	host(h), port(p), socketAddr(h, p), socket(), stream(socket) {
	std::cout << "Host: " << host << "\tPort: " << port << std::endl;	
}

// Connect to the initialized socket address' hostname and port
bool ClientHandler::connected() {
	std::cout << "Creating a connection with [" 
			  << socketAddr.host().toString() 
			  << "] through port [" << socketAddr.port() << "] ..."; 
	try { 
		socket.connect(socketAddr); 
		std::cout << "Success!" << std::endl;
	} 
	catch(Poco::Exception err) {
		std::cout << std::endl;
		std::cout << "Socket connection error: [" << err.displayText() << "]" << std::endl;
		return false;
	}
	return true;
}

// Send a message to the connected server
bool ClientHandler::sendMessage() {
	std::cout << std::endl;
	
	try { 
		std::string message;

		std::cout << "Enter a message to send to the server: ";
		std::cin >> message;

		if(message.compare("exit") != 0) { 
			std::cout << "Sending the message \"" << message << "\" to the server!" << std::endl;
			socket.sendBytes(message.data(), message.size()); 
			return true;
		}
		else return false;
	}
	catch(Poco::Exception err) {
		std::cout << "Data send error: [" << err.displayText() << "]" << std::endl; 
		return false;
	}
}
