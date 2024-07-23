#include <iostream>
#include <vector>
#include <stack>
#include <ctime>
using namespace std;

class Task {
public:
    string description;
    string category;
    bool completed;
    string dueDate;
    string priority;

    Task(string description, string category, string priority, string dueDate) {
        this->description = description;
        this->category = category;
        this->dueDate = dueDate;
        this->priority = priority;
        this->completed = false;
    }
};

stack<Task> undoStack;
vector<Task> NotesAdded;
vector<string> categories = {"Work", "Personal", "Study", "Shopping", "Other"};

// Function to display tasks with a formatted border
void displayTasks() {
    if (NotesAdded.empty()) {
        cout << "*============================================*" << endl;
        cout << "           |__No tasks added yet__|           " << endl;
        cout << "*============================================*" << endl;
    } else {
        cout << "*============================================*" << endl;
        cout << "                  Tasks                       " << endl;
        cout << "*============================================*" << endl;
        cout << "   Task     |   Category   |  Priority  |  Due Date  |  Status   " << endl;
        cout << "--------------------------------------------------" << endl;
        for (int i = 0; i < NotesAdded.size(); i++) {
            cout.width(3);
            cout << right << i + 1 << ". ";
            cout.width(12);
            cout << left << NotesAdded[i].description.substr(0, 12);
            cout.width(14);
            cout << left << NotesAdded[i].category.substr(0, 14);
            cout.width(12);
            cout << left << NotesAdded[i].priority.substr(0, 12);
            cout.width(12);
            cout << left << NotesAdded[i].dueDate.substr(0, 12);
            cout.width(10);
            cout << left << (NotesAdded[i].completed ? "Completed" : "Pending") << endl;
        }
        cout << "--------------------------------------------------" << endl;
    }
}

// Function to mark a task as completed
void markTaskAsCompleted() {
    int taskNumber;
    cout << "Enter task number to mark as completed: ";
    cin >> taskNumber;

    if (taskNumber > 0 && taskNumber <= NotesAdded.size()) {
        NotesAdded[taskNumber - 1].completed = true;
        cout << "Task marked as completed." << endl;
    } else {
        cout << "Invalid Task Number" << endl;
    }
}

// Function to delete a task
void deleteTask() {
    int taskNumber;
    cout << "Enter task number to delete: ";
    cin >> taskNumber;

    if (taskNumber > 0 && taskNumber <= NotesAdded.size()) {
        Task task = NotesAdded[taskNumber - 1];
        undoStack.push(task);
        NotesAdded.erase(NotesAdded.begin() + taskNumber - 1);
        cout << "Task deleted successfully." << endl;
    } else {
        cout << "Invalid Task Number" << endl;
    }
}

// Function to undo the last deleted task
void undoLastDelete() {
    if (!undoStack.empty()) {
        NotesAdded.push_back(undoStack.top());
        undoStack.pop();
        cout << "Last deleted task restored." << endl;
    } else {
        cout << "Nothing to Undo" << endl;
    }
}

// Function to filter tasks by category
void filterTaskByCategory() {
    string filterCategory;
    cout << "Enter category to filter (Work, Personal, Study, Shopping, Other): ";
    cin >> filterCategory;

    cout << "*============================================*" << endl;
    cout << "         |Tasks in category| '" << filterCategory << "'         " << endl;
    cout << "*============================================*" << endl;
    cout << "   Task     |   Category   |  Priority  |  Due Date  |  Status   " << endl;
    cout << "--------------------------------------------------" << endl;

    for (int i = 0; i < NotesAdded.size(); i++) {
        if (NotesAdded[i].category == filterCategory) {
            cout.width(3);
            cout << right << i + 1 << ". ";
            cout.width(12);
            cout << left << NotesAdded[i].description.substr(0, 12);
            cout.width(14);
            cout << left << NotesAdded[i].category.substr(0, 14);
            cout.width(12);
            cout << left << NotesAdded[i].priority.substr(0, 12);
            cout.width(12);
            cout << left << NotesAdded[i].dueDate.substr(0, 12);
            cout.width(10);
            cout << left << (NotesAdded[i].completed ? "Completed" : "Pending") << endl;
        }
    }
    cout << "--------------------------------------------------" << endl;
}

// Function to add a new category
void createNewCategory() {
    string newCategory;
    cout << "Enter new category name: ";
    cin.ignore();
    getline(cin, newCategory);
    categories.push_back(newCategory);
    cout << "New category '" << newCategory << "' created successfully." << endl;
}

// Function to display task statistics
void displayTaskStats() {
    int totalTasks = NotesAdded.size();
    int completedTasks = 0;

    for (const auto& task : NotesAdded) {
        if (task.completed) {
            completedTasks++;
        }
    }

    cout << "Total Tasks: " << totalTasks << ", Completed Tasks: " << completedTasks << endl;
}

// Function to add a task
void addTask() {
    string description, category, priority;

    cout << "Enter task description: ";
    cin.ignore();
    getline(cin, description);

    auto now = time(nullptr);
    tm* current = localtime(&now);

    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", current);
    string dueDate(buffer);

    cout << "Do you want to assign a category? (y/n): ";
    char categoryChoice;
    cin >> categoryChoice;

    if (categoryChoice == 'y' || categoryChoice == 'Y') {
        cout << "Choose a category:\n";
        for (size_t i = 0; i < categories.size(); ++i) {
            cout << i + 1 << ". " << categories[i] << endl;
        }
        int categoryIndex;
        cin >> categoryIndex;
        if (categoryIndex > 0 && categoryIndex <= categories.size()) {
            category = categories[categoryIndex - 1];
        } else {
            cout << "Invalid choice, defaulting to 'Other'" << endl;
            category = "Other";
        }
    } else {
        category = "Other";
    }

    cout << "Enter priority (HIGH/LOW/MEDIUM): ";
    cin >> priority;

    Task task(description, category, priority, dueDate);
    NotesAdded.push_back(task);
    cout << "Task added successfully." << endl;
}

// Function to display the main menu and handle user choices
void displayMenu() {
    int choice;

    do {
        cout << "==================================================" << endl;
        cout << "                |__Task Manager__|                " << endl;
        cout << "==================================================" << endl;
        cout << "Menu:\n"
             << "1. Add Task\n"
             << "2. View Tasks\n"
             << "3. Mark Task as Completed\n"
             << "4. Delete Task\n"
             << "5. Undo Last Delete\n"
             << "6. Filter Tasks By Category\n"
             << "7. Display Task Stats\n"
             << "8. Create New Category\n"
             << "9. Exit\n"
             << "Enter your choice: ";

        cin >> choice;

        switch (choice) {
            case 1:
                addTask();
                break;
            case 2:
                displayTasks();
                break;
            case 3:
                markTaskAsCompleted();
                break;
            case 4:
                deleteTask();
                break;
            case 5:
                undoLastDelete();
                break;
            case 6:
                filterTaskByCategory();
                break;
            case 7:
                displayTaskStats();
                break;
            case 8:
                createNewCategory();
                break;
            case 9:
                cout << "Goodbye! Please complete your tasks on time." << endl;
                break;
            default:
                cout << "Please enter a valid choice." << endl;
                break;
        }
    } while (choice != 9);
}

int main() {
    displayMenu();
    return 0;
}
