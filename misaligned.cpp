#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <assert.h>

std::vector<std::string> generateColorMap() {
    const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
    const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};
    std::vector<std::string> colorMap;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            std::ostringstream oss;
            // BUG introduced: wrong use of minorColor[i] instead of minorColor[j]
            oss << (i * 5 + j) << " | " << majorColor[i] << " | " << minorColor[i];
            colorMap.push_back(oss.str());
        }
    }
    return colorMap;
}

void printColorMap(const std::vector<std::string>& colorMap) {
    for (const auto& entry : colorMap) {
        std::cout << entry << "\n";
    }
}

void testColorMap() {
    auto colorMap = generateColorMap();

    assert(colorMap.size() == 25);
    
    assert(colorMap[0] == "0 | White | Blue");

    assert(colorMap[24] == "24 | Violet | Slate");

    assert(colorMap[7] == "7 | Red | Brown");

    std::cout << "All tests passed!\n";
}

int main() {
    testColorMap(); // will fail
    return 0;
}
