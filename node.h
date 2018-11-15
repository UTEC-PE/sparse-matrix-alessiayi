#ifndef NODE_H
#define NODE_H

using namespace std;

template <class T>
struct Node {
    int x, y;
    T data;
    Node* next;
    Node* down;

    Node(T data) :  data(data){
        next = down = nullptr;
    };

    Node(int x, int y, T data) : x(x), y(y), data(data){
        next = down = nullptr;
    };

};

#endif
