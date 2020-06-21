/*


All testing funtionnaity for gdt segments should be implemennt here

It is more complicated to test the basic descriptor for OS code OS data OS Stack

*/

// GDT testing functionnality

#define TEST_H
#define TEST_M

#include "../../../include/string.h"
#include "../../../include/test.h"
#include <stddef.h>

extern char* kgdt;

TEST_UNIT_FUNC(gdt_testing_func__2_);
TEST_UNIT_FUNC(gdt_testing_func__3_);
TEST_UNIT(__gdt_testing_2_);
TEST_UNIT(__gdt_testing_3_);

// Try to go beyond the limit expected , test DS segment

TEST_UNIT(__gdt_testing_2_) = {
    true,
    "test DS segment\n",
    "Verify the DS segment beyond his expected limit\n",
    &gdt_testing_func__2_,
    NULL,
    NULL};

TEST_UNIT_FUNC(gdt_testing_func__2_)
{
    __gdt_testing_2_.passed = true;
    asm volatile(
        "push $0xFFFFFF\n\t"
        "push $0x0\n\t"
        "pop %edx\n\t"
        "pop %ds\n\t"
        "retf\n\t");
}

// Try to go beyond the CS limit with RETF
TEST_UNIT(__gdt_testing_3_) = {true,
                               "test CS segment\n",
                               "Verify the CS beyond his expected limit\n",
                               &gdt_testing_func__3_,
                               NULL,
                               NULL};
TEST_UNIT_FUNC(gdt_testing_func__3_)
{
    __gdt_testing_3_.passed = true;
    asm volatile(
        "push $0xFFFFFF\n\t"
        "push $0x0\n\t"
        "pop %edx\n\t"
        "pop %es\n\t"
        "retf\n\t");
}

TEST_CASE(__gdt_testing__) = {true,
                              "GDT testing\n\t",
                              "Test each segment entries\n\t",
                              {
                                  &__gdt_testing_2_,
                                  &__gdt_testing_3_,
                              },
                              2};