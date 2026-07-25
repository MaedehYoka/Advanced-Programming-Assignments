#include "data.hpp"
string question::returnOption(int i)
{
    switch (i)
    {
    case 1:
        return option1;
        break;
    case 2:
        return option2;
        break;
    case 3:
        return option3;
        break;
    case 4:
        return option4;
        break;
    default:
        return "invalid";
        break;
    }
}
void question::getOption(int i, string option)
{
    switch (i)
    {
    case 1:
        option1 = option;
        break;
    case 2:
        option2 = option;
        break;
    case 3:
        option3 = option;
        break;
    case 4:
        option4 = option;
        break;
    default:
        break;
    }
}
void saveData(string fileAddress, vector<question *> &questions, vector<subject *> &subjects)
{
    ifstream file(fileAddress);
    string line;
    getline(file, line);
    int i = 1;
    while (getline(file, line))
    {
        saveSplitedData(line, questions, subjects);
    }
}
void saveSplitedData(string line, vector<question *> &questions, vector<subject *> &subjects)
{
    stringstream ss(line);
    string subjectName;
    question *q = new question();
    q = saveQuestions(ss, questions, subjectName);
    saveSubject(subjectName, subjects, *q);
}
question *saveQuestions(stringstream &ss, vector<question *> &questions, string &subjectName)
{
    string str;
    getline(ss, str, ',');
    question *newQuestion = new question();
    questions.push_back(newQuestion);
    newQuestion->getQuestionText(str);
    for (int i = 1; i <= 4; i++)
    {
        getline(ss, str, ',');
        newQuestion->getOption(i, str);
    }
    getline(ss, str, ',');
    newQuestion->getAns(str);
    getline(ss, str, ',');
    newQuestion->getDifficulty(str);
    getline(ss, subjectName);
    newQuestion->getSubject(subjectName);
    return newQuestion;
}
void saveSubject(string &subjectName, vector<subject *> &subjects, question &q)
{
    auto it = find_if(subjects.begin(), subjects.end(), [subjectName](subject *a) { 
        return a->returnName() == subjectName; });


    subject *sub = new subject();
    if (it == subjects.end())
    {
        sub = makeNewSub(subjects, subjectName);
    }
    else
    {
        sub = *it;
    }
    questionInSubjectVec(q, *sub);
}
subject *makeNewSub(vector<subject *> &subjects, string name)
{
    subject *newSub = new subject();
    newSub->getName(name);
    subjects.push_back(newSub);
    return newSub;
}
void questionInSubjectVec(question &q, subject &s)
{
    if (q.returnDifficulty() == EASY)
    {
        s.easy.push_back(&q);
    }
    else if (q.returnDifficulty() == MEDIUM)
    {
        s.medium.push_back(&q);
    }
    else if (q.returnDifficulty() == HARD)
    {
        s.hard.push_back(&q);
    }
}
string extractWithQuotes(stringstream &ss)
{
    string result;
    char ch;
    int quoteCount = 0;

    while (ss.get(ch))
    {
        if (ch == '\'')
        {
            quoteCount++;
            result += ch; // خود ' هم اضافه می‌کنیم
            if (quoteCount == 2)
                break;
            continue;
        }
        if (quoteCount >= 1)
        {
            result += ch;
        }
    }
    ss.get(ch);
    return result;
}
subject *findSubject(vector<subject *> &subjects, string subjectName)
{
    auto it = find_if(subjects.begin(), subjects.end(), [subjectName](subject *a)
 { return a->returnName() == subjectName; });

    if (it != subjects.end())
    {
        return *it;
    }
    else
    {
        return NULL;
    }
}
float subject:: percentage(){
    int correct , all;
    correct = 0;
    all = 0;
    for(auto it: easy){
        correct += (*it).correct;
        all = all + (*it).correct + (*it).incorrect + (*it).blank;
    }
    for(auto it: medium){
        correct += (*it).correct;
        all = all + (*it).correct + (*it).incorrect + (*it).blank;
    }
    for(auto it: hard){
        correct += (*it).correct;
        all = all + (*it).correct + (*it).incorrect + (*it).blank;
    }
    percent = (correct / all)*100;
    return percent;
}
void findSubjectWithLowestPercentage(subject *&sub1 , subject *&sub2 , vector<subject *> &subjects){
    if (subjects.size() < 2) {
        sub1 = nullptr;
        sub2 = nullptr;
        return;
    }
    if (subjects[0]->percentage() < subjects[1]->percentage()) {
        sub1 = subjects[0];
        sub2 = subjects[1];
    } else {
        sub1 = subjects[1];
        sub2 = subjects[0];
    }
    for (size_t i = 2; i < subjects.size(); i++) {
        if (subjects[i]->percentage() < sub1->percentage()) {
            sub2 = sub1;
            sub1 = subjects[i];
        } else if (subjects[i]->percentage() < sub2->percentage()) {
            sub2 = subjects[i];
        }
    }
}

void subject:: returnReports(){
    for(auto it : easy){
        correct += (*it).correct;
        blank += (*it).blank;
        incorrect += (*it).incorrect;
    }
    for(auto it : medium){
        correct += (*it).correct;
        blank += (*it).blank;
        incorrect += (*it).incorrect;
    }
    for(auto it : hard){
        correct += (*it).correct;
        blank += (*it).blank;
        incorrect += (*it).incorrect;
    }
}