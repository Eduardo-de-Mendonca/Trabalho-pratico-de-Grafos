g++ -c Representation.cpp -O3 -m64
g++ -c Graph.cpp -O3 -m64
g++ -c main.cpp -O3 -m64
g++ Representation.o Graph.o main.o -O3 -o main.exe -m64
.\main.exe