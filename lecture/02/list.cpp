#include "list.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void List::insert(int number) {
    list_.insert(std::upper_bound( list_.begin(), list_.end(), number), number);
    // auto it = list_.begin();
    // while (it != list_.end() && (*it < number)) {
    //     ++it;
    // }
    // list_.insert(it,number);

}

int List::find(int number) {
    // int index = 0;
    // for (auto it = list_.begin(); it != list_.end(); ++it) {
    // //     if (*it == number) {
    // //         return index; // Element found, return its position
    // //     }
    // //     ++index;
    // // }
    // // return -1; // Element not found
    auto iter = std::find (list_.begin(), list_.end(), number);
    return *iter;
}

void List::remove(int index) {
    auto it = list_.begin();
    while(index-- > 0) {
        ++it;
    }
    list_.erase(it);
}
void List::insertAt(int index, int number) {
    if (index < 0 || index > list_.size()) {
        // Invalid index, do nothing
        return;
    }

    auto it = list_.begin();
    std::advance(it, index);  // Move the iterator to the specified position
    list_.insert(it, number); // Insert the element at the specified position
}

void List::removeAt(int index) {
    if (index < 0 || index >= list_.size()) {
        // Invalid index, do nothing
        return;
    }

    auto it = list_.begin();
    std::advance(it, index);  // Move the iterator to the specified position
    list_.erase(it);          // Erase the element at the specified position
}

void List::print() {

    for( int num : list_) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}