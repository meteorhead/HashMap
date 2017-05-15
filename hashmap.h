#ifndef HASHMAP_H
#define HASHMAP_H
#include <memory>
#include <iostream>
#include <mutex>

#include "hashitem.h"

constexpr static int SIZE = 999;

using std::unique_ptr;
using std::lock_guard;
using std::mutex;

template <class k, class v>
class HashMap
{
private:
    unique_ptr< HashItem<k,v> > hashmap[SIZE];
    mutex mtx;

public:
    HashMap<k,v>():hashmap({}){}

    void insert(const HashItem<k,v> & iHashItem)
    {
        lock_guard<mutex> lockGuard(mtx);
        unique_ptr< HashItem <k,v> > itemToInsert = std::make_unique<HashItem<k,v>>(iHashItem);

        size_t index = std::hash<k>{}(itemToInsert->getKey() ) % SIZE;
        hashmap[index] = std::move(itemToInsert);

    }

    bool remove(const k & iKeyToDelete)
    {
        lock_guard<mutex> lockGuard(mtx);
        size_t index = std::hash<k>{}( iKeyToDelete ) % SIZE;
        hashmap[index].reset(nullptr);
        if (hashmap[index] == nullptr)
            return true;
        return false;
    }

    const v & lookup(const k & iKeyToSearch)
    {
        lock_guard<mutex> lockGuard(mtx);
        size_t index = std::hash<k>{}(iKeyToSearch) % SIZE;
        return hashmap[index]->getValue();


    }

    size_t count()
    {
        lock_guard<mutex> lockGuard(mtx);
        size_t numberOfElements = 0;
        for ( const auto & item : hashmap)
        {
            if (item != nullptr)
            {
                std::cout << "one item found "  << item->getValue() << std::endl;
                numberOfElements++;
            }
        }
        return numberOfElements;
    }

    bool isEmpty()
    {
        return !count();
    }

};

#endif // HASHMAP_H
