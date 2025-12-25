/*
 * File: pointer_traps.c
 * Purpose: Common pointer traps asked in Embedded C interviews
 * Author: Ajay Kumar
 *
 * This file covers real-world pointer mistakes, undefined behavior,
 * and embedded-system-specific implications.
 */

#include <stdio.h>
#include <stdint.h>

/* ============================================================
 * 1. UNINITIALIZED POINTER (Wild Pointer)
 * ============================================================
 *
 * Interview Question:
 * What happens if you dereference an uninitialized pointer?
 *
 * Explanation:
 * - Pointer contains a garbage address
 * - Dereferencing leads to undefined behavior
 * - On embedded systems → HardFault / BusFault
 */

void uninitialized_pointer_demo(void)
{
    int *ptr;          // ❌ uninitialized
    //*ptr = 10;        // ❌ undefined behavior
}

/*
 * Interview Expectation:
 * - Candidate must say "undefined behavior"
 * - Must mention HardFault in ARM Cortex-M
 * - Correct fix: initialize to NULL
 */

/* ============================================================
 * 2. NULL POINTER DEREFERENCE
 * ============================================================
 *
 * Interview Question:
 * Difference between NULL pointer and uninitialized pointer?
 *
 * Explanation:
 * - NULL pointer points to address 0x0
 * - Dereferencing NULL is still undefined behavior
 * - Easier to detect/debug than wild pointer
 */

void null_pointer_demo(void)
{
    int *ptr = NULL;

    if (ptr != NULL)
    {
        *ptr = 10;
    }
}

/*
 * Embedded Insight:
 * - NULL dereference → HardFault
 * - MPU can be used to catch early
 */

/* ============================================================
 * 3. DANGLING POINTER
 * ============================================================
 *
 * Interview Question:
 * What is a dangling pointer?
 *
 * Explanation:
 * - Pointer points to memory that is no longer valid
 * - Common with stack variables or freed heap memory
 */

int *dangling_pointer_demo(void)
{
    int local = 10;
    return &local;     // ❌ returns address of stack variable
}

/*
 * Interview Expectation:
 * - Stack memory becomes invalid after function returns
 * - Using this pointer later = undefined behavior
 */

/* ============================================================
 * 4. POINTER TO CONST vs CONST POINTER
 * ============================================================
 *
 * Interview Question (Very Common):
 * Difference between:
 *   const int *p
 *   int *const p
 */

void const_pointer_demo(void)
{
    int a = 10;
    int b = 20;

    const int *p1 = &a;    // data is const
    int *const p2 = &a;    // pointer is const

    //*p1 = 5;             // ❌ not allowed
    p1 = &b;               // ✅ allowed

    *p2 = 15;              // ✅ allowed
    //p2 = &b;             // ❌ not allowed
}

/*
 * Interview Expectation:
 * - Explain in simple English
 * - "const applies to left, otherwise right"
 */

/* ============================================================
 * 5. POINTER ARITHMETIC TRAP
 * ============================================================
 *
 * Interview Question:
 * What does ptr+1 mean?
 *
 * Explanation:
 * - ptr+1 moves by sizeof(type), NOT 1 byte
 */

void pointer_arithmetic_demo(void)
{
    int arr[3] = {10, 20, 30};
    int *p = arr;

    printf("%d\n", *(p + 1));   // prints 20
}

/*
 * Embedded Insight:
 * - Critical when accessing memory-mapped registers
 * - Wrong type = wrong address access
 */

/* ============================================================
 * 6. VOID POINTER TRAP
 * ============================================================
 *
 * Interview Question:
 * Why can't we dereference a void pointer?
 *
 * Explanation:
 * - void has no size
 * - Compiler doesn't know how many bytes to read
 */

void void_pointer_demo(void)
{
    int a = 10;
    void *vp = &a;

    //printf("%d\n", *vp);       // ❌ invalid
    printf("%d\n", *(int *)vp); // ✅ correct
}

/*
 * Interview Expectation:
 * - Mention type casting
 * - Mention generic APIs (malloc, memcpy)
 */

/* ============================================================
 * 7. FUNCTION POINTER TRAP
 * ============================================================
 *
 * Interview Question:
 * Why are function pointers used in embedded systems?
 */

void handler1(void)
{
    printf("Handler 1\n");
}

void handler2(void)
{
    printf("Handler 2\n");
}

void function_pointer_demo(void)
{
    void (*fp)(void);

    fp = handler1;
    fp();

    fp = handler2;
    fp();
}

/*
 * Embedded Usage:
 * - ISR vector table
 * - Driver callbacks
 * - State machines
 */

/* ============================================================
 * 8. ARRAY vs POINTER CONFUSION
 * ============================================================
 *
 * Interview Question:
 * Difference between array and pointer?
 */

void array_pointer_demo(void)
{
    int arr[5];
    int *p = arr;

    printf("%lu\n", sizeof(arr)); // 20 bytes
    printf("%lu\n", sizeof(p));   // 4 or 8 bytes
}

/*
 * Interview Expectation:
 * - Arrays decay to pointers
 * - sizeof behavior difference
 */

/* ============================================================
 * 9. DOUBLE POINTER TRAP
 * ============================================================
 *
 * Interview Question:
 * Why use double pointer?
 */

void update_pointer(int **pp)
{
    static int x = 100;
    *pp = &x;
}

void double_pointer_demo(void)
{
    int *p = NULL;
    update_pointer(&p);
}

/*
 * Embedded Usage:
 * - Memory management
 * - Driver initialization
 * - Passing buffers
 */

/* ============================================================
 * 10. VOLATILE POINTER TRAP (Embedded GOLD)
 * ============================================================
 *
 * Interview Question:
 * Why volatile is mandatory for hardware registers?
 */

#define REG_ADDR 0x40000000
volatile uint32_t *reg = (volatile uint32_t *)REG_ADDR;

/*
 * Explanation:
 * - Prevents compiler optimization
 * - Hardware value may change asynchronously
 * - Mandatory for memory-mapped IO
 */

/* ============================================================
 * END OF FILE
 * ============================================================
 */
