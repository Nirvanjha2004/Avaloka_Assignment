#include <iostream>
#include <unordered_map>
#include <list>
using namespace std;

class LRUCache {
private:
    int capacity;

    // Stores key-value pairs, most recently used at the front.
    list<pair<int, int>> cache;

    // Maps each key to its position in the list.
    unordered_map<int, list<pair<int, int>>::iterator> mp;

public:
    LRUCache(int cap) {
        capacity = cap;
    }

    int get(int key) {
        auto it = mp.find(key);

        if (it == mp.end()) {
            return -1;
        }

        // Move the accessed item to the front.
        cache.splice(cache.begin(), cache, it->second);

        return it->second->second;
    }

    void put(int key, int value) {
        // A zero-capacity cache cannot store anything.
        if (capacity <= 0) {
            return;
        }

        auto it = mp.find(key);

        if (it != mp.end()) {
            // Update the existing value.
            it->second->second = value;

            // Mark it as recently used.
            cache.splice(cache.begin(), cache, it->second);
            return;
        }

        // Evict the least recently used item if full.
        if (cache.size() == capacity) {
            int lruKey = cache.back().first;

            cache.pop_back();
            mp.erase(lruKey);
        }

        // Insert the new item at the front.
        cache.push_front({key, value});
        mp[key] = cache.begin();
    }
};

int main() {
    LRUCache lru(2);

    lru.put(1, 10);
    lru.put(2, 20);

    cout << lru.get(1) << '\n';  // 10

    lru.put(3, 30);              // Evicts key 2

    cout << lru.get(2) << '\n';  // -1
    cout << lru.get(3) << '\n';  // 30

    lru.put(4, 40);              // Evicts key 1

    cout << lru.get(1) << '\n';  // -1
    cout << lru.get(4) << '\n';  // 40

    return 0;
}