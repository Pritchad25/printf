#include "main.h"

/*************************PRINT A PERCENT SIGN**************/
/**
 * print_percent - this function prints a percent sign
 * @width: get the width
 * @precision: the precision specification
 * @size: the size specifier
 * @types: a list of the arguments
 * @buffer: the buffer array to handle print
 * @flags: calculates active flags
 * Return: the number of chars printed
 */
int print_percent(va_list types, char buffer[], int flags,
		int size, int width, int precision)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}
/******************PRINTS AN INT*************************/
/**
 * print_int - this function prints int
 * @width: get the width
 * @precision: the precision specification
 * @size: the size specifier
 * @types: a list of the arguments
 * @buffer: the buffer array to handle print
 * @flags: calculates active flags
 * Return: the number of chars printed
 */
int print_int(va_list types, char buffer[], int flags,
		int size, int width, int precision)
{
	int isNumNegative = 0;
	long int longn = va_arg(types, long int);
	int s = BUFF_SIZE - 2;
	unsigned long int num;

	longn = convert_size_number(longn, size);
	if (longn == 0)
		buffer[s--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)longn;
	if (longn < 0)
	{
		num = (unsigned long int)((-1) * longn);
		isNumNegative = 1;
	}

	while (num > 0)
	{
		buffer[s--] = (num % 10) + '0';
		num /= 10;
	}
	s++;

	return (write_number(isNumNegative, s, buffer, flags,
				width, precision, size));
}

/****************PRINT A STRING***********/
/**
 * print_string - this function prints a string
 * @width: get width
 * @precision: the precision specification
 * @size: the size specifier
 * @types: this is a list of arguments
 * @buffer: the buffer array to handle print
 * @flags: calculates active flags
 * Return: the number of chars printed
 */
int print_string(va_list types, char buffer[], int flags,
		int size, int width, int precision)
{
	char *str = va_arg(types, char *);
	int f, len = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "     ";
	}
	while (str[len] != '\0')
		len++;

	if (precision >= 0 && precision < len)
		len = precision;

	if (width > len)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], len);
			for (f = width - len; f > 0; f--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (f = width - len; f > 0; f--)
				write(1, " ", 1);
			write(1, &str[0], len);
			return (width);
		}
	}
	return (write(1, str, len));
}

/********************PRINTS A CHAR************************/
/**
 * prints_char - this function prints a char(character).
 * @width: the width
 * @precision: the precision specification
 * @size: the size specifier
 * @types: this is a list of arguments
 * @buffer: the buffer array to handle print
 * @flags: calculate active flags
 *
 *
 * Return: number of chars printed
 */
int print_char(va_list types, char buffer[], int flags,
		int size, int width, int precision)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}

/*************PRINT A BINARY ***********************/
/**
 * print_binary - this function prints an unsigned number
 * @width: get the width
 * @precision: the precision specfication
 * @size: the size specifier
 * @types: a list of arguments
 * @buffer: the buffer array to handle print
 * @flags: calculates active flags
 *
 *
 * Return: the number of char printed
 */
int print_binary(va_list types, char buffer[], int flags,
		int size, int width, int precision)
{
	int count;
	unsigned int j, e, index, sum;
	unsigned int a[32];

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	j = va_arg(types, unsigned int);
	e = 2147483648; /* (2 ^ 31) */
	a[0] = j / e;
	for (index = 1; index < 32; index++)
	{
		e /= 2;
		a[index] = (j / e) % 2;
	}
	for (index = 0, sum = 0, count = 0; index < 32; index++)
	{
		sum += a[index];
		if (sum || index == 31)
		{
			char z = '0' + a[index];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}

