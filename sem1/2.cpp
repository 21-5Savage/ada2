#include <iostream>
#include <vector>

using namespace std;
vector<int> choose(int houses[], int k, vector<int> &memo, vector<int> &choices) {
    if (k <= 0) 
        return {};
    if (memo[k] != -1) 
        return choices;
    
    vector<int> take_choice, skip_choice;
    int take = houses[k - 1];
    if (k > 1) {
        take_choice = choose(houses, k - 2, memo, choices);
        take += memo[k - 2];
    }
    take_choice.push_back(k - 1);
    
    skip_choice = choose(houses, k - 1, memo, choices);
    
    if (take > memo[k - 1]) {
        memo[k] = take;
        choices = take_choice;
    } 
    else {
        memo[k] = memo[k - 1];
        choices = skip_choice;
    }
    
    return choices;
}

vector<int> robber(int houses[], int k) {
    vector<int> memo(k + 1, -1);
    vector<int> choices;
    choose(houses, k, memo, choices);
    return memo;
}

int main() {
    int S[5] = {13,2,7,9,1};
    
    vector<int> robbedS = robber(S, 5);
    
    cout << "S: ";
    for (int house : robbedS) {
        if(house != -1)
            cout << house << " ";
    }
    cout << "\n";
    
    return 0;
}
