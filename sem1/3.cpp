#include <iostream>
#include <vector>
#include <climits>
/*
mungun dung zadalj boloh hamgiin tsuun zoos
zoos: 3,15,25
herev bolomjgui bol -1
*/
using namespace std;
vector<int> minCoins(int amount, vector<int> &coins) {
    vector<int> dp(amount + 1, INT_MAX);
    dp[0] = 0;
    
    for (int i = 1; i <= amount; i++) {
        for (int coin : coins) {
            if (i >= coin && dp[i - coin] != INT_MAX) {
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
    }
    
    return dp;
}

int main() {
    vector<int> coins = {3, 15, 25};
    int amount;
    cout << "total: ";
    cin >> amount;
    
    vector <int> result = minCoins(amount, coins);
    
    for (int coin : result) {
        cout << coin << " ";
    }
    
    return 0;
}