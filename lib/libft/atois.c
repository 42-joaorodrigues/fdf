/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 14:35:53 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/01 17:25:08 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_is_base_char(char c, int base)
{
	if (base <= 10)
		return (c >= '0' && c < '0' + base);
	return ((c >= '0' && c <= '9')
		|| (c >= 'A' && c < 'A' + base - 10)
		|| (c >= 'a' && c < 'a' + base - 10));
}

static int	ft_value_of(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	else if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	return (0);
}

int	ft_atoi_base(const char *str, int base)
{
	int		sign;
	long	result;

	if (!str || base < 2 || base > 16)
		return (0);
	while ((*str == ' ' || *str == '\n' || *str == '\t'
			|| *str == '\v' || *str == '\f' || *str == '\r'))
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	if (base == 16 && str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
		str += 2;
	result = 0;
	while (ft_is_base_char(*str, base))
	{
		result = result * base + ft_value_of(*str);
		str++;
	}
	return ((int)(result * sign));
}

int	ft_atoi(const char *nptr)
{
	int	result;
	int	sign;

	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	sign = 1;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	result = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	return (result * sign);
}
