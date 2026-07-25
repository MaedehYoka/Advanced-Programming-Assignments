#ifndef TESE_HPP
#define TEST_HPP
#include "data.hpp"
#include "template.hpp"
class test{
    public:
    test(): correct(0) , incorrect(0) ,blank(0) , percent(0), autoCheck(false){};
    void putName(string name){testName = name;};
    void putTemplate(testTemplate *templ){templatee = templ;};
    string returnName() const {return testName;};
    testTemplate *returnTemplate(){return templatee;};
    void setReqs(vector<questionRequirement> req){testReqs = req;};
    vector<questionRequirement> returnReq(){return testReqs;};
    void itsAuto(bool a){autoCheck = a;};
    bool returnBool(){return autoCheck;};
    vector<question *> testQuestions;
    vector <int> correction;
    int correct , incorrect , blank , percent;
    private:
    vector<questionRequirement> testReqs;
    testTemplate *templatee;
    string testName;
    bool autoCheck;
};

test* handleGenerateTest(stringstream &ss , vector<testTemplate*> &templates , vector<test*> &tests);
test *findTest(string testName , vector<test *> &tests);
void autoTest(stringstream &ss , vector<subject*> subjects , vector<test *>&tests);
#endif