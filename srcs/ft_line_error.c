/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 05:43:50 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/07/07 19:22:25 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static void		ft_putnbr_error(int i)
{
	if (i == -2147483648)
	{
		ft_putnbr_error(-214748364);
		ft_putnbr_error(8);
		return ;
	}
	if (i < 0)
	{
		ft_putchar_fd('-', 2);
		i = i * (-1);
	}
	if (i < 10)
		ft_putchar_fd(i + 48, 2);
	else
	{
		ft_putnbr_error(i / 10);
		ft_putnbr_error(i % 10);
	}
}

void			ft_line_error(int n, char *err)
{
	ft_putstr("\033[H\033[J");
	if (!err)
		perror(err);
	else
	{
		if (n >= 0)
		{
			ft_putstr_fd("\e[38;5;196mError \e[38;5;37m[line ", 2);
			ft_putnbr_error(n);
			ft_putstr_fd("]", 2);
		}
		else
			ft_putstr_fd("\e[38;5;196mError \e[38;5;37m", 2);
		ft_putstr_fd("\e[0m => \e[38;5;214m", 2);
		ft_putstr_fd(err, 2);
		ft_putstr_fd("\e[0m\n", 2);
	}
	exit(1);
}
