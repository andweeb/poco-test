CC = g++
CFLAGS = -Wall -Werror 
INC = -I/usr/local/poco/Net/include \
	      -I/usr/local/poco/Foundation/include \
		  -I/usr/local/poco/JSON/include
LIB = -L/usr/local/poco/lib/Linux/x86_64
LINK = -lPocoFoundation -lPocoNet -lPocoJSON
SRC = main.cpp ClientHandler.cpp

main: 
	$(CC) $(CFLAGS) $(INC) -o main $(SRC) $(DEPS) $(LIB) $(LINK)

clean:
	rm main main.o 
