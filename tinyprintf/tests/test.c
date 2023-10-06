#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "../src/tinyprintf.h"

// Basic tests
Test(simple, char_only)
{
    cr_redirect_stdout();
    tinyprintf("%c", 'c');
    fflush(stdout);
    cr_assert_stdout_eq_str("c");
}

Test(simple, empty)
{
    cr_redirect_stdout();
    tinyprintf("%s", "");
    fflush(stdout);
    cr_assert_stdout_eq_str("");
}

Test(simple, string_only)
{
    cr_redirect_stdout();
    tinyprintf("%s", "Hello\n");
    fflush(stdout);
    cr_assert_stdout_eq_str("Hello\n");
}

Test(simple, int_base10_only)
{
    cr_redirect_stdout();
    tinyprintf("%d", -345);
    fflush(stdout);
    cr_assert_stdout_eq_str("-345");
}

Test(simple, un_only)
{
    cr_redirect_stdout();
    tinyprintf("%u", 345);
    fflush(stdout);
    cr_assert_stdout_eq_str("345");
}

// Medium tests
Test(medium, int_hex_only)
{
    cr_redirect_stdout();
    tinyprintf("%x", 32);
    fflush(stdout);
    cr_assert_stdout_eq_str("20");
}

Test(medium, int_oct_only)
{
    cr_redirect_stdout();
    tinyprintf("%o", 16);
    fflush(stdout);
    cr_assert_stdout_eq_str("20");
}

Test(medium, mix_int_str)
{
    cr_redirect_stdout();
    tinyprintf("%s [%d] %s", "Hello", 42, "world!");
    fflush(stdout);
    cr_assert_stdout_eq_str("Hello [42] world!");
}

Test(medium, mix_hex_str)
{
    cr_redirect_stdout();
    tinyprintf("%s [%x] %s", "Hello", 42, "world!");
    fflush(stdout);
    cr_assert_stdout_eq_str("Hello [2a] world!");
}

Test(medium, pourcentage)
{
    cr_redirect_stdout();
    tinyprintf("%%s", "in your head");
    fflush(stdout);
    cr_assert_stdout_eq_str("%s");
}

// Hard tests
Test(hard, tricky_case)
{
    cr_redirect_stdout();
    tinyprintf("%c%c is %s... %d too.", '4', '2', "the answer", '*');
    fflush(stdout);
    cr_assert_stdout_eq_str("42 is the answer... 42 too.");
}

Test(hard, unknown_case)
{
    cr_redirect_stdout();
    tinyprintf("Good morning ACU! %t Tinyprintf is cool", 12);
    fflush(stdout);
    cr_assert_stdout_eq_str("Good morning ACU! %t Tinyprintf is cool");
}
