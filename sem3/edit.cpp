#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

int edit_distance(string P, string Q){
    //init
    int m = P.length();
    int n = Q.length();
    int dp[m + 1][n + 1];
    memset(dp, 0, sizeof(dp));
    for(int i = 0; i <= m; i++){
        dp[i][0] = i;
    }
    for(int j = 0; j <= n; j++){
        dp[0][j] = j;
    }

    //distance dynamic programming
    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            if(Q[j - 1] == P[i - 1])
                dp[i][j] = dp[i - 1][j - 1]; //chars equal do nothing
            else{
                dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}); //delete insert replace
            }
        }
    }
    //print
    // for(int i = 0; i <= m; i++){
    //     for(int j = 0; j <= n; j++){
    //         cout << dp[i][j] << "\t";
    //     }
    //     cout << "\n";
    // }
    // cout << dp[m][n] << "\t";
    for(int i = m; i < 0; i--){
        for(int j = n; j < 0; j--){
            int x = min({dp[i-1][j-1], dp[i-1][j], dp[i][j-1]});
            cout << x << "\t";
        }
        cout << "\n";
    }

    int i = m, j = n;
    string P_mod, Q_mod;
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && P[i - 1] == Q[j - 1]) {
            P_mod = P[i - 1] + P_mod;
            Q_mod = Q[j - 1] + Q_mod;
            i--; j--;
        }
        else if (i > 0 && dp[i][j] == dp[i - 1][j] + 1) {
            P_mod = P[i - 1] + P_mod;
            Q_mod = '_' + Q_mod;
            i--;
        } 
        else if (j > 0 && dp[i][j] == dp[i][j - 1] + 1) {
            P_mod = '_' + P_mod;
            Q_mod = Q[j - 1] + Q_mod;
            j--;
        } 
        else if (i > 0 && j > 0 && dp[i][j] == dp[i - 1][j - 1] + 1) {
            P_mod = P[i - 1] + P_mod;
            Q_mod = Q[j - 1] + Q_mod;
            i--; j--;
        }
    }
    
    cout << "Q: " << Q_mod << "\n";
    cout << "P: " << P_mod << "\n";
    
    //edit distance
    return dp[m][n];
}

int main(){
    string Q = "mongolia"; //mur
    string P = "ogota"; //bagana
    cout << "Edit distance : " << edit_distance(P,Q);
    return 0;
}