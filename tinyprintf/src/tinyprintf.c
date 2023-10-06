#include "tinyprintf.h"

int str_len(const char *s)
{
    int n = 0;
    while (s[n] != '\0')
    {
        n++;
    }
    return n;
}

void str_revert(char *s)
{
    int n = str_len(s);
    int i = 0;
    char tmp;
    while (i < n / 2)
    {
        tmp = s[i];
        s[i] = s[n - 1 - i];
        s[n - 1 - i] = tmp;
        i++;
    }
}

// Convert for an int in any base
char *itoa_base(int n, char *base)
{
    char *s = malloc(sizeof(char) * 20);
    if (n == 0)
    {
        s[0] = base[0];
        s[1] = '\0';
        return s;
    }
    int bis = n;
    if (n < 0)
        n = -n;
    int i = 0;
    int nb_base = str_len(base);
    int r;
    while (n > 0)
    {
        r = n % nb_base;
        s[i] = base[r];
        i++;
        n = n / nb_base;
    }
    if (bis < 0)
    {
        s[i] = '-';
        i++;
    }
    s[i] = '\0';
    str_revert(s);
    return s;
}

// Display the string in the terminal
void print_res(char *s, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (s[i] == '\\' && i + 1 < len)
        {
            if (s[i + 1] == 'n')
            {
                putchar('\n');
                i++;
            }
            else if (s[i + 1] == 't')
            {
                putchar('\t');
                i++;
            }
            else
            {
                putchar('\\');
            }
        }
        putchar(s[i]);
    }
}

int display(char *s)
{
    int length = str_len(s);
    print_res(s, length); // Display string
    return length;
}

int match(char c, char type, va_list ap)
{
    int count = 0;
    switch (type)
    {
    case '%':
        putchar('%');
        count++;
        break;
    // Signed decimal
    case 'd':
        count += display(itoa_base(va_arg(ap, int), "0123456789"));
        break;
    // Decimal unsigned
    case 'u':
        count += display(itoa_base(va_arg(ap, unsigned), "0123456789"));
        break;
    // String
    case 's':
        count += display(va_arg(ap, char *));
        break;
    // Char
    case 'c':
        count++;
        putchar(va_arg(ap, int));
        break;
    // Octal
    case 'o':
        count += display(itoa_base(va_arg(ap, unsigned), "01234567"));
        break;
    // Hexa
    case 'x':
        count += display(itoa_base(va_arg(ap, unsigned), "0123456789abcdef"));
        break;
    default:
        count++;
        putchar(c);
        putchar(type);
        break;
    }
    return count;
}

// Main function
int tinyprintf(const char *format, ...)
{
    va_list ap;
    va_start(ap, format); // Start va
    int count = 0; // Final count of the string
    int len = str_len(format);
    for (int i = 0; i < len; i++)
    {
        if (format[i] == '%')
        {
            i++;
            count += match('%', format[i], ap);
        }
        else
        {
            count++;
            putchar(format[i]);
        }
    }
    va_end(ap); // Close va
    return count;
}
