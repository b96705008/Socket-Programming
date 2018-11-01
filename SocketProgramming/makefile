binaries=aws client serverA serverB serverC

all: $(binaries)

clean: 
	-rm *.o $(binaries)

aws: aws.o UDPSocket.o LinkDataset.o LinkData.o DataParser.o TCPServerSocket.o TCPChildSocket.o
	g++ -g -o aws aws.o UDPSocket.o LinkDataset.o LinkData.o DataParser.o TCPServerSocket.o TCPChildSocket.o

client: client.o
	g++ -g -o client client.o

serverA: serverA.o UDPSocket.o LinkDataset.o LinkData.o DataParser.o
	g++ -g -o serverA serverA.o UDPSocket.o LinkDataset.o LinkData.o DataParser.o

serverB: serverB.o UDPSocket.o LinkDataset.o LinkData.o DataParser.o
	g++ -g -o serverB serverB.o UDPSocket.o LinkDataset.o LinkData.o DataParser.o

serverC: serverC.o UDPSocket.o ComputedLinkData.o LinkData.o DataParser.o
	g++ -g -o serverC serverC.o UDPSocket.o ComputedLinkData.o LinkData.o DataParser.o

aws.o: aws.cpp LinkData.hpp UDPSocket.hpp DataParser.hpp defs.h
	g++ -g -c aws.cpp

client.o: client.cpp defs.h
	g++ -g -c client.cpp

serverA.o: serverA.cpp UDPSocket.hpp LinkData.hpp defs.h
	g++ -g -c serverA.cpp

serverB.o: serverB.cpp UDPSocket.hpp LinkData.hpp defs.h
	g++ -g -c serverB.cpp

serverC.o: serverC.cpp UDPSocket.hpp ComputedLinkData.hpp DataParser.hpp defs.h
	g++ -g -c serverC.cpp

UDPSocket.o: UDPSocket.cpp UDPSocket.hpp defs.h
	g++ -g -c UDPSocket.cpp

TCPServerSocket.o: TCPServerSocket.cpp TCPServerSocket.hpp defs.h
	g++ -g -c TCPServerSocket.cpp

TCPChildSocket.o: TCPChildSocket.cpp TCPChildSocket.hpp defs.h
	g++ -g -c TCPChildSocket.cpp

LinkDataset.o: LinkDataset.cpp LinkDataset.hpp
	g++ -g -c LinkDataset.cpp

LinkData.o: LinkData.cpp LinkData.hpp
	g++ -g -c LinkData.cpp

DataParser.o: DataParser.cpp DataParser.hpp
	g++ -g -c DataParser.cpp

ComputedLinkData.o: ComputedLinkData.cpp ComputedLinkData.hpp LinkData.cpp LinkData.hpp
	g++ -g -c ComputedLinkData.cpp


