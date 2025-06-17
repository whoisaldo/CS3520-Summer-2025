#ifndef OBJECTPOOL_H
#define OBJECTPOOL_H

#include <queue>
#include <vector>
#include <memory>
#include <mutex>
#include <cstddef>      // for std::size_t
using namespace std;

template<typename T>
class ObjectPool {
private:
    queue<T*> availableObjects;
    vector<unique_ptr<T>> allObjects;
    std::size_t maxSize;
    mutable mutex poolMutex;

public:
    explicit ObjectPool(std::size_t initialSize = 10);
    ~ObjectPool();
    
    T* get_object();
    void return_object(T* obj);
    std::size_t size() const;
    void alloc_more();
    
    // Delete copy constructor and assignment operator for thread safety
    ObjectPool(const ObjectPool&) = delete;
    ObjectPool& operator=(const ObjectPool&) = delete;
};

// Constructor: allocate initial objects (initialSize) and set max capacity (double initial)
template<typename T>
ObjectPool<T>::ObjectPool(std::size_t initialSize)
    : maxSize(initialSize * 2) {
    for (std::size_t i = 0; i < initialSize; ++i) {
        auto obj = make_unique<T>();
        availableObjects.push(obj.get());
        allObjects.push_back(move(obj));
    }
}

// Destructor: unique_ptrs automatically free all objects
template<typename T>
ObjectPool<T>::~ObjectPool() {
    // No additional cleanup required (RAII)
}

// Acquire an object from the pool; may grow or create a temporary if at capacity
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

// Return an object to the pool or delete if it was temporary
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
        availableObjects.push(obj);
    } else {
        // This was a temporary object, delete it
        delete obj;
    }
}

// Return number of free objects
template<typename T>
std::size_t ObjectPool<T>::size() const {
    lock_guard<mutex> lock(poolMutex);
    return availableObjects.size();
}

// Allocate additional objects up to maxSize
template<typename T>
void ObjectPool<T>::alloc_more() {
    // This method should be called while holding the mutex
    int currentSize = static_cast<int>(allObjects.size());
    int newObjects = std::min<int>(5, static_cast<int>(maxSize) - currentSize);
    
    for (int i = 0; i < newObjects; ++i) {
        auto obj = make_unique<T>();
        availableObjects.push(obj.get());
        allObjects.push_back(move(obj));
    }
}

#endif // OBJECTPOOL_H
