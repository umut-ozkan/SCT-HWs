#include "SmartPointer.hpp"
#include <memory>

int main() {
    // Test SmartPointer
    int* adress;
    {
    SmartPointer<int> sp(new int(42));
    std::cout << *sp << std::endl;
    std::cout << *sp << std::endl;
    adress = sp.getptr();
    std::cout << adress << std::endl;
    std::cout << *adress << std::endl;
    }
    std::cout << adress << std::endl;
    std::cout << *adress << std::endl;

    std::cout << "--------------------------" << std::endl;
    // Test std::unique_ptr
    std::cout << "Test std::unique_ptr" << std::endl;
    std::unique_ptr<int> uniquePtr(new int(99));
    int* uniquePtrData = uniquePtr.get();
    std::cout << "Before Move: " << uniquePtrData << std::endl;
    std::unique_ptr<int> uniquePtrMoved = std::move(uniquePtr);
    std::cout << "After move: " << uniquePtr.get() << std::endl;  // uniquePtr is become nullptr
    std::cout << "--------------------------" << std::endl;
    // Test std::shared_ptr
    std::cout << "Test std::shared_ptr" << std::endl;
    std::shared_ptr<int> sharedPtr1 = std::make_shared<int>(123);
    std::shared_ptr<int> sharedPtr2 = sharedPtr1;
    std::cout << "use_count: " << sharedPtr1.use_count() << std::endl; // 2 because sharedPtr1 and sharedPtr2 both point to the same object
    std::shared_ptr<int> sharedPtr1Moved = std::move(sharedPtr1); // sharedPtr1 losing ownership of the object and becomes nullptr
    std::cout << "After move: use_count: " << sharedPtr1.use_count() << std::endl;  // because sharedPtr1 is nullptr
    std::cout << "--------------------------" << std::endl;
    // Explanation: shared_ptr uses a reference counting mechanism to manage ownership.

    // Test std::weak_ptr
    std::cout << "Test std::weak_ptr" << std::endl;
    std::shared_ptr<int> sharedPtr3 = std::make_shared<int>(456);
    std::weak_ptr<int> weakPtr = sharedPtr3; // weakPtr is pointing to the same object as sharedPtr3
    std::shared_ptr<int> sharedPtr4 = weakPtr.lock(); // sharedPtr4 is now owning the object
    std::cout << "weak_ptr.use_count: " << weakPtr.use_count() << std::endl; // 2 because sharedPtr3 and sharedPtr4 both point to the same object weakPtr does not count
    std::shared_ptr<int> sharedPtr3Moved = std::move(sharedPtr3); // sharedPtr3 losing ownership of the object and becomes nullptr
    std::cout << "After move: weak_ptr.use_count: " << weakPtr.use_count() << std::endl;  // 2 because sharedPtr4 is still owning the object
    std::cout << "--------------------------" << std::endl;
    // Explanation: weak_ptr is used to break cyclic dependencies in shared_ptr scenarios.
    
    return 0;
}