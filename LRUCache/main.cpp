#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node {
    Node* next;
    Node* prev;
    int value;
    int key;
    Node(Node* p, Node* n, int k, int val) :prev(p), next(n), key(k), value(val) {};
    Node(int k, int val) :prev(NULL), next(NULL), key(k), value(val) {};
};

class Cache {

protected:
    map<int, Node*> mp; //map the key to the node in the linked list
    int cp;  //capacity
    Node* tail; // double linked list tail pointer
    Node* head; // double linked list head pointer
    virtual void set(int, int) = 0; //set function
    virtual int get(int) = 0; //get function

};

class LRUCache : public virtual Cache {
private:
    bool cacheFull() {
        return mp.size() == cp;
    }

    Node* removeLRU() {
        //throw away LRU.
        //which one is LRU? Tail.
        Node* lru = tail;
        mp.erase(lru->key);
        Node* prev = lru->prev;
        tail = prev;
        if (prev) {
            prev->next = nullptr;
        }
        //only node because cache size = 1
        if (head == lru) {
            head = nullptr;
        }
        return lru;
    }

    void insertFront(Node* newHead) {
        Node* curHead = head;
        if (curHead) {
            newHead->next = curHead;
            curHead->prev = newHead;
        }
        head = newHead;
        if (!tail) {
            tail = head;
        }
    }

    //Promote a node to front on cache hit
    void promoteNode(Node* newHead) {
        if (head == newHead) return;
        Node* prev = newHead->prev;
        if (prev) {
            Node* next = newHead->next;
            prev->next = next;
            if (next) {
                next->prev = prev;
            }
            newHead->prev = nullptr;
        }
        insertFront(newHead);
    }

public:
    explicit LRUCache(int cap) : Cache() {
        cp = cap;
    }
    LRUCache() = delete;
    //Don't care about leaks right now. 
    ~LRUCache() {
        while (head != nullptr) {
            delete removeLRU();
        }
    }

    //Insert a new node in the cache
    void set(int key, int val) override {
        //do I need to throw away the LRU data? How do I know if the cache is full?
        //if (cacheFull()){
        //    removeLRU();  
        //}

        Node* newNode = cacheFull() ? removeLRU() : new Node(key, val);
        //set operation is insert at head
        insertFront(newNode);
        mp[key] = newNode;   //throw an exception if key already exist
    }

    int get(int key) override {
        //Find the key in the map. if not found return -1. if found, promote the
        //node to the front of the cache then return the key
        auto loc = mp.find(key);
        if (loc == mp.end()) return -1;
        //Now promote the node
        Node* cacheItem = loc->second;
        promoteNode(cacheItem);
        return cacheItem->value;
    }
};

int main() {
    int n, capacity, i;
    cin >> n >> capacity;
    LRUCache l(capacity);
    for (i = 0; i < n; i++) {
        string command;
        cin >> command;
        if (command == "get") {
            int key;
            cin >> key;
            cout << l.get(key) << endl;
        }
        else if (command == "set") {
            int key, value;
            cin >> key >> value;
            l.set(key, value);
        }
    }
    return 0;
}