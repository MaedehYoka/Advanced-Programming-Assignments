#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>

const std::string DOOR = "door";
const std::string WINDOW = "window";
const std::string MIDDLE = "middle";
const std::string SHOW_TABLE_INFO = "show_table_info";
const std::string ENTER = "enter";
const std::string RESERVE_TABLE = "reserve_table";
const std::string EXIT = "exit";
const std::string SWITCH = "switch";
using namespace std;

typedef struct table
{
    int id;
    int x;
    int y;
    int capacity;
    string type;
    int waitingNum, seatedNum;
    list<struct student *> waitingList;
    list<struct student *> seatedList;
    int score;
    bool operator<(const table &other) const
    {
        return score > other.score;
    }

} TABLE;

typedef struct student
{
    int id;
    string name;
    int friendId;
    int enemyId;
    bool isSeated;
    TABLE *sittingTable;
    TABLE *waitingTable;

    bool operator<(const student &other) const
    {
        return name < other.name;
    }
} STUDENT;

void readTableCSV(const string &fileAddress, vector<TABLE> &table);
TABLE createTableVec(stringstream &tableInformation, vector<TABLE> &table);
STUDENT createStudentVec(stringstream &studentInformation, vector<STUDENT> &student);
void readStudentCSV(const string &fileaddress, vector<STUDENT> &student);
void showTableInfo(vector<TABLE> &table, stringstream &command);
void showSeatedPeople(TABLE &table);
void showTableRemaningCapacity(TABLE &table);
void getCommand(vector<TABLE> &table, vector<STUDENT> &student);
int findDistance(TABLE table1, TABLE table2);
int ratingByType(string type);
STUDENT *findStudentById(int id, vector<STUDENT> &student);
vector<TABLE> arrangeTables(vector<TABLE> table, STUDENT student, vector<STUDENT> studentVec);
void enter(vector<STUDENT> &student, vector<TABLE> &table, stringstream &command);
void reserveTable(stringstream &command, vector<TABLE> &table, vector<STUDENT> &student);
TABLE *findTableById(int id, vector<TABLE> &table);
void exit(stringstream &command, vector<STUDENT> &student);
void removeStudent(STUDENT &student);
void vacateTable(TABLE &table, STUDENT &student);
void replaceWithNewStudent(TABLE &table, STUDENT &student, STUDENT &mate);
void switchStudents(stringstream &command, vector<STUDENT> &studentVec);

int main(int argc, char *argv[])
{
    string tableFile = argv[1];
    string studentFile = argv[2];
    vector<TABLE> table;
    vector<STUDENT> student;
    readTableCSV(tableFile, table);
    readStudentCSV(studentFile, student);
    getCommand(table, student);
    return 0;
}

void getCommand(vector<TABLE> &table, vector<STUDENT> &student)
{
    string command;
    while (getline(cin, command))
    {
        stringstream commandstream;
        commandstream << command;
        string action;
        commandstream >> action;
        if (action == SHOW_TABLE_INFO)
        {
            showTableInfo(table, commandstream);
        }
        else if (action == ENTER)
        {
            enter(student, table, commandstream);
        }
        else if (action == RESERVE_TABLE)
        {
            reserveTable(commandstream, table, student);
        }
        else if (action == EXIT)
        {
            exit(commandstream, student);
        }
        else if (action == SWITCH)
        {
            switchStudents(commandstream, student);
        }
    }
}

void readTableCSV(const string &fileAddress, vector<TABLE> &table)
{
    ifstream file(fileAddress);
    string line;
    getline(file, line);
    while (getline(file, line))
    {
        stringstream tableInformation(line);
        createTableVec(tableInformation, table);
    }
}

void readStudentCSV(const string &fileaddress, vector<STUDENT> &student)
{
    ifstream file(fileaddress);
    string line;
    getline(file, line);
    while (getline(file, line))
    {
        stringstream studentInformation(line);
        createStudentVec(studentInformation, student);
    }
}

TABLE createTableVec(stringstream &tableInformation, vector<TABLE> &table)
{
    TABLE newTable;
    int id, x, y, capacity;
    string type, tmp;
    newTable.seatedNum = 0;
    newTable.waitingNum = 0;
    newTable.score = 0;
    getline(tableInformation, tmp, ',');
    newTable.id = stoi(tmp);
    getline(tableInformation, tmp, ',');
    newTable.x = stoi(tmp);
    getline(tableInformation, tmp, ',');
    newTable.y = stoi(tmp);
    getline(tableInformation, tmp, ',');
    newTable.capacity = stoi(tmp);
    getline(tableInformation, newTable.type);
    table.push_back(newTable);
    return newTable;
}

STUDENT createStudentVec(stringstream &studentInformation, vector<STUDENT> &student)
{
    STUDENT newStudent;
    int id, friendId, enemyId;
    string name, tmp;
    getline(studentInformation, tmp, ',');
    newStudent.id = stoi(tmp);
    getline(studentInformation, newStudent.name, ',');
    getline(studentInformation, tmp, ',');
    newStudent.friendId = stoi(tmp);
    getline(studentInformation, tmp);
    newStudent.enemyId = stoi(tmp);
    student.push_back(newStudent);
    newStudent.isSeated = false;

    return newStudent;
}

void showTableInfo(vector<TABLE> &table, stringstream &command)
{
    string tmp;
    command >> tmp;
    int id = stoi(tmp);
    for (auto it = table.begin(); it != table.end(); ++it)
    {
        if (it->id == id)
        {
            cout << "Table ID: " << it->id << "\n";
            TABLE tmpTable = *it;
            showSeatedPeople(tmpTable);
            showTableRemaningCapacity(*it);
            cout << "Waiting queue length: " << it->waitingNum << endl;
        }
    }
}

void showSeatedPeople(TABLE &table)
{
    cout << "People at the table: ";
    bool commaChek = false;
    table.seatedList.sort([](const STUDENT *a, const STUDENT *b)
                          { return a->name < b->name; });
    for (auto peopleIt = table.seatedList.begin(); peopleIt != table.seatedList.end(); ++peopleIt)
    {
        if (!commaChek)
        {
            cout << (*peopleIt)->name;
            commaChek = true;
        }
        else
        {
            cout << ", " << (*peopleIt)->name;
        }
    }
    cout << endl;
}

void showTableRemaningCapacity(TABLE &table)
{
    cout << "Table remaning capacity: ";
    int remainingcapacity = table.capacity - table.seatedNum;
    cout << remainingcapacity << endl;
}

int findDistance(TABLE table1, TABLE table2)
{
    int xDistance, yDistance;
    xDistance = table1.x - table2.x;
    yDistance = table1.y - table2.y;
    xDistance = abs(xDistance);
    yDistance = abs(yDistance);
    return xDistance + yDistance;
}

vector<TABLE> arrangeTables(vector<TABLE> table, STUDENT student, vector<STUDENT> studentVec)
{
    int friendId, enemyId;
    friendId = student.friendId;
    enemyId = student.enemyId;
    STUDENT *mate;
    STUDENT *enemy;
    mate = findStudentById(friendId, studentVec);
    enemy = findStudentById(enemyId, studentVec);
    int friendDistance, enemyDiastance, typeBonus;
    friendDistance = 0;
    enemyDiastance = 0;
    for (auto it = table.begin(); it != table.end(); ++it)
    {
        if (mate->isSeated)
        {
            friendDistance = findDistance(*it, *mate->sittingTable);
        }
        if (enemy->isSeated)
        {
            enemyDiastance = findDistance(*it, *enemy->sittingTable);
        }
        typeBonus = ratingByType(it->type);
        it->score = enemyDiastance - friendDistance + typeBonus;
    }
    sort(table.begin(), table.end());
    return table;
}

STUDENT *findStudentById(int id, vector<STUDENT> &student)
{

    for (auto &it : student)
    {
        if (it.id == id)
        {
            return &it;
        }
    }
}

int ratingByType(string type)
{
    if (type == DOOR)
    {
        return 4;
    }
    else if (type == WINDOW)
    {
        return 6;
    }
    else
    {
        return 2;
    }
}

void enter(vector<STUDENT> &student, vector<TABLE> &table, stringstream &command)
{
    string tmp;
    command >> tmp;
    int id = stoi(tmp);
    STUDENT *identifiedStudent;
    identifiedStudent = findStudentById(id, student);
    vector<TABLE> sortedTableList = arrangeTables(table, *identifiedStudent, student);
    for (auto it : sortedTableList)
    {
        cout << "Table " << it.id << ": ";
        cout << (it.capacity - it.seatedNum) << " " << it.waitingNum;
        cout << endl;
    }
}

void reserveTable(stringstream &command, vector<TABLE> &table, vector<STUDENT> &student)
{
    string tmp;
    int studentId, tableId;
    command >> tmp;
    studentId = stoi(tmp);
    STUDENT *identifiedStudent = findStudentById(studentId, student);
    if (command.eof())
    {
        vector<TABLE> sortedTable = arrangeTables(table, *identifiedStudent, student);
        tableId = sortedTable.front().id;
    }
    else
    {
        command >> tmp;
        tableId = stoi(tmp);
    }
    TABLE *requestedTable = findTableById(tableId, table);
    if (requestedTable->capacity - requestedTable->seatedNum > 0)
    {
        requestedTable->seatedNum++;
        requestedTable->seatedList.push_back(identifiedStudent);
        identifiedStudent->isSeated = true;
        identifiedStudent->sittingTable = requestedTable;
        cout << identifiedStudent->name << " sits at table " << requestedTable->id << endl;
    }
    else
    {
        requestedTable->waitingNum++;
        requestedTable->waitingList.push_back(identifiedStudent);
        identifiedStudent->waitingTable = requestedTable;
        cout << identifiedStudent->name << " enters the waiting queue of table " << requestedTable->id << endl;
    }
}

TABLE *findTableById(int id, vector<TABLE> &table)
{
    for (auto &it : table)
    {
        if (it.id == id)
        {
            return &it;
        }
    }
}

void exit(stringstream &command, vector<STUDENT> &student)
{
    string tmp;
    command >> tmp;
    int id = stoi(tmp);
    STUDENT *identifiedStudent;
    identifiedStudent = findStudentById(id, student);
    TABLE *identifiedTable = identifiedStudent->sittingTable;
    STUDENT *mate = findStudentById(identifiedStudent->friendId , student);
    replaceWithNewStudent(*identifiedTable, *identifiedStudent, *mate);  
    vacateTable(*identifiedTable, *identifiedStudent);
    removeStudent(*identifiedStudent);

    cout << identifiedStudent->name << " exits!\n";
}

void removeStudent(STUDENT &student)
{
    student.sittingTable = nullptr;
    student.isSeated = false;
}

void vacateTable(TABLE &table, STUDENT &student)
{
    for (auto it = (table.seatedList).begin(); it != (table.seatedList).end(); ++it)
    {
        if (*it == &student)
        {
            table.seatedList.erase(it);
            table.seatedNum--;
            break;
        }
    }
}

void replaceWithNewStudent(TABLE &table, STUDENT &student, STUDENT &mate)
{
    int id = student.friendId;
    if (table.waitingList.empty())
    {
    }
    else if (mate.waitingTable == &table)
    {
        table.seatedNum++;
        table.seatedList.push_back(&mate);
        table.waitingNum--;
        mate.waitingTable = nullptr;
        mate.sittingTable = &table;
        for (auto it = table.waitingList.begin(); it != table.waitingList.end(); ++it)
        {
            if (*it == &mate)
            {
                table.waitingList.erase(it);
                break;
            }
        }
    }
    else
    {
       table.seatedNum++;
        table.waitingNum--;
        STUDENT *newStudent = table.waitingList.front();
        newStudent->isSeated = true;
        newStudent->sittingTable = &table;
        newStudent->waitingTable = nullptr;
        table.seatedList.push_back(newStudent);
        table.waitingList.pop_front();
    }
}

void switchStudents(stringstream &command, vector<STUDENT> &studentVec)
{
    string tmp;
    int id;
    command >> tmp;
    id = stoi(tmp);
    STUDENT *student, *studentsfriend;
    student = findStudentById(id, studentVec);
    studentsfriend = findStudentById(student->friendId, studentVec);
    TABLE *tableTmp = student->sittingTable;
    for (auto it = tableTmp->seatedList.begin(); it != tableTmp->seatedList.end(); ++it)
    {
        if (*it == student)
        {
            tableTmp->seatedList.erase(it);
            break;
        }
    }
    tableTmp->seatedList.push_back(studentsfriend);
    student->sittingTable = studentsfriend->sittingTable;
    studentsfriend->sittingTable = tableTmp;
    tableTmp = student->sittingTable;
    for (auto it = tableTmp->seatedList.begin(); it != tableTmp->seatedList.end(); ++it)
    {
        if (*it == studentsfriend)
        {
            tableTmp->seatedList.erase(it);
            break;
        }
    }
    tableTmp->seatedList.push_back(student);
    cout << student->name << " switches seats with " << studentsfriend->name << "!" << endl;
}
