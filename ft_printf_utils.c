/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azamario <azamario@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 19:24:27 by azamario          #+#    #+#             */
/*   Updated: 2021/07/20 22:33:13 by azamario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar_len(char c, int *len)
{
	write(1, &c, 1);
	(*len)++;
}

int		ft_strchr(char *s, char c)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i++] == c)
			return (1);
	}
	return (0);
}

void		print_c(char c, int *len, t_flags fl)
{
	if (fl.minus == 0 && fl.width == 0)
	{
		ft_putchar_len(c, len);	
	}
	else if (fl.minus == 0 && fl. width > 0)
	{
		while (fl.width-- > 1)
		{
			write(1, " ", 1);
			len++;
		}
		ft_putchar_len(c, len);
	}
	else if (fl.minus == 1)
	{
		ft_putchar_len(c, len);
		while (fl.width-- > 1)
		{
			write(1, " ", 1);
			len++;
		}
	}
}
/*
void	print_s(char *c, int *len, t_flags fl)
{
	if (fl.minus == 0 && fl.width == 0 && fl.precision == 0)
		ft_putstr_len(c, len);
	if (fl.minus == 0 && fl.width > 0 && fl.precision == 0)
	{
		int num;

		num  = fl.width - (int)ft_strlen(c);
		while (num > 0)
		{
			write(1, " ", 1);
			num--, len++;
		}
		ft_putstr_len(c, len);		
	}
	if (fl.minus == 0 && fl.width == 0 && fl.precision > 0)
	{
		if (fl.precision >= (int)ft_strlen(c))
			ft_putstr_len(c, len);	
		else
		{
			while (fl.precision > 0)
			{
				write(1, &*c, 1);
				fl.precision--, len++, c++;			
			}
		}	
	}
	if (fl.minus == 0 && fl.width > 0 && fl.precision > 0)
	{

	}
}
*/

void	print_s(char *c, int *len, t_flags fl)
{
	int size;

	size = (int)ft_strlen(c);
	if (fl.precision < size && fl.width < size)
		while (fl.precision > 0)
		{
			write(1, &*c, 1);
			fl.precision--, len++, c++;				
		}
	if (fl.precision > size && fl.width > size )
		imprime a string
			if fl.minus == 0 imprime espaço antes
			else fl.minus == 1 imprime espaço depois
	if (fl.precision < size && fl.width > size)
		corta a string usando a precisão
			if fl.minus == 0 imprime espaço antes
			else fl.minus == 1 imprime espaço depois
	else
		ft_putstr_len(c, len); (8 casos)
}	


void 	print_i_d(t_flags fl, va_list args, int *len)
{
	fl.strNum = ft_itoa(va_arg(args, int));
	ft_putstr_len(fl.strNum, len);
}

void 	print_u(t_flags fl, va_list args, int *len)
{
	fl.strNum = ft_uitoa(va_arg(args, unsigned int));
	ft_putstr_len(fl.strNum, len);	
}

void	print_p(t_flags fl, va_list args, int *len)
{
	fl.strNum = ft_int_to_hex_pxX(va_arg(args, unsigned long int), fl);
	ft_putstr_len_p(fl.strNum, len);
}

void	print_x(t_flags fl, va_list args, int *len)
{
	fl.strNum = ft_int_to_hex_pxX(va_arg(args, unsigned long int), fl);
	ft_putstr_len(fl.strNum, len);
}

void	print_X(t_flags fl, va_list args, int *len)
{
	fl.strNum = ft_int_to_hex_pxX(va_arg(args, unsigned long int), fl);
	ft_putstr_len(fl.strNum, len);
}

void print_pct(int *len)
{
	ft_putstr_len("%", len);
}
void	ft_putstr_len_p(char *s, int *len)
{
	int i;

	write(1, "0x", 2);
	if (s != NULL)
	{
		i = 0;
		while (s[i])
			ft_putchar_len(s[i++], len);
	}
}

int		ft_len_hex(unsigned long int x)
{
	int len;
	
	len  = 0;
	while (x)
	{
		x = x / 16;
		len++;
	}
	return (len);
}

char	*ft_int_to_hex_pxX(unsigned long int n, t_flags fl)
{ 
	int len;
	char *result;
	int temp;

	len = ft_len_hex(n);
	result = (char *)malloc(len + 1);
	if (result == NULL)
		return (0);
	result[len--] = '\0';
	while (len >= 0)
	{
		temp = 0;
		temp = n % 16;
        if (temp < 10) 
            result[len--] = temp + 48;
        else 
		{
			if (fl.type == 'x' || fl.type == 'p')
            	result[len--] = temp + 87;
			else
				result[len--] = temp + 55;
		}
		n = n / 16;
    }
	return (result);	
}

//para imprimir integer:
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*(s++))
		i++;
	return (i);
}

void	ft_putstr(char *s)
{
	if (!s)
		return ;
	write(1, s, ft_strlen(s));
}

void	ft_putstr_len(char *s, int *len)
{
	int i;

	if (s != NULL)
	{
		i = 0;
		while (s[i])
			ft_putchar_len(s[i++], len);
	}
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	if (n == -2147483648)
		ft_putstr("-2147483648");
	if (n < 0 && n != -2147483648)
	{
		ft_putchar('-');
		n = n * -1;
	}
	if (n <= 9 && n >= 0)
		ft_putchar(n + 48);
	else if (n > 0)
	{
		ft_putnbr(n / 10);
		ft_putchar(n % 10 + 48);
	}
}

int	ft_len(int num)
{
	size_t	len;

	if (num <= 0)
		len = 1;
	else
		len = 0;
	while (num != 0)
	{
		num = num / 10;
		len++;
	}
	return (len);
}

int	ft_to_positive(int num)
{
	if (num < 0)
		return (-num);
	else
		return (num);
}

char	*ft_itoa(int n)
{
	int		sign;
	int		len;
	char	*result;

	if (n < 0)
		sign = -1;
	else
		sign = 1;
	len = ft_len(n);
	result = (char *)malloc(sizeof(char) * len + 1);
	if (result == NULL)
		return (0);
	result[len] = '\0';
	len--;
	while (len >= 0)
	{
		result[len] = '0' + ft_to_positive(n % 10);
		n = ft_to_positive(n / 10);
		len--;
	}
	if (sign == -1)
		result[0] = '-';
	return (result);
}

int	ft_ulen(unsigned int num)
{
	size_t	len;

	if (num <= 0)
		len = 1;
	else
		len = 0;
	while (num != 0)
	{
		num = num / 10;
		len++;
	}
	return (len);
}

char	*ft_uitoa(unsigned int n)
{
	int		len;
	char	*result;

	len = ft_ulen(n);
	result = (char *)malloc(sizeof(char) * len - 1);
	if (result == NULL)
		return (0);
	result[len] = '\0';
	len--;
	while (len >= 0)
	{
		result[len] = '0' + (n % 10);
		n = n / 10;
		len--;
	}
	return (result);
}

t_flags	ft_clean_flags(void)
{
	t_flags fl;

	fl.minus = 0;
	fl.zero = 0;
	fl.width = 0;
	fl.dot = 0;
	fl.precision = 0;
	return (fl);
}
