#include "Logger.h"
#include "TaskManager.h"
#include "Command.h"
#include <unordered_map>
#include <variant>

int main() {
    TaskManager taskManager;
    // Method 1: Virtual Base Class
    // std::unordered_map<std::string, std::unique_ptr<CommandBase>> commands;
    // commands["add"] = std::make_unique<AddCommand>(taskManager);
    // commands["delete"] = std::make_unique<DeleteCommand>(taskManager);
    // commands["update"] = std::make_unique<UpdateCommand>(taskManager);
    // commands["list"] = std::make_unique<ListCommand>(taskManager);

    // Method 2: Type-erasure with std::function
    // std::unordered_map<std::string, std::function<void(const std::string&)>> commands;
    // auto addCommand = std::make_shared<AddCommand>(taskManager);
    // auto deleteCommand = std::make_shared<DeleteCommand>(taskManager);
    // auto updateCommand = std::make_shared<UpdateCommand>(taskManager);
    // auto listCommand = std::make_shared<ListCommand>(taskManager);
    // commands["add"] = [addCommand](const std::string& args) {
    //     addCommand->execute(args);
    // };
    // commands["delete"] = [deleteCommand](const std::string& args) {
    //     deleteCommand->execute(args);
    // };
    // commands["update"] = [updateCommand](const std::string& args) {
    //     updateCommand->execute(args);
    // };
    // commands["list"] = [listCommand](const std::string& args) {
    //     listCommand->execute(args);
    // };

    // Method 3: std::variant
    // using CommandVariant = std::variant<
    // std::unique_ptr<AddCommand>,
    // std::unique_ptr<DeleteCommand>,
    // std::unique_ptr<UpdateCommand>,
    // std::unique_ptr<ListCommand>
    // >;

    // std::unordered_map<std::string, CommandVariant> commands;
    // commands["add"] = std::make_unique<AddCommand>(taskManager);
    // commands["delete"] = std::make_unique<DeleteCommand>(taskManager);
    // commands["update"] = std::make_unique<UpdateCommand>(taskManager);
    // commands["list"] = std::make_unique<ListCommand>(taskManager);

    // Methods 4: 
    std::unordered_map<std::string, CommandWrapper> commands;
    commands.emplace("add", AddCommand(taskManager));
    commands.emplace("delete", DeleteCommand(taskManager));
    commands.emplace("list", ListCommand(taskManager));
    commands.emplace("update", UpdateCommand(taskManager));

    std::cout << "Welcome to the Task Manager!" << std::endl;
    std::cout << "Available commands: add, delete, update, list" << std::endl;
    std::string input;
    while (true) {
        std::cout << "\n";
        std::getline(std::cin, input);
        if (input.empty()) {
            continue;
        }
         
        size_t spacePos = input.find(' ');
        std::string command = input.substr(0, spacePos);
        std::string args;
        if (spacePos != std::string::npos) {
            args = input.substr(spacePos + 1);
        }

        if (command == "exit") {
            std::cout << "Exiting the Task Manager." << std::endl;
            break;
        }
        auto it = commands.find(command);
        if (it != commands.end()) {
        //    std::visit([&args](auto&& cmdPtr) {
        //     cmdPtr->execute(args);
        //    }, it->second);
        it->second.execute(args);
        } else {
            std::cout << "Invalid command. Available commands: add, delete, update, list" << std::endl;
        }
    }

    return 0;
}
