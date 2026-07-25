#include <iostream>
#include <string>
const std::string typeFrac = "+\\frac{";
const std::string typeFracP2 = "}{";
const std::string typeFracP3 = "}";
using namespace std;
void doLaTeX(int step , int firstStep);
int main(){
    int n;
    cin >> n;
    doLaTeX (n, 1);
    return 0;
}
void doLaTeX(int step , int firstStep){
    if (step == 1){
        cout << firstStep;
    }
    else{
        int upNum , downNum;
        upNum = 2 * firstStep;
        downNum = upNum + 1;
        cout << firstStep << typeFrac;
        doLaTeX(step - 1 , upNum);
        cout << typeFracP2;
        doLaTeX(step - 1 , downNum);
        cout << typeFracP3;
    }
}