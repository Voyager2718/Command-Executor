# Summary
This project allows you to multiple commands and programs schedulely and parallelly.

Also, this project enables you to validate the outputs and the results of commands and programs.

The main purpose of this project is to create an universal framework so that we don't have to worry about how does a command work. What we need to do is to create a Command or a Transaction, and let them be called by users.

# Mechanism
For execution, we have 2 classes inherite from `IRunnable` called `Command` and `Transaction`. Both these 2 classes have `Run()` while `Run()` in `Command` execute certain commands/programs and `Run()` in `Transaction` just call `Run()` into `Command`. `Transaction` is designed to run multiple `Command`.

In `Command` class, we can add a command or a program that needs to be run. Also, we can inheritate `OutputChecker` and `Validator` and add them to the instance of `Command`. During execution, `Command` will `fork()` and use `exec()` family to execute command or program, then redirect `STDOUT_FILENO` and `STDERR_FILENO` to desinated output `OutputChecker`. After execution, `Command` will execute `Validator` to do the verification. No matter which one of these operations failed, `Command` will return `Result.FAILED`.

In Transaction, we can add multiple `ParallelCommand` to `ParallelTransaction` to run multiple commands/programs at the same time. We use a thread pool to create multi-threads to call `Run()` in `Command`. You can modify the number of maximum threads in `Settings.h`.

`Executor` contains a list of `IRunnable` so that we can add both `Command` and `Transaction` into `Executor`. When we add a `Transaction` as well as a `ParallelTransaction` into `Executor`, then commands/programs will be executed in serial mode first, then in parallel mode.

For report generation, we created a singleton class called `Report`. After command execution in `Command`, `Transaction` will collect execution report and add them to `Report` automatically.

## Further functionalities
### Execute command with desinated user
We are developing a mechanism to execute commands/programs with desinated users. What users have to do is to indicate which user that they want to use for certain commands/programs and provide appropriate password if needed.

### Improved scalability
C++ is not easy to control, so we support using other programming language by using either *shared object** or programs in other languages.

The class `Parser` is designed to parse a file that describe which commands/programs should be run in either serial or parallel mode. Then `Parser` should return an `Executor` that can be used easily.

Officially, we recommand to use YCE file and YCE parser.

#### YCE file
For those who don't want to modify C++ codes, you can use YCE file to integrate your command/program into this project.

YCE(YCE Command Executor) file describes command/program location, what kind of arguments should be pass to it, how to execute, what kind of OutputChecker/Validator should be used.

YCE will be interpreted by Launcher and call Executor to do concrete tasks.

Example of YCE file (v 0.0.1):
```
Version:0001
parallel{
    command("~/Documents/p_program1");
    command("~/Documents/p_program2"){
        validator("~/Documents/validator");
        checker("~/Documents/checker");
    };
serial{
    command("~/Documents/s_program1";
    command("~/Documents/s_program2"){
        validator("~/Documents/validator");
        checker("~/Documents/checker");
    };
}
# Comments
```


YCE file v0.0.1 supports following lexical rules:
- key:integer;
    - key:string;
- program(string);
    - program(string){ programs };
- running_mode{};
- variable=integer;
    - variable=string;
- #comments\n
    - #comments\r\n

You can put yce file reference in both parallel and serial part. However, as YCE file can contains both parallel and serial tasks, if you want to put yce file reference in parallel part, you MUST insure that there's no serial tasks in referenced YCE file.


### Multi-nodes
In order to execute commands/programs on multi-nodes environment, we plan to create a daemon that listens to certain port, sending and receiving parsable strings to achieve multi-nodes execution.

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
|`virtual Result Run(vector<string> arguments = vector<string>())`|`vector<string>`: Arguments vector|`Result`: Result of command execution, defined in **Result.h**|This method implements `IRunnable::Run` and it will run command.|
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

|Methods|Arguments|Return Value|Comments|
|-------|---------|------------|--------|
|`virtual void AddCommand(shared_ptr<Command> command)`|`shared_ptr<Command> command`: Command that needs to be run.|void|Add command that needs to be run by Transaction.|
|`virtual Result Run(vector<string> arguments = vector<string>())`|`vector<string> arguments = vector<string>()`: Argument for the first command.|`Result`: Result of execution, defined in **Result.h**.|This method implements `IRunnable::Run` and it will run commands in *serial* mode.|

## ParallelTransaction
File name: **ParallelTransaction.h**

`ParallelTransaction` can only hold `ParallelCommand` or classes inherit from `ParallelCommand`. `ParallelCommand`s in `ParallelTransaction` will be run in multiple threads. The number of threads depends on `MAX_THREADS` defined in **Settings.h**.

|Methods|Arguments|Return Value|Comments|
|-------|---------|------------|--------|
|`virtual void AddCommand(shared_ptr<ParallelCommand> command)`|`shared_ptr<ParallelCommand> command`: Command that needs to be run.|void|Add command that needs to be run by Transaction.|
|`virtual Result Run(vector<string> arguments = vector<string>())`|`vector<string> arguments = vector<string>()`: Argument for the first command.|`Result`: Result of execution, defined in **Result.h**.|This method overrides `Transaction::Run` and it will run commands in *parallel* mode.|

## Executor
File name: **Executor.h**

`Executor` executes classes implements `IRunnable` using virtual method `Result Run(vector<string> arguments = vector<string>())`. `Command`, `ParallelCommand`, `Transaction`, `ParallelTransaction` can be added to `Executor`. `IRunnable`s in `Executor` will be executed in serial mode.

## Launcher [Future feature]
Launcher defines several interfaces to launch appropriate tasks. Also, Launcher takes the responsibility of YCE file interpretation.

What's more, Launcher will have daemons listen to certain ports so that it can receive launching tasks from remote users.

## Report
File name: **Report.h**

`Report` is a Singleton class which means you can always use `Report::GetInstance())` to get Report instance and do your operations. Reminder, Report should be used in main process or you will need to sync data yourself.

This class CANNOT be inherited.

## Result
`Result` is an enum which defines three result status `SUCCESSFUL`, `FAILED` and `IGNORED`. `IGNORED` means that during execution, one or more failures were hit, but ALL of them can be ignored.

# Example
```c++
#include <iostream>
#include <memory>

#include "src/Executor/Executor.h"
#include "src/Runnable/Command/Command.h"
#include "src/Runnable/IRunnable.h"
#include "src/Runnable/Transaction/ParallelTransaction/ParallelTransaction.h"
#include "src/Runnable/Command/ParallelCommand/ParallelCommand.h"
#include "src/Runnable/Transaction/Transaction.h"

using std::cout;
using std::cin;
using std::endl;

using std::shared_ptr;
using std::make_shared;

#include "src/OutputChecker/IStdoutChecker.h"

/**
  * MyStdoutChecker that checks the std output.
  */
class MyStdoutChecker : public IStdoutChecker
{
    Result Check(string allOutput)
    {
        cout << "Output Checker: " << allOutput;
        return SUCCESSFUL;
    }

    string GetSuccessDescription() { return "Succ"; }

    string GetFatalDescription() { return "Fatal"; }

    string GetIgnoredDescription() { return "Ignored"; }

    string GetLastReportNumber() { return "TEST-0001"; }
};

int main(int argc, char *argv[])
{
    Executor executor;  // Create an Executor.
    shared_ptr<ParallelTransaction> transaction = make_shared<ParallelTransaction>();   // Create a ParallelTransaction.

    shared_ptr<ParallelCommand> tmp = make_shared<ParallelCommand>("./test_programs/print1");   // Create a ParallelCommand that can be executed in parallel.

    tmp->AddStdoutChecker(make_shared<stdouttest>());   // Add a std output checker.

    transaction->AddCommand(tmp);   // Add the parallel command with output checker into parallel transaction.
    transaction->AddCommand(make_shared<ParallelCommand>("./test_programs/print2"));    // Add the parallel command without output checker into parallel transaction.

    executor.AddRunnable(transaction);  // Add parallel transaction into executor.

    executor.Execute();
    return 0;
}
```