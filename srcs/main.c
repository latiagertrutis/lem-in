/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodrigu <mrodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 20:32:11 by mrodrigu          #+#    #+#             */
/*   Updated: 2018/06/20 16:12:46 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		main(int argc, char **argv)
{
	t_data	data;
	t_node	*node;
	t_map	*paths;

	data = (t_data){0, 0, 1, 0, NULL, NULL, (t_error){0, 0}};
	if (argc >= 2 && (data.fd = open(argv[1], O_RDONLY)) < 0)
		return (0);
	node = ft_reader(&data);
	int i;
	/* while (node) */
	/* { */
	/* 	ft_printf("id: %i | name: %s | links: ", node->id, node->name); */
	/* 	i = 0; */
	/* 	while (i < node->n_links) */
	/* 		printf("%s, ", (node->links[i++])->name); */
	/* 	printf("\n"); */
	/* 	node = node->next; */
	/* } */


//	ft_map_lector(NULL, node);
	ft_depure_graf(node);
	ft_printf("MAP DEPURED \n");
	ft_map_lector(NULL, node);
	paths = ft_search_paths(data.start);
	ft_printf("PATHS GENERATE \n");
	ft_map_lector(paths, NULL);
//	ft_putstr(data.start->name);
	return (0);
}
// para sdl
	/* if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) */
	/* 	ft_error((char *)SDL_GetError()); */
	/* if (!(win = SDL_CreateWindow("PUTA", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0))) */
	/* { */
	/* 	ft_putstr_fd(SDL_GetError(), 2); */
	/* 	SDL_Quit(); */
	/* 	return (0); */
	/* } */
	/* if (!(rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED))) */
	/* { */
	/* 	SDL_DestroyWindow(win); */
	/* 	SDL_Quit(); */
	/* 	return (0); */
	/* } */
	/* if (!(surf = IMG_Load("archerpng.png"))) */
	/* { */
	/* 	SDL_DestroyRenderer(rend); */
	/* 	SDL_DestroyWindow(win); */
	/* 	SDL_Quit(); */
	/* 	return (0); */
	/* } */
	/* if (!(tex = SDL_CreateTextureFromSurface(rend, surf))) */
	/* { */
	/* 	SDL_DestroyRenderer(rend); */
	/* 	SDL_DestroyWindow(win); */
	/* 	SDL_Quit(); */
	/* 	return (0); */
	/* } */
	/* SDL_FreeSurface(surf); */
	/* SDL_RenderClear(rend); */
	/* SDL_RenderCopy(rend, tex, NULL, NULL); */
	/* SDL_RenderPresent(rend); */
	/* SDL_RaiseWindow(win); */
	/* SDL_Delay(10000); */
	/* SDL_DestroyWindow(win); */
	/* SDL_Quit(); */
