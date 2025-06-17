#ifndef OBJECTPOOL_H
#define OBJECTPOOL_H

#include <queue>
#include <vector>
#include <memory>
#include <mutex>
using namespace std;
template<typename T>
class ObjectPool {
private:
    queue<T*> availableObjects;
    vector<unique_ptr<T>> allObjects;
    int maxSize;
    mutable mutex poolMutex;

public:
    explicit ObjectPool(int initialSize = 10);
    ~ObjectPool();
    
    T* get_object();
    void return_object(T* obj);
    int size() const;
    void alloc_more();
    
    // Delete copy constructor and assignment operator for thread safety
    ObjectPool(const ObjectPool&) = delete;
    ObjectPool& operator=(const ObjectPool&) = delete;
};

template<typename T>
ObjectPool<T>::ObjectPool(int initialSize) : maxSize(initialSize * 2) {
    for (int i = 0; i < initialSize; ++i) {
        auto obj = make_unique<T>();
        availableObjects.push(obj.get());
        allObjects.push_back(move(obj));
    }
}

template<typename T>
ObjectPool<T>::~ObjectPool() {
    // Unique pointers will automatically clean up
}

template<typename T>
T* ObjectPool<T>::get_object() {
    lock_guard<mutex> lock(poolMutex);
    
    if (availableObjects.empty()) {
        if (allObjects.size() < maxSize) {
            alloc_more();
        } else {
            // Pool is at capacity, create temporary object
            return new T();
        }
    }
    
    T* obj = availableObjects.front();
    availableObjects.pop();
    return obj;
}

template<typename T>
void ObjectPool<T>::return_object(T* obj) {
    if (!obj) return;
    
    lock_guard<mutex> lock(poolMutex);
    
    // Check if this object belongs to our pool
    bool belongsToPool = false;
    for (const auto& poolObj : allObjects) {
        if (poolObj.get() == obj) {
            belongsToPool = true;
            break;
        }
    }
    
    if (belongsToPool) {
        // Reset object state if needed (T should have a reset method)
        // obj->reset(); // Uncomment if T has reset method
        availableObjects.push(obj);
    } else {
        // This was a temporary object, delete it
        delete obj;
    }
}

template<typename T>
int ObjectPool<T>::size() const {
    lock_guard<mutex> lock(poolMutex);
    return availableObjects.size();
}

template<typename T>
void ObjectPool<T>::alloc_more() {
    // This method should be called while holding the mutex
    int currentSize = allObjects.size();
    int newObjects = min(5, maxSize - currentSize);
    
    for (int i = 0; i < newObjects; ++i) {
        auto obj = make_unique<T>();
        availableObjects.push(obj.get());
        allObjects.push_back(move(obj));
    }
}

#endif // OBJECTPOOL_H
