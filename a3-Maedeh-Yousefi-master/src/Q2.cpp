#include <iostream>
#include <string>
using namespace std;
int findOldestInRightSits(int n, int giverSitNum, int *a, bool *sited);
int findOldestInLefttSits(int n, int giverSitNum, int *a, bool *sited);
void giveMoney(int giverSit, int *a, int *t, int *finalMoney, bool *sited, int n);
void receiveNum(int n, int *arr);
int findTheOldest(int n, int *a);
void printFinalMony(int n, int *finalMoney);
int main()
{
    int n, cnt;
    cnt = 0;
    cin >> n;
    int t[n];
    int a[n];
    receiveNum(n, a);
    receiveNum(n, t);
    bool sited[n];
    fill(sited, sited + n, true);
    int finalMoney[n] = {0};
    int king = findTheOldest(n, a);
    giveMoney(king, a, t, finalMoney, sited, n);
    printFinalMony(n, finalMoney);
    return 0;
}
void printFinalMony(int n, int *finalMoney)
{
    for (int i = 0; i < n; i++)
    {
        cout << finalMoney[i] << " ";
    }
}
int findTheOldest(int n, int *a)
{
    int oldestAge = 0;
    int oldestSit;
    for (int i = 0; i < n; i++)
    {
        if (a[i] > oldestAge)
        {
            oldestAge = a[i];
            oldestSit = i;
        }
    }
    return oldestSit;
}
void receiveNum(int n, int *arr)
{
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
}
void giveMoney(int giverSit, int *a, int *t, int *finalMoney, bool *sited, int n)
{
    sited[giverSit] = false;
    int rightTaker, leftTaker;
    rightTaker = -1;
    leftTaker = -1;
    rightTaker = findOldestInRightSits(n, giverSit, a, sited);
    leftTaker = findOldestInLefttSits(n, giverSit, a, sited);
    if (rightTaker == -1 && leftTaker == -1)
    {
        finalMoney[giverSit] += t[giverSit];
    }
    else
    {
        if (rightTaker >= 0 && leftTaker >= 0)
        {
            finalMoney[rightTaker] += (t[giverSit] / 2);
            finalMoney[leftTaker] += (t[giverSit] / 2);
            giveMoney(rightTaker, a, t, finalMoney, sited, n);
            giveMoney(leftTaker, a, t, finalMoney, sited, n);
        }
        else if (rightTaker >= 0)
        {
            finalMoney[rightTaker] += t[giverSit];
            giveMoney(rightTaker, a, t, finalMoney, sited, n);
            sited[rightTaker] = false;
        }
        else
        {
            finalMoney[leftTaker] += t[giverSit];
            giveMoney(leftTaker, a, t, finalMoney, sited, n);
            sited[leftTaker] = false;
        }
    }
}
int findOldestInRightSits(int n, int giverSitNum, int *a, bool *sited)
{
    if (n - 1 == giverSitNum)
    {
        return -1;
    }
    else
    {
        int finder = giverSitNum + 1;
        int oldest = 0;
        int oldestSitNum = -1;
        while (finder < n)
        {
            if (!sited[finder])
            {
                break;
            }
            else
            {
                if (a[finder] > oldest)
                {
                    oldest = a[finder];
                    oldestSitNum = finder;
                }
            }
            finder++;
        }
        return oldestSitNum;
    }
}
int findOldestInLefttSits(int n, int giverSitNum, int *a, bool *sited)
{
    if (giverSitNum == 0)
    {
        return -1;
    }
    else
    {
        int finder = giverSitNum - 1;
        int oldest = 0;
        int oldestSitNum = -1;
        while (finder >= 0)
        {
            if (!sited[finder])
            {
                break;
            }
            else
            {
                if (a[finder] > oldest)
                {
                    oldest = a[finder];
                    oldestSitNum = finder;
                }
            }
            finder--;
        }
        return oldestSitNum;
    }
}
