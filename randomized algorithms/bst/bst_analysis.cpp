#include "BST.cpp"
#include <unordered_set>

using namespace std;

static std::mt19937 gen(time(0)); 

int build(BST &bst, int node_count){
    std::uniform_int_distribution<> dis(0, node_count * 2 - 1); 
    std::unordered_set<int> used;

    while (used.size() < node_count) {
        //only odd numbers are inserted into the treap
        int num = dis(gen) | 1;
        if (used.insert(num).second) { 
            bst.insert(num);
        }
    }
    return 0;
}
int search(BST &bst, int epoch, int node_count) {
    std::uniform_int_distribution<> dis(0, node_count * 2 + 1); 
    std::unordered_set<int> used_odd, used_even;

    double odd_avg = 0, even_avg = 0;
    int odd_count = 0, even_count = 0;


    while (used_odd.size() < (epoch / 2)) {
        int num = dis(gen) | 1;
        int count = 0;  
        if (used_odd.insert(num).second) { 
            bst.search(num, count);
            odd_count += count;
        }
    }

    while (used_even.size() < (epoch / 2)) {
        int num = dis(gen) & ~1; 
        int count = 0;  
        if (used_even.insert(num).second) { 
            bst.search(num, count);
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
    srand(time(0));
    BST bst;
    int node_count = 50000000;
    int epoch = 10000;
    build(bst, node_count);
    search(bst, epoch, node_count);
    return 0;
}