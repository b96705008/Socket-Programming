all: compile_aws compile_client compile_monitor compile_serverA compile_serverB compile_serverC

binaries = prog_serverA prog_serverB prog_serverC prog_aws prog_monitor client

.PHONY: binaries

clean: 
	-rm *.o $(binaries)

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

compile_aws: aws.o udpsocket.o linkdataset.o linkdata.o dataparser.o tcpserversocket.o tcpchildsocket.o
	g++ -std=c++11 -g -o prog_aws aws.o udpsocket.o linkdataset.o linkdata.o dataparser.o tcpserversocket.o tcpchildsocket.o

compile_client: client.o
	g++ -std=c++11 -g -o client client.o

compile_monitor: monitor.o dataparser.o
	g++ -std=c++11 -g -o prog_monitor monitor.o dataparser.o

compile_serverA: serverA.o udpsocket.o linkdataset.o linkdata.o dataparser.o
	g++ -std=c++11 -g -o prog_serverA serverA.o udpsocket.o linkdataset.o linkdata.o dataparser.o

compile_serverB: serverB.o udpsocket.o linkdataset.o linkdata.o dataparser.o
	g++ -std=c++11 -g -o prog_serverB serverB.o udpsocket.o linkdataset.o linkdata.o dataparser.o

compile_serverC: serverC.o udpsocket.o computedlinkdata.o linkdata.o dataparser.o
	g++ -std=c++11 -g -o prog_serverC serverC.o udpsocket.o computedlinkdata.o linkdata.o dataparser.o

aws.o: aws.cpp linkdata.h udpsocket.h dataparser.h defs.h
	g++ -std=c++11 -g -c aws.cpp

client.o: client.cpp defs.h
	g++ -std=c++11 -g -c client.cpp

monitor.o: monitor.cpp dataparser.h defs.h 
	g++ -std=c++11 -g -c monitor.cpp

serverA.o: serverA.cpp udpsocket.h linkdata.h defs.h
	g++ -std=c++11 -g -c serverA.cpp

serverB.o: serverB.cpp udpsocket.h linkdata.h defs.h
	g++ -std=c++11 -g -c serverB.cpp

serverC.o: serverC.cpp udpsocket.h computedlinkdata.h dataparser.h defs.h
	g++ -std=c++11 -g -c serverC.cpp

udpsocket.o: udpsocket.cpp udpsocket.h defs.h
	g++ -std=c++11 -g -c udpsocket.cpp

tcpserversocket.o: tcpserversocket.cpp tcpserversocket.h defs.h
	g++ -std=c++11 -g -c tcpserversocket.cpp

tcpchildsocket.o: tcpchildsocket.cpp tcpchildsocket.h defs.h
	g++ -std=c++11 -g -c tcpchildsocket.cpp

linkdataset.o: linkdataset.cpp linkdataset.h
	g++ -std=c++11 -g -c linkdataset.cpp

linkdata.o: linkdata.cpp linkdata.h
	g++ -std=c++11 -g -c linkdata.cpp

dataparser.o: dataparser.cpp dataparser.h
	g++ -std=c++11 -g -c dataparser.cpp

computedlinkdata.o: computedlinkdata.cpp computedlinkdata.h linkdata.cpp linkdata.h
	g++ -std=c++11 -g -c computedlinkdata.cpp


