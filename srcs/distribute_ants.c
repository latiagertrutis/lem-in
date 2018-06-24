/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribute_ants.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 18:22:38 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/06/25 00:11:20 by mrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static void show_matrix(double **matriz)
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			ft_printf("%f ", matriz[i][j]);
		}
		ft_printf("\n");
	}
	ft_printf("\n");
}

static int 	search_pivot(double **mat, int j, int fil)
{
	double max;
	int row;
	int i;

	max = ft_abs_double(mat[j][j]);
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
		ft_printf("ha cambiado\n");
		aux = mat[j];
		mat[j] = mat[aux_r];
		mat[aux_r] = aux;
	}
}

static void	normalize(double **mat, int j, int col)
{
	double piv;
	int i;

	piv = mat[j][j];
	i = j;
	while (i < col)
	{
		ft_printf("ha normalizado\n");
		mat[j][i] = mat[j][i] / piv;
		i++;
	}
}

static void	put_zeros(double **mat, int j, int col, int row)
{
	double factor;
	int i;
	int k;

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

int			distribute_ants(double **mat, int row, int col)
{
	int j;
	int aux_r;

	j = 0;
	while(j < 3)
	{
		show_matrix(mat);
		if ((aux_r = search_pivot(mat, j, row)) < 0)
			return (0);
		change_rows(mat, j, aux_r);
		normalize(mat, j, col);
		put_zeros(mat, j, col, row);
		j++;
	}
	return (1);
}
