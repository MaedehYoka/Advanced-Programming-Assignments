#include "template.hpp"
testTemplate* handleCreateTemplate(stringstream &ss , vector<testTemplate*> &templates){
    string templateName = extractWithQuotes(ss);
    auto it = find_if(templates.begin() , templates.end() , [templateName](testTemplate *a){
        return a->returnName() == templateName;
    });
    if(it != templates.end()){
        cout << DUPLICATED_NAME << templateName << endl;
        return *it;
    }
    else{
        testTemplate* a = new testTemplate();
        a = makeNewTemplate(templateName , templates , ss);
        cout <<"Template " <<templateName<<" created successfully."<<endl;
        return a;
    }
}
testTemplate* makeNewTemplate(string templateName , vector<testTemplate*> &templates , stringstream &ss){
    testTemplate *newTemp = new testTemplate();
    newTemp->putName(templateName);
    templates.push_back(newTemp);
    string requirmentData;
    while(getline(ss , requirmentData , ' ')){
        stringstream require(requirmentData);
        string sub , difficulty , cnt;
        getline(require , sub, ':');
        getline(require , difficulty , ':');
        getline(require , cnt);
        questionRequirement newReq;
        newReq.subjectName=sub;
        newReq.difficulty=difficulty;
        newReq.count= stoi(cnt);
        newTemp->returnrequirments().push_back(newReq);
    }
    return newTemp;
}
testTemplate *findTemplate(string name , vector<testTemplate*> &templates){
    auto it = find_if(templates.begin(), templates.end(), [name](testTemplate *a){
        return a->returnName() == name;
    });
    if(it != templates.end()){
    return *it;
    }
    else{
        return NULL;
    }
}