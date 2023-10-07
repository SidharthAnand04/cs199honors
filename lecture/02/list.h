#include <list>

class List {
private:
    std::list<int> list_;
public:
    void insert(int number);
    void remove(int index);
    int find(int number);
    void insertAt(int index, int number);
    void removeAt(int index);
    void print();
};
