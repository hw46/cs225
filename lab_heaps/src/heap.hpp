
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */
#include <cstddef>

template <class T, class Compare>
class heap;

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    return currentIdx*2;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    return currentIdx*2+1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    return currentIdx/2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child
    if(_elems.size()>currentIdx*2){
        return true;
    }
    else{
        return false;
    }
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    if(!hasAChild(currentIdx)){
        return currentIdx;
    }
    else if((currentIdx*2+1)>=_elems.size()){
        return currentIdx*2;
    }
    else if(higherPriority(_elems[leftChild(currentIdx)],_elems[rightChild(currentIdx)])){
        return leftChild(currentIdx);
    }
    else{
        return rightChild(currentIdx);
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // @TODO Implement the heapifyDown algorithm.
    /*if(!hasAChild(currentIdx)){
        return;
    }
    else{
        size_t maxPChild=maxPriorityChild(currentIdx);
        if(higherPriority(_elems[maxPChild],_elems[currentIdx])){
            std::swap(_elems[maxPChild],_elems[currentIdx]);
            heapifyDown(maxPChild);
        }
    }*/

    /*if(currentIdx*2>=_elems.size()){
        return;
    }
    else{
        int min;
        if(_elems[currentIdx*2+1]>=_elems.size()){
            min=currentIdx*2;
        }
        else if(_elems[currentIdx*2]<=_elems[currentIdx*2+1]){
            min=currentIdx*2;
        }
        else{
            min=currentIdx*2+1;
        }
        if(_elems[currentIdx]>=_elems[min]){
            std::swap(_elems[currentIdx],_elems[min]);
            heapifyDown(min);
        }
    }*/
    



    if(currentIdx*2>=_elems.size()){
        return;
    }
    else{
        size_t maxP;
        if(currentIdx*2+1>=_elems.size()){
            maxP=currentIdx*2;
        }
        else if(higherPriority(_elems[currentIdx*2],_elems[currentIdx*2+1])){
            maxP=currentIdx*2;
        }
        else{
            maxP=currentIdx*2+1;
        }
        if(higherPriority(_elems[maxP],_elems[currentIdx])){
            std::swap(_elems[maxP],_elems[currentIdx]);
            heapifyDown(maxP);
        }
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    /*if(currentIdx==root()){
        return;
    }
    else{
        if(higherPriority(_elems[currentIdx],_elems[parent(currentIdx)])){
            std::swap(_elems[currentIdx],_elems[parent(currentIdx)]);
            heapifyUp(parent(currentIdx));
        }
    }*/

    /*if(currentIdx=1){
        return;
    }
    else{
        if(_elems[currentIdx]<_elems[currentIdx/2]){
            std::swap(_elems[currentIdx],_elems[currentIdx/2]);
            heapifyUp(currentIdx/2);
        }
    }*/


    if(currentIdx==1){
        return;
    }
    else{
        if(higherPriority(_elems[currentIdx],_elems[currentIdx/2])){
            std::swap(_elems[currentIdx],_elems[currentIdx/2]);
            heapifyUp(currentIdx/2);
        }
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
    _elems.push_back(T());
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
    // @TODO Construct a heap using the buildHeap algorithm
    _elems.push_back(T());
    for(size_t i=0; i<elems.size(); i++){
        _elems.push_back(elems[i]);
    }
    for(size_t i=parent(_elems.size() - 1); i>0; i--){
        heapifyDown(i);
    }
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority
    if(_elems.size()!=1){
        std::swap(_elems[1],_elems[_elems.size()-1]);
        T tmp=_elems[_elems.size()-1];
        _elems.pop_back();
        heapifyDown(1);
        return tmp;
    }
    return T();
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    return _elems[1];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap
    _elems.push_back(elem);
    heapifyUp(_elems.size()-1);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    // @TODO In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update
    T tmp=_elems[idx];
    _elems[idx]=elem;
    if(higherPriority(elem,tmp)){
        heapifyUp(idx);
    }
    else{
        heapifyDown(idx);
    }
    return;
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    if(_elems.size()<=1){
        return true;
    }
    else{
        return false;
    }
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for(size_t i=root(); i<_elems.size(); i++){
        heaped.push_back(_elems[i]);
    }
}

/*vector<int> result;
Heap h;
for(unsigned i=0; i<v.size(); i++){
    h.insert(v[i]);
}
for(unsigned i=0; i<n; i++){
    int tmp=h.remove();
    result.push_back(tmp);
}
return result;*/