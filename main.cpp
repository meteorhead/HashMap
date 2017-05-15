#include <iostream>
#include <string>
#include <thread>
#include <assert.h>

#include "hashmap.h"

using namespace std;

/* GoogleTest could be used here for testing, but to not add dependencies
we'll set up functions that each target a specific case */

// Test inserting to the hashmap from several threads, sometimes with same key

void testInsertThreads()
{
    HashMap<int, std::string> hMap;
    HashItem<int, std::string> hItem1(1,"Thread 1");
    HashItem<int, std::string> hItem2(2,"Thread 2");
    HashItem<int, std::string> hItem3(3,"Thread 3");
    // Yes, same key as hItem3 the idea is to have only one value with that key
    HashItem<int, std::string> hItem4(3,"Thread 4");

    thread th1( [&hMap, hItem1, &th1](){ cout << "insert from thread 1 " << th1.get_id() << endl;
        hMap.insert(hItem1);} );
    thread th2( [&hMap, hItem2, &th2](){ cout << "insert from thread 2 " << th2.get_id() << endl;
        hMap.insert(hItem2);} );
    thread th3( [&hMap, hItem3, &th3](){ cout << "insert from thread 3 " << th3.get_id() << endl;
        hMap.insert(hItem3);} );

    thread th4( [&hMap, hItem4, &th4](){ cout << "insert from thread 4 " << th4.get_id() << endl;
        hMap.insert(hItem4);} );

    th1.join();
    th2.join();
    th3.join();
    th4.join();


    // expect 3
    assert( hMap.count() == 3);

}

// Try removing the same key from two different threads and ensure that
// if it's removed by one, we don't get a segfault from the other

void testRemoveThreads()
{
    HashMap<int, std::string> hMap;
    HashItem<int, std::string> hItem5(5,"Item To Delete");
    hMap.insert(hItem5);

    thread th5( [&hMap, &th5](){
        if ( hMap.remove(5) )
        {
            cout << "remove from thread 5 " << th5.get_id() << endl;
        }
    });

    thread th6( [&hMap, &th6](){ if ( hMap.remove(5) )
        {
            cout << "remove from thread 6 " << th6.get_id() << endl;
        } });

    th5.join();
    th6.join();

    // expect 0
    assert( hMap.count() == 0);
}

void basicLookup()
{
    HashMap<int, std::string> hMap;
    HashItem<int, std::string> hItem1(1,"1st");
    hMap.insert(hItem1);
    assert(hMap.lookup(1) == "1st");

    HashMap<std::string, int> hMap2;
    HashItem<std::string,int> hItem2("1st",1);
    hMap2.insert(hItem2);
    assert(hMap.lookup(1) == "1st");
}

int main(int argc, char *argv[])
{

    testInsertThreads();
    testRemoveThreads();
    basicLookup();

    return 0;
}
