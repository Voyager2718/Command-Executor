CC=g++
opt=-std=c++11 -Wno-unused-command-line-argument -O3 -Wall

main=.
build=./build
executor=./src/Executor
command=./src/Runnable/Command
parallel_command=./src/Runnable/Command/ParallelCommand
report=./src/Report
runnable=./src/Runnable
result=./src/Result
transaction=./src/Runnable/Transaction
parallel_transaction=./src/Runnable/Transaction/ParallelTransaction
ytime=./lib/ytime
yrandom=./lib/yrandom
settings=.
reportString=./src/ReportString
outputChecker=./src/OutputChecker

main_dep=./build/yce.a
$(main)/main: $(main)/main.cpp $(main_dep)
	g++ main.cpp $(main_dep) -o main $(opt)

yce_dep=$(build)/Executor.o $(build)/Command.o $(build)/Report.o $(build)/ytime.o $(build)/Transaction.o $(build)/ParallelCommand.o $(build)/ParallelTransaction.o $(build)/ATransaction.o $(build)/Result.o $(build)/ReportString.o $(build)/AOutputChecker.o
$(build)/yce.a: $(yce_dep)
	ar rcs build/yce.a build/*.o

report_dep=$(build)/ytime.o $(build)/Result.o
$(build)/Report.o: $(report)/Report.h $(report)/Report.cpp $(report_dep)
	$(CC) -c $(report_dep) $(report)/Report.cpp -o $(build)/Report.o $(opt)

report_str_dep=
$(build)/ReportString.o: $(reportString)/ReportString.cpp
	$(CC) -c $(report_str_dep) $(reportString)/ReportString.cpp -o $(build)/ReportString.o $(opt)

executor_dep=$(build)/Report.o
$(build)/Executor.o: $(executor)/Executor.h $(executor)/Executor.cpp $(runnable)/IRunnable.h $(executor_dep)
	$(CC) -c $(executor_dep) $(executor)/Executor.cpp -o $(build)/Executor.o $(opt)

command_dep=$(build)/Report.o 
$(build)/Command.o: $(command)/Command.h $(command)/Command.cpp $(runnable)/IRunnable.h $(command_dep)
	$(CC) -c $(command_dep) $(command)/Command.cpp -o $(build)/Command.o $(opt)

parallel_command_dep=$(build)/Command.o
$(build)/ParallelCommand.o: $(parallel_command)/ParallelCommand.h $(parallel_command)/ParallelCommand.cpp $(parallel_command_dep)
	$(CC) -c $(parallel_command_dep) $(parallel_command)/ParallelCommand.cpp -o $(build)/ParallelCommand.o $(opt) 

atransaction_dep=
$(build)/ATransaction.o: $(transaction)/ATransaction.cpp $(transaction)/ATransaction.h $(atransaction_dep)
	$(CC) -c $(atransaction_dep) $(transaction)/ATransaction.cpp -o $(build)/ATransaction.o $(opt)

transaction_dep=$(build)/Command.o $(build)/Result.o
$(build)/Transaction.o: $(transaction)/Transaction.cpp $(transaction)/Transaction.h $(runnable)/IRunnable.h $(transaction_dep)
	$(CC) -c $(transaction_dep) $(transaction)/Transaction.cpp -o $(build)/Transaction.o $(opt)

parallel_transaction_dep=$(build)/ATransaction.o
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

aoutput_checker_dep=$(build)/Result.o
$(build)/AOutputChecker.o: $(build)/Result.o
	$(CC) -c $(outputChecker)/AOutputChecker.cpp -o $(build)/AOutputChecker.o $(opt)

rclean:
	rm -f $(main)/main
	find . -name "*.[ao]" -delete

clean:
	rm -f $(main)/main

rc:
	rm -f $(main)/main
	find . -name "*.[ao]" -delete
