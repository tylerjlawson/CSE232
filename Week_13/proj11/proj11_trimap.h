#ifndef SINGLELINK_H
#define SINGLELINK_H
//Project 11
//Redo of Trimap
#include<iostream>
using std::ostream; using std::cout; using std::endl;
#include<sstream>
using std::ostringstream;
#include<utility>
using std::swap;
#include<string>
using std::string;

// forward declaration so we can make Element a friend of TriMap
template<typename K, typename V>
class TriMap;

// private Element, friend of TriMap class
template <typename K, typename V>
class Element{

private:
  K key_;
  size_t index_ = 0;
  Element *next_ = nullptr;  

public:
  V value_;
  
  Element() = default;
  Element(K key, V val, size_t i) : key_(key),index_(i), next_(nullptr), value_(val) {};

  // *defined* in the class, makes templating easier.
  friend ostream& operator<<(ostream& out, Element& e){
    out << e.key_ << ":" << e.value_ << ":" << e.index_;
    return out;
  }
  friend class TriMap<K,V>;
};


template<typename K, typename V>
class TriMap{

private:
  Element<K,V> *head_ = nullptr;
  Element<K,V> *tail_ = nullptr;
  size_t size_ = 0;
  
  // a private function, used by operator<<
  void print_list(ostream& out);
  
public:
  TriMap() = default;
  TriMap(K, V);
  TriMap(const TriMap&);
  TriMap& operator=(TriMap);
  ~TriMap();
  long size();
  bool insert(K,V);
  bool remove(K);
  Element<K,V>* find_key(K);
  Element<K,V>* find_value(V);
  Element<K,V>* find_index(size_t);  
  
  // *defined* in the class, makes templating easier.
  // uses private method print_list
  // you can remove print_list and just do it here if you
  // prefer. I won't test print_list
  friend ostream& operator<<(ostream& out, TriMap<K,V>& sl){
    sl.print_list(out);
    return out;
  };
};

template<typename K, typename V>
TriMap<K,V>::TriMap(K key, V value){
    size_ = 1;
    tail_ = new Element<K,V>(key,value,0);
    head_ = tail_;
};

/* 
bit of work. we need to remember a pointer that walks
down the list to copy, as tail_ walks down the new list. 
Make a new node (copy the current node of the list we are copying), 
update the tail_->next_ to point to the new node, update tail_ to new node
 */
template<typename K, typename V>
TriMap<K,V>::TriMap(const TriMap& tm){//copy constructor
  for(auto ptr = tm.head_; ptr != nullptr; ptr = ptr->next_ ){//iterate through
    insert(ptr->key_, ptr->value_);//inserts each one
    auto E = find_key(ptr->key_);
    E->index_ = ptr->index_;//sets correct index
  }
}

template<typename K, typename V>
TriMap<K,V>& TriMap<K,V>::operator=(TriMap tm){//assignment operator
  for(auto ptr = tm.head_; ptr != nullptr; ptr = ptr->next_ ){//iterate
    insert(ptr->key_, ptr->value_);//insert each element
    auto E = find_key(ptr->key_);
    E->index_ = ptr->index_;//correct index
  }
  return *this;
}
	

// walk down the list using head_ , keeping a trailer pointer called to_del
// delete what to_del points to
// move head_ and to_del to the next node.
template<typename K, typename V>
TriMap<K,V>::~TriMap(){//destructor
  for(auto ptr = head_; ptr != nullptr; ptr = ptr->next_ ){
    auto to_del = ptr;//to delete pointer
    delete(to_del);//deletes
    head_++;//next one is head
  }
}

template<typename K, typename V>
long TriMap<K,V>::size(){//returns the size of the trimap
  return static_cast<long>(size_);
}

template<typename K, typename V>
bool TriMap<K,V>::insert(K key, V value){
  // inserts a new element based on key and value
  Element<K,V> *E1 = new Element<K,V>(key,value,0);//new element to insert
  Element<K,V> *E2 = nullptr;//variable tool
  if ( find_key(key) == nullptr ){//see if it is already in there
    if (size_ == 0){//if empty case
      tail_ = E1;
      head_ = tail_;
      size_++;
    }
    else if (tail_->key_ < key ){//if it is the tail case
      E1->index_ = size_;   
      tail_->next_ = E1;
      tail_ = E1;
      size_++;
    }
    else if ( head_->key_ > key ){//if it is the head case
      E1->next_ = head_;
      E1->index_ = size_;
      head_ = E1;
      size_++;
    }
    else{//case for when it is in the middle area
      for( auto ptr = head_; ptr != nullptr; ptr = ptr->next_ ){
        if ( key < ptr->key_ ){//when found
          E2->next_ = E1;
          E1->index_ = size_;
          E1->next_ = ptr;
          size_++;
        }
        E2 = ptr;//save pointer
      }
    }
    return 1;//it inserted so true
  }
  return 0;//did not insert so false
}
    
template<typename K, typename V>
bool TriMap<K,V>::remove(K key){
  // this removes an element by key
  Element<K,V> *E = nullptr;//variables as tools
  auto spot = find_key(key);
  if ( find_key(key) != nullptr ){//if found first
    if (key == tail_->key_){// if it is the tail case
      for ( auto ptr = head_; ptr != nullptr; ptr = ptr->next_ ){
        if ( tail_ == ptr->next_ ){
          ptr->next_ = nullptr;
          tail_ = ptr;
          size_--;
        }
      }
    }
    else if ( head_->key_ == key){//when it is the head case
      head_ = head_->next_;
      size_--;
      for( auto ptr = head_; ptr != nullptr; ptr = ptr->next_ ){
        ptr->index_--;//adjust indexes
      }
    }
    
    else{//when it is in the middle area case
      for ( auto ptr = head_; ptr != nullptr; ptr = ptr->next_ ){
        if(ptr->key_ == key){
          E->next_ = ptr->next_;
          size_--;
          ptr = ptr->next_;
        }
        if (spot->index_ < ptr->index_){
          ptr->index_-=1;//adjust index
        }
        E = ptr;//save pointer
      }
    }
    return 1;//when removed
  }
  return 0;//nothing removed
}
 

template<typename K, typename V>
Element<K,V>* TriMap<K,V>::find_key(K key){
  // uses linear search in order to find the key
  for ( auto ptr = head_; ptr != nullptr; ptr = ptr->next_ ){
    if (key == ptr->key_){
      return ptr;
    }
  }
  return nullptr;// if not found 
}    

template<typename K, typename V>
Element<K,V>* TriMap<K,V>::find_value(V val){
  // uses linear search in order to find the value
  for ( auto ptr = head_; ptr != nullptr; ptr = ptr->next_ ){
    if (val == ptr->value_){
      return ptr;
    }
  }
  return nullptr;// if not found
}  

template<typename K, typename V>
Element<K,V>* TriMap<K,V>::find_index(size_t i){
  // uses linear search in order to find the index
  for ( auto ptr = head_; ptr != nullptr; ptr = ptr->next_ ){
    if (i == ptr->index_){
      return ptr;
    }
  }
  return nullptr;
}  

template<typename K, typename V>
void TriMap<K,V>::print_list(ostream &out){
  //iterates through trimap and sends it to an out stream
  ostringstream oss;
  for(auto ptr = head_; ptr != nullptr; ptr = ptr->next_){            
    oss << *ptr << ", ";
  }
  string result = oss.str();
  result = result.substr(0, (result.size() - 2) );
  out << result;
};


#endif
  