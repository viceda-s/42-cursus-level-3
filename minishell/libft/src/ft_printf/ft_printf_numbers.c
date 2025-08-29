/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_numbers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:50:24 by viceda-s          #+#    #+#             */
/*   Updated: 2025/06/26 09:23:01 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_print_num(int num)
{
	int	len;

	len = 0;
	if (num == -2147483648)
		return (ft_print_str("-2147483648"));
	if (num < 0)
	{
		len += ft_print_char('-');
		num = -num;
	}
	if (num >= 10)
		len += ft_print_num(num / 10);
	len += ft_print_char((num % 10) + '0');
	return (len);
}

int	ft_print_unsigned(unsigned int num)
{
	int		len;

	len = 0;
	if (num >= 10)
		len += ft_print_unsigned(num / 10);
	len += ft_print_char((num % 10) + '0');
	return (len);
}

int	ft_print_hex(unsigned int num, int uppercase)
{
	int		len;
	char	*hex;

	len = 0;
	if (uppercase)
		hex = "0123456789ABCDEF";
	else
		hex = "0123456789abcdef";
	if (num >= 16)
		len += ft_print_hex(num / 16, uppercase);
	len += ft_print_char(hex[num % 16]);
	return (len);
}

static int	ft_print_hex_ulong(unsigned long num)
{
	int		len;

	len = 0;
	if (num >= 16)
		len += ft_print_hex_ulong(num / 16);
	len += ft_print_char("0123456789abcdef"[num % 16]);
	return (len);
}

int	ft_print_pointer(void *ptr)
{
	int				len;
	unsigned long	num;

	if (!ptr)
		return (ft_print_str("(nil)"));
	len = 0;
	num = (unsigned long)ptr;
	len += ft_print_str("0x");
	len += ft_print_hex_ulong(num);
	return (len);
}
