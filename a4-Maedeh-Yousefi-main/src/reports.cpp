#include "reports.hpp"
void reportAll(vector<subject *> subjects)
{
    sort(subjects.begin(), subjects.end(), [](subject *a, subject *b)
         { return a->returnName() < b->returnName(); });
    cout << "Total report:\n";
    cout << endl;
    int totalCorrect = 0, totalBlank = 0, totalIncorrect = 0;
    for (auto it : subjects)
    {
        totalBlank += (*it).returnBlank();
        totalCorrect += (*it).returnCorrect();
        totalIncorrect += (*it).returnIncorrect();
        subject *tmp = it;
        showThisRep(tmp->returnName(), tmp->returnCorrect(), tmp->returnIncorrect(), tmp->returnBlank());
    }
    totalResult(totalCorrect , totalIncorrect , totalBlank);
}
void reportTest(stringstream &ss, vector<subject *> &subjects, vector<test *> &tests)
{
    string testName;
    getline(ss, testName);
    test *tst = findTest(testName, tests);
    testName = testName.substr(1, testName.size() - 2);
    cout << "Results for " << testName << ":\n";
    cout << endl;
    string subName = "";
    int correct = 0, incorrect = 0, blank = 0, i = 0;
    int totalCorrect = 0 , totalIncorrect = 0 , totalBlank = 0;
    for (auto it : tst->testQuestions)
    {
        if (subName == "")
        {
            subName = (*it).returnSubName();
        }
        if (subName != (*it).returnSubName())
        {
            showThisRep(subName, correct, incorrect, blank);
            correct = 0;
            incorrect = 0;
            blank = 0;
            subName = (*it).returnSubName();
        }
        if (tst->correction[i] == 1)
        {
            correct++;
            totalCorrect++;
        }
        else if (tst->correction[i] == 0)
        {
            blank++;
            totalBlank++;
        }
        else
        {
            incorrect++;
            totalIncorrect++;
        }
        i++;
    }
    totalResult(totalCorrect , totalIncorrect , totalBlank);
}
void showThisRep(string name, int correct, int incorrect, int blank)
{
    cout << name << ": ";
    cout << correct << " corrects, ";
    cout << incorrect << " incorrects and ";
    cout << blank << " blanks. Score: ";
    float percentage = ((float)correct / (correct + incorrect + blank)) * 100;
    cout << fixed << setprecision(3) << percentage << "%.\n";
}
void totalResult(int correct, int incorrect, int blank)
{
    float score = ((float)correct / (correct + incorrect + blank)) * 100;
    cout << endl;
    cout << "Total results: " << correct << " corrects, ";
    cout << incorrect << "incorrects and " << blank << " blanks.\n";
    cout << "Total score: " << fixed << setprecision(3) << score << "%.\n";
}
void reportTests(vector <test *> &attendingTests){
    string testName;
    cout << "Result per attended tests:\n";
    cout << endl;
    for(auto it: attendingTests){
        test *a = it;
        showThisRep(a->returnName().substr(1 , a->returnName().size() - 2) , a->correct , a->incorrect , a->blank);
    }  
}
void reportSubject(stringstream &ss , vector<subject *> &subjects){
    string name;
    getline(ss , name);
    cout << "Result for " << name << ":\n";
    cout << endl;
   // name = '\''+name+'\'';
    subject *sub = findSubject(subjects , name);
    int correct , incorrect , blank;
    int totalCorrect = 0, total = 0;
    correct = incorrect = blank = 0;
    sumCorrection(correct,incorrect,blank, sub->easy);
    totalCorrect += correct;
    total = total + correct + incorrect + blank;
    cout << "Easy: " << correct << " corrects, " << incorrect;
    cout <<" incorrects and " << blank << " blanks.\n";
    correct = incorrect = blank = 0;
    sumCorrection(correct,incorrect,blank, sub->medium);
    totalCorrect += correct;
    total = total + correct + incorrect + blank;
    cout << "Medium: " << correct << " corrects, " << incorrect;
    cout <<" incorrects and " << blank << " blanks.\n";
    correct = incorrect = blank = 0;
    sumCorrection(correct,incorrect,blank, sub->hard);
    totalCorrect += correct;
    total = total + correct + incorrect + blank;
    cout << "Hard: " << correct << " corrects, " << incorrect;
    cout <<" incorrects and " << blank << " blanks.\n";
    cout << endl;
    float scor = ((float)totalCorrect/total)*100;
    cout << "Total score: " ;
    cout << fixed << setprecision(3) << scor << "%.";  
    
}
void sumCorrection(int &correct , int &incorrect , int &blank , vector<question *> questions){
    for(auto it : questions){
        correct += (*it).correct;
        incorrect += (*it).incorrect;
        blank += (*it).blank;
    }
}