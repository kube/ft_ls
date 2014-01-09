/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeijoo <cfeijoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/09 20:36:45 by cfeijoo           #+#    #+#             */
/*   Updated: 2013/12/13 23:00:24 by cfeijoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	check_parameter(char *params, char param)
{
	if (params && ft_strchr(params, param))
		return (1);
	return (0);
}

static void	sort_file_list(t_list **file_list)
{
	(void)file_list;
}

static void	display_chmod(struct stat *file_stat)
{
	char	todisplay;

    todisplay = ((S_ISDIR(file_stat->st_mode)) ? 'd' : '-');
	ft_putchar(todisplay);
    todisplay = ((file_stat->st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar(todisplay);
    todisplay = ((file_stat->st_mode & S_IWUSR) ? 'w' : '-');
	ft_putchar(todisplay);
    todisplay = ((file_stat->st_mode & S_IXUSR) ? 'x' : '-');
	ft_putchar(todisplay);
    todisplay = ((file_stat->st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar(todisplay);
    todisplay = ((file_stat->st_mode & S_IWGRP) ? 'w' : '-');
	ft_putchar(todisplay);
    todisplay = ((file_stat->st_mode & S_IXGRP) ? 'x' : '-');
	ft_putchar(todisplay);
    todisplay = ((file_stat->st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar(todisplay);
    todisplay = ((file_stat->st_mode & S_IWOTH) ? 'w' : '-');
	ft_putchar(todisplay);
    todisplay = ((file_stat->st_mode & S_IXOTH) ? 'x' : '-');
	ft_putchar(todisplay);
	ft_putchar('\t');
}

static void	display_owner_name(struct stat *file_stat)
{
	ft_putstr(getpwuid(file_stat->st_uid)->pw_name);
	ft_putchar('\t');
}

static void display_group_name(struct stat *file_stat)
{
	ft_putstr(getgrgid(file_stat->st_gid)->gr_name);
	ft_putstr("\t");
}

static void	display_mtime(struct stat *file_stat)
{
	char	*todisplay;

	todisplay = ctime(&file_stat->st_mtime);
	todisplay = todisplay + 4;
	todisplay[12] = 0;
	ft_putstr(todisplay);
	ft_putstr("\t");
}

static void	display_file_stat(struct stat *file_stat)
{
	display_chmod(file_stat);
	ft_putlnbr((long int)file_stat->st_nlink);
	ft_putstr("\t");
	display_owner_name(file_stat);
	display_group_name(file_stat);
	ft_putnbr((int)file_stat->st_size);
	ft_putstr("\t");
	display_mtime(file_stat);
}

static void	display_file_list(t_list *file_list, int recursive, int long_format)
{
	t_file_item	*current;

	(void)recursive;
	while (file_list)
	{
		current = (t_file_item*)file_list->content;
		if (long_format)
			display_file_stat(current->stat);
		ft_putendl((char*)(current->name));
		file_list = file_list->next;
	}
}

static void	get_file_list(t_list **file_list, int hide_hidden, char *folder)
{
	t_file_item		*file_item;
	DIR				*dir;
	struct dirent	*entry;

	if (!(dir = opendir(folder)))
	{
		ft_putendl_fd("Error during opening folder.", 2);
		exit (1);
	}
	while ((entry = readdir(dir)) != NULL)
	{
		if (!hide_hidden || (entry->d_name)[0] != '.')
		{
			file_item = (t_file_item*)malloc(sizeof(t_file_item));
			file_item->name = ft_strdup((const char*)(entry->d_name));
			if (!stat((char*)file_item->name, file_item->stat))
			{
				ft_putstr_fd("Cannot access file ", 2);
				ft_putendl_fd(file_item->name, 2);
				exit(1);
			}
			ft_lstadd(file_list, ft_lstnew(file_item, sizeof(t_file_item)));
			// Check elements length
		}
	}
	closedir(dir);
}

int	ft_ls(char *params, char *folder)
{
	t_list	*file_list;

	file_list = NULL;
	get_file_list(&file_list, !check_parameter(params, 'a'), folder);
	sort_file_list(&file_list);
	if (check_parameter(params, 'r'))
		ft_lstrev(&file_list);
	display_file_list(file_list,
			check_parameter(params, 'R'),
			check_parameter(params, 'l'));
	return (0);
}
