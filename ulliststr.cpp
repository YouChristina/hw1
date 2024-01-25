#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE

//push_back
/**
  * Adds a new value to the back of the list
  *   - MUST RUN in O(1)
  */
void ULListStr::push_back(const std::string& val){
  //check if empty
  if (empty()){
    //create head (same as tail)
    head_ = new Item();
    tail_ = head_;

    //add size
    size_++;

    //initialize element, first (already 0) and last
    head_->val[0] = val;
    head_->last = 1;

    return;
  }

  //check if last item has an empty last element
  if (tail_->last < ARRSIZE){
    tail_->val[tail_->last] = val; //set tail last element to val
    tail_->last++; //update last
  } else {
    //if no empty last element, create new tail item
    Item* tmp = new Item();
    
    //initialize element, first (already 0) and last
    tmp->val[0] = val;
    tmp->last = 1;

    //update next, prev, and tail
    tail_->next = tmp;
    tmp->prev = tail_;
    tail_ = tmp;
  }
  size_++; //update size
}

//push_front
/**
  * Adds a new value to the front of the list.
  * If there is room before the 'first' value in
  * the head node add it there, otherwise, 
  * allocate a new head node.
  *   - MUST RUN in O(1)
  */
void ULListStr::push_front(const std::string& val){
  //check if empty
  if (empty()){
    //create head (same as tail)
    head_ = new Item();
    tail_ = head_;

    //initialize prev and next and size
    size_++;

    //initialize element, first and last
    head_->val[ARRSIZE-1] = val;
    head_->first = ARRSIZE-1;
    head_->last = ARRSIZE;

    return;
  }

  //check if first item has an empty first element
  if (head_->first > 0){
    head_->val[head_->first-1] = val; //set head first element to val
    head_->first--; //update first
  } else {
    //if no empty first element, create new head item
    Item* tmp = new Item();

    //initialize element, first and last
    tmp->val[ARRSIZE-1] = val;
    tmp->first = ARRSIZE-1;
    tmp->last = ARRSIZE;

    //update next, prev, and head
    tmp->prev = nullptr;
    tmp->next = head_;
    head_->prev = tmp;
    head_ = tmp;
  }
  size_++; //update size
}

//pop_back
/**
  * Removes a value from the back of the list
  *   - MUST RUN in O(1)
  */
void ULListStr::pop_back(){
  //check if empty; nothing to remove
  if (empty()){
    return;
  }

  //check if there is only one element
  if (size_ == 1){ 
    delete head_;
    head_ = nullptr;
    size_--;
    return;
  }

  //check if tail only has one element
  if (tail_->last == 1){
    Item* tmp = tail_;
    tail_ = tmp->prev;
    tail_->next = nullptr;
    size_--;
    delete tmp;
    return;
  }

  //otherwise, take tail and set the last element to null by 
  tail_->last--; //updating last
  size_--; //update size
}

//pop_front
/**
  * Removes a value from the front of the list
  *   - MUST RUN in O(1)
  */
void ULListStr::pop_front(){
  //check if empty; nothing to remove
  if (empty()){
    return;
  }

  //check if there is only one element
  if (size_==1){
    delete head_;
    head_ = nullptr; //delete the only item
    size_--;
    return;
  }

  //check if head only has one element
  if (head_->first == ARRSIZE-1){
    Item* tmp = head_;
    head_ = tmp->next;
    head_->prev = nullptr;
    size_--;
    delete tmp;
    return;
  }

  //otherwise, take head and set the first element to null by
  head_->first++; //updating first
  size_--; //update size
}

//back
/**
  * Returns a const reference to the back element
  *   - MUST RUN in O(1)
  */
std::string const & ULListStr::back() const{
  return tail_->val[tail_->last-1];
}

//front
/**
  * Returns a const reference to the front element
  *   - MUST RUN in O(1)
  */
std::string const & ULListStr::front() const{
  return head_->val[head_->first];
}

//getValAtLoc
/** 
  * Returns a pointer to the item at index, loc,
  *  if loc is valid and NULL otherwise
  *   - MUST RUN in O(n) 
  */
std::string* ULListStr::getValAtLoc(size_t loc) const{
  //check if loc is valid
  if (loc >= size_ || loc < 0){
    return NULL;
  }

  size_t i = loc;
  Item* tmp = head_;
  while((tmp->last - tmp->first)-1 < i){ //check if item reaches index
    i -= (tmp->last - tmp->first); //if not, subtract elements from index
    tmp = tmp->next; //go to next item
  }
  return &(tmp->val[tmp->first + i]); 
}

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
