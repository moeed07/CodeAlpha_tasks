#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
class Task
{
public:
    string name;
    bool completed;
    Task(string n)
    {
        name = n;
        completed = false;
    }
};
class ToDoList
{
    vector<Task> tasks;
    void saveToFile()
    {
        ofstream file("tasks.txt");
        for (auto& t : tasks)
            file << t.name << "|" << t.completed << "\n";
        file.close();
    }
    void loadFromFile()
    {
        ifstream file("tasks.txt");
        if (!file) return;
        string line;
        while (getline(file, line))
        {
            int sep = line.find('|');
            Task t(line.substr(0, sep));
            t.completed = line.substr(sep + 1) == "1";
            tasks.push_back(t);
        }
        file.close();
    }
public:
    ToDoList() { loadFromFile(); }
    void addTask()
    {
        string name;
        cout << "Enter task: ";
        cin.ignore();
        getline(cin, name);
        tasks.push_back(Task(name));
        saveToFile();
        cout << "Task added!\n";
    }
    void markCompleted()
    {
        viewTasks();
        if (tasks.empty()) return;
        int n;
        cout << "Enter task number to mark complete: ";
        cin >> n;
        if (n < 1 || n > tasks.size()) { cout << "Invalid!\n"; return; }
        tasks[n - 1].completed = true;
        saveToFile();
        cout << "Marked as completed!\n";
    }
    void viewTasks()
    {
        if (tasks.empty()) { cout << "No tasks.\n"; return; }
        cout << "\n--- Tasks ---\n";
        for (int i = 0; i < tasks.size(); i++)
            cout << i + 1 << ". [" << (tasks[i].completed ? "X" : " ") << "] " << tasks[i].name << "\n";
    }
};
int main()
{
    ToDoList list;
    int choice;
    do
    {
        cout << "\n1. Add Task\n2. Mark Completed\n3. View Tasks\n0. Exit\nChoice: ";
        cin >> choice;
        if (choice == 1) list.addTask();
        else if (choice == 2) list.markCompleted();
        else if (choice == 3) list.viewTasks();
    } while (choice != 0);

    return 0;
}