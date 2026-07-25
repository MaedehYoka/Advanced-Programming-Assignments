#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <list>
#include <stdlib.h>

#define ADDTASK "add_task"
#define ADDEMPLOYEE "add_employee"
#define ASSIGNEMPLOYEE "assign_employee"
#define FINISHTASK "finish_task"
#define REPORT "report"
#define TODO "TODO"
#define ONGOING "ONGOING"
#define DONE "DONE"

using namespace std;
typedef struct system
{
    stringstream onGoingCommand;
    list<struct task> tasksList;
    list<struct employee> employeeList;
    int toDo;
    int onGoing;
    int done;

} SYSTEM;

typedef struct employee
{
    string name;
    list<struct task> tasklist;
    int doneTasks;
    int tasks;
} EMPLOYEE;

typedef struct task
{
    string taskName;
    int taskPriority;
    string taskStatus;
    list<EMPLOYEE> employeelist;
} TASK;

void base(SYSTEM &sys, string &command);
void doCommand(SYSTEM &);
void addTask(SYSTEM &);
void findTaskPosition(SYSTEM &sys, TASK &task);
void addEmployee(SYSTEM &sys);
void assignEmployee(SYSTEM &sys);
EMPLOYEE &findEmployee(SYSTEM &sys, string employeeName);
TASK &findTask(SYSTEM &sys, string taskName);
void employeeManagement(SYSTEM &sys, TASK &task, EMPLOYEE &employee);
void taskManagement(SYSTEM &sys, TASK &task, EMPLOYEE &employee);
void assignEmployee(SYSTEM &sys);
void finishTask(SYSTEM &sys);
void report(SYSTEM &sys);
void reportAll(SYSTEM &sys);
void reportOnGoing(SYSTEM &sys);
void reportEmployee(SYSTEM &sys);
void erasetask(SYSTEM &sys, TASK &task);

int main()
{
    string command;
    SYSTEM sys;
    sys.done = 0;
    sys.onGoing = 0;
    sys.toDo = 0;
    base(sys, command);

    return 0;
}

void base(SYSTEM &sys, string &command)
{
    while (getline(cin, command))
    {
        sys.onGoingCommand << command;
        doCommand(sys);
        sys.onGoingCommand.clear();
    }
}

void doCommand(SYSTEM &sys)
{
    string order;
    sys.onGoingCommand >> order;
    if (order == ADDTASK)
    {
        addTask(sys);
    }
    else if (order == ADDEMPLOYEE)
    {
        addEmployee(sys);
    }
    else if (order == ASSIGNEMPLOYEE)
    {
        assignEmployee(sys);
    }
    else if (order == FINISHTASK)
    {
        finishTask(sys);
    }
    else if (order == REPORT)
    {
        report(sys);
    }
}

void addTask(SYSTEM &sys)
{
    sys.toDo++;
    string taskName;
    string tmp;
    int taskPriority;
    sys.onGoingCommand >> taskName;
    sys.onGoingCommand >> tmp;
    taskPriority = stoi(tmp);
    TASK task;
    task.taskName = taskName;
    task.taskPriority = taskPriority;
    task.taskStatus = TODO;
    findTaskPosition(sys, task);
}

void findTaskPosition(SYSTEM &sys, TASK &task)
{
    if (sys.tasksList.empty())
    {
        sys.tasksList.push_back(task);
    }
    else
    {
        bool inserted = false;
        for (auto i = sys.tasksList.begin(); i != sys.tasksList.end(); ++i)
        {
            if (i->taskPriority == task.taskPriority && i->taskName > task.taskName)
            {
                sys.tasksList.insert(i, task);
                inserted = true;
                break;
            }
            if (i->taskPriority > task.taskPriority)
            {
                sys.tasksList.insert(i, task);
                inserted = true;
                break;
            }
        }
        if (!inserted)
        {
            sys.tasksList.push_back(task);
        }
    }
}

void addEmployee(SYSTEM &sys)
{
    string employeeName;
    sys.onGoingCommand >> employeeName;
    EMPLOYEE employee;
    employee.name = employeeName;
    employee.doneTasks = 0;
    employee.tasks = 0;
    sys.employeeList.push_back(employee);
}

void assignEmployee(SYSTEM &sys)
{
    string taskName, employeeName;
    sys.onGoingCommand >> taskName;
    sys.onGoingCommand >> employeeName;
    TASK &task = findTask(sys, taskName);
    EMPLOYEE &employee = findEmployee(sys, employeeName);
    taskManagement(sys, task, employee);
    employeeManagement(sys, task, employee);
}

void taskManagement(SYSTEM &sys, TASK &task, EMPLOYEE &employee)
{
    bool inserted = false;
    if (task.taskStatus == TODO)
    {
        task.taskStatus = ONGOING;
        sys.toDo--;
        sys.onGoing++;
        task.employeelist.push_back(employee);
        inserted = true;
    }
    else
    {
        for (auto it = task.employeelist.begin(); it != task.employeelist.end(); ++it)
        {
            if (it->name > employee.name)
            {
                task.employeelist.insert(it, employee);
                inserted = true;
                break;
            }
        }
    }
    if (!inserted)
    {
        task.employeelist.push_back(employee);
    }
}

void employeeManagement(SYSTEM &sys, TASK &task, EMPLOYEE &employee)
{
    employee.tasklist.push_back(task);
    employee.tasks++;
}

TASK &findTask(SYSTEM &sys, string taskName)
{
    for (auto it = sys.tasksList.begin(); it != sys.tasksList.end(); ++it)
    {
        if (it->taskName == taskName)
        {
            return *it;
        }
    }
    throw runtime_error(" ");
}

EMPLOYEE &findEmployee(SYSTEM &sys, string employeeName)
{
    for (auto it = sys.employeeList.begin(); it != sys.employeeList.end(); ++it)
    {
        if (it->name == employeeName)
        {
            return *it;
        }
    }
    throw runtime_error(" ");
}

void finishTask(SYSTEM &sys)
{
    string taskName;
    sys.onGoingCommand >> taskName;
    TASK &task = findTask(sys, taskName);
    sys.onGoing--;
    sys.done++;
    task.taskStatus = DONE;
    for (auto it = task.employeelist.begin(); it != task.employeelist.end(); ++it)
    {
        EMPLOYEE &realEmployee = findEmployee(sys, it->name);
        realEmployee.doneTasks++;
    }
    erasetask(sys, task);
}

void erasetask(SYSTEM &sys, TASK &task)
{
    for (auto it = task.employeelist.begin(); it != task.employeelist.end(); ++it)
    {
        EMPLOYEE &realEmployee = findEmployee(sys, it->name);
        for (auto it2 = (realEmployee.tasklist).begin(); it2 != (realEmployee.tasklist).end();)
        {
            if (it2->taskName == task.taskName)
            {
                realEmployee.tasklist.erase(it2);

                break;
            }
            else
            {
                ++it2;
            }
        }
    }
}
void report(SYSTEM &sys)
{
    string reportstr;
    sys.onGoingCommand >> reportstr;
    if (reportstr == "all")
    {
        reportAll(sys);
    }
    else if (reportstr == "ongoing")
    {
        reportOnGoing(sys);
    }
    else if (reportstr == "employee")
    {
        reportEmployee(sys);
    }
}

void reportAll(SYSTEM &sys)
{
    cout << "TODO: " << sys.toDo << endl;
    cout << "ONGOING: " << sys.onGoing << endl;
    cout << "DONE: " << sys.done << endl;
}

void reportOnGoing(SYSTEM &sys)
{
    for (auto ittask = sys.tasksList.begin(); ittask != sys.tasksList.end(); ++ittask)
    {
        if (ittask->taskStatus == ONGOING)
        {
            cout << ittask->taskName << " (" << ittask->taskPriority << "): ";
            bool flag = true;
            for (auto itemployee = (ittask->employeelist).begin(); itemployee != (ittask->employeelist).end(); ++itemployee)
            {
                if (itemployee == --(ittask->employeelist).end())
                {
                    flag = false;
                }
                cout << itemployee->name;
                if (!flag)
                {
                    cout << "\n";
                }
                else
                {
                    cout << ", ";
                }
            }
        }
    }
}

void reportEmployee(SYSTEM &sys)
{
    string employeeName;
    sys.onGoingCommand >> employeeName;
    EMPLOYEE &employee = findEmployee(sys, employeeName);
    cout << employee.name << " has done " << employee.doneTasks << " tasks." << endl;
    if (employee.tasks - employee.doneTasks == 0)
    {
        cout << employee.name << " is currently not working on any tasks." << endl;
    }
    else
    {
        cout << employee.name << " is currently working on these tasks:\n";
        int i = 0;
        for (auto it = employee.tasklist.begin(); it != employee.tasklist.end(); ++it)
        {
            if (it->taskStatus == ONGOING)
            {
                i++;
                cout << i << ". " << it->taskName << endl;
            }
        }
    }
}
