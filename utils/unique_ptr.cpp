#include <stdexcept>

template <class T>
class my_unique_ptr
{
   private:
    T* ptr = nullptr;

   public:
    my_unique_ptr() : ptr(nullptr)  // default constructor
    {
    }

    my_unique_ptr(T* ptr) : ptr(ptr)  // constructor
    {
    }

    // do not allow copying of one object to another
    // because that would mean the address of the underlying memory
    // being copied that will leave the ownership of that memory with
    // more than one my_unique_ptr objects
    my_unique_ptr(const my_unique_ptr& obj) = delete;
    // copy contructor is deleted

    my_unique_ptr& operator=(const my_unique_ptr& obj) = delete;
    // copy assignment is deleted

    my_unique_ptr(my_unique_ptr&& dyingObj)  // move constructor
    {
        // Transfer ownership of memory pointed by dyingObj
        this->ptr    = dyingObj.ptr;
        dyingObj.ptr = nullptr;  // mmm, I have transferred ownership, but
                                 // dyingObj is still alive
    }

    void operator=(my_unique_ptr&& dyingObj)  // move assignment
    {
        // cleanup any existing data
        __cleanup__();

        // Transfer ownership of memory pointed
        this->ptr    = dyingObj.ptr;
        dyingObj.ptr = nullptr;
    }

    // we also need object dereferencing through overloaded operators in our
    // class
    T* operator->()  // obtaining pointer using arrow operator
    {
        return this->ptr;
    }

    T& operator*()  // dereferencing underlying pointer
    {
        return *(this->ptr);
    }

    ~my_unique_ptr()
    {
        __cleanup__();
    }

   private:
    void __cleanup__()
    {
        if (ptr != nullptr)
            delete ptr;
    }
};


// Another templated version with[] i.e. <T[]> is also added to support the
// creation of arrays.

template <class T>
class my_unique_ptr<T[]>
{
   private:
    T* ptr = nullptr;

   public:
    my_unique_ptr() : ptr(nullptr)  // default constructor
    {
    }

    my_unique_ptr(T* ptr) : ptr(ptr)
    {
    }

    my_unique_ptr(const my_unique_ptr& obj) =
        delete;  // copy constructor is deleted
    my_unique_ptr& operator=(const my_unique_ptr& obj) =
        delete;  // copy assignment is deleted

    my_unique_ptr(my_unique_ptr&& dyingObj)  // move constructor
    {
        __cleanup__();  // cleanup any existing data

        // Transfer ownership of the memory pointed by dyingObj to this object
        this->ptr    = dyingObj.ptr;
        dyingObj.ptr = nullptr;
    }

    void operator=(my_unique_ptr&& dyingObj)  // move assignment
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

    ~my_unique_ptr()  // destructor
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
    // delete as the destructor of my_unique_ptr will be called when its scope
    // completes and the destructor will take care of the deallocation of the
    // dynamically allocated memory.
    // creates a my_unique_ptr object holding a 'Box' object
    my_unique_ptr<Box> box1(new Box);
    // creates a my_unique_ptr object holding an array of 'Box' objects
    my_unique_ptr<Box[]> boxArr(new Box[5]);
    Box                  b1 = boxArr[0];  // index based access
    return 0;
}