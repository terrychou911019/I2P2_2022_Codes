#include "function.h"

// Darray
Darray::~Darray() {
    delete []this->data;
}

void Darray::pushback(int x) {
    if (size >= capacity)
        resize();
    this->data[size++] = x;
}

void Darray::resize() {
    int *tmp = new int[capacity << 1];
    for (int i = 0; i < capacity; i++)
        tmp[i] = this->data[i];
    delete []this->data;
    this->data = tmp;
    capacity <<= 1;
}

int& Darray::operator[] (int x) {
    return this->data[x];
}

void Darray::clear() {
    this->size = 0;
}

int Darray::length() {
    return this->size;
}
