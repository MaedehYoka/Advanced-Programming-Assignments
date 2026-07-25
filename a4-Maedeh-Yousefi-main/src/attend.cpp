#include "attend.hpp"

void showTest(test *&tst)
{
    string testName = tst->returnName().substr(1, tst->returnName().size() - 2);
    cout << testName << ":" << endl;
    int cnt = 0;
    int questionSize = tst->testQuestions.size();
    vector<string> answer(questionSize, "");
    int k =0;
    while(cnt < questionSize && cnt >= 0){
        cout << endl;
        cout << cnt + 1 << ") ";
        showQuestion(tst->testQuestions[cnt], answer[cnt], cnt, answer, k);
    }
    cout <<endl<< "Finished " << testName << endl;
    finalizeTest(tst , answer);
    return;
}
void finalizeTest(test *&tst , vector<string> &answer){
    int i = 0;
    while(i < tst->testQuestions.size()){
        if(answer[i].empty()){
            tst->correction[i] = 0;
            tst->testQuestions[i]->blank++;
            tst->testQuestions[i]->priority ++;
        }
        else if(answer[i] == "1" || answer[i] == "2" ||answer[i] == "3"||answer[i] == "4") {
            if(stoi(answer[i]) == tst->testQuestions[i]->returnAns()){
                tst->correction[i] = 1;
                tst->testQuestions[i]->correct++;
                tst->testQuestions[i]->priority -= 2;
            }
            else{
                tst->correction[i] = -1;
                tst->testQuestions[i]->incorrect++;
                tst->testQuestions[i]->priority +=3;
            }
        }
        i++;
    }
    return;
}
void showQuestion(question *q, string &ans, int &cnt, vector<string> &answer , int &k)
{
    cout << q->returnText() << endl;
    for (int i = 1; i <= 4; i++)
    {
        showOption(i, ans, q);
    }
    getAnswer(cnt, answer , k);
    return;
}
void showOption(int i, string answer, question *q)
{
    int ans = 0;
    if (answer == "1" || answer == "2" || answer == "3" || answer == "4")
    {
        ans = stoi(answer);
    }
    cout << "    " << i << ". ";
    cout << q->returnOption(i);
    if (i == ans)
    {
        cout << " <-";
    }
    cout << endl;
    return;
}
void getAnswer(int &cnt, vector<string> &ans , int &k)
{
    cout << "Your answer: ";
    string answer;
    getline(cin, answer);
    while (!checkAnsValidation(answer, cnt, ans , k))
    {
        cout << "Invalid answer, please try again." << endl;
        cout << "Your answer: ";
        getline(cin, answer);
    }
    return;
}
bool checkAnsValidation(string answer, int &i, vector<string> &ans , int &k)
{
    if (answer.empty())
    {
        i++;
        return true;
    }
    else if (answer == "1" || answer == "2" || answer == "3" || answer == "4")
    {
        ans[i] = answer;
        i++;
        return true;
    }
    else if (answer == PREVIOUS)
    {
        if (i == 0)
        {

            return false;
        }
        else
        {
            i--;
            return true;
        }
    }
    else
    {

        return false;
    }
}
test *prepareTest(stringstream &ss, vector<test *> &tests, vector<subject *> &subjects)
{

    string testName = extractWithQuotes(ss);
    test *tst = findTest(testName, tests);



    if (tst == NULL)
    {
        cout << "Could not find test: " << testName << endl;
        return NULL;
    }
    bool checkAuto = tst->returnBool();
    if(!checkAuto)
    tst->setReqs(tst->returnTemplate()->returnrequirments());
    makeVecOfQuestions(tst->returnReq(), subjects , tst->testQuestions);
    sortQuestionVec(tst->testQuestions);
    tst->correction.resize(tst->testQuestions.size());
    return tst;
}
void sortQuestionVec(vector<question *> & questions){
    sort(questions.begin() , questions.end() , [](question *a , question *b){
        if(a->returnSubName() == b->returnSubName()){
            return a->returnText() < b->returnText();
        }
        return a->returnSubName() < b->returnSubName();
    });
}
void makeVecOfQuestions(vector<questionRequirement> reqs, vector<subject *> &subjects , vector<question *> &testQuestions)
{
    for (auto it = reqs.begin(); it != reqs.end(); it++)
    {
        addReqQuestionsToVec(*it, subjects, testQuestions);
    }

}
void addReqQuestionsToVec(questionRequirement req, vector<subject *> &subjects, vector<question *> &questionVec)
{
    subject *reqSub = findSubject(subjects, req.subjectName);
    if(reqSub == NULL){
        return;
    }
    vector<question *> reqVec = sortReqVec(reqSub, req.difficulty);
    for (int i = 0; i < req.count; i++)
    {
        questionVec.push_back(reqVec[i]);
    }
}
vector<question *> sortReqVec(subject *sub, string difficulty)
{
    vector <question *> questions;
    if (difficulty == EASY)
    {
        questions.resize(sub->easy.size());
        questions = sub->easy;
    }
    else if (difficulty == MEDIUM)
    {
        questions.resize(sub->medium.size());
        questions= sub->medium;
    }
    else if(difficulty == HARD)
    {
        questions.resize(sub->hard.size());
        questions = sub->hard;

    }
    sort(questions.begin(), questions.end(), [](question *a, question *b)
             { return a->priority > b->priority; });
    return questions;
}
void attendingTest(stringstream &ss, vector<subject *> &subjects, vector<test *> &tests , vector<test *> &attendedTests)
{

    test *tst = prepareTest(ss, tests, subjects );

    if (tst == NULL)
    {
        return;
    }
    showTest(tst);
    attendedTests.push_back(tst);
    return;
}