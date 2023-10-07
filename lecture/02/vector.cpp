#include "vector.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void List::insert(int number) {
    // list_.insert(std::upper_bound( list_.begin(), list_.end(), number), number);
    auto it = list_.begin();
    while (it != list_.end() && (*it < number)) {
        ++it;
    }
    list_.insert(it,number);

}

void List::remove(int index) {
    // auto it = list_.begin();

    // it += index;
    // // while(index-- > 0) {
    // //     ++it;
    // // }

    // list_.erase(it);

    if (index >= 0 && index < list_.size()) {
        list_.erase(list_.begin() + index);
    }
}

int List::find(int number) {
    for (int i = 0; i < list_.size(); ++i) {
        if (list_[i] == number) {
            return i; // Element found, return its position
        }
    }
    return -1; // Element not found
}

void List::removeAt(int index) {
    if (index < 0 || index >= list_.size()) {
        // Invalid index, do nothing
        return;
    }

    list_.erase(list_.begin() + index);
}

void List::insertAt(int index, int number) {
    if (index < 0 || index > list_.size()) {
        // Invalid index, do nothing
        return;
    }

    list_.insert(list_.begin() + index, number);
}


void List::print() {

    for( int num : list_) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}