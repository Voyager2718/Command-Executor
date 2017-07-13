CC=g++
std=-std=c++11

main=.
ytime=./lib/ytime
yrandom=./lib/yrandom

rmr_outputs=find . -name "*.o" -delete

$(main)/main: main.cpp
	$(CC) main.cpp -o main $(std)

$(yrandom)/yrandom.o: $(yrandom)/yrandom.cpp $(yrandom)/yrandom.h
	$(CC) -c $(yrandom)/yrandom.cpp -o $(yrandom)/yrandom.o $(std)

$(ytime)/ytime.o: $(ytime)/ytime.cpp $(ytime)/ytime.h
	$(CC) -c $(ytime)/ytime.cpp -o $(ytime)/ytime.o $(std)

rclean:
	rm -f $(main)/main; $(rmr_outputs)