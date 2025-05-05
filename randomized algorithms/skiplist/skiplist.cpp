#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <vector>
#include <limits>

using namespace std;

struct node {
    int key;
    vector<node*> forward;

    node(int key, int level) : key(key), forward(level + 1, nullptr) {}
};

class SkipList {
private:
    int maxLevel;
    float probability;
    int currentLevel;
    node* header;

    int random_level() {
        int lvl = 0;
        while (((float)rand() / RAND_MAX) < probability && lvl < maxLevel)
            lvl++;
        return lvl;
    }

public:
    SkipList(int maxLevel, float probability) : maxLevel(maxLevel), probability(probability), currentLevel(0) {
        header = new node(std::numeric_limits<int>::min(), maxLevel);
    }
    void insert(int key) {
        vector<node*> update(maxLevel + 1);
        node* x = header;

        for (int i = currentLevel; i >= 0; i--) {
            while (x->forward[i] != nullptr && x->forward[i]->key < key) {
                x = x->forward[i];
            }
            update[i] = x;
        }

        x = x->forward[0];

        if (x == nullptr || x->key != key) {
            int lvl = random_level();
            if (lvl > currentLevel) {
                for (int i = currentLevel + 1; i <= lvl; i++) {
                    update[i] = header;
                }
                currentLevel = lvl;
            }

            node* newnode = new node(key, lvl);
            for (int i = 0; i <= lvl; i++) {
                newnode->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = newnode;
            }
        }
    }

    void erase(int key) {
        vector<node*> update(maxLevel + 1);
        node* x = header;

        for (int i = currentLevel; i >= 0; i--) {
            while (x->forward[i] != nullptr && x->forward[i]->key < key) {
                x = x->forward[i];
            }
            update[i] = x;
        }

        x = x->forward[0];

        if (x != nullptr && x->key == key) {
            for (int i = 0; i <= currentLevel; i++) {
                if (update[i]->forward[i] != x)
                    break;
                update[i]->forward[i] = x->forward[i];
            }
            delete x;

            while (currentLevel > 0 && header->forward[currentLevel] == nullptr) {
                currentLevel--;
            }
        }
    }

    bool search(int key, int &count) {
        node* x = header;
    
        for (int i = currentLevel; i >= 0; i--) {
            while (x->forward[i] && x->forward[i]->key < key) {
                x = x->forward[i];
                count++;  
            }
            count++;
        }
    
        x = x->forward[0];
        count++;  
        return (x && x->key == key);
    }

    void display() {
        cout << "\n***** Skip List *****\n";
        for (int i = currentLevel; i >= 0; i--) {
            node* x = header->forward[i];
            cout << "Level " << i << ": ";
            while (x != nullptr) {
                cout << x->key << " ";
                x = x->forward[i];
            }
            cout << "\n";
        }
    }
};

// int main() {
//     srand(time(0));
//     SkipList list(5, 0.5);

//     list.insert(3);
//     list.insert(6);
//     list.insert(7);
//     list.insert(9);
//     list.insert(12);
//     list.insert(19);
//     list.insert(17);
//     list.insert(26);
//     list.insert(21);
//     list.insert(25);

//     list.display();

//     int x = 0;
//     cout << "\nSearching :" << (list.search(26, x) ? "Found" : "Not Found") << endl;


//     return 0;
// }
