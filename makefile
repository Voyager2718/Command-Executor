CC=g++
opt=-std=c++11

main=.
executor=.
command=.
command=.
report=.
irunnable=.
result=.
transaction=.
ytime=./lib/ytime
yrandom=./lib/yrandom
settings=.

rmr_outputs=find . -name "*.o" -delete

make: $(main)/main.cpp $(executor)/Executor.o $(command)/Command.o $(irunnable)/IRunnable.h $(report)/Report.o $(result)/Result.o $(ytime)/ytime.o $(transaction)/Transaction.o $(command)/ParallelCommand.o $(transaction)/ParallelTransaction.o $(transaction)/ATransaction.o
	$(CC) $(command)/Command.o $(command)/ParallelCommand.o $(transaction)/Transaction.o $(report)/Report.o $(executor)/Executor.o $(result)/Result.o $(ytime)/ytime.o $(transaction)/ATransaction.o $(transaction)/ParallelTransaction.o $(main)/main.cpp -o $(main)/main $(opt)

$(report)/Report.o: $(report)/Report.h $(report)/Report.cpp $(ytime)/ytime.o $(result)/Result.o
	$(CC) -c $(ytime)/ytime.o $(result)/result.o $(report)/Report.cpp -o $(report)/Report.o $(opt) -Wno-unused-command-line-argument

$(executor)/Executor.o: $(executor)/Executor.h $(executor)/Executor.cpp $(irunnable)/IRunnable.h $(report)/Report.o
	$(CC) -c $(report)/Report.o $(executor)/Executor.cpp -o $(executor)/Executor.o $(opt) -Wno-unused-command-line-argument

$(command)/Command.o: $(command)/Command.h $(command)/Command.cpp $(report)/Report.o $(irunnable)/IRunnable.h
	$(CC) -c $(report)/Report.o $(command)/Command.cpp -o $(command)/Command.o $(opt) -Wno-return-type -Wno-unused-command-line-argument

$(command)/ParallelCommand.o: $(command)/ParallelCommand.h $(command)/ParallelCommand.cpp $(command)/Command.o
	$(CC) -c $(command)/Command.o $(command)/ParallelCommand.cpp -o $(command)/ParallelCommand.o $(opt) -Wno-unused-command-line-argument

$(transaction)/ATransaction.o: $(transaction)/ATransaction.cpp $(transaction)/ATransaction.h
	$(CC) -c $(transaction)/ATransaction.cpp -o $(transaction)/ATransaction.o $(opt) -Wno-unused-command-line-argument

$(transaction)/Transaction.o: $(transaction)/Transaction.cpp $(transaction)/Transaction.h $(irunnable)/IRunnable.h $(command)/Command.o $(result)/Result.o
	$(CC) -c $(command)/Command.o $(result)/Result.o $(transaction)/Transaction.cpp -o $(transaction)/Transaction.o $(opt) -Wno-unused-command-line-argument

$(transaction)/ParallelTransaction.o: $(transaction)/ParallelTransaction.h $(transaction)/ParallelTransaction.cpp $(settings)/Settings.h $(transaction)/Transaction.h $(transaction)/ATransaction.o
	$(CC) -c $(transaction)/ATransaction.o $(transaction)/ParallelTransaction.cpp -o $(transaction)/ParallelTransaction.o $(opt) -Wno-unused-command-line-argument

$(result)/Result.o: $(result)/Result.cpp $(result)/Result.h
	$(CC) -c $(result)/Result.cpp -o $(result)/Result.o $(opt)

$(yrandom)/yrandom.o: $(yrandom)/yrandom.cpp $(yrandom)/yrandom.h
	$(CC) -c $(yrandom)/yrandom.cpp -o $(yrandom)/yrandom.o $(opt)

$(ytime)/ytime.o: $(ytime)/ytime.cpp $(ytime)/ytime.h
	$(CC) -c $(ytime)/ytime.cpp -o $(ytime)/ytime.o $(opt)

rclean:
	rm -f $(main)/main; $(rmr_outputs)