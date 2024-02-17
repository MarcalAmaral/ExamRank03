#include <stdarg.h>
#include <unistd.h>

void    ft_putstr(char *string, int *lenght)
{
    if (!string)
        string = "(null)";
    while (*string)
        *lenght += write(1, string++, 1);
}

void    ft_putdigit(int num, int base, int *lenght)
{
    char *hexadecimal = "0123456789abcdef";

    if (num < 0)
    {
        num *= -1;
        *lenght += write(1, "-", 1);
    }
    if (num >= base)
        ft_putdigit((num / base), base, lenght);
    *lenght += write(1, &hexadecimal[num % base], 1);
}

int ft_printf(const char *format, ...)
{
    int     lenght;
    va_list list;

    va_start(list, format);
    lenght = 0;

    while (*format)
    {
        if ((*format == '%') && ((*(format + 1) == 's') || (*(format + 1) == 'd') || (*(format + 1) == 'x')))
        {
            format++;
            if (*format == 's')
                ft_putstr(va_arg(list, char *), &lenght);
            else if (*format == 'd')
                ft_putdigit((long int) va_arg(list, int), 10, &lenght);
            else if (*format == 'x')
                ft_putdigit((long int) va_arg(list, unsigned int), 16, &lenght);
        }
        else
            lenght += write(1, format, 1);
        format++;
    }
    return (lenght);
}

int main(void)
{
    ft_printf("%d\n", ft_printf("Hello World! %d %x %s %s\n", 2024, 2024, "Hello World!", NULL));
    return (0);
}