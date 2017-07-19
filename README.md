# Summary
This project allows you to multiple commands and programs schedulely and parallelly.

Also, this project enables you to validate the outputs and the results of commands and programs.

The main purpose of this project is to create an universal framework so that we don't have to worry about how does a command work. What we need to do is to create a Command or a Transaction, and let them be called by users.

# Status
|Functionality|Progress|Status|
|-------------|--------|------|
|Architecture|50%|Makefile and source codes should be re-arranged. What's more, after finished this project, rule of three/five should also be implemented too.|
|Command & ParallelCommand|66%|Command & ParallelCommand can be used, OutputChecker and Validator are still not implemented.|
|OutputChecker|0%|Not implemented yet.|
|Validator|0%|Not implemented yet.|
|Transaction & ParallelTransaction|80%|Serial Transaction and Parallel Transaction can be used, argument injection still in development. ParallelTransaction has some minor bugs.|
|Executor|90%|Executor can be used, argument injection still in development.|
|Launcher|0%|Not implemented yet.|
|Report|100%|Finished.|
|GlobalArea|0%|Not implemented yet.|

# YCE file
For those who don't want to modify C++ codes, you can use YCE file to integrate your command/program into this project.

YCE(YCE Command Executor) file describes command/program location, what kind of arguments should be pass to it, how to execute, what kind of OutputChecker/Validator should be used.

YCE will be interpret by Launcher and call Executor to do concrete tasks.

Example of YCE file:
```
#Version0001
parallel:
    command: "~/Documents/p_program1";
    command: "~/Documents/p_program2"{
        validator: "~/Documents/validator";
        checker: "~/Documents/checker";
    };
    yce: "~/Documents/p_yce_task.yce";
serial:
    command: "~/Documents/s_program1";
    command: "~/Documents/s_program2"{
        validator: "~/Documents/validator";
        checker: "~/Documents/checker";
    };
    yce: "~/Documents/s_yce_task.yce";

# Comments
```

You can put yce file reference is both parallel and serial part. However, as YCE file can contains both parallel and serial tasks, if you want to put yce file reference in parallel part, you MUST insure that there's no serial tasks in referenced yce file.

# Components
## Settings
File name: **Settings.h**

- `TARGET_OS`: Specify the target platform. This value can be [linux].
- `MAX_THREADS`: Specify the maximum number of threads while doing parallel tasks. This value can be positive non zero integers.

## Command
File name: **Command.h**

`Command` inherit from `IRunnable`, and implements `Result Run(vector<string> arguments = vector<string>())`. During execution of method `Command::Run`, a new *process* is created to execute desinated command.

|Methods|Arguments|Return Value|Comments|
|-------|---------|------------|--------|
|`Command()`|`void`|None|Constructor.|
|`Command(int timeout, string description)`|`int timeout`: Timeout of command execution. <br />`string description`: Description.|None|Constructor.|
|`virtual ~Command()`|None|None|Destructor.|
|`Command(const Command& command)`|`const Command& command`: Object to be copied.|None|Copy constructor.|
|`virtual Result Run(vector<string> arguments = vector<string>())`|`vector<string>`: Arguments vector|`Result`: Result of command execution, defined in **Result.h**|This method implements `IRunnable::Run`.|
|`virtual void SetCommand(string command)`|`string command`: Command that need to be run.|void|Add command that need to be run.|
|`virtual string GetCommand()`|void|`string`: Command that added to this class.|Return command that added to this class.|
|`virtual void SetTimeout(int timeout)`|`int timeout`: Timeout of command execution.|void|Command process will be terminated when exceeded timeout.|
|`virtual int GetTimeout()`|void|`int`: Command timeout.|Return command timeout.|
|`virtual void AddValidator(shared_ptr<AValidator> validator)`|`shared_ptr<AValidator> validator`: Validator that can validate command results.|void|Add validator that can validate command results.|
|`virtual void AddOutputChecker(shared_ptr<AOutputChecker> outputChecker)`|`shared_ptr<AOutputChecker> outputChecker`: OutputChecker that can check command output.|void|Add outputChecker that can check command output.|
|`virtual string GetDescription()`|void|`string`: Command description.|Get command description.|

## ParallelCommand
File name: **ParallelCommand.h**

`ParallelCommand` inherit from `Command`. However, this class does not add new methods. The main purpose of this class is create a parallel command for parallel transaction.

## Transaction
File name: **Transaction.h**

`Transaction` can hold multiple `Command`s (`Command`, `ParallelCommand` and classes inherit from these 2 classes are acceptable) and will run each command in seria    l mode. `Transaction` enables shared space for `Command`s.

## ParallelTransaction
File name: **ParallelTransaction.h**

`ParallelTransaction` can only hold `ParallelCommand` or classes inherit from `ParallelCommand`. `ParallelCommand`s in `ParallelTransaction` will be run in multiple threads. The number of threads depends on `MAX_THREADS` defined in **Settings.h**.

## Executor
File name: **Executor.h**

`Executor` executes classes implements `IRunnable` using virtual method `Result Run(vector<string> arguments = vector<string>())`. `Command`, `ParallelCommand`, `Transaction`, `ParallelTransaction` can be added to `Executor`. `IRunnables` in `Executor` will be executed in serial mode.

## Launcher [Future feature]
Launcher defines several interfaces to launch appropriate tasks. Also, Launcher takes the responsibility of YCE file interpretation.

What's more, Launcher will have daemons listen to certain ports so that it can receive launching tasks from remote users.

## Report
File name: **Report.h**

`Report` is a Singleton class which means you can always use `Report::GetInstance())` to get Report instance and do your operations. Reminder, Report should be used in main process or you will need to sync data yourself.

## Result
`Result` is an enum which defines three result status `SUCCESSFUL`, `FAILED` and `IGNORED`. `IGNORED` means that during execution, one or more failures were hit, but ALL of them can be ignored.