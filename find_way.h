/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_way.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 18:06:04 by uhand             #+#    #+#             */
/*   Updated: 2019/08/19 16:02:13 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIND_WAY_H
# define FIND_WAY_H

# include "./parser.h"

# define CUR find->crnt_set
# define PRE find->crnt_set->prev

/*
** Way params: way
*/

typedef struct		s_way
{
	int				len_way;
	int				num_way;
	int				status;
	t_list			*rooms;
	struct s_way	*next;
}					t_way;

/*
** Way set params: set
*/

typedef struct			s_way_set
{
	int					steps;
	int					ways_cnt;
	t_list				*ways;
	struct s_way_set	*next;
	struct s_way_set	*prev;
}						t_way_set;

/*
** find_the_way params: find
*/

typedef struct	s_find_way
{
	t_way_set		*sets;  // сurrent set
	t_way_set		*crnt_set;  // сurrent set
	t_way_set		*answer;
	t_way			*ways;
	int 			way_nbr;
	t_list_rooms	*start;
}				t_find_way;

int 	find_the_way(t_intldta *indta);
int		rec_finding(t_intldta *indta, t_find_way *fnd_wy);
int		wide_search(t_find_way *fnd_wy, t_intldta *indta);

#endif
