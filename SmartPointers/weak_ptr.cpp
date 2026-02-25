#include <memory>
#include <algorithm>
#include <iostream>
#include <vector>

/**
* ********************* Weak Pointers (std::weak_ptr) ***********************
*
* shared_ptr has ONE major weakness - circular references:
*
*		 A owns B, B owns A → Both ref_counts never reach 0 → MEMORY LEAK!
*        
*          struct Node {
*            int value;
*            std::shared_ptr<Node> next;  // ❌ This can cause memory leaks!
*    
*            Node(int v) : value(v) {
*                std::cout << "Node " << value << " created\n";
*            }
*    
*            ~Node() {
*                std::cout << "Node " << value << " destroyed\n";
*            }
*         };
*
*         void circularReferenceBug() {
*            auto node1 = std::make_shared<Node>(1);  // ref_count = 1
*            auto node2 = std::make_shared<Node>(2);  // ref_count = 1
*    
*            node1->next = node2;  // node2 ref_count = 2
*            node2->next = node1;  // node1 ref_count = 2
*    
*            // Function ends:
*            // node1 goes out of scope → ref_count = 1 (still held by node2->next)
*            // node2 goes out of scope → ref_count = 1 (still held by node1->next)
*            // MEMORY LEAK! Neither can be deleted!
*         }
* 
* Solution -> std::weak_ptr
*	- weak_ptr is a non-owning observer:
*	- Doesn't increase reference count
*	- Can check if resource still exists
*	- Must convert to shared_ptr before use
*	- Breaks circular references
* 
* Lets Start again with std::weak_ptr :)
* 
*        struct Node {
*            int value;
*            std::shared_ptr<Node> next;    // Forward reference (owns)
*            std::weak_ptr<Node> prev;      // Backward reference (observes) ✅
*    
*            Node(int v) : value(v) {
*                std::cout << "Node " << value << " created\n";
*            }
*    
*            ~Node() {
*                std::cout << "Node " << value << " destroyed\n";
*            }
*        };
*
*        void fixedCircularReference() {
*            auto node1 = std::make_shared<Node>(1);  // ref_count = 1
*            auto node2 = std::make_shared<Node>(2);  // ref_count = 1
*    
*            node1->next = node2;  // node2 ref_count = 2
*            node2->prev = node1;  // node1 ref_count STILL 1 (weak_ptr doesn't count!)
*    
*            // Function ends:
*            // node1 goes out of scope → ref_count = 0 → DELETED ✅
*            // node2->prev becomes invalid (but that's okay, it's weak)
*            // node2 goes out of scope → ref_count = 0 → DELETED ✅
*        }
*
* 
* WHEN TO USE std::weak_ptr ?
*   - Breaking cycles (parent-child with back-references)
*   - Caching without preventing deletion
*   - Observer pattern (observers shouldn't keep subject alive)
*   - Temporary references to shared resources
*
*/


void weakPtrUsage() {
    std::weak_ptr<int> weak;

    {
        auto shared = std::make_shared<int>(42);
        weak = shared;  // weak observes shared

        std::cout << "Ref count: " << shared.use_count() << "\n";  // 1
        std::cout << "Weak count: " << weak.use_count() << "\n";    // 1

        // Use weak_ptr: must lock() first
        if (auto locked = weak.lock()) {  // Returns shared_ptr
            std::cout << "Value: " << *locked << "\n";  // 42
        }
        else {
            std::cout << "Resource deleted\n";
        }

    }  // shared destroyed, resource deleted

    // Try to use weak_ptr after resource deleted
    if (auto locked = weak.lock()) {
        std::cout << "Value: " << *locked << "\n";
    }
    else {
        std::cout << "Resource deleted\n";  // This prints!
    }
}

int main()
{
    weakPtrUsage();

    return 0;
}