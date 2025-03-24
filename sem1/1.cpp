#include <iostream>
#include <vector>

int opt[101];  

int solve(int num) {
    if (num == 0) 
        return 0;
    if (num == 1) 
        return 1;
    if (num == 2) 
        return 2;

    if (opt[num] != -1) 
        return opt[num];  

    if (num % 2 == 1)
        return opt[num] = solve(num - 1) + 1;
    else
        return opt[num] = solve(num / 2) + 1;
}

int main() {
    std::fill(opt, opt + 101, -1); 

    for (int i = 0; i <= 100; i++) {
        std::cout << i << "  " << solve(i) << "\n";
    }

    return 0;
}
