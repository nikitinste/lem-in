/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rec_finding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 12:59:54 by uhand             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/08/27 18:10:48 by uhand            ###   ########.fr       */
=======
/*   Updated: 2019/08/27 17:23:36 by dfrost-a         ###   ########.fr       */
>>>>>>> 2a1ba4a1a542d4a4b15cc1ecb4d6362fa03fdbc7
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	check_free_rooms(t_list_rooms *start)
{
	t_list			*ptr;
	t_list_links	*link;
	t_list_rooms	*room;

	room = start;
	if (!start->act_lnks)
		return (0);
	ptr = start->links;
	while (ptr)
	{
		link = (t_list_links*)ptr->content;
		if (link->rm1 != start)
			room = link->rm1;
		else
			room = link->rm2;
		if (room->way_nbr < 0)
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

static void	count_set_steps(t_intldta *indta, t_way_set *set)
{
	t_count_steps	c;

	c.ptr = set->ways;
	c.pre_lems = 0;
	c.max_len = 0;
	while (c.ptr)
	{
		c.way = (t_way**)c.ptr->content;
		c.pre_lems += (*c.way)->len_way - 1;
		if (c.max_len < (*c.way)->len_way)
			c.max_len = (*c.way)->len_way;
		c.ptr = c.ptr->next;
	}
	if (c.pre_lems > indta->num_ants)
		set->full_steps = 0;
	else
	{
		c.steps =(indta->num_ants - c.pre_lems) / set->ways_cnt;
		if (c.steps > (int)c.steps)
			c.steps++;
		set->full_steps = (int)c.steps;
	}
	set->steps = set->full_steps + c.max_len - 1;
}

static void	add_new_set(t_find_way *find, t_intldta *indta, int ways_cnt)
{
	t_way_set	*set;
	t_way		*ptr;
	t_way		**showme;

	if (!(set = (t_way_set*)malloc(sizeof(t_way_set))))
		ft_malloc_error();
	set->ways = NULL;
	set->next = NULL;
	set->ways_cnt = ways_cnt;
	ptr = find->ways;
	while (ptr)
	{
		if (ptr->status)
<<<<<<< HEAD
			if (!ft_lstaddnext(&set->ways, (void*)&ptr, sizeof(ptr)))
=======
//		{
//			if (set->ways == NULL)
//				set->ways = ft_lstnew_addr((void *)ptr, sizeof(ptr));
//			else
//			{
//				while (set->ways->next != NULL)
//					set = set->next;
//				set->next = ft_lstnew_addr((void *)ptr, sizeof(ptr));
//			}
//		}
			if (!ft_lstaddnext(&set->ways, (void *)&ptr, sizeof(ptr)))
>>>>>>> 2a1ba4a1a542d4a4b15cc1ecb4d6362fa03fdbc7
				ft_malloc_error();
		showme = (t_way **)set->ways->content;
		ptr = ptr->next;
	}
	count_set_steps(indta, set);
	if (!CUR)
		set->prev = NULL;
	else
	{
		set->prev = CUR;
		CUR->next = set;
	}
	CUR = set;
	if (!find->sets)
		find->sets = find->crnt_set;
}

static int	check_set_load(t_find_way *find, t_intldta *indta)
{
	t_way	*ptr;
	int		counter;

	ptr = find->ways;
	counter = 0;
	while (ptr)
	{
		if (ptr->status)
			counter++;
		ptr = ptr->next;
	}
	if ((!CUR && counter) || (CUR && counter > CUR->ways_cnt))
	{
		add_new_set(find, indta, counter);
		return (1);
	}
	return (0);
}

int			rec_finding(t_intldta *indta, t_find_way *find)
{
	if (find->crnt_set && (find->crnt_set->ways_cnt == indta->num_ants || \
		CUR->full_steps == 0 || (PRE && CUR->steps > PRE->steps) || \
		!check_free_links(indta->start_room)))
		return (1);
	if (wide_search(&find, &indta))
	{
		if (!check_set_load(find, indta))
			return (rec_finding(indta, find));
	}
	return (0);
}
