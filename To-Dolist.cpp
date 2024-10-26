#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>

struct Task {
    std::string description;
    std::string dueDate;  // Format: YYYY-MM-DD
    std::string dueTime;   // Format: HH:MM (24-hour format)
    bool isCompleted;

    Task(std::string desc, std::string date, std::string time)
        : description(desc), dueDate(date), dueTime(time), isCompleted(false) {}
};

std::string getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    return std::to_string(1900 + ltm->tm_year) + "-" +
           std::to_string(1 + ltm->tm_mon) + "-" +
           std::to_string(ltm->tm_mday);
}

std::string getCurrentTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    return std::to_string(ltm->tm_hour) + ":" +
           std::to_string(ltm->tm_min);
}

void addTask(std::vector<Task>& tasks) {
    std::string description, dueDate, dueTime;
    std::cout << "Enter task description: ";
    std::cin.ignore();
    std::getline(std::cin, description);
    
    std::cout << "Enter due date (YYYY-MM-DD): ";
    std::getline(std::cin, dueDate);

    std::cout << "Enter due time (HH:MM, 24-hour format): ";
    std::getline(std::cin, dueTime);
    
    tasks.push_back(Task(description, dueDate, dueTime));
    std::cout << "Task added successfully.\n";
}

void deleteTask(std::vector<Task>& tasks) {
    int index;
    std::cout << "Enter task number to delete: ";
    std::cin >> index;

    if (index > 0 && index <= tasks.size()) {
        tasks.erase(tasks.begin() + index - 1);
        std::cout << "Task deleted successfully.\n";
    } else {
        std::cout << "Invalid task number.\n";
    }
}

void editTask(std::vector<Task>& tasks) {
    int index;
    std::cout << "Enter task number to edit: ";
    std::cin >> index;

    if (index > 0 && index <= tasks.size()) {
        std::string description, dueDate, dueTime;
        std::cout << "Enter new task description: ";
        std::cin.ignore();
        std::getline(std::cin, description);

        std::cout << "Enter new due date (YYYY-MM-DD): ";
        std::getline(std::cin, dueDate);

        std::cout << "Enter new due time (HH:MM, 24-hour format): ";
        std::getline(std::cin, dueTime);

        tasks[index - 1] = Task(description, dueDate, dueTime);
        std::cout << "Task edited successfully.\n";
    } else {
        std::cout << "Invalid task number.\n";
    }
}

void showOverdueTasks(const std::vector<Task>& tasks) {
    std::string currentDate = getCurrentDate();
    std::string currentTime = getCurrentTime();

    std::cout << "Overdue Tasks:\n";
    bool hasOverdue = false;

    for (const auto& task : tasks) {
        if (!task.isCompleted && (task.dueDate < currentDate || 
            (task.dueDate == currentDate && task.dueTime < currentTime))) {
            std::cout << "Description: " << task.description
                      << ", Due Date: " << task.dueDate
                      << ", Due Time: " << task.dueTime << "\n";
            hasOverdue = true;
        }
    }

    if (!hasOverdue) {
        std::cout << "No overdue tasks found.\n";
    }
}

void markTaskCompleted(std::vector<Task>& tasks) {
    int index;
    std::cout << "Enter task number to mark as completed: ";
    std::cin >> index;

    if (index > 0 && index <= tasks.size()) {
        tasks[index - 1].isCompleted = true;
        std::cout << "Task marked as completed.\n";
    } else {
        std::cout << "Invalid task number.\n";
    }
}

void viewTasks(const std::vector<Task>& tasks) {
    if (tasks.empty()) {
        std::cout << "No tasks available.\n";
        return;
    }
    std::cout << "To-Do List:\n";
    for (size_t i = 0; i < tasks.size(); ++i) {
        std::cout << i + 1 << ". " << tasks[i].description
                  << " [Due: " << tasks[i].dueDate << " " << tasks[i].dueTime << "] "
                  << "[" << (tasks[i].isCompleted ? "Completed" : "Pending") << "]\n";
    }
}

int main() {
    std::vector<Task> tasks;
    int choice;

    while (true) {
        std::cout << "\nTo-Do List Menu:\n";
        std::cout << "1. Add Task\n";
        std::cout << "2. Mark Task as Completed\n";
        std::cout << "3. View Tasks\n";
        std::cout << "4. Edit Task\n";
        std::cout << "5. Delete Task\n";
        std::cout << "6. Show Overdue Tasks\n";
        std::cout << "7. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addTask(tasks);
                break;
            case 2:
                markTaskCompleted(tasks);
                break;
            case 3:
                viewTasks(tasks);
                break;
            case 4:
                editTask(tasks);
                break;
            case 5:
                deleteTask(tasks);
                break;
            case 6:
                showOverdueTasks(tasks);
                break;
            case 7:
                std::cout << "Exiting the program.\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}
