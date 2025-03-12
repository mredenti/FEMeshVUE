/**
 * @file mesh.cpp
 * @brief Implementation of the Mesh class for managing a dynamic array of
 * integers.
 *
 * This file contains the implementation of the Mesh class, which provides
 * functionalities to create, manage, and manipulate a dynamic array of
 * integers. It includes methods to get the size of the array, retrieve values
 * at specific indices, and set values at specific indices. The class ensures
 * proper memory management by allocating and deallocating memory in the
 * constructor and destructor.
 *
 * @version 0.1
 * @date 2025-02-28
 *
 * @copyright Copyright (c) 2025
 *
 */

module;

#include <stdexcept>

export module mesh;


/**
 * @brief A class to manage a dynamic array of integers.
 *
 * The Mesh class provides functionalities to create, manage, and manipulate a
 * dynamic array of integers. It includes methods to get the size of the array,
 * retrieve values at specific indices, and set values at specific indices. The
 * class ensures proper memory management by allocating and deallocating memory
 * in the constructor and destructor.
 */
export class Mesh {
   public:
    /**
     * @brief Construct a new Mesh object
     *
     * @param size The size of the mesh
     */
    explicit Mesh(int size);

    /**
     * @brief Destroy the Mesh object
     *
     */
    ~Mesh();

    /**
     * @brief Get the size of the mesh
     *
     * @return int The size of the mesh
     */
    int getSize() const;

    /**
     * @brief Get the value at the specified index
     *
     * @param index The index of the value to retrieve
     * @return int The value at the specified index
     */
    int getValue(int index) const;

    /**
     * @brief Set the value at the specified index
     *
     * @param index The index at which to set the value
     * @param value The value to set
     */
    void setValue(int index, int value);

   private:
    int* data;
    int  size;
};

Mesh::Mesh(int size) : size(size) {
    data = new int[size];
}

Mesh::~Mesh() {
    delete[] data;
}

int Mesh::getSize() const {
    return size;
}

int Mesh::getValue(int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

void Mesh::setValue(int index, int value) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    data[index] = value;
}