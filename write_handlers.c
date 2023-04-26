#include "main.h"

/*******************WRITE HANDLERS*******************/
/**
 * handle_write_char - this function prints a string
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 * @c: char types.
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags.
 *
 *
 * Return: Number of chars printed.
 */
int handle_write_char(char c, char buffer[],
		int flags, int size, int width, int precision)
{ /* char is stored at left and padded at buffer's right */
	char padd = ' ';
	int x = 0;

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
	{
		padd = '0';
	}

	buffer[x++] = c;
	buffer[x] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (x = 0; x < width - 1; x++)
			buffer[BUFF_SIZE - x - 2] = padd;
		if (flags & F_MINUS)
		{
			return (write(1, &buffer[0], 1) + write(1,
						&buffer[BUFF_SIZE - x - 1], width - 1));
		}
		else
		{
			return (write(1, &buffer[BUFF_SIZE - x - 1], width - 1) +
					write(1, &buffer[0], 1));
		}
	}

	return (write(1, &buffer[0], 1));
}

/****************WRITE NUMBER*****************/
/**
 * write_number - the function prints a string
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 * @is_negative: Lista of arguments
 * @ind: char types.
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 *
 * Return: Number of chars printed.
 */
int write_number(int is_negative, int ind, char buffer[],
		int flags, int precision, int size, int width)
{
	int len = BUFF_SIZE - ind - 1;
	char extra_ch = 0, padd = ' ';

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
	{
		padd = '0';
	}
	if (is_negative)
	{
		extra_ch = '-';
	}
	else if (flags & F_PLUS)
	{
		extra_ch = '+';
	}
	else if (flags & F_SPACE)
	{
		extra_ch = ' ';
	}

	return (write_num(ind, buffer, flags, width, precision,
				len, padd, extra_ch));
}

/**
 * write_num - this function writes a number using a buffer
 * @prec: Precision specifier
 * @length: Number length
 * @padd: Padding char
 * @extra_c: Extra char
 * @ind: Index at which the number starts on the buffer
 * @buffer: Buffer
 * @flags: Flags
 * @width: width
 *
 * Return: Number of printed chars.
 */
int write_num(int ind, char buffer[], int flags, int length, int prec,
		int width, char extra_c, char padd)
{
	int padd_start = 1, v;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' '; /* width is displayed with padding ' ' */
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (v = 1; v < width - length + 1; v++)
			buffer[v] = padd;
		buffer[v] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Assign extra char to left of buffer */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], v - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buff */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], v - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			return (write(1, &buffer[padd_start], v - padd_start) +
					write(1, &buffer[ind], length - (1 - padd_start)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - this function writes an unsigned number
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * @is_negative: Number indicating if the num is negative
 * @ind: Index at which the number starts in the buffer
 * @buffer: Array of chars
 * @flags: Flags specifiers
 *
 * Return: Number of written chars.
 */
int write_unsgnd(int is_negative, int ind, char buffer[], int flags, int width,
		int precision, int size)
{
	/* The number is stored at the bufer's right and starts at position i */
	int length = BUFF_SIZE - ind - 1, i = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (precision > 0 && precision < length)
		padd = ' ';

	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';

	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			buffer[i] = padd;

		buffer[i] = '\0';

		if (flags & F_MINUS) /* Assign extra char to left of buffer [buffer>padd]*/
		{
			return (write(1, &buffer[ind], length) + write(1, &buffer[0], i));
		}
		else /* Assign extra char to left of padding [padd>buffer]*/
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[ind], length));
		}
	}

	return (write(1, &buffer[ind], length));
}

/**
 * write_pointer - this function writes a memory address
 * @buffer: Arrays of chars
 * @ind: Index at which the number starts in the buffer
 * @length: Length of number
 * @width: Width specifier
 * @flags: Flags specifier
 * @padd: Char representing the padding
 * @extra_c: Char representing extra char
 * @padd_start: Index at which padding should start
 *
 *
 * Return: Number of written chars.
 */
int write_pointer(char buffer[], int ind, int length,
		int width, int flags, char padd, char extra_c, int padd_start)
{
	int z;

	if (width > length)
	{
		for (z = 3; z < width - length + 3; z++)
			buffer[z] = padd;
		buffer[z] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Assign extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], z - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], z - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], z - padd_start) +
					write(1, &buffer[ind],
						length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
