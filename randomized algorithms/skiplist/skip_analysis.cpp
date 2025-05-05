#include "skiplist.cpp"
#include <random>
#include <unordered_set>
#include <algorithm>
using namespace std;

static std::mt19937 gen(time(0)); 

int build(SkipList &sl, int node_count) {
    std::vector<int> odds;

    for (int i = 1; i < node_count * 2; i += 2) {
        odds.push_back(i);
    }
    std::shuffle(odds.begin(), odds.end(), gen);

    for (int num : odds) {
        sl.insert(num);
    }

    return 0;
}
int search(SkipList &sl, int epoch, int node_count) {
    std::uniform_int_distribution<> dis(0, node_count * 2 + 1); 
    std::unordered_set<int> used_odd, used_even;

    double odd_avg = 0, even_avg = 0;
    int odd_count = 0, even_count = 0;


    while (used_odd.size() < (epoch / 2)) {
        int num = dis(gen) | 1;
        int count = 0;  
        if (used_odd.insert(num).second) { 
            sl.search(num, count);
            odd_count += count;
        }
    }

    while (used_even.size() < (epoch / 2)) {
        int num = dis(gen) & ~1; 
        int count = 0;  
        if (used_even.insert(num).second) { 
            sl.search(num, count);
            even_count += count; 
        }
    }

    odd_avg = (double)odd_count / (epoch / 2);
    even_avg = (double)even_count / (epoch / 2);

    cout << "For " << node_count << " nodes, Search count : " << epoch << "\n";
    cout << "Odd avg: " << odd_avg << "\tEven avg: " << even_avg << "\n";
    return 0;
}

int main(){
    int nodes = 5000000;
    SkipList sl(32, 0.5);
    int count = 0;
    int epoch = 1000000;
    build(sl, nodes);
    search(sl, epoch, nodes);
    return 0;
}

