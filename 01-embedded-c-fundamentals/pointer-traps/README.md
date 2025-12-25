# Pointer Traps – Embedded C Interview

This module covers common pointer mistakes, undefined behavior,
and embedded-system-specific pitfalls frequently asked in interviews.

---

## 1. Uninitialized (Wild) Pointer
**Question:** What happens if you dereference an uninitialized pointer?

**Answer:**
- Points to random memory
- Causes undefined behavior
- On ARM Cortex-M → HardFault / BusFault

**Fix:**
Always initialize pointers to NULL.

---

## 2. NULL Pointer vs Wild Pointer
**Question:** Difference between NULL pointer and uninitialized pointer?

**Answer:**
- NULL → known invalid address (0x0)
- Wild → random address
- Both cause undefined behavior if dereferenced

---

## 3. Dangling Pointer
**Question:** What is a dangling pointer?

**Answer:**
- Points to memory that is no longer valid
- Common when returning address of stack variable

---

## 4. Pointer to Const vs Const Pointer
**Question:** Difference between `const int *p` and `int *const p`?

**Rule:**
- `const` applies to the left, otherwise right

---

## 5. Pointer Arithmetic
**Question:** What does `ptr + 1` do?

**Answer:**
- Moves by `sizeof(type)`
- NOT by 1 byte

---

## 6. Void Pointer
**Question:** Why can't we dereference a void pointer?

**Answer:**
- Compiler doesn't know the size
- Must typecast before dereferencing

---

## 7. Double Pointer
**Question:** Why do we use double pointers?

**Answer:**
- Modify pointer itself
- Used in drivers, allocators, init APIs

---

## 8. Array vs Pointer
**Question:** Difference between array and pointer?

**Key Point:**
- `sizeof(array)` ≠ `sizeof(pointer)`

---

## 9. Function Pointers
**Question:** Where are function pointers used in embedded systems?

**Answer:**
- ISR vector table
- Driver callbacks
- State machines

---

## 10. Volatile Pointer (Embedded GOLD)
**Question:** Why volatile is mandatory for hardware registers?

**Answer:**
- Prevents compiler optimization
- Register value can change asynchronously
