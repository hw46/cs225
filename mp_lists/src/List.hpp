#include <iostream>
using namespace std;
/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() {
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in mp_lists part 1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in mp_lists part 1
  return ListIterator(nullptr,this->tail_);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  ListNode* temp;
  ListNode* prev;
  temp = head_;
  if(head_ != nullptr){
    while(temp != nullptr){
      prev = temp;
      temp = temp -> next;
      delete prev;
    }
    delete temp;
    length_ = 0;
  }
  else{
    return;
  }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in mp_lists part 1
  ListNode* newNode = new ListNode(ndata);
  if(length_ == 0){
    head_ = newNode;
    tail_ = newNode;
  }
  else{
    newNode -> next = head_;
    newNode -> prev = nullptr;
    head_ -> prev = newNode;
    head_ = newNode;
  }
  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in mp_lists part 1
  ListNode* newNode = new ListNode(ndata);
  if(length_ == 0){
    head_ = newNode;
    tail_ = newNode;
  }
  else{
    newNode -> prev = tail_;
    newNode -> next = nullptr;
    tail_ -> next = newNode;
    tail_ = newNode;
  }
  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in mp_lists part 1
  ListNode* curr = start;
  ListNode* temp;
  if(start == nullptr || splitPoint < 1){
    return start;
  }
  if(splitPoint >= length_){
    return nullptr;
  }
  for(int i = 0; i < splitPoint-1; i++){
    curr = curr->next;
  }
  temp = curr;
  curr = curr->next;
  temp -> next = nullptr;

  curr -> prev = nullptr;
  return curr;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in part 1
  ListNode* curr = head_;
  ListNode* temp;
  if(length_ > 2){
    while(curr -> next -> next != nullptr){
      temp = curr -> next;
      curr -> next = curr -> next -> next;
      curr -> next -> prev = curr;

      tail_ -> next = temp;
      temp = tail_;
      tail_ = tail_ -> next;
      tail_ -> prev = temp;
      tail_ -> next = nullptr;

      curr = curr -> next;
    }
  }
  else{
    return;
  }
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in mp_lists part 2
  if(startPoint == endPoint || startPoint == nullptr || endPoint ==  nullptr){
    return;
  }
  ListNode* fu = startPoint;
  ListNode* cr = startPoint;
  ListNode* pa = startPoint;
  ListNode* startPrev = startPoint -> prev;
  ListNode* tmp;
  while(cr != endPoint){
    pa = cr -> prev;
    fu = cr;
    fu = fu -> next;
    cr -> next = pa;
    cr -> prev = fu;
    cr = cr -> prev;
  }
  pa = cr -> prev;
  fu = cr;
  fu = fu -> next;
  cr -> next = pa;
  cr -> prev = fu;
  if(startPrev != nullptr){
    cr -> prev = startPrev;
    startPrev -> next = cr;
  }
  else{
    cr -> prev = nullptr;
  }
  if(fu != nullptr){
    startPoint -> next = fu;
    fu -> prev = startPoint;
  }
  else{
    startPoint -> next = nullptr;
  }
  tmp = startPoint;
  startPoint = endPoint;
  endPoint = tmp;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in mp_lists part 2
  if(n<2){
    return;
  }
  int counter = length_;
  int div;
  int mod;

  ListNode* start = head_;
  ListNode* end = head_;

  if(start == nullptr){
    return;
  }

  div = counter / n;
  mod = counter % n;

  if(counter < n){
    reverse(head_, tail_);
  }
  else{
    for(int i = 0; i < n-1; i++){
      end = end -> next;
    }
    reverse(start, end);
    head_ = start;
    for(int i = 0; i < div-1; i++){
      for(int i = 0; i < n; i++){
        start = start -> next;
        end = end -> next;
      }
      reverse(start, end);
    }
    if(end -> next != nullptr){
      for(int i = 0; i < n ; i++){
        start = start -> next;
      }
      for(int i = 0; i < mod ; i++){
        end = end -> next;
      }
      reverse(start, end);
    }
    tail_ = end;
  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in mp_lists part 2
  ListNode* fir = first;
  ListNode* sec = second;
  ListNode* start;
  ListNode* node;

  if(fir == nullptr && sec == nullptr){
    return nullptr;
  }
  if(fir != nullptr && sec == nullptr){
    return first;
  }
  if(sec != nullptr && fir == nullptr){
    return second;
  }

  if(fir -> data < sec -> data){
    start = fir;
    node = start;
    fir = fir -> next;
  }
  else{
    start = sec;
    node = start;
    sec = sec -> next;
  }

  while(fir != nullptr && sec != nullptr){
    if(sec -> data < fir -> data){
      node -> next = sec;
      sec -> prev = node;
      node = node -> next;
      sec = sec -> next;
    }
    else{
      node -> next = fir;
      fir -> prev = node;
      node = node -> next;
      fir = fir -> next;
    }
  }

  if(fir != nullptr && sec == nullptr){
    fir -> prev = node;
    node -> next = fir;
  }
  if(sec != nullptr && fir == nullptr){
    sec -> prev = node;
    node -> next = sec;
  }
  
  return start;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in mp_lists part 2
  if(chainLength == 0){
    return nullptr;
  }
  if(chainLength == 1){
    return start;
  }
  int fir = (chainLength/2)+(chainLength%2);
  int sec = (chainLength/2);
  ListNode* secHalf = split(start, fir);
  return merge(mergesort(start, fir), mergesort(secHalf, sec));
}