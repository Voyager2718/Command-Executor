#include "ParallelCommand.h"

ParallelCommand::ParallelCommand(string command) : Command(command) {}

ParallelCommand::ParallelCommand(string command, int timeout, string description) : Command(command, timeout, description) {}

ParallelCommand::ParallelCommand(int timeout, string description) : Command(timeout, description) {}

ParallelCommand::ParallelCommand() {}