#include "Region.hpp"

int main(int argc, char const *argv[]) {
    Point p1(12.0, 4.0, -3.0);
    Point p2(12.0, 1.0, 0.0);
    
    // Test zero_distance function
    float zeroDistResult = zero_distance(p1);
    std::cout << "zero_distance(p1) = " << zeroDistResult << std::endl;
    
    // Test distance function
    float distResult = distance(p1, p2);
    std::cout << "distance(p1, p2) = " << distResult << std::endl;
    
    // Test compare function
    bool compareResult = compare(p1, p2);
    std::cout << "compare(p1, p2) = " << (compareResult ? "true" : "false") << std::endl;
 
    // Test region function
    int regionResult = region(p1);
    std::cout << "region(p1) = " << regionResult << std::endl;
    
    // Test is_in_same_region function
    Point p3(2.0, 3.0, 4.0);
    bool sameRegionResult = is_in_same_region(p1, p3);
    std::cout << "is_in_same_region(p1, p3) = " << (sameRegionResult ? "true" : "false") << std::endl;

    return 0;
}