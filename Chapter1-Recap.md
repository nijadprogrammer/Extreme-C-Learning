# Extreme C — Chapter 1: Essential Features

## 1. Preprocessor

The **preprocessor** runs before the compiler and modifies the source code.

Common directives:

```c
#include <stdio.h>
#define PI 3.14
#ifdef DEBUG
```

### Macros

Macros are substitutions performed by the preprocessor.

```c
#define SQUARE(x) ((x) * (x))
```

Advantages:

* No function-call overhead in the traditional sense
* Useful for constants and conditional compilation

Disadvantages:

* No normal type checking
* Can produce unexpected results if not carefully written

---

## 2. Bits, Bytes & Memory

### Bit

The smallest unit of information:

```text
0 or 1
```

### Byte

A byte is typically **8 bits**.

```text
01000001
```

can represent the decimal value:

```text
65
```

and under ASCII:

```text
65 → 'A'
```

Important:

> `65` is the **value of a byte**, not 65 bytes.

### Memory

Memory can be thought of as a sequence of addressable locations:

```text
Address     Data
1000        65
1001        66
1002        67
```

* **Address** = where the data is
* **Data** = what is stored there
* **Byte** = the unit of memory being stored
* **Bits** = the 0s and 1s making up the byte

---

# 3. Pointers

A pointer is a variable that stores an **address**.

```c
int x = 10;
int *ptr = &x;
```

Conceptually:

```text
x
Address 1000
   ↓
  [10]

ptr
 ↓
1000
```

### `&`

Gets the address of a variable:

```c
&x
```

> "Where is `x`?"

### `*`

Dereferences a pointer:

```c
*ptr
```

> "Give me the data at the address stored in `ptr`."

Important distinction:

```text
ptr   → address
*ptr  → data at that address
&x    → address of x
```

---

# 4. Pointer Types

The pointer type tells C **what type of object the pointer points to**.

```c
char *p;
short *p;
int *p;
```

Typical sizes:

```text
char   → 1 byte
short  → 2 bytes
int    → 4 bytes
```

Therefore pointer arithmetic depends on the pointer type.

```c
char *p;
p++;
```

typically moves 1 byte.

```c
int *p;
p++;
```

typically moves 4 bytes.

Important:

> The address itself does not change size based on the pointer type. The pointer type determines how C interprets the memory and how pointer arithmetic works.

---

# 5. Casting

A cast tells C:

> "For this particular expression, treat this value as another type."

Example:

```c
unsigned char *ptr = (unsigned char *)data;
```

The address itself does **not** change.

```text
data
 ↓
1000

(unsigned char*)data
 ↓
1000
```

Only the interpretation/type changes.

Example:

```c
circle_t *p1 = &c;
point_t  *p2 = (point_t *)&c;
int      *p3 = (int *)&c;
```

All can contain the same address:

```text
p1 ──→ 1000
p2 ──→ 1000
p3 ──→ 1000
```

but they interpret that address differently.

---

# 6. Generic Pointers — `void*`

```c
void *ptr;
```

A `void*` is a generic pointer.

It means:

> "This is an address, but I am not specifying what type of object is there."

Useful for generic functions, but the pointed-to type usually needs to be known/cast before performing typed operations.

---

# 7. `typedef`

`typedef` creates an alternative name for a type.

```c
typedef int bool_t;
```

Now:

```c
bool_t x;
```

is equivalent to:

```c
int x;
```

### Function-pointer typedef

```c
typedef bool_t (*less_than_func_t)(int, int);
```

This creates a type representing:

> A pointer to a function that takes two `int`s and returns `bool_t`.

Then:

```c
less_than_func_t func_ptr;
```

means:

```text
less_than_func_t → type
func_ptr         → variable
```

This makes complicated function-pointer declarations easier to read and reuse.

---

# 8. Function Pointers

Functions also have addresses.

```c
int sum(int a, int b) {
    return a + b;
}
```

A function pointer:

```c
int (*func_ptr)(int, int);
```

can point to `sum`:

```c
func_ptr = &sum;
```

and call it:

```c
func_ptr(5, 4);
```

The same pointer can later point to another compatible function:

```c
func_ptr = &subtract;
```

This allows a program to choose which function to execute through a pointer.

Common uses:

* Callbacks
* Interrupt handlers
* Drivers
* Function tables
* Selecting different operations at runtime

---

# 9. Structs

A `struct` groups related data into one object.

```c
struct sample_t {
    char first;
    char second;
    char third;
    short fourth;
};
```

Creating an object:

```c
struct sample_t data;
```

creates the actual structure in memory.

A pointer to it:

```c
struct sample_t *data;
```

means:

> `data` stores the address of a `struct sample_t`.

---

# 10. Struct Memory Layout

A struct is stored as bytes in memory.

For example:

```c
struct sample_t {
    char first;
    char second;
    char third;
    short fourth;
};
```

Typical layout:

```text
Address     Content
1000        first
1001        second
1002        third
1003        padding
1004        fourth
1005        fourth
```

Total:

```text
3 char + 1 padding + 2 short = 6 bytes
```

### Padding & Alignment

The compiler may insert unused bytes (**padding**) to satisfy alignment requirements.

For example, a `short` is typically 2 bytes and commonly aligned to an even address:

```text
1002 → char
1003 → padding
1004 → short
```

Padding bytes do not represent a struct field and their value should not be relied upon.

---

# 11. `sizeof` with Pointers

Given:

```c
void print_size(struct sample_t *data) {
    printf("%zu\n", sizeof(*data));
}
```

`data` is a pointer:

```text
data
 ↓
address
 ↓
struct sample_t
```

Therefore:

```c
sizeof(data)
```

= size of the **pointer**

while:

```c
sizeof(*data)
```

= size of the **struct being pointed to**

Important:

> `*data` means the object at the address stored in `data`.

Inside `sizeof`, `sizeof(*data)` uses the type of `*data` to determine its size; it does not need to actually read the struct's memory.

For printing `size_t`:

```c
printf("%zu", sizeof(*data));
```

`%zu` is the appropriate format specifier.

---

# 12. Viewing Raw Memory

Example:

```c
void print_bytes(struct sample_t *data) {
    unsigned char *ptr = (unsigned char *)data;

    for (int i = 0; i < sizeof(*data); i++, ptr++) {
        printf("%d ", (unsigned int)*ptr);
    }
}
```

The important line is:

```c
unsigned char *ptr = (unsigned char *)data;
```

This means:

1. `data` contains the address of the struct.
2. Cast that address to `unsigned char*`.
3. Create `ptr` to view the memory one byte at a time.

The address does not change:

```text
data
 ↓
1000

ptr
 ↓
1000
```

But their types are different:

```text
data → struct sample_t*
ptr  → unsigned char*
```

Because `ptr` is an `unsigned char*`:

```c
ptr++;
```

moves to the next byte.

---

# 13. Understanding `print_bytes()` Output

Suppose:

```c
data->first  = 'A';
data->second = 'B';
data->third  = 'C';
data->fourth = 765;
```

A typical memory representation might be:

```text
Address     Byte       Meaning
1000        65         'A'
1001        66         'B'
1002        67         'C'
1003        125        padding
1004        253        part of 765
1005        2          part of 765
```

Therefore:

```text
65 66 67 125 253 2
```

### Important

`65` does **not** mean 65 bytes.

It means:

```text
1 byte
01000001
   ↓
decimal value 65
   ↓
ASCII 'A'
```

---

# 14. Integer Representation & Endianness

The number:

```text
765 decimal
```

is:

```text
0x02FD
```

On a typical little-endian system, the lower byte is stored first:

```text
FD 02
```

Therefore:

```text
FD → 253
02 → 2
```

The computer stores the **bytes**, not a decimal number written as "765".

---

# 15. Nested Structs & Pointer Casting

Example:

```c
typedef struct {
    int x;
    int y;
} point_t;

typedef struct {
    point_t center;
    int radius;
} circle_t;
```

Memory can look like:

```text
circle_t
┌──────────────┐
│ center.x     │
│ center.y     │
│ radius       │
└──────────────┘
```

Because `center` is the first member, the address of the `circle_t` begins at the same location as the address of `center`.

Therefore:

```c
circle_t *p1 = &c;
point_t  *p2 = (point_t *)&c;
int      *p3 = (int *)&c;
```

can all contain the same starting address.

```text
p1 ──→ address 1000 → circle_t
p2 ──→ address 1000 → point_t
p3 ──→ address 1000 → int
```

The cast doesn't move the address.

It changes how C interprets the address.

---

# 16. Core Mental Model

The most important concepts from this chapter:

```text
BIT
 ↓
0 or 1

BYTE
 ↓
typically 8 bits

MEMORY
 ↓
collection of addressable locations

ADDRESS
 ↓
where something is

DATA
 ↓
what is stored there

POINTER
 ↓
stores an address

POINTER TYPE
 ↓
tells C what the address points to

DEREFERENCE (*)
 ↓
access the object at that address

CAST
 ↓
temporarily treat a value/address as another type

STRUCT
 ↓
groups multiple pieces of data

PADDING
 ↓
extra memory inserted for alignment
```

### One sentence summary

> **C gives direct control over memory by allowing us to work with addresses, pointers, types, raw bytes, and different interpretations of the same memory.**
