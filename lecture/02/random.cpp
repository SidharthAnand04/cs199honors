#include <iostream>
#include <random>

// #include "vector.h"
// #include "list.h"
#include "deque.h"

#include <climits>
int main(int argc, char **argv) {
    if(argc != 2) {
        std::cout << "random: must specify number" << std::endl;
        return (404);
    }
    int number = atoi(argv[1]);

    List list;

    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> randint(1, INT_MAX);

//     for(int i = 0; i < number; ++i){    
//         int number =  randint(gen);
//         list.insert(number);
//     }
    
//     // list.print();

//     for(int i = number; i > 0; --i){
//         int index = randint(gen) % i;
//         list.find(index);
//         // list.print();
//    }

 // Insert random elements at the middle of the list
    for (int i = 0; i < number; ++i) {
        int num = randint(gen);
        int index = number / 2; // Insert at the middle
        list.insertAt(index, num);
    }

    // Remove elements from the middle of the list
    for (int i = 0; i < number; ++i) {
        int index = number / 2; // Remove from the middle
        list.removeAt(index);
    }

    return 0;
}