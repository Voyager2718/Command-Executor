CC=g++
std=-std=c++11

main=.
executor=.
command=.
report=.
irunnable=.
result=.
ytime=./lib/ytime
yrandom=./lib/yrandom

rmr_outputs=find . -name "*.o" -delete

make: $(main)/main.cpp $(executor)/Executor.o $(command)/Command.o $(irunnable)/IRunnable.h $(report)/Report.o $(result)/Result.o $(ytime)/ytime.o
	$(CC) $(command)/Command.o $(report)/Report.o $(executor)/Executor.o $(result)/Result.o $(ytime)/ytime.o $(main)/main.cpp -o $(main)/main $(std)

$(report)/Report.o: $(report)/Report.h $(report)/Report.cpp $(ytime)/ytime.o $(result)/Result.o
	$(CC) -c $(ytime)/ytime.o $(result)/result.o $(report)/Report.cpp -o $(report)/Report.o $(std) -Wno-unused-command-line-argument

$(executor)/Executor.o: $(executor)/Executor.h $(executor)/Executor.cpp $(irunnable)/IRunnable.h $(report)/Report.o
	$(CC) -c $(report)/Report.o $(executor)/Executor.cpp -o $(executor)/Executor.o $(std) -Wno-unused-command-line-argument

$(command)/Command.o: $(command)/Command.h $(command)/Command.cpp $(report)/Report.o $(irunnable)/IRunnable.h
	$(CC) -c $(report)/Report.o $(command)/Command.cpp -o $(command)/Command.o $(std) -Wno-return-type -Wno-unused-command-line-argument

$(result)/Result.o: $(result)/Result.cpp $(result)/Result.h
	$(CC) -c $(result)/Result.cpp -o $(result)/Result.o $(std)

$(yrandom)/yrandom.o: $(yrandom)/yrandom.cpp $(yrandom)/yrandom.h
	$(CC) -c $(yrandom)/yrandom.cpp -o $(yrandom)/yrandom.o $(std)

$(ytime)/ytime.o: $(ytime)/ytime.cpp $(ytime)/ytime.h
	$(CC) -c $(ytime)/ytime.cpp -o $(ytime)/ytime.o $(std)

rclean:
	rm -f $(main)/main; $(rmr_outputs)