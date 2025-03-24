#include <iostream>
#include <vector>


using namespace std;

vector<vector<int>> dp;

void fill (vector<vector<int>> &A, int N, int W){
    A.assign(N, vector<int>(W, 0));
}
vector<vector<int>> knapsacker(vector<int> &v, vector<int> &w, int N, int W) {  

    fill(dp, N + 1, W + 1);
    for (int i = 1; i <= N; i++) {  
        for (int j = 0; j <= W; j++) {
            //herev i dugaar item-iin jin limit boloh j ees heterhgui bol (i dugaar item tsunhend bagtaj baival)
            if (w[i - 1] <= j) { 
                dp[i][j] = max(  
                                    //bellman ii tegshitgel
                                    dp[i - 1][j],          
                                    dp[i - 1][j - w[i - 1]]  + v[i - 1]
                                );
            } 
            //herev bagtahgui bol i dugaar item baisan baigaagui ylgaagui
            else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    return dp; 
}
void wrapper(vector <int> &v, vector<int> &w, int N, int W) {
    knapsacker(v, w, N, W);
    int weight = W;
    int total = dp[N][W];
    cout << "Total : " << total << "\nItems :\n";
    for (int i = N; i > 0; i--) {
        //herev item baih eseh bodlogod nuluuluhgui bol tus item-iig avaagui gej uzne
        if (dp[i][weight] != dp[i - 1][weight]) {
            cout << v[i - 1] << " at index [" << i << "]\n";  
            weight -= w[i - 1];  
        }
    }
    cout << "\n";
}
void showDP(){
    for(auto &x : dp){
        for(int y : x){
            cout << y << "\t";
        }
        cout << "\n";
    }
}
int main() {
    // 1
    vector<int> v1 = {1, 6, 18, 22, 28}; 
    vector<int> w1 = {1, 2, 5, 6, 7};    
    wrapper(v1, w1, 5, 11);
    showDP();

    // 2
    vector<int> v2 = {19, 19, 13, 13, 13};
    vector<int> w2 = {7, 5, 4, 2, 3};
    wrapper(v2, w2, 5, 12);
    showDP();

    // 3
    vector<int> v3 = {19, 19, 13, 13, 13};
    vector<int> w3 = {6, 6, 4, 4, 4};
    wrapper(v3, w3, 5, 12);
    showDP();

    // 4
    vector<int> v4 = {6, 3, 8, 1, 7, 3, 8, 6, 5, 6};
    vector<int> w4 = {1, 2, 10, 6, 5, 1, 7, 4, 10, 4};
    wrapper(v4, w4, 10, 10);
    showDP();
  
    return 0;
}
