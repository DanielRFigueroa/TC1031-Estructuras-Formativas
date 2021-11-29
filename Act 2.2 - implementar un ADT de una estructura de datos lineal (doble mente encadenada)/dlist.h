/*
Author: Daniel Rodriguez Figueroa

A01612889

correcion act 2.2
*/

#ifndef DLIST_H_
#define DLIST_H_

#include <string>
#include <sstream>

using namespace std;

template <class T> class DList;

template <class T>
class DLink {
  private:
    DLink(T);
    DLink(T, DLink<T>*, DLink<T>*);
    DLink(const DLink<T>&);

    T	    value;
    DLink<T> *previous;
    DLink<T> *next;

    friend class DList<T>;
};

template <class T>
DLink<T>::DLink(T val) : value(val), previous(0), next(0) {}

template <class T>
DLink<T>::DLink(T val, DLink *prev, DLink* nxt) : value(val), previous(prev), next(nxt) {}

template <class T>
DLink<T>::DLink(const DLink<T> &source) : value(source.value), previous(source.previous), next(source.next) {}

template <class T>
class DList {
  public:
    DList();
    ~DList();
    void insertion(T val);
    int search(T val);
    void update(int index, T val);
    T deleteAt(int index);
    void clear();
    string toStringBackward();
    string toStringForward();
    string toString();
    bool empty() const;
  private:
    DLink<T> *head;
    DLink<T> *tail;
    int size;
};

template <class T>
DList<T>::DList() : head(0), tail(0), size(0) {}

template <class T>
DList<T>::~DList() {clear();}

template <class T>
bool DList<T>::empty() const {
	return (head == 0 && tail == 0);
}

template <class T>
void DList<T>::clear() {
	DLink<T> *p, *q;
	p = head;
	while (p != 0) {
		q = p->next;
		delete p;
		p = q;
	}
	head = 0;
	tail = 0;
	size = 0;
}

template <class T>
void DList<T>::insertion(T val){
    
    DLink<T> *newLink;
    newLink = new DLink<T>(val);
    
    if (empty()) {
		head = newLink;
		tail = newLink;
	} else {
		tail->next = newLink;
		newLink->previous = tail;
		tail = newLink;
	}
	size++;
}

template <class T>
int DList<T>::search(T val) {

  int pos = 0;
  DLink<T> *p;
  p = head;
  
  while (p != 0) {
    if(p->value == val){
      return pos;
    }
        p = p->next;
        pos++;
  }
  return -1;
}

template <class T>
void DList<T>::update(int index, T val) {

  int pos = 0;
  DLink<T> *p;
  p = head;

  while (p != 0){
    if (pos == index){
      p->value = val;
    }
    p = p->next;
    pos++;
  }
}

template <class T>
T DList<T>::deleteAt(int index) {

  DLink<T> *p, *q;
  int pos = 0;
  p = head;
  T val;

  if (index == 0){
    head = p->next;
    p->next->previous = 0;
    val = p->value;
    delete p;
    size--;
    return val;
  }

  else{
    while (p != 0){
      if(pos == index-1){
        q = p -> next;
        p-> next = q -> next;
        q -> next->previous = p;
        val = p->value;
        delete q;
        size--;
        return val;
        }
        pos++;
        p = p -> next;
      }
  }
  return val;
}

template <class T>
string DList<T>::toStringForward(){

  stringstream aux;
  DLink<T> *p;
  p = head;
  aux << "[";
  
  while (p != 0) {
      aux << p->value;
      if (p->next != 0) {
        aux << ", ";
      }
      p = p->next;
  }

  aux << "]";
  return aux.str();
}

template <class T>
string DList<T>::toStringBackward() {

  stringstream aux;
  DLink<T> *p;
  p = tail;
  aux << "[";

  while (p != 0) {
      aux << p->value;
      if (p->previous != 0) {
        aux << ", ";
      }
      p = p->previous;
  }

  aux << "]";
  return aux.str();
}

#endif