CXX=g++

CargoSim : main.o Cargo.o CargoShip.o Client.o Fleet.o MainCargoControl.o MainVesselControl.o test_main.o
	$(CXX) -std=c++11 -o CargoSim main.o Cargo.o CargoShip.o Client.o Fleet.o MainCargoControl.o MainVesselControl.o test_main.o

main.o : main.cpp
	$(CXX) -std=c++11 -c main.cpp

Cargo.o : Cargo.cpp Cargo.h
	$(CXX) -std=c++11 -c Cargo.cpp

CargoShip.o : CargoShip.cpp CargoShip.h
	$(CXX) -std=c++11 -c CargoShip.cpp

Client.o : Client.cpp Client.h
	$(CXX) -std=c++11 -c Client.cpp

Fleet.o : Fleet.cpp Fleet.h
	$(CXX) -std=c++11 -c Fleet.cpp

MainCargoControl.o : MainCargoControl.cpp MainCargoControl.h
	$(CXX) -std=c++11 -c MainCargoControl.cpp

MainVesselControl.o : MainVesselControl.cpp MainVesselControl.h
	$(CXX) -std=c++11 -c MainVesselControl.cpp

test_main.o : test_main.cpp test_main.h
	$(CXX) -std=c++11 -c test_main.cpp

.PHONY : clean
clean:
	-rm *.o
