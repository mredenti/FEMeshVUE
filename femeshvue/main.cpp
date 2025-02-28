import mesh;
#include <iostream>

int main()
{
    Mesh mesh(10);

    for (int i = 0; i < mesh.getSize(); ++i) {
        mesh.setValue(i, i * 10);
    }

    for (int i = 0; i < mesh.getSize(); ++i) {
        std::cout << "Value at index " << i << ": " << mesh.getValue(i)
                  << std::endl;
    }

    return 0;
}