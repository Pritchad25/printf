#include "main.h"

/*********PRINT UNSIGNED NUMBER****************/
/**
 * print_unsigned - this functions prints an unsigned number.
 * @width: get the width
 * @precision: the precision specification
 * @size: the size specifier
 * @types: the list of arguments
 * @buffer: the buffer array to handle print
 * @flags: calculates active flags
 * Return: number of chars printed
 */
int print_unsigned(va_list types, char buffer[], int flags,
		int width, int size, int precision)
{
	unsigned long int digit = va_arg(types, unsigned long int);
	int x = BUFF_SIZE - 2;

	digit = convert_size_unsgnd(digit, size);

	if (digit == 0)
	{
		buffer[x--] = '0';
	}
	buffer[BUFF_SIZE - 1] = '\0';
	while (digit > 0)
	{
		buffer[x--] = (digit % 10) + '0';
		digit /= 10;
	}
	x++;

	return (write_unsgnd(0, x, buffer, flags, width, precision, size));
}

/*****************PRINT UNSIGNED NUMBER IN OCTAL***********/
/**
 * print_octal - prints an unsigned number in octal
 * @width: get the width
 * @precision: the precision specification
 * @size: the size specifier
 * @types: the list of arguments
 * @buffer: the buffer array to handle print
 * @flags: calculates active flags
 * Return: the unsigned number in octal
 */
int print_octal(va_list types, char buffer[], int flags, int size,
		int precision, int width)
{
	unsigned long int num = va_arg(types, unsigned long int);
	int b = BUFF_SIZE - 2;
	unsigned long int init_num = num;

	UNUSED(width);
	num = convert_size_unsgnd(num, size);

	if (num == 0)
	{
		buffer[b--] = '0';
	}
	buffer[BUFF_SIZE - 1] = '\0';
	while (num > 0)
	{
		buffer[b--] = (num % 8) + '0';
		num /= 8;
	}
	if (flags & F_HASH && init_num != 0)
	{
		buffer[b--] = '0';
	}
	b++;

	return (write_unsgnd(0, b, buffer, flags, width, precision, size));
}

/************PRINT UNSIGNED NUMBER IN HEXADECIMAL**********/
/**
 * print_hexadecimal - the function prints an unsigned number in hexadecimal
 * @width: get the width
 * @precision: the precision specification
 * @size: the size specifier
 * @types: the list of arguments
 * @buffer: the buffer array to handle print
 * @flags: calculates active flags
 * Return: the unsigned number in hexadecimal
 */
int print_hexadecimal(va_list types, char buffer[], int flags,
		int precision, int size, int width)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
				flags, 'X', width, precision, size));
}

/****************PRINT HEXADECIMAL NUMBER IN LOWER OR UPPER**********/
/**
 * print_hexa - the function prints a hexadecimal number in lower or upper
 * @flag_ch: calculates active flags
 * @width: get width
 * @precision: the precision specification
 * @size: the size specifier
 * @types: this is a list of arguments
 * @map_to: the array of values to map the number to
 * @buffer: the buffer array to handle print
 * @flags: calculates active flags
 * Return: the hexadecimal number in lower or upper
 */
int print_hexa(va_list types, char map_to[], char buffer[],
		int flags, char flag_ch, int size, int width, int precision)
{
	unsigned long int num = va_arg(types, unsigned long int);
	int a = BUFF_SIZE - 2;
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);
	if (num == 0)
		buffer[a--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[a--] = map_to[num % 16];
		num /= 16;
	}
	if (flags & F_HASH && init_num != 0)
	{
		buffer[a--] = flag_ch;
		buffer[a--] = '0';
	}
	a++;

	return (write_unsgnd(0, a, buffer, flags, width, precision, size));
}
