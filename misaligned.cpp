#include <assert.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int printColorMap() {
    const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
    const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};
    int i = 0, j = 0;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            std::cout << i * 5 + j << " | " << majorColor[i] << " | " << minorColor[i] << "\n";
        }
    }
    return i * j;
}

// Function to capture the output of printColorMap to a string
std::string capturePrintColorMapOutput() {
    std::ostringstream oss;
    std::streambuf* consoleOutputBuffer = std::cout.rdbuf(oss.rdbuf());
    printColorMap();
    std::cout.rdbuf(consoleOutputBuffer);
    return oss.str();
}

// Function to split a string based on a delimiter provided, '|' in this case
std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void testPrintColorMap() {
    std::string output = capturePrintColorMapOutput();
    std::istringstream outputStream(output);
    std::string line;
    const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
    const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};
    int lineNumber = 0;

    while (std::getline(outputStream, line)) {
        std::vector<std::string> parts = split(line, '|');
        
        // Ensure there are exactly 3 parts in each line
        assert(parts.size() == 3); 

        // Check for consistent column widths
        std::string indexStr = std::to_string(lineNumber);
        //assert(parts[0].find(indexStr) != std::string::npos); // Check the index
        //assert(parts[1].find(majorColor[lineNumber / 5]) != std::string::npos); // Check the major color
        //assert(parts[2].find(minorColor[lineNumber % 5]) != std::string::npos); // Check the minor color

        // Checks for alignment
        size_t indexPos = line.find(indexStr);
        size_t majorColorPos = line.find(majorColor[lineNumber / 5]);
        size_t minorColorPos = line.find(minorColor[lineNumber % 5]);

        // Ensure that the positions of the columns are consistent
        // Index should start at position 0
        assert(indexPos == 0); 
        // Major color should start at position 4 (after "0 | ")
        assert(majorColorPos == 4); 
        // Minor color should start at position 12 (after "0 | White | ")
        assert(minorColorPos == 12); 

        lineNumber++;
    }

    assert(lineNumber == 25); // Ensure all 25 lines are printed
}

int main() {
    int result = printColorMap();
    assert(result == 25);
    testPrintColorMap();
    std::cout << "All is well (maybe!)\n";
    return 0;
}
