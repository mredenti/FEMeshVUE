#include <stdexcept>

template <class T>
class my_shared_ptr
{
   private:
    T*    ptr = nullptr;
    uint* refCount =
        nullptr;  // # shared_ptr objects owning the same underlying pointer

   public:
    my_shared_ptr()
        : ptr(nullptr), refCount(new uint(0))  // default constructor
    {
    }

    my_shared_ptr(T* ptr) : ptr(ptr), refCount(new uint(1))  // constructor
    {
    }

    // do not allow copying of one object to another
    // because that would mean the address of the underlying memory
    // being copied that will leave the ownership of that memory with
    // more than one my_shared_ptr objects
    my_shared_ptr(const my_shared_ptr& obj)
    {                                   // copy contructor
        this->ptr      = obj.ptr;       // share the underlying pointer
        this->refCount = obj.refCount;  // share the refCount
        if (nullptr != obj.ptr) {
            // if the pointer is not null, increment the refCount
            *(this->refCount)++;
        }
    }

    // copy assignment
    my_shared_ptr& operator=(const my_shared_ptr& obj)
    {
        __cleanup__();  // cleanup any existing data

        // Assign incoming object's data to this object
        this->ptr      = obj.ptr;       // share the underlying pointer
        this->refCount = obj.refCount;  // share refCount
        if (nullptr != obj.ptr) {
            // if the pointer is not null, increment the refCount
            *(this->refCount)++;
        }
    }

    // move constructor
    my_shared_ptr(my_shared_ptr&& dyingObj)
    {
        // Transfer ownership of memory pointed by dyingObj
        this->ptr      = dyingObj.ptr;
        this->refCount = dyingObj.refCount;
        dyingObj.ptr   = dyingObj.refCount =
            nullptr;  // mmm, I have transferred ownership, but dyingObj is
                      // still alive
    }

    // move assignment
    void operator=(my_shared_ptr&& dyingObj)
    {
        __cleanup__();

        // Transfer ownership of memory pointed
        this->ptr      = dyingObj.ptr;
        this->refCount = dyingObj.refCount;

        dyingObj.ptr = dyingObj.refCount = nullptr;  // clean up dyingObj
    }

    // we also need object dereferencing through overloaded operators in our
    // class
    T* operator->() const  // obtaining pointer using arrow operator
    {
        return this->ptr;
    }

    T& operator*() const  // dereferencing underlying pointer
    {
        return *(this->ptr);
    }

    uint get_count() const
    {
        return *refCount;
    }

    T* get() const
    {
        return this->ptr;
    }

    ~my_shared_ptr()
    {
        __cleanup__();
    }

   private:
    void __cleanup__()
    {
        if (nullptr != refCount) {
            (*refCount)--;
            // cleanup any existing data
            if (*refCount == 0) {
                if (nullptr != ptr)
                    delete ptr;
                delete refCount;
            }
        }
    }
};


// Another templated version with[] i.e. <T[]> is also added to support the
// creation of arrays.

template <class T>
class my_shared_ptr<T[]>
{
   private:
    T* ptr = nullptr;

   public:
    my_shared_ptr() : ptr(nullptr)  // default constructor
    {
    }

    my_shared_ptr(T* ptr) : ptr(ptr)
    {
    }

    my_shared_ptr(const my_shared_ptr& obj) =
        delete;  // copy constructor is deleted
    my_shared_ptr& operator=(const my_shared_ptr& obj) =
        delete;  // copy assignment is deleted

    my_shared_ptr(my_shared_ptr&& dyingObj)  // move constructor
    {
        __cleanup__();  // cleanup any existing data

        // Transfer ownership of the memory pointed by dyingObj to this object
        this->ptr    = dyingObj.ptr;
        dyingObj.ptr = nullptr;
    }

    void operator=(my_shared_ptr&& dyingObj)  // move assignment
    {
        __cleanup__();  // cleanup any existing data

        // Transfer ownership of the memory pointed by dyingObj to this object
        this->ptr    = dyingObj.ptr;
        dyingObj.ptr = nullptr;
    }

    T* operator->()  // deferencing arrow operator
    {
        return this->ptr;
    }

    T& operator*()
    {
        return *(this->ptr);
    }

    T& operator[](int index)
    {
        if (index < 0) {
            // Throw negative index exception
            throw std::runtime_error("Negative index exception");
        }
        return this->ptr[index];  // doesn't check out of bounds
    }

    ~my_shared_ptr()  // destructor
    {
        __cleanup__();
    }

   private:
    void __cleanup__()
    {
        if (ptr != nullptr)
            delete[] ptr;
    }
};

class Box
{
   private:
    int length, width, height;
};
Box* func()
{
    Box* b = new Box();
    return b;
}

int main()
{
    // Every new must have a corresponding delete but here as the Box object(s)
    // is being encapsulated in a smart pointer object, we don’t need to call
    // delete as the destructor of my_shared_ptr will be called when its scope
    // completes and the destructor will take care of the deallocation of the
    // dynamically allocated memory.
    // creates a my_shared_ptr object holding a 'Box' object
    my_shared_ptr<Box> box1(new Box);
    // creates a my_shared_ptr object holding an array of 'Box' objects
    my_shared_ptr<Box[]> boxArr(new Box[5]);
    Box                  b1 = boxArr[0];  // index based access
    return 0;
}