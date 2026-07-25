#include "test.hpp"
test *handleGenerateTest(stringstream &ss, vector<testTemplate *> &templates, vector<test *> &tests)
{
    string testName, templateName;
    testName = extractWithQuotes(ss);
    templateName = extractWithQuotes(ss);
    testTemplate *tmpl = findTemplate(templateName, templates);
    if (tmpl == NULL)
    {
        cout << "Could not find template: " << templateName << endl;
        return NULL;
    }
    test *newTest = new test();
    bool a = false;
    newTest->itsAuto(a);
    newTest->putName(testName);
    newTest->putTemplate(tmpl);
    tests.push_back(newTest);
    cout << "Test " << testName << " was generated successfully.\n";
    return newTest;
}
test *findTest(string testName, vector<test *> &tests)
{
    auto it = find_if(tests.begin(), tests.end(), [testName](test *a)
                      { return a->returnName() == testName; });
    if (it != tests.end())
    {
        return *it;
    }
    else
    {
        return NULL;
    }
}
void autoTest(stringstream &ss, vector<subject *> subjects, vector<test *> &tests)
{
    string testName = extractWithQuotes(ss);
    test *newTest = new test();
    newTest->itsAuto(true);
    newTest->putName(testName);
    subject *sub1, *sub2;
    findSubjectWithLowestPercentage(sub1, sub2, subjects);
    vector<questionRequirement> req;
    req.push_back({sub1->returnName(), EASY, 3});
    req.push_back({sub1->returnName(), MEDIUM, 2});
    req.push_back({sub1->returnName(), HARD, 1});
    req.push_back({sub2->returnName(), EASY, 2});
    req.push_back({sub2->returnName(), MEDIUM, 1});
    req.push_back({sub2->returnName(), HARD, 1});
    newTest->setReqs(req);
    tests.push_back(newTest);
    cout << "Test " << testName << " was generated successfully.\n";
}