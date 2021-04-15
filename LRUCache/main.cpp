//I suspect this solution almost work. But unnecessarily complex with the pre-allocation of an "empty" linked list
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

//Implement this as a fixed-size doubly linked list. Maybe STL can help,
class LRUCache : public virtual Cache {
private:
    vector<Node*> cacheStorage;
    size_t nextEmpty = 0;
    //eventually this is mostly true
    bool cacheFull() {
        return mp.size() == cp;
    }

    void removeLRU(int key, int val) {
        //throw away LRU.
        //which one is LRU? Tail.
        Node* lru = tail;
        mp.erase(lru->key);
        lru->key = key;
        lru->value = val;
        mp[key] = lru;
        moveToFront(lru);
    }

    //Promote a node to front on cache hit
    void moveToFront(Node* newHead) {
        //implies tail does not move
        if (head == newHead) return;
        Node* prev = newHead->prev;
        if (prev) {
            if (tail == newHead) tail = prev;
            Node* next = newHead->next;
            prev->next = next;
            if (next) {
                next->prev = prev;
            }
        }
        newHead->prev = head->prev;
        if (newHead->prev) {
            newHead->prev->next = newHead;
        }
        newHead->next = head;
        head->prev = newHead;
        head = newHead;
    }

    //allocate cache nodes. head initially points to the same node as tail
    void allocateCache() {
        //Preallocate storage
        generate(cacheStorage.begin(), cacheStorage.end(), []() { return new Node{ 0,0 }; });
        for (auto node = 0; node < cacheStorage.size() - 1; ++node) {
            cacheStorage.at(node)->next = cacheStorage.at(node + 1);
            cacheStorage.at(node + 1)->prev = cacheStorage.at(node);
        }
        head = nullptr;
        tail = cacheStorage.back();
    }

    void printCache() {
        Node* toPrint = head;
        while (toPrint != nullptr) {
            cout << toPrint->key << " ";
            toPrint = toPrint->next;
        }
        cout << endl;
    }
public:
    explicit LRUCache(int cap) : Cache(), cacheStorage(cap), nextEmpty(cap - 1) {
        cp = cap;
        allocateCache();
    }

    LRUCache() = delete;
    //Don't care about leaks right now. 
    ~LRUCache() {
        for (auto i = 0; i < cacheStorage.size(); ++i) {
            delete cacheStorage.at(i);
        }
    }


    //Insert a new node in the cache
    void set(int key, int val) override {
        //do I need to throw away the LRU data? How do I know if the cache is full?
        if (cacheFull()) {
            removeLRU(key, val);
            //printCache();
            return;
        }
        //Fill the cache backward
        Node* newNode = cacheStorage.at(nextEmpty);
        newNode->key = key;
        newNode->value = val;
        head = newNode;
        mp[key] = newNode;
        nextEmpty -= 1;
        //printCache();
    }

    int get(int key) override {
        //Find the key in the map. if not found return -1. if found, promote the
        //node to the front of the cache then return the key
        auto loc = mp.find(key);
        if (loc == mp.end()) {
            //printCache();
            return -1;
        }
        //Now promote the node
        Node* cacheItem = loc->second;
        moveToFront(cacheItem);
        //printCache();
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
