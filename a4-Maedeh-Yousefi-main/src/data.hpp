#ifndef DATA_HPP
#define DATA_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
using namespace std;
const string HARD = "hard";
const string MEDIUM = "medium";
const string EASY = "easy";
const string PREVIOUS = "previous";
class question
{
public:
    question() : correct(0), incorrect(0), blank(0), priority(0) {};
    void getQuestionText(string text) { questionText = text; };
    void getOption(int i, string option);
    void getAns(string i) { ans = stoi(i); };
    void getSubject(string str){subjectName = str;};
    string returnSubName(){return subjectName;};
    void getDifficulty(string str) { difficulty = str; };
    string returnDifficulty() { return difficulty; };
    string returnText() { return questionText; };
    string returnOption(int i);
    int returnAns(){return ans;};
    int correct, incorrect, blank, priority;

private:
    string questionText;
    string option1, option2, option3, option4;
    string subjectName;
    int ans;
    string difficulty;
};
class subject
{
public:
    subject() : easy(), medium(), hard() , percent(0), correct(0) , incorrect(0) , blank(0) {};
    void getName(string subjectName) { name = subjectName; };
    string returnName() { return name; };
    float percentage();
    vector<question *> easy;
    vector<question *> medium;
    vector<question *> hard;
    void returnReports();
    int returnCorrect(){return correct;};
    int returnBlank(){return blank;};
    int returnIncorrect(){return incorrect;};
private:
    string name;
    float percent;
    int correct , incorrect , blank;
};
void saveData(string fileAddress , vector<question *> &questions, vector<subject *> &subjects);
void saveSplitedData(string line, vector<question *> &questions, vector<subject *> &subjects);
question * saveQuestions(stringstream &ss, vector<question *> &questions , string &subjectName);
void saveSubject(string &subjectName , vector<subject*>& subjects , question &q);
subject* makeNewSub(vector<subject*> &subjects , string name);
void questionInSubjectVec(question &q , subject &s);
string extractWithQuotes(stringstream &ss);
subject *findSubject(vector<subject *> &subjects, string subjectName);
void findSubjectWithLowestPercentage(subject *&sub1 , subject *&sub2 , vector<subject *> &subjects);
#endif