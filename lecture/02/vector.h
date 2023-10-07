#include <vector>

class List {
private:
    std::vector<int> list_;
public:
    void insert(int number);
    void remove(int index);
    void removeAt(int index);
    void insertAt(int index, int number);
    int find(int number);
    void print();
};
