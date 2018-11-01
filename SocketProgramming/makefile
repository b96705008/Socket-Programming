all: compile_aws compile_client compile_monitor compile_serverA compile_serverB compile_serverC

clean: 
	-rm *.o prog_* client

serverA: prog_serverA
	./prog_serverA

serverB: prog_serverB
	./prog_serverB

serverC: prog_serverC
	./prog_serverC

aws: prog_aws
	./prog_aws

monitor: prog_monitor
	./prog_monitor

compile_aws: aws.o UDPSocket.o LinkDataset.o LinkData.o DataParser.o TCPServerSocket.o TCPChildSocket.o
	g++ -g -o prog_aws aws.o UDPSocket.o LinkDataset.o LinkData.o DataParser.o TCPServerSocket.o TCPChildSocket.o

compile_client: client.o
	g++ -g -o client client.o

compile_monitor: monitor.o DataParser.o
	g++ -g -o prog_monitor monitor.o DataParser.o

compile_serverA: serverA.o UDPSocket.o LinkDataset.o LinkData.o DataParser.o
	g++ -g -o prog_serverA serverA.o UDPSocket.o LinkDataset.o LinkData.o DataParser.o

compile_serverB: serverB.o UDPSocket.o LinkDataset.o LinkData.o DataParser.o
	g++ -g -o prog_serverB serverB.o UDPSocket.o LinkDataset.o LinkData.o DataParser.o

compile_serverC: serverC.o UDPSocket.o ComputedLinkData.o LinkData.o DataParser.o
	g++ -g -o prog_serverC serverC.o UDPSocket.o ComputedLinkData.o LinkData.o DataParser.o

aws.o: aws.cpp LinkData.hpp UDPSocket.hpp DataParser.hpp defs.h
	g++ -g -c aws.cpp

client.o: client.cpp defs.h
	g++ -g -c client.cpp

monitor.o: monitor.cpp DataParser.hpp defs.h 
	g++ -g -c monitor.cpp

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


