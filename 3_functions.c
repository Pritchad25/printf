#include "main.h"

/*************PRINT POINTER********/
/**
 * print_pointer - this function prints the value of a pointer variable.
 * @width: get the width
 * @precision: the precision specification
 * @size: the size specifier
 * @types: the list of arguments
 * @buffer: the buffer array to handle print
 * @flags: calculates active flags
 * Return: the number of chars printed
 */
int print_pointer(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);
	char xtra_c = 0, padding = ' ';
	unsigned long digit_addrs;
	int ind = BUFF_SIZE - 2, len = 2, padd_start = 1; /*where len = 2, for '0x' */

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));
	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);
	digit_addrs = (unsigned long)addrs;

	while (digit_addrs > 0)
	{
		buffer[ind--] = map_to[digit_addrs % 16];
		digit_addrs /= 16;
		len++;
	}
	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padding = '0';
	if (flags & F_PLUS)
		xtra_c = '+', len++;
	else if (flags & F_SPACE)
		xtra_c = ' ', len++;
	ind++;

	/* return (write(1, &buffer[i], BUFF_SIZE - i - 1)); */

	return (write_pointer(buffer, ind, len, width,
				flags, padding, xtra_c, padd_start));
}

/***************PRINT A NON PRINTABLE************/
/**
 * print_non_printable - this function prints ASCII codes in hexadecimal
 * of non printable chars(characters)
 * @width: get width
 * @precision: the precision specification
 * @size: the size specifier
 * @types: the list of arguments
 * @buffer: the buffer array to handle print
 * @flags: calculates active flags
 * Return: the non printable chars.The number of chars printed
 */
int print_non_printable(va_list types, char buffer[], int flags,
		int size, int width, int precision)
{
	char *str = va_arg(types, char *);
	int offset = 0, index = 0;

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
	{
		return (write(1, "(null)", 6));
	}
	while (str[index] != '\0')
	{
		if (is_printable(str[index]))
		{
			buffer[index + offset] = str[index];
		}
		else
		{
			offset += append_hexa_code(str[index], buffer, index + offset);
		}
		index++;
	}
	buffer[index + offset] = '\0';

	return (write(1, buffer, index + offset));
}

/***********PRINT REVERSE********/
/**
 * print_reverse - this function prints a reverse string.
 * @width: get the width
 * @precision: the precision specification
 * @size: the size specifier
 * @types: the list of arguments
 * @buffer: the buffer array to handle print
 * @flags: calculates active flags
 * Return: the number of chars printed
 */
int print_reverse(va_list types, char buffer[], int flags,
		int precision, int size, int width)
{
	int counter = 0, n;
	char *str;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);
	if (str == NULL)
	{
		UNUSED(precision);
		str = "(NULL)";
	}

	for (n = 0; str[n]; n++)
		;

	for (n = n - 1; n >= 0; n--)
	{
		char z = str[n];

		write(1, &z, 1);
		counter++;
	}

	return (counter);
}

/**************PRINT A STRING IN ROT 13**********/
/**
 * print_rot13string - this function prints a string in rot13
 * @width: get width
 * @precision: the precision specification
 * @size: the size specifier
 * @types: the list of arguments
 * @buffer: the buffer array to handle print
 * @flags: calculates active flags
 * Return: the number of chars(characters) printed
 */
int print_rot13string(va_list types, char buffer[], int flags,
		int precision, int width, int size)
{
	char *str;
	int count = 0;
	char t;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";
	unsigned int j, i;

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
	{
		str = "(AHYY)";
	}
	for (i = 0; str[i]; i++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[i])
			{
				t = out[j];
				write(1, &t, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			t = str[i];
			write(1, &t, 1);
			count++;
		}
	}

	return (count);
}
