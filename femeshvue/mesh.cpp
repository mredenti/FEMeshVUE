module;

#include <stdexcept>

export module mesh;


export class Mesh
{
   public:
    Mesh(int size);
    ~Mesh();

    int  getSize() const;
    int  getValue(int index) const;
    void setValue(int index, int value);

   private:
    int* data;
    int  size;
};

Mesh::Mesh(int size) : size(size)
{
    data = new int[size];
}

Mesh::~Mesh()
{
    delete[] data;
}

int Mesh::getSize() const
{
    return size;
}

int Mesh::getValue(int index) const
{
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

void Mesh::setValue(int index, int value)
{
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    data[index] = value;
}