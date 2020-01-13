/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 18:33:45 by srouhe            #+#    #+#             */
/*   Updated: 2020/01/13 20:24:36 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		cursor_move(int x, int y)
{
	ft_putstr_fd(tgoto(CM, x, y + HEADER), 0);
	g_sel.x = x;
	g_sel.y = y;
}

void		action_bks(void)
{
	t_arg	*tmp;

	if (!g_sel.active)
		return ;
	tmp = *g_sel.active;
	if (tmp == g_sel.head)
		g_sel.head = tmp->next;
	g_sel.ac--;
	if (g_sel.ac)
	{
		g_sel.active = &tmp->next;
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
	}
	free_arg(&tmp);
	if (!g_sel.ac)
		exit_program(0, 1);
	tputs(CL, 1, printnbr);
}

void		action_arrow(long key)
{
	t_arg	*tmp;

	tmp = *g_sel.active;
	if (key == DOWN)
		g_sel.active = &tmp->next;
	else if (key == UP)
		g_sel.active = &tmp->prev;
	else
		jump_columns(key);
}

void		action_spc(void)
{
	t_arg	*tmp;

	tmp = *g_sel.active;
	tmp->toggle = tmp->toggle ? 0 : 1;
}

void		action_all(long key)
{
	int		i;
	int		toggle;
	t_arg	*tmp;

	i = 0;
	tmp = *g_sel.active;
	toggle = key == A_UP ? 1 : 0;
	while (i < g_sel.ac)
	{
		tmp->toggle = toggle;
		g_sel.active = &tmp->next;
		tmp = tmp->next;
		i++;
	}
}
