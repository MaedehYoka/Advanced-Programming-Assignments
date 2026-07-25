#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;
const double TAX = 1.1;
typedef struct dailySystem
{
    int numOfItems;
    int discountPercent;
    int maxDiscount;
    int minPurchase;
    vector<pair<string, int>> menuItems;
} SYSTEM;
void getInput(SYSTEM &system);
void printTheBestWay(const vector<int> &finalvec, const vector<pair<string, int>> &menu);
void findBestSubset(const SYSTEM &system, int &maxValidSum, vector<int> &finalVec, int n, const vector<pair<string, int>> &menu, vector<int> &subset, int index);
void updateVectorWithBetterPattern(int &maxValidSum, vector<int> &finalVec, vector<int> &subset, int sum);
int sumOfItemsValue(const vector<pair<string, int>> &menu, vector<int> &subset);
bool checkValidity(int price, const SYSTEM system);
bool checkMaxDiscount(float discount, const SYSTEM &system);
bool checkMinPrice(float price, const SYSTEM &system);
float applyTax(int price);
float calculateDiscount(const SYSTEM &system, float price);
float applyDiscount(float price, float discount);
int main()
{
    SYSTEM system;
    getInput(system);
    vector<int> finalVec, subset;
    int maxValid = 0;
    int index = 0;
    findBestSubset(system, maxValid, finalVec, system.numOfItems, system.menuItems, subset , index);
    printTheBestWay(finalVec , system.menuItems);
    return 0;
}
void getInput(SYSTEM &system)
{
    cin >> system.numOfItems;
    cin >> system.discountPercent;
    cin >> system.minPurchase;
    cin >> system.maxDiscount;
    for (int i = 0; i < system.numOfItems; i++)
    {
        pair<string, int> itemInfo;
        cin >> itemInfo.first;
        cin >> itemInfo.second;
        system.menuItems.push_back(itemInfo);
    }
}
void printTheBestWay(const vector<int> &finalvec, const vector<pair<string, int>> &menu)
{
    for (auto it = finalvec.begin(); it != finalvec.end(); it++)
    {
        cout << menu[*it].first << endl;
    }
}
void findBestSubset(const SYSTEM &system, int &maxValidSum, vector<int> &finalVec, int n, const vector<pair<string, int>> &menu, vector<int> &subset, int index)
{
    if (index == n)
    {
        int sum = sumOfItemsValue(menu, subset);
        if (checkValidity(sum, system) && sum > maxValidSum)
        {
            updateVectorWithBetterPattern(maxValidSum, finalVec, subset, sum);
        }
        return;
    }
    findBestSubset(system, maxValidSum, finalVec, n, menu, subset, index + 1);
    subset.push_back(index);
    findBestSubset(system, maxValidSum, finalVec, n, menu, subset, index + 1);
    subset.pop_back();
}
void updateVectorWithBetterPattern(int &maxValidSum, vector<int> &finalVec, vector<int> &subset, int sum)
{
    maxValidSum = sum;
    finalVec = subset;
}
int sumOfItemsValue(const vector<pair<string, int>> &menu, vector<int> &subset)
{
    int sum = 0;
    for (auto it = subset.begin(); it != subset.end(); it++)
    {
        sum += menu[*it].second;
    }
    return sum;
}
bool checkValidity(int price, const SYSTEM system)
{
    float priceWithTax = applyTax(price);
    float discount = calculateDiscount(system, priceWithTax);
    float finalAmount = applyDiscount(priceWithTax, discount);
    if (checkMinPrice(priceWithTax, system) && checkMaxDiscount(discount, system))
    {
        return true;
    }

    return false;
}
bool checkMaxDiscount(float discount, const SYSTEM &system)
{
    if (discount > system.maxDiscount)
    {
        return false;
    }
    return true;
}
bool checkMinPrice(float price, const SYSTEM &system)
{
    if (price < system.minPurchase)
    {
        return false;
    }
    return true;
}
float applyTax(int price)
{
    float priceWithTax = price * TAX;
    return priceWithTax;
}
float calculateDiscount(const SYSTEM &system, float price)
{
    float discount = (price * system.discountPercent) / 100;
    return discount;
}
float applyDiscount(float price, float discount)
{
    return price - discount;
}