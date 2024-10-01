class ListIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
  private:
    ListNode* position_;
    ListNode* tail_;

  public:
    ListIterator() : position_(nullptr) { }
    ListIterator(ListNode* x) : position_(x) { }
    ListIterator(ListNode* x,ListNode* y) : position_(x),tail_(y) { }

    // Pre-Increment, ++iter
    ListIterator& operator++() {
        position_ = position_ -> next;
        return *this;
    }
    
    // Post-Increment, iter++
    ListIterator operator++(int) {
        ListNode* temp = position_;
        position_ = position_->next;
        return ListIterator(temp);
    }

    // Pre-Decrement, --iter
    ListIterator& operator--() {
        // @TODO: graded in mp_lists part 1
    
        if(position_ != nullptr){
        position_ = position_->prev;
        return *this;
        }
        else{
            position_ = tail_;
            return *this;
        }
    }

    // Post-Decrement, iter--
    ListIterator operator--(int) {
        // @TODO: graded in mp_lists part 1
        if(position_ != nullptr){
        ListNode* temp = position_;
        position_ = position_ -> prev;
        position_ -> next = temp;
        return ListIterator(temp);
       }
       else{
            position_= tail_;
            return *this;
        }
    }

    bool operator!=(const ListIterator& rhs) {
        if(this->position_ != rhs.position_){
          return true;
        }
        return false;
    }

    bool operator==(const ListIterator& rhs) {
        return !(*this != rhs);
    }

    const T& operator*() {
        return position_->data;
    }

    const T* operator->() {
        return &(position_->data);
    }
};
