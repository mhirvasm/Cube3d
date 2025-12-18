/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirvasm <mhirvasm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:23:35 by mhirvasm          #+#    #+#             */
/*   Updated: 2025/12/18 09:55:24 by mhirvasm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	int	minus_sign;
	int	result;

	minus_sign = 0;
	result = 0;
	while (((*nptr >= 9) && (*nptr <= 13)) || (*nptr == 32))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			minus_sign = 1;
		nptr++;
	}
	while ((*nptr >= '0') && (*nptr <= '9'))
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	if (*nptr != '\0')
		return (1);
	if (minus_sign != 0)
		result = -result;
	return (result);
}
