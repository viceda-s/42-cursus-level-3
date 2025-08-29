/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:41:01 by viceda-s          #+#    #+#             */
/*   Updated: 2025/06/26 09:24:34 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static int	check_format(char specifier, va_list args)
{
	if (specifier == 'c')
		return (ft_print_char(va_arg(args, int)));
	if (specifier == 's')
		return (ft_print_str(va_arg(args, char *)));
	if (specifier == 'p')
		return (ft_print_pointer(va_arg(args, void *)));
	if (specifier == 'd' || specifier == 'i')
		return (ft_print_num(va_arg(args, int)));
	if (specifier == 'u')
		return (ft_print_unsigned(va_arg(args, unsigned int)));
	if (specifier == 'x')
		return (ft_print_hex(va_arg(args, unsigned int), 0));
	if (specifier == 'X')
		return (ft_print_hex(va_arg(args, unsigned int), 1));
	if (specifier == '%')
		return (ft_print_percent());
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		print_len;

	i = 0;
	print_len = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			print_len += check_format(format[i], args);
		}
		else
			print_len += ft_print_char(format[i]);
		i++;
	}
	va_end(args);
	return (print_len);
}
