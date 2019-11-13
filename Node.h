#ifndef SPARSEMATRIX_NODE_H
#define SPARSEMATRIX_NODE_H

template<typename T>
class ValNode{
public:
    ValNode<T>* next;
    ValNode<T>* down;
    T value;
    int x;
    int y;
    ValNode(){
        next = nullptr;
        down = nullptr;
    }

    ValNode(std::tuple<int,int,T>par) {
        next = nullptr;
        down = nullptr;
        value = std::get<2>(par);
        this->x = std::get<1>(par);
        this->y = std::get<0>(par);
    }
};

template<typename T>
class IndexNodeC{
public:
    IndexNodeC<T>* next;
    ValNode<T>* down;
    int indice;
    IndexNodeC() {

    }
    IndexNodeC(int v) {
        next = nullptr;
        down = nullptr;
        this->indice = v;
    }
};

template<typename T>
class IndexNodeR{
public:
    IndexNodeR<T>* down;
    ValNode<T>* next;
    int indice;
    IndexNodeR() {

    }
    IndexNodeR(int v) {
        next = nullptr;
        down = nullptr;
        this->indice = v;
    }
};

template<typename T>
class Node{
public:
    IndexNodeC<T>* next;
    IndexNodeR<T>* down;
    Node() {
        down = nullptr;
        next = nullptr;
    }
};




#endif //SPARSEMATRIX_NODE_H