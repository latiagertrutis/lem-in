/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solve_system.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 14:01:59 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/06/26 18:45:07 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	search_pivot(double **mat, int j, int fil)
{
	double	max;
	int		row;
	int		i;

	max = ft_abs_double(mat[j][j]);
	row = 0;
	i = j + 1;
	while (i < fil)
	{
		if (max < ft_abs_double(mat[i][j]))
		{
			max = ft_abs_double(mat[i][j]);
			row = i;
		}
		i++;
	}
	if (!max)
		return (-1);
	return (row);
}

static void	change_rows(double **mat, int j, int aux_r)
{
	double *aux;

	if (aux_r != j)
	{
		aux = mat[j];
		mat[j] = mat[aux_r];
		mat[aux_r] = aux;
	}
}

static void	normalize(double **mat, int j, int col)
{
	double	piv;
	int		i;

	piv = mat[j][j];
	i = j;
	while (i < col)
	{
		mat[j][i] = mat[j][i] / piv;
		i++;
	}
}

static void	put_zeros(double **mat, int j, int col, int row)
{
	double	factor;
	int		i;
	int		k;

	i = 0;
	while (i < row)
	{
		if (i != j)
		{
			factor = mat[i][j];
			k = j;
			while (k < col)
			{
				mat[i][k] = mat[i][k] - (factor * mat[j][k]);
				k++;
			}
		}
		i++;
	}
}

int			ft_solve_system(double **mat, int row, int col)
{
	int j;
	int aux_r;

	j = 0;
	while (j < row - 1)
	{
		if ((aux_r = search_pivot(mat, j, row)) < 0)
			return (0);
		change_rows(mat, j, aux_r);
		normalize(mat, j, col);
		put_zeros(mat, j, col, row);
		j++;
	}
	return (1);
}
