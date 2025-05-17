#include "Logger.h"
#include "TaskManager.h"
#include "Command.h"

int main() {
    TaskManager taskManager;
    AddCommand addCommand(taskManager);
    addCommand.execute("Buy groceries,2,2025-05-18");
    return 0;
}
