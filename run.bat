g++ -c Representation.cpp -O3
g++ -c Graph.cpp -O3
g++ -c main.cpp -O3
g++ Representation.o Graph.o main.o -O3 -o main.exe
.\main.exe