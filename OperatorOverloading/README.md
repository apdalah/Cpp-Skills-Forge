# ⚙️ Operator Overloading in C++

> Demonstrating how C++ allows custom types to use built-in operators through a 2D coordinate class `MP`.

---

## 📌 Overview

C++ lets you redefine the behavior of operators (`+`, `-`, `*`, `/`, `==`, `<<`, ...) for your own types. This is called **operator overloading** — it makes user-defined classes feel as natural to use as built-in types like `int` or `float`.

```cpp
// Without operator overloading — verbose and unnatural
MP result = position.add(move).subtract(offset);

// With operator overloading — clean and expressive
MP result = position + move - offset;
```

This module implements operator overloading through `MP` (Manipulate Operators), a lightweight 2D coordinate class that models positions and movements on a 2D plane.

---

## 📂 Files

| File | Description |
|------|-------------|
| `OperatorOverloading.cpp` | Full implementation of the `MP` class with all overloaded operators and a demo `main()` |

---

## 🏗️ The `MP` Class

```cpp
class MP {
public:
    float X, Y;

    MP();                    // Default: (0, 0)
    MP(float x, float y);   // Parameterized
    void printPosition(const std::string& movement);
};
```

`MP` represents a 2D point or vector. It is the vehicle for demonstrating all operator overloading techniques covered in this module.

---

## 🔧 Implemented Operators

### `operator+` — Addition
Adds two `MP` objects component-wise. Neither operand is modified.

```cpp
MP operator+(const MP& other) const;
```

```cpp
MP position(10.0f, 20.0f);
MP move(0.5f, 0.5f);
MP result = position + move;  // X[10.5] Y[20.5]
```

---

### `operator-` — Subtraction
Subtracts one `MP` from another component-wise. Useful for computing displacement or reversing movement.

```cpp
MP operator-(const MP& other) const;
```

```cpp
MP position(10.0f, 20.0f);
MP step(1.8f, 1.8f);
MP result = position - step;  // X[8.2] Y[18.2]
```

---

### `operator*` — Multiplication (Component-wise)
Multiplies each component independently. This is a **Hadamard product**, not a dot or cross product.

```cpp
MP operator*(const MP& other) const;
```

```cpp
MP position(10.0f, 20.0f);
MP scale(1.5f, 1.5f);
MP result = position * scale;  // X[15] Y[30]
```

---

### `operator/` — Division (with Zero Guard)
Divides component-wise. Returns `MP(0, 0)` if **either** divisor component is zero to prevent undefined behavior.

```cpp
MP operator/(const MP& other) const;
```

```cpp
MP position(10.0f, 20.0f);
MP divisor(2.0f, 2.0f);
MP result = position / divisor;  // X[5] Y[10]

MP zero(0.0f, 2.0f);
MP safe = position / zero;  // X[0] Y[0]  ← zero guard triggered
```

> ⚠️ **Note:** The zero guard returns `MP(0, 0)` if **either** component is zero, meaning a valid component may be silently discarded. For example, `MP(10, 5) / MP(2, 0)` returns `MP(0, 0)`, not `MP(5, 0)`. Consider per-component handling if precision matters.

---

### `operator==` — Equality Comparison
Returns `true` only if both X and Y components match exactly.

```cpp
bool operator==(const MP& other) const;
```

```cpp
MP a(10.0f, 20.0f);
MP b(10.0f, 20.0f);
a == b;  // true

MP c(10.0f, 19.9f);
a == c;  // false
```

> ⚠️ **Note:** Compares `float` values with `==`, which can produce unexpected results for values computed through floating-point arithmetic. For computed positions, prefer an epsilon-based comparison: `std::abs(X - rhs.X) < 1e-5f`.

---

### `operator!=` — Inequality Comparison
Returns the logical negation of `operator==`. Implemented by delegating to `*this == other`, ensuring both operators stay consistent with zero duplication.

```cpp
bool operator!=(const MP& other) const;
```

```cpp
MP a(10.0f, 20.0f);
MP b(9.0f, 20.0f);
a != b;  // true
```

---

### `operator<<` — Stream Insertion *(non-member)*
Enables `std::cout << mp` syntax. Defined **outside the class** so that the stream appears on the left and the `MP` object on the right — matching how stream operators naturally work. Returns a reference to the stream to support chaining.

```cpp
std::ostream& operator<<(std::ostream& stream, const MP& obj);
```

```cpp
MP pos(3.0f, 7.5f);
std::cout << pos;                      // X[3] Y[7.5]
std::cout << "Position: " << pos;      // Position: X[3] Y[7.5]  ← chaining works
```

---

## 📋 Operators Summary

| Operator | Type | Member? | Returns | Purpose |
|----------|------|---------|---------|---------|
| `+` | Binary | Member | `MP` | Component-wise addition |
| `-` | Binary | Member | `MP` | Component-wise subtraction |
| `*` | Binary | Member | `MP` | Component-wise multiplication (Hadamard) |
| `/` | Binary | Member | `MP` | Component-wise division with zero guard |
| `==` | Comparison | Member | `bool` | Exact equality check |
| `!=` | Comparison | Member | `bool` | Inequality (delegates to `==`) |
| `<<` | Stream | **Non-member** | `ostream&` | Formatted output + chaining |

---

## 💡 Key Design Decisions

**Member vs. Non-member operators:**
Arithmetic and comparison operators are implemented as **member functions** since they directly access `X` and `Y`. The `<<` operator is a **non-member** because `std::ostream` is on the left-hand side — a class can't control what happens to its left operand.

**`const` correctness:**
All operators are marked `const` since they don't modify the object they're called on. This allows them to be used on `const MP` instances safely.

**Delegating `!=` to `==`:**
Rather than reimplementing the comparison logic, `operator!=` delegates to `operator==` via `!(*this == other)`. This guarantees both operators always agree and eliminates duplicated logic.

**Return by value:**
Arithmetic operators return a new `MP` by value rather than modifying either operand. This matches how mathematical expressions work — `a + b` should never change `a` or `b`.

---

## 🛠️ Build & Run

Requires **C++11** or later:

```bash
g++ -std=c++11 -Wall -Wextra -o operators OperatorOverloading.cpp && ./operators
```

---

## 🔗 Related Modules

- [`../SmartPointers`](../SmartPointers) — Memory management with `unique_ptr`, `shared_ptr`, `weak_ptr`
- [`../ManualTesting`](../ManualTesting) — Testing patterns in C++

---

> Part of [Cpp-Skills-Forge](https://github.com/apdalah/Cpp-Skills-Forge) — a hands-on repository for mastering advanced C++ concepts.
