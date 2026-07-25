#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "data.hpp"
#include "attend.hpp"
#include "reports.hpp"
using namespace std;
const string CREATE = "create_template";
const string GENERATE = "generate_test";
const string ATTEND = "attend";
const string AUTO = "auto_generate";
const string ALL = "all";
const string TEST = "test";
const string TESTS = "tests";
const string SUBJECT = "subject";
const string REPORT = "report";
void handleCommand(stringstream &ss, string &line, string &command, vector<testTemplate *> &templates, vector<test *> &tests, vector<subject *> &subjects, vector<question *> &questions , vector<test *> &attendedTests);
int main(int argc, char *argv[])
{
    string fileAddress = argv[1];
    vector<question *> questions;
    vector<subject *> subjects;
    vector<testTemplate *> templates;
    vector<test *> tests;
    vector<test *> attendedTests;
    saveData(fileAddress, questions, subjects);
    string line;
    while (getline(cin, line))
    {
        stringstream ss(line);
        string command;
        getline(ss, command, ' ');
        handleCommand(ss , line , command, templates, tests, subjects, questions , attendedTests);
        ss.str("");
        line.clear();
    }
    return 0;
}
void handleCommand(stringstream &ss, string &line, string &command, vector<testTemplate *> &templates, vector<test *> &tests, vector<subject *> &subjects, vector<question *> &questions , vector<test *> &attendedTests)
{
    if (command == CREATE)
    {
        handleCreateTemplate(ss, templates);
    }
    else if (command == GENERATE)
    {
        handleGenerateTest(ss, templates, tests);
    }
    else if (command == ATTEND)
    {
        attendingTest(ss , subjects , tests , attendedTests);
    }
    else if (command == AUTO)
    {
        
        autoTest(ss, subjects, tests);
    }
    else if(command == REPORT){
        getline(ss , command , ' ');
        if (command == ALL)
        {
            reportAll(subjects);
        }
        else if (command == TEST)
        {
            reportTest(ss , subjects , tests);
        }
        else if (command == TESTS)
        {
            reportTests(attendedTests);
        }
        else if (command == SUBJECT)
        {
            reportSubject(ss , subjects);
        }
    }
   
}
