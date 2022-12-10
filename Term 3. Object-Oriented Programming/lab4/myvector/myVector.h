//
// Created by USER on 06.12.2022.
//

#ifndef MEPHI_LABS_MYVECTOR_H
#define MEPHI_LABS_MYVECTOR_H
#include <utility>
#include <iterator>
#include <initializer_list>


namespace myVec {

    template <class T>
    class vectorIt;

    template <class T>
    class vector {
        using size_type = unsigned int;

        typedef vectorIt <T> iterator;
        typedef vectorIt <const T> const_iterator;

        friend void swap(vector& a, vector& b) {
            std::swap(a.arr, b.arr);
            std::swap(a.capacity, b.capacity);
            std::swap(a.current, b.current);
        }

    private:
        static const size_type adder = 10;
        T* arr;
        size_type capacity, current;

    public:
        //destructor
        ~vector() {
            delete[] arr;
        }
        //constructors
        vector(): capacity(0), current(0), arr(nullptr) {}

        vector(const vector<T>& v): current(v.current), capacity(v.capacity) {
            delete[] arr;
            arr = new T[capacity];
            T *ptr = arr, *ptr2 = v.arr;
            for (size_type i = 0; i < current; ++i) {
                *ptr(*ptr2);
                ++ptr;
                ++ptr2;
            }
        }

        explicit vector(size_type& sz, const T& val = T()): capacity(sz), current(sz) {
            delete[] arr;
            arr = new T[sz];
            T *ptr = arr;
            for (size_type i = 0; i < sz; ++i) {
                *ptr(val);
            }
        }
        vector(std::initializer_list <T>& l): capacity(0), current(0) {
            for (auto i = l.begin(); i < l.end(); ++i) {
                push_back(l[i]);
            }
        }
        //modify
        void push_back(const T &obj) {
            if (current == capacity) {
                T *narr = new T[capacity + adder], *nptr = narr, *ptr = arr;
                for (size_type i = 0; i < current; i++) {
                    ++nptr;
                    (*nptr)(*ptr);
                    ++ptr;
                }
                delete[] arr;
                arr = narr;
            }
            arr[++current](obj);
        }
        void pop_back() {
            delete arr[current];
            --current;
            /* Do I even need to do this?
            if (current == capacity - adder) {
                T *narr = new T[capacity - adder], *nptr = narr, *ptr = arr;
                for (size_type i = 0; i < current; i++) {
                    ++nptr;
                    *nptr(*ptr);
                    ++ptr;
                }
                delete[] arr;
                arr = narr;
            }*/
            return;
        }
        //iterators
        iterator begin() {
            return iterator(arr);
        }

        iterator end() {
            return iterator(arr + current);
        }
        //info
        const size_type size() const {
            return current;
        }

        friend bool operator ==(vector& l, vector& r) {
            if (l.current != r.current || r.capacity != r.capacity) {
                return false;
            }
            T *lptr = l.arr, *rptr = r.arr;
            for(size_type i = 0; i < l.current; ++i) {
                if (*lptr != *rptr) {
                    return false;
                }
            }
            return true;
        }
        friend bool operator !=(vector& l, vector& r) {
            return !(l == r);
        }

        const T& operator[](const iterator it) const {
            return *(it.p);
        }
        const T& operator[](const size_type num) const {
            if (num > current) {
                throw std::range_error("Out of range.");
            }
            return arr[num];
        }
    };

    template <class T>
    class vectorIt: public std::iterator<std::input_iterator_tag, T> {
        using size_type = unsigned int;
        friend class vector <T>;
    private:
        T* p;
    public:
        vectorIt(T* p): p(p) {}
        vectorIt(const vectorIt& it): p(it.p) {}

        bool operator !=(const vectorIt &r) {
            return p != r.p;
        }

        bool operator ==(const vectorIt &r) {
            return p == r.p;
        }

        T& operator*() {
            return *p;
        }

        T* operator->() {
            return *p;
        }
    };
}


#endif //MEPHI_LABS_MYVECTOR_H
