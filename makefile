CC=g++
opt=-std=c++11 -Wno-unused-command-line-argument

main=.
build=./build
executor=./src/Executor
command=./src/Runnable/Command
parallel_command=./src/Runnable/Command/ParallelCommand
report=./src/Report
irunnable=./src/Runnable
result=./src/Result
transaction=./src/Runnable/Transaction
parallel_transaction=./src/Runnable/Transaction/ParallelTransaction
ytime=./lib/ytime
yrandom=./lib/yrandom
settings=.

rmr_outputs=find . -name "*.o" -delete

main_dep=$(build)/Executor.o $(build)/Command.o $(build)/IRunnable.h $(build)/Report.o $(build)/ytime.o $(build)/Transaction.o $(build)/ParallelCommand.o $(build)/ParallelTransaction.o $(build)/ATransaction.o

make: $(main)/main.cpp $(main_dep)
	$(CC) $(main_dep) $(main)/main.cpp -o $(main)/main $(opt)

report_dep=$(ytime)/ytime.o $(result)/Result.o

$(build)/Report.o: $(report)/Report.h $(report)/Report.cpp $(report_dep)
	$(CC) -c $(report_dep) $(report)/Report.cpp -o $(build)/Report.o $(opt)

executor_dep=$(report)/Report.o

$(build)/Executor.o: $(executor)/Executor.h $(executor)/Executor.cpp $(irunnable)/IRunnable.h $(executor_dep)
	$(CC) -c $(executor_dep) $(executor)/Executor.cpp -o $(build)/Executor.o $(opt)

command_dep=$(report)/Report.o 

$(build)/Command.o: $(command)/Command.h $(command)/Command.cpp $(irunnable)/IRunnable.h $(command_dep)
	$(CC) -c $(command_dep) $(command)/Command.cpp -o $(build)/Command.o $(opt)

parallel_command_dep=$(command)/Command.o

$(build)/ParallelCommand.o: $(parallel_command)/ParallelCommand.h $(parallel_command)/ParallelCommand.cpp $(parallel_command_dep)
	$(CC) -c $(parallel_command_dep) $(parallel_command)/ParallelCommand.cpp -o $(build)/ParallelCommand.o $(opt) 

atransaction_dep=

$(build)/ATransaction.o: $(transaction)/ATransaction.cpp $(transaction)/ATransaction.h $(atransaction_dep)
	$(CC) -c $(atransaction_dep) $(transaction)/ATransaction.cpp -o $(build)/ATransaction.o $(opt)

transaction_dep=$(command)/Command.o $(result)/Result.o

$(build)/Transaction.o: $(transaction)/Transaction.cpp $(transaction)/Transaction.h $(irunnable)/IRunnable.h $(transaction_dep)
	$(CC) -c $(transaction_dep)$(transaction)/Transaction.cpp -o $(build)/Transaction.o $(opt)

parallel_transaction_dep=$(transaction)/ATransaction.o

$(build)/ParallelTransaction.o: $(parallel_transaction)/ParallelTransaction.h $(parallel_transaction)/ParallelTransaction.cpp $(settings)/Settings.h $(transaction)/Transaction.h $(parallel_transaction_dep)
	$(CC) -c $(parallel_transaction_dep) $(parallel_transaction)/ParallelTransaction.cpp -o $(build)/ParallelTransaction.o $(opt)

result_dep=

$(build)/Result.o: $(result)/Result.cpp $(result)/Result.h $(result_dep)
	$(CC) -c $(result_dep) $(result)/Result.cpp -o $(build)/Result.o $(opt)

yrandom_dep=

$(build)/yrandom.o: $(yrandom)/yrandom.cpp $(yrandom)/yrandom.h $(yrandom_dep)
	$(CC) -c $(yrandom_dep) $(yrandom)/yrandom.cpp -o $(build)/yrandom.o $(opt)

ytime_dep=

$(build)/ytime.o: $(ytime)/ytime.cpp $(ytime)/ytime.h $(ytime_dep)
	$(CC) -c $(ytime_dep) $(ytime)/ytime.cpp -o $(build)/ytime.o $(opt)

rclean:
	rm -f $(main)/main; $(rmr_outputs)