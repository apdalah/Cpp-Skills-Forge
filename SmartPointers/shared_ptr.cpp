#include <memory>
#include <string>
#include <iostream>
#include <vector>

/**
* ********** Shared Pointers (std::shared_ptr) ***********
* 
* Imagine a scenario:
*	- Multiple blog posts can have the same author
*	- Posts can be deleted independently
*	- Author should only be deleted when ALL posts are gone
*	-> Who owns the Author? 
* 
* With unique_ptr, you'd have issues:
*
*	class Author { ...... };
*	class BlogPost {
*		std::unique_ptr<Author> author;  // ❌ Each post would own a different author! [Can't share the same Author between posts with unique_ptr]
*	};
*
* Solution -> std::shared_ptr - Reference Counting
*	- shared_ptr implements shared ownership using reference counting:
*	- Multiple shared_ptrs can own the same resource
*	- Keeps a count of how many owners exist
*	- Resource deleted when last owner is destroyed (count reaches 0)
*	- Thread-safe reference counting (can share across threads)
* 
*	unique_ptr: ONE owner, can't copy, can move
*		std::unique_ptr<int> u1 = std::make_unique<int>(42);
*		auto u2 = u1;  // ❌ Can't copy
*
*	shared_ptr: MULTIPLE owners, can copy AND move
*		std::shared_ptr<int> s1 = std::make_shared<int>(42);
*		auto s2 = s1;  // ✅ Both own the same int, count = 2
*
*	### **How Reference Counting Works**
*		- Create shared_ptr:   [Resource] ← ref_count = 1
*		- Copy shared_ptr:     [Resource] ← ref_count = 2
*		- Copy again:          [Resource] ← ref_count = 3
*		- First ptr destroyed: [Resource] ← ref_count = 2
*		- Second destroyed:    [Resource] ← ref_count = 1
*		- Last one destroyed:  [Resource DELETED] ← ref_count = 0
*/



void basicSharedPtr() {
    // Create shared_ptr using make_shared (ALWAYS prefer this!)
    auto ptr1 = std::make_shared<int>(42);
    std::cout << "Value: " << *ptr1 << "\n";
    std::cout << "Ref count: " << ptr1.use_count() << "\n";  // 1

    // Copy - both point to same resource
    auto ptr2 = ptr1;
    std::cout << "After copy, ref count: " << ptr1.use_count() << "\n";  // 2

    {
        auto ptr3 = ptr1;  // Another copy
        std::cout << "Inside scope, ref count: " << ptr1.use_count() << "\n";  // 3
    }  // ptr3 destroyed

    std::cout << "After scope, ref count: " << ptr1.use_count() << "\n";  // 2
}  // ptr1 and ptr2 destroyed, resource deleted when count hits 0


void proceduralExample() {
    // Create shared resource
    auto data = std::make_shared<std::string>("Important Data");

    std::cout << "Initial ref count: " << data.use_count() << "\n";  // 1

    // Store in vector - copies the shared_ptr
    std::vector<std::shared_ptr<std::string>> holders;
    holders.push_back(data);  // ref count: 2
    holders.push_back(data);  // ref count: 3
    holders.push_back(data);  // ref count: 4

    std::cout << "After adding to vector: " << data.use_count() << "\n";  // 4

    // All point to same data
    *data = "Modified Data";
    for (const auto& holder : holders) {
        std::cout << *holder << "\n";  // All print "Modified Data"
    }

    // Remove some references
    holders.pop_back();  // ref count: 3
    holders.clear();     // ref count: 1 (only 'data' remains)

    std::cout << "Final ref count: " << data.use_count() << "\n";  // 1
}  // data destroyed, resource deleted (count = 0)


///////////////// OOP Style - Shared Author Between Posts

class Author {
private:
    std::string name;
    std::string email;

public:
    Author(const std::string& n, const std::string& e)
        : name(n), email(e) {
        std::cout << "✍️  Author created: " << name << "\n";
    }

    ~Author() {
        std::cout << "🗑️  Author destroyed: " << name << "\n";
    }

    std::string getName() const { return name; }
    std::string getEmail() const { return email; }
};

class BlogPost {
private:
    std::string title;
    std::string content;
    std::shared_ptr<Author> author;  // Shared ownership!

public:
    BlogPost(const std::string& t, const std::string& c,
        std::shared_ptr<Author> a)
        : title(t), content(c), author(a) {
        std::cout << "📝 Post created: " << title << "\n";
    }

    ~BlogPost() {
        std::cout << "🗑️  Post destroyed: " << title << "\n";
    }

    void display() const {
        std::cout << "Title: " << title << "\n";
        std::cout << "Author: " << author->getName()
            << " (" << author->getEmail() << ")\n";
        std::cout << "Content: " << content << "\n";
        std::cout << "Author ref count: " << author.use_count() << "\n";
    }
};

void blogWithSharedAuthor() {
    std::cout << "=== Creating shared author ===\n";

    // Create author - will be shared by multiple posts
    auto abdullah = std::make_shared<Author>("Abdullah", "abdullah@example.com");
    std::cout << "Author ref count: " << abdullah.use_count() << "\n\n";  // 1

    std::vector<std::unique_ptr<BlogPost>> posts;

    std::cout << "=== Creating posts with shared author ===\n";
    posts.push_back(std::make_unique<BlogPost>(
        "C++ Smart Pointers",
        "Learn memory management",
        abdullah  // Share the author
    ));
    std::cout << "Author ref count: " << abdullah.use_count() << "\n\n";  // 2

    posts.push_back(std::make_unique<BlogPost>(
        "DSA Tutorial",
        "Master algorithms",
        abdullah  // Same author
    ));
    std::cout << "Author ref count: " << abdullah.use_count() << "\n\n";  // 3

    posts.push_back(std::make_unique<BlogPost>(
        "Database Guide",
        "SQL fundamentals",
        abdullah  // Same author again
    ));
    std::cout << "Author ref count: " << abdullah.use_count() << "\n\n";  // 4

    std::cout << "=== Displaying all posts ===\n";
    for (const auto& post : posts) {
        post->display();
        std::cout << "---\n";
    }

    std::cout << "=== Deleting first post ===\n";
    posts.erase(posts.begin());  // Delete first post
    std::cout << "Author ref count: " << abdullah.use_count() << "\n\n";  // 3

    std::cout << "=== Function ending ===\n";
    // posts vector destroyed (deletes all BlogPosts)
    // abdullah destroyed
    // Author deleted when last reference (abdullah) is destroyed
}


//int main()
//{
//	// basicSharedPtr();
//    //proceduralExample();
//    blogWithSharedAuthor();
//
//    return 0;
//}