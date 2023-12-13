#ifndef SMARTPOINTER_HPP
#define SMARTPOINTER_HPP

#include <iostream>

template <typename T>
class SmartPointer
{
private:
    T *ptr;
public:
    SmartPointer(T *p = nullptr) { ptr = p; }
    ~SmartPointer() { 
        delete(ptr);
        ptr = nullptr;
    }
    T *getptr(){
        return ptr;
    }
    T &operator *() { return *ptr; }
    T *operator ->() { return ptr; }
};

#endif
