#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// a = {start_time, finish_time, value, index}
//compare finish time
bool compare(vector<int> &a, vector<int> &b) {
    return a[1] < b[1]; 
}

int latest_available_job(vector<vector<int>> &jobs, int index) {
    int low = 0, high = index - 1, ans = -1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (jobs[mid][1] <= jobs[index][0]) {  
            ans = mid;
            low = mid + 1;  
        } 
        else {
            high = mid - 1;
        }
    }
    //index of the very previous non conflicting job
    return ans;
}

int max_profit(vector<vector<int>> &jobs, vector<vector <int>> &choices) {
    int n = jobs.size();
    
    //sort jobs by end time
    sort(jobs.begin(), jobs.end(), compare);
    
    vector<int> dp(n, 0);
    choices.resize(n);
    //first job
    dp[0] = jobs[0][2]; 
    choices[0].push_back(jobs[0][3]);

    for (int i = 1; i < n; i++) {
        //i dugaar job oo avna
        int take = jobs[i][2];

        //i dugaar job bolon tuuntei davhtsahgui ajluudiin une nemegdene
        int last = latest_available_job(jobs, i);
        if (last != -1)
            take += dp[last];

        //i dugaar jobiig avahgui baih songolttoi haritsuulna
        if(take > dp[i - 1]){
            dp[i] = take;
            if(last != -1)
                //davhtsahgui job oldoj baival umnuh songoltuudaa uvluj avna
                choices[i] = choices[last];
            else
                //buh ajiltai davhtsaj baival songoltoo arilgana
                choices[i] =  vector<int>(); 
            //i dugaar job iig songoj avna
            choices[i].push_back(jobs[i][3]);
        }
        else{
            dp[i] = dp[i - 1];
            //i dugaar job iig avahgui buguud songolt uurchlugduhgui
            choices[i] = choices[i - 1];
        }
        dp[i] = max(dp[i - 1], take);
    }

    return dp[n - 1];
}


int main() {
    vector<vector<int>> test1 = {
        {3, 9, 60, 1},
        {8, 9, 10, 2}, 
        {6, 8, 20, 3}, 
        {0, 6, 70, 4},
        {6, 9, 40, 5}, 
        {3, 5, 30, 6}, 
        {1, 4, 40, 7}, 
        {1, 3, 30, 8}
    };
    vector<vector<int>> test2 = {
        {5, 8, 4000, 1}, 
        {1, 4, 6000, 2}, 
        {3, 4, 1800, 3}, 
        {6, 8, 5000, 4},
        {3, 5, 2000, 5}, 
        {4, 8, 6000, 6}, 
        {2, 4, 2000, 7}, 
        {0, 3, 5000, 8}, 
        {0, 8, 4500, 9}
    };

    vector<vector<int>> choices;

    cout << "Max Profit (Test 1): " << max_profit(test1, choices) << "\n";

    for(const auto& row : choices){
        for(int x : row){
            cout << x << "\t";
        }
        cout << "\n";
    }
    choices.clear();
    cout << "Max Profit (Test 2): " << max_profit(test2, choices) << "\n";
    for(const auto& row : choices){
        for(int x : row){
            cout << x << "\t";
        }
        cout << "\n";
    }
    return 0;
}
