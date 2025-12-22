#ifndef LISTLINKED_H
#define LISTLINKED_H
#include "List.h"
#include "Node.h"
#include <stdexcept>
#include <ostream>

template <typename T>
class ListLinked : public List<T>{
  
  private:
    
    Node<T>* first;
    int n;

  public:
    
    ListLinked() : first(nullptr), n(0) {}

    ~ListLinked() {
      
      Node<T>* aux;
      
      while (first != nullptr) {
        
        aux = first -> next;
        delete first;
        first = aux;

      }
    }

    void insert(int pos, T e) override {
      
      if (pos < 0 || pos > n) {

        throw std::out_of_range("Position out of range");

      }

      Node<T>* newNode = new Node<T>(e);

      if (pos == 0) {

        newNode -> next = first;
        first = newNode;

      }

      else {
        
        Node<T>* current = first;

        for (int i = 0; i < pos - 1; i++) {
          
          current = current -> next;

        }
        
        newNode -> next = current -> next;
        current -> next = newNode;

      }

      ++n;

    }

    void append(T e) override {
      
      insert(n, e);

    }

    void prepend(T e) override {
      
      insert(0, e);

    }

    T remove(int pos) override {
      
      if (pos < 0 || pos >= n) {
        
        throw std::out_of_range("Position out of range");

      }

      Node<T>* toDelete;
      T removedData;

      if (pos == 0) {
        
        toDelete = first;
        first = first -> next;

      }

      else {
        
        Node<T>* current = first;
        
        for (int i = 0; i < pos - 1; i++) {
          
          current = current -> next;

        }

        toDelete = current -> next;
        current -> next = toDelete -> next;

      } 

      removedData = toDelete -> data;
      delete toDelete;
      --n;

      return removedData;

    }

    T get(int pos) const override {
      
      if (pos < 0 || pos >= n) {
        
        throw std::out_of_range("Position out of range");

      }

      Node<T>* current = first;
      
      for (int i = 0; i < pos; i++) {
        
        current = current -> next;

      }

      return current -> data;

    }

    int search(T e) const override {
      
      Node<T>* current = first;

      for (int i = 0; i < n; ++i) {

        if (current -> data == e) {
          
          return i;

        }

        current = current -> next;

      }

      return -1;

    }

    bool empty() const override {

      return n == 0;

    }

    int size() const override {
      
      return n;

    }

    T operator[](int pos) {

      return get(pos);

    }

    friend std::ostream& operator << (std::ostream &out, const ListLinked<T> &list) {

      Node<T>* current = list.first;
      out << "[";

      while (current != nullptr) {
        
        out << current -> data;

        if (current -> next != nullptr) {

          out << ", ";

        }

        current = current -> next;

      }

      out << "]";
      return out;

    }
};

#endif
