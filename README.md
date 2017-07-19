# Summary
This is a project that can run multiple commands and programs schedulely.

Also, this project enables you to validate the outputs and the results of commands and programs.

# Status
|Functionality|Progress|Status|
|-------------|--------|------|
|Architecture|50%|Makefile and source codes should be re-arranged.|
|Command & ParallelCommand|66%|Command & ParallelCommand can be used, OutputChecker and Validator are still not implemented|
|OutputChecker|0%|Not implemented yet.|
|Validator|0%|Not implemented yet.|
|Transaction & ParallelTransaction|80%|Serial Transaction and Parallel Transaction can be used, argument injection still in development. ParallelTransaction has some minor bugs.|
|Executor|90%|Executor can be used, argument injection still in development.|

# Components
# Settings
File name: **Settings.h**

- `TARGET_OS`: Specify the target platform. This value can be [linux].
- `MAX_THREADS`: Specify the maximum number of threads while doing parallel tasks. This value can be positive non zero integers.

# Command
File name: **Command.h**

`Command` inherit from `IRunnable`, and implements `Result Run(vector<string> arguments = vector<string>())`. During execution of method `Command::Run`, a new *process* is created to execute desinated command.

|Methods|Arguments|Return Value|Comments|
|-------|---------|------------|--------|
|`Command()`|`void`|None|Constructor.|
|`Command(int timeout, string description)`|`int timeout`: Timeout of command execution. <br />`string description`: Description.|None|Constructor|
|`virtual ~Command()`|None|None|Destructor|
|`Command(const Command&)`|`const Command& command`: Object to be copied.|None|Copy constructor.|
|`virtual Result Run(vector<string> arguments = vector<string>())`|`vector<string>`: Arguments vector|`Result`: Result of command execution, defined in **Result.h**|This method implements `IRunnable::Run`.|
|`virtual void SetCommand(string command)`|`string command`: Command that need to be run.|void|Add command that need to be run.|
|`virtual string GetCommand()`|void|`string`: Command that added to this class.|Return command that added to this class.|
|`virtual void SetTimeout(int timeout)`|`int timeout`: Timeout of command execution.|void|Command process will be terminated when exceeded timeout.|
|`virtual int GetTimeout()`|void|`int`: Command timeout.|Return command timeout.|
|`virtual void AddValidator(shared_ptr<AValidator> validator)`|`shared_ptr<AValidator> validator`: Validator that can validate command results.|void|Add validator that can validate command results.|
|`virtual void AddOutputChecker(shared_ptr<AOutputChecker> outputChecker)`|`shared_ptr<AOutputChecker> outputChecker`: OutputChecker that can check command output.|void|Add outputChecker that can check command output.|
|`virtual string GetDescription()`|void|`string`: Command description.|Get command description.|

# ParallelCommand
File name: **ParallelCommand.h**

`ParallelCommand` inherit from `Command`. However, this class does not add new methods. The main purpose of this class is create a parallel command for parallel transaction.

# Transaction
File name: **ParallelCommand.h**

`Transaction` can hold multiple `Command`s (`Command`, `ParallelCommand` and classes inherit from these 2 classes are acceptable) and will run each command in serial mode. `Transaction` enables shared space for `Command`s.

# ParallelTransaction
File name: **ParallelCommand.h**

`ParallelTransaction` can only hold `ParallelCommand` or classes inherit from `ParallelCommand`. `ParallelCommand`s in `ParallelTransaction` will be run in multiple threads. The number of threads depends on `MAX_THREADS` defined in **Settings.h**.

# Executor
File name: **ParallelCommand.h**

`Executor` executes classes implements `IRunnable` using virtual method `Result Run(vector<string> arguments = vector<string>())`. `Command`, `ParallelCommand`, `Transaction`, `ParallelTransaction` can be added to `Executor`. `IRunnables` in `Executor` will be executed in serial mode.

# Report
File name: **ParallelCommand.h**

`Report` is a Singleton class which means you can always use `Report::GetInstance())` to get Report instance and do your operations. Reminder, Report should be used in main process or you will need to sync data yourself.

# Result
`Result` is an enum which defines three result status `SUCCESSFUL`, `FAILED` and `IGNORED`. `IGNORED` means that during execution, one or more failures were hit. But ALL of them can be ignored.