std = -std=c++11

main.cpp: 
	g++ main.cpp -o CmdExe $(std)

Report.o: lib/ytime.o
	g++ -c Report.cpp lib/ytime.o $(std)

