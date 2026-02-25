# 🧠 Smart Pointers in C++

> Hands-on practice with modern C++ memory management using `unique_ptr`, `shared_ptr`, and `weak_ptr`.

---

## 📌 Overview

Raw pointers in C++ require manual `new` / `delete` management, which leads to memory leaks, dangling pointers, and double-free bugs. **Smart pointers** — introduced in C++11 — automate memory management through **RAII** (Resource Acquisition Is Initialization), eliminating these issues entirely.

This module covers all three smart pointer types with real-world examples, documented use cases, and detailed inline comments.

---

## 📂 Files

| File | Description |
|------|-------------|
| `unique_ptr.cpp` | Exclusive ownership — one owner, move-only semantics |
| `shared_ptr.cpp` | Shared ownership — reference-counted, multiple owners |
| `weak_ptr.cpp` | Non-owning observer — breaks circular references |

---

## 🔑 Concepts Covered

### `std::unique_ptr` — Exclusive Ownership

- Only **one** `unique_ptr` can own a resource at a time
- **Cannot be copied** — copy constructor is deleted
- **Can be moved** — transfers ownership via `std::move()`
- Automatically destroys the resource when it goes out of scope

```cpp
// Preferred: make_unique (safe, exception-friendly)
auto user = std::make_unique<User>(1, "abdullah", "a@email.com", "1234");

// Transfer ownership — source becomes null
auto user2 = std::move(user);
```

**When to use:**
- Default choice for any dynamic allocation
- Factory functions returning new objects
- Class members with clear single ownership
- Anywhere you'd use `new` — use `make_unique` instead

---

### `std::shared_ptr` — Shared Ownership

- **Multiple** `shared_ptr`s can own the same resource
- Maintains an internal **reference count**
- Resource is deleted only when the **last owner** is destroyed (count reaches 0)
- Reference counting is **thread-safe**

```cpp
auto author = std::make_shared<Author>("Abdullah", "a@email.com");
// ref_count = 1

auto post1 = std::make_unique<BlogPost>("C++ Guide", "...", author); // ref_count = 2
auto post2 = std::make_unique<BlogPost>("DSA Tutorial", "...", author); // ref_count = 3

// Author is only deleted when ALL posts and 'author' are destroyed
```

**When to use:**
- Multiple objects need to share the same resource
- Lifetime of a resource is determined at runtime
- Shared ownership across containers or threads

---

### `std::weak_ptr` — Non-Owning Observer

`shared_ptr` has one critical weakness: **circular references** cause memory leaks because ref counts never reach 0.

```
// ❌ Circular reference — memory leak!
node1->next = node2;  // node2 ref_count = 2
node2->prev = node1;  // node1 ref_count = 2
// Neither ever reaches 0 → leaked forever
```

`weak_ptr` solves this by observing a resource **without incrementing the ref count**:

```cpp
// ✅ Fixed with weak_ptr
std::shared_ptr<Node> next;  // owns forward reference
std::weak_ptr<Node>   prev;  // observes backward reference — no count!

// Must lock() before use — checks if resource still exists
if (auto locked = weak.lock()) {
    // safe to use locked
} else {
    // resource was already deleted
}
```

**When to use:**
- Breaking cycles in parent-child or graph structures
- Caching without preventing deletion
- Observer pattern (observers shouldn't keep subject alive)
- Temporary references to shared resources

---

## ⚖️ Comparison Summary

| Feature | `unique_ptr` | `shared_ptr` | `weak_ptr` |
|---------|-------------|-------------|------------|
| Ownership | Exclusive | Shared | None |
| Copyable | ❌ | ✅ | ✅ |
| Movable | ✅ | ✅ | ✅ |
| Ref counting | ❌ | ✅ | Doesn't increment |
| Overhead | Zero | Slight (control block) | Slight |
| Use case | Default choice | Multiple owners | Break cycles / observe |

---

## ⚠️ Key Rules & Pitfalls

**Always prefer `make_unique` / `make_shared` over `new`:**
```cpp
// ❌ Less safe — two separate allocations, exception-unsafe
std::shared_ptr<User> u(new User(...));

// ✅ Preferred — single allocation, exception-safe
auto u = std::make_shared<User>(...);
```

**Never mix raw pointers and smart pointers on the same resource.**

**After `std::move`, the source `unique_ptr` becomes null** — accessing it is undefined behavior.

**`weak_ptr` must be `lock()`ed before use** — always check if the returned `shared_ptr` is valid.

---

## 🛠️ Build & Run

Requires **C++14** or later (C++17 recommended):

```bash
g++ -std=c++17 -Wall -Wextra -o unique_ptr unique_ptr.cpp && ./unique_ptr
g++ -std=c++17 -Wall -Wextra -o shared_ptr shared_ptr.cpp && ./shared_ptr
g++ -std=c++17 -Wall -Wextra -o weak_ptr   weak_ptr.cpp   && ./weak_ptr
```

---

## 🔗 Related Modules

- [`../OperatorOverloading`](../OperatorOverloading) — Custom operator implementations
- [`../ManualTesting`](../ManualTesting) — Testing patterns in C++

---

> Part of [Cpp-Skills-Forge](https://github.com/apdalah/Cpp-Skills-Forge) — a hands-on repository for mastering advanced C++ concepts.
