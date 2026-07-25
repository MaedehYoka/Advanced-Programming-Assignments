#ifndef ATTEND_HPP
#define ATTEND_HPP
#include "data.hpp"
#include "test.hpp"
#include "template.hpp"
void attendingTest(stringstream &ss, vector<subject *> &subjects ,vector<test *> &tests ,vector<test *> &attendedTests);
void showTest(test *&tst);
void showQuestion(question *q, string &ans, int &cnt, vector<string> &answer , int &k);
void showOption(int i, string answer, question *q);
void getAnswer(int &i, vector<string> &ans , int &k);
bool checkAnsValidation(string answer, int &i, vector<string>& ans , int &k);
test *prepareTest(stringstream &ss, vector<test *> &tests, vector<subject *> &subjects);
void makeVecOfQuestions(vector<questionRequirement> reqs, vector<subject *> &subjects , vector<question *> &testQuestions);
void addReqQuestionsToVec(questionRequirement req, vector<subject *> &subjects, vector<question *> &questionVec);
vector<question *> sortReqVec(subject *sub, string difficulty);
void sortQuestionVec(vector<question *> & questions);
void finalizeTest(test *&tst , vector<string> &answer);
#endif