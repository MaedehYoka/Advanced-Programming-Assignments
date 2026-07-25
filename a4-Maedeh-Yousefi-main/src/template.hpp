#ifndef TEMPLATE_HPP
#define TEMPLATE_HPP
#include "data.hpp"
const string DUPLICATED_NAME = "Duplicate name: ";
struct questionRequirement{
    string subjectName;
    string difficulty;
    int count;
};
class testTemplate
{
public:
    testTemplate(){};
    string returnName()const {return name;};
    void putName(string str){name = str;};
    vector <questionRequirement>&returnrequirments(){return questionRequirements;};
private:
    string name;
    vector <questionRequirement> questionRequirements;
};
testTemplate* handleCreateTemplate(stringstream &ss , vector<testTemplate*> &templates);
testTemplate* makeNewTemplate(string templateName , vector<testTemplate*> &templates , stringstream &ss);
testTemplate* findTemplate(string name , vector<testTemplate*> &templates);
#endif