#include "dsets.h"

using namespace std;

void DisjointSets::addelements(int num){
    for(int i = 0; i < num; i++){
        elements.push_back(-1);
    }
}
int DisjointSets::find(int elem){
    if(elements[elem] < 0){
        return elem;
    }
    elements[elem] = find(elements[elem]);
    return elements[elem];
}

void DisjointSets::setunion(int a, int b){
    int rootA = find(a);
    int rootB = find(b);
    if(rootA == rootB){
        return;
    }
    if(elements[rootA] >= elements[rootB]){
        int temp = elements[rootA];
        elements[rootA] = rootB;
        elements[rootB] += temp;
        return;
    }
    if(elements[rootA] < elements[rootB]){
        int temp = elements[rootB];
        elements[rootB] = rootA;
        elements[rootA] += temp;
        return;
    }
}
int DisjointSets::size(int elem){
    return (-1)*elements[find(elem)];
}