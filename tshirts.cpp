#include <iostream>
#include <assert.h>

char size(int cms) {
    char sizeName = '\0';
    if (cms < 38) {
        sizeName = 'S';
    } else if (cms > 38 && cms < 42) {
        sizeName = 'M';
    } else if (cms > 42) {
        sizeName = 'L';
    }
    return sizeName;
}

void testTshirtSize() {
    std::cout << "\nT-shirt size tests\n";

    assert(size(37) == 'S');
    
    assert(size(38) == 'S');

    assert(size(40) == 'M');

    assert(size(42) == 'M');

    assert(size(43) == 'L');

    std::cout << "All tests passed!\n";
}

int main() {
    testTshirtSize(); // will fail
    return 0;
}
