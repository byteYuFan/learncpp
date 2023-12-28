#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    std::sort(numbers.begin(), numbers.end(), [](int x, int y) { return x < y; });
    std::for_each(numbers.begin(), numbers.end(), [](int num) {
        std::cout << num << " ";
    });

}