#include <iostream>
#include <memory>

using namespace std;

class User
{
private:
	int id;
	string username;
	string email;
	string password;
public:
	User(int initialId, string initialUsername, string initialEmail, string initialPassword) :
		id(initialId), username(initialUsername), email(initialEmail), password(initialPassword)
	{}

	User(const User& other) :
		id(other.id), username(other.username), email(other.email), password(other.password)
	{}

	User& operator=(const User& other)
	{
		if (this != &other)
		{
			id = other.id;
			username = other.username;
			email = other.email;
			password = other.password;
		}
	}

	~User()
	{
		cout << "User with id " << id << " is being destroyed." << endl;
	}

	void display()
	{
		cout << "\nID: " << id << endl;
		cout << "Username: " << username << endl;
		cout << "Email: " << email << endl;
		cout << endl;
	}

};

void uniquePtr()
{
	/**
	* @brief Using std::unique_ptr to manage a User object
	* 
	* ** unique_ptr ** 
	* 
	* - Only ONE unique_ptr can own a resource at a time
	* - Cannot be copied (copy constructor deleted)
	* - Can be moved (transfers ownership)
	* - Automatically deletes when it goes out of scope
	* 
	* 
	* ** WHEN TO USE unique_ptr **
	* 
	* 1- Default choice for dynamic allocation :
	* 
	*	 Instead of: int* arr = new int[100]; -> auto arr = std::make_unique<int[]>(100); // safer and more efficient
	* 
    * 2- Factory functions (returning new objects) :
	* 
	*	 std::unique_ptr<User> createPost(const string& email) 
	*	 {
	*	   return std::make_unique<User>(id, email, "username", "password");
	*	 }
	* 
	* 3- Class members (owning resources)
	* 
	*	 class BlogManager 
	*	 {
	*	   std::unique_ptr<Database> db;  // BlogManager owns the database
	*	   std::vector<std::unique_ptr<Post>> posts;  // Owns all posts
	*    };
	* 
	* 4- Single ownership semantics (clear who's responsible)
	* 
	*/
	std::unique_ptr<User> user1 = std::make_unique<User>(1, "abdullah", "apdullah@email.com", "1234"); // default syntax

	auto autoUser = std::make_unique<User>(2, "mohamed", "mohamed@email.com", "1234"); // auto keyword can be used to simplify the syntax

	std::unique_ptr<User> user2(new User(3, "khaled", "khaled@email.com", "1234")); // direct initialization (not recommended, less safe than make_unique)
	
	user1->display();

	// Example 2: Moving Ownership(Can't Copy)
	std::unique_ptr<User> user3 = std::move(autoUser); // Transfer ownership from user to user3

	user3->display();

	// Important Note: 
	// 
	// 1- Local variables are destroyed in reverse order of declaration 
	//    -> destruction happens in reverse: user3 → user2 → autoUser → user1
	// 
	// 2- After std::move, the source pointer becomes null/empty 
	//	  -> autoUser is destroyed, it has nothing to delete, which is why there's no destructor message for it (autoUser = silence)
	//
}

//int main()
//{
//	uniquePtr();
//
//	return 0;
//}

