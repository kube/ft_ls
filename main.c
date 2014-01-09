/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeijoo <cfeijoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/12 23:43:56 by cfeijoo           #+#    #+#             */
/*   Updated: 2013/12/13 04:17:13 by cfeijoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void print_usage(int fd)
{
	ft_putstr_fd("usage: ft_ls [-", fd);
	ft_putstr_fd(ACCEPTED_PARAMS, fd);
	ft_putendl_fd("] [file ...]", fd);
}

static void	print_illegal_option(char chr)
{
	ft_putstr_fd("ft_ls: illegal option -- ", 2);
	write(2, &chr, 1);
	ft_putendl_fd("", 2);
	print_usage(2);
	exit(1);
}

static int	get_search(int argc, char **argv, char ***search_ret)
{
	int		i;
	int		j;
	char	**search;

	i = 1;
	while (i < argc && argv[i][0] == '-' && argv[i][1])
		i++;
	if (argc - i)
	{
		search = (char**)malloc((argc - i + 1) * sizeof(char*));
		j = i;
		while (j < argc)
		{
			search[j - i] = argv[j];
			j++;
		}
		search[j - 1] = NULL;
		*search_ret = search;
		return (j - 1);
	}
	else
		return (0);
}

static char	*get_parameters(int argc, char **argv)
{
	int		i;
	int		j;
	int		k;
	char	*read_parameters;

	k = 0;
	i = 1;
	read_parameters = ft_strnew(ft_strlen(ACCEPTED_PARAMS));
	while (i < argc && argv[i][0] == '-' && argv[i][1])
	{
		j = 1;
		while (argv[i][j])
		{
			if (ft_strchr(ACCEPTED_PARAMS, argv[i][j]))
			{
				if (!ft_strchr(read_parameters, argv[i][j]))
					read_parameters[k++] = argv[i][j];
			}
			else
				print_illegal_option(argv[i][j]);
			j++;
		}
		i++;
	}
	return (read_parameters);
}

static void	list_folder(char *params, char **search, int searchlen)
{
	while (search && *search)
	{
		if (searchlen > 1)
		{
			ft_putstr(*search);
			ft_putendl(":");
		}
		// Stat() search to know if file or folder, and exists.
		ft_ls(params, *search);
		if (*(search + 1) && searchlen > 1)
			ft_putendl("");
		search++;
	}
}

int	main(int argc, char **argv)
{
	int		searchlen;
	char	**search;
	char	*params;

	searchlen = 0;
	search = NULL;
	params = NULL;
	if (argc > 1)
	{
		params = get_parameters(argc, argv);
		searchlen = get_search(argc, argv, &search);
	}
	if (search)
		list_folder(params, search, searchlen);
	else
		ft_ls(params, ".");
	return (0);
}
