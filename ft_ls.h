/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeijoo <cfeijoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/10 19:11:57 by cfeijoo           #+#    #+#             */
/*   Updated: 2013/12/13 23:07:43 by cfeijoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include <libft.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <pwd.h>
# include <time.h>
# define ACCEPTED_PARAMS "Radfglrtu"

# include <stdio.h>
int	ft_ls(char *params, char *folder);
typedef struct			s_file_item
{
	char				*name;
	struct stat			*stat;
}						t_file_item;
typedef struct			s_format_max_sizes
{
	unsigned int		extra_column;
	unsigned int		group_name;
	unsigned int		owner_name;
	unsigned int		size;
	unsigned int		links;
}						t_format_max_sizes;
#endif
