#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int editDistance(string P, string Q) {
    int m = P.length();
    int n = Q.length();
    
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0)
                dp[i][j] = j;  // Insert all characters of Q
            else if (j == 0)
                dp[i][j] = i;  // Delete all characters of P
            else if (P[i - 1] == Q[j - 1])
                dp[i][j] = dp[i - 1][j - 1];  // No operation needed
            else
                dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});  // Min of insert, delete, replace
        }
    }
    for(int i = 0; i <= m; i++){
        for(int j = 0; j <= n; j++){
            cout << dp[i][j] << "\t";
        }
        cout << "\n";
    }
    return dp[m][n];
}

int main() {
    string P = "altruistic";
    string Q = "algorithm";
    cout << "Edit Distance: " << editDistance(P, Q) << endl;
    return 0;
}
