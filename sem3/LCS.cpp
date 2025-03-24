#include <iostream>
#include <vector>
using namespace std;

int LCS(string P, string Q) {
    int m = P.length();
    int n = Q.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            if(P[i - 1] == Q[j - 1]){
                dp[i][j] = dp[i-1][j-1] + 1;
            }
            else{
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }

    int i = m, j = n;
    string lcs_seq = "";
    string P_mod = "", Q_mod = "";

    while (i > 0 && j > 0) {
        if (P[i - 1] == Q[j - 1]) {
            lcs_seq = P[i - 1] + lcs_seq;
            P_mod = P[i - 1] + P_mod;
            Q_mod = Q[j - 1] + Q_mod;
            i--; j--;
        } 
        else if (dp[i - 1][j] >= dp[i][j - 1]) {
            P_mod = P[i - 1] + P_mod;
            Q_mod = "_" + Q_mod;
            i--;
        }
        else {
            P_mod = "_" + P_mod;
            Q_mod = Q[j - 1] + Q_mod;
            j--;
        }
    }

    while (i > 0) {
        P_mod = P[i - 1] + P_mod;
        Q_mod = "_" + Q_mod;
        i--;
    }
    while (j > 0) {
        P_mod = "_" + P_mod;
        Q_mod = Q[j - 1] + Q_mod;
        j--;
    }

    cout << "P: " << P_mod << "\n";
    cout << "Q: " << Q_mod << "\n";
    cout << "LCS: " << lcs_seq << "\n";
    for(int i = 0; i <= m; i++){
        for(int j = 0; j <= n; j++){
            cout << dp[i][j] << "\t";
        }
        cout << "\n";
    }
    return dp[m][n];
}

int main() {
    string P = "algorithm";
    string Q = "altruistic";
    cout << "LCS Length: " << LCS(P, Q) << "\n";
    return 0;
}
