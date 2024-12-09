#include "fractol.h"

double power_of_ten(int decimals)
{
    double  result;
    int     i;

    i = -1;
    result = 1.0;
    while (++i < decimals)
        result *= 10.0;
    return result;
}

double ft_atod(const char *str)
{
    const char  *point = ft_strchr(str, '.');
    int         left;
    int         decimals;
    int         right;
    double      fraction;

    if (!point)
        return ((double)ft_atoi(str));
    left = ft_atoi(str);
    right = ft_atoi(point + 1);
    decimals = ft_strlen(point + 1);
    fraction = right / power_of_ten(decimals);
    if (left < 0)
        return (left - fraction);
    return (left + fraction);
}
