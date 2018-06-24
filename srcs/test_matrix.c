/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 20:24:27 by jagarcia          #+#    #+#             */
/*   Updated: 2018/06/24 20:51:54 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int	main(void)
{
	//double matriz[3][3] = {{1, 1, -3}, {2, (1/2), -11}, {1, -2, 3}};
	double **matriz = (double **)malloc((sizeof(double *) * 3));
	matriz[0] = (double *)malloc(sizeof(double) * 3);
	matriz[1] = (double *)malloc(sizeof(double) * 3);
	matriz[2] = (double *)malloc(sizeof(double) * 3);

	matriz[0][0] = 1;
	matriz[0][1] = 1;
	matriz[0][2] = -3;
	matriz[1][0] = 2;
	matriz[1][1] = -0.5;
	matriz[1][2] = -11;
	matriz[2][0] = 1;
	matriz[2][1] = -2;
	matriz[2][2] = 3;

	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			ft_printf("%f ", (matriz)[i][j]);
		}
		ft_printf("\n");
	}
	ft_printf("\n");
	distribute_ants((double **)matriz, 3 ,3);
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			ft_printf("%f ", matriz[i][j]);
		}
		ft_printf("\n");
	}
}
