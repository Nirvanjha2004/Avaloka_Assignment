#include <mutex>
using namespace std;

class ThreadSafeCache {
private:
    mutex mtx;

public:
    int get(int key) {
        lock_guard<mutex> lock(mtx);

        // Perform the complete get operation here.
        // Access the map and list only while locked.
        return -1;
    }

    void put(int key, int value) {
        lock_guard<mutex> lock(mtx);

        // Perform the complete put operation here.
    }
};