#ifndef REPORTS_HPP
#define REPORTS_HPP
#include "data.hpp"
#include "attend.hpp"
void reportAll(vector<subject*> subjects);
void reportTest(stringstream &ss, vector<subject *> &subjects, vector<test *> &tests);
void showThisRep(string name, int correct, int incorrect, int blank);
void totalResult(int correct, int incorrect, int blank);
void reportTests(vector <test *> &attendingTests);
void reportSubject(stringstream &ss , vector<subject *> &subjects);
void sumCorrection(int &correct , int &incorrect , int &blank , vector<question *> questions);
#endif