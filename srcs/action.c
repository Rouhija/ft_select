/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 18:33:45 by srouhe            #+#    #+#             */
/*   Updated: 2020/01/14 17:01:57 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void		cursor_move(int x, int y)
{
	ft_putstr_fd(tgoto(CM, x, y + HEADER), 0);
	g_sel.x = x;
	g_sel.y = y;
}

void		action_bks(void)
{
	t_arg	*prev;
	t_arg	*next;
	t_arg	*tmp;

	prev = g_sel.active->prev;
	next = g_sel.active->next;
	tmp = g_sel.active;
	if (tmp == g_sel.head)
		g_sel.head = next;
	free_arg(&tmp);
	g_sel.ac--;
	if (g_sel.ac)
	{
		g_sel.active = next;
		prev->next = next;
		next->prev = prev;
	}
	else
		exit_program(0, 1);
	tputs(CL, 1, printnbr);
}

void		action_arrow(long key)
{
	if (key == DOWN)
		g_sel.active = g_sel.active->next;
	else if (key == UP)
		g_sel.active = g_sel.active->prev;
	else
		jump_columns(key);
}

void		action_spc(void)
{
	g_sel.active->toggle = g_sel.active->toggle ? 0 : 1;
	g_sel.active = g_sel.active->next;
}

void		action_all(long key)
{
	int	i;
	int	toggle;

	i = 0;
	toggle = key == A_UP ? 1 : 0;
	while (i < g_sel.ac)
	{
		g_sel.active->toggle = toggle;
		g_sel.active = g_sel.active->next;
		i++;
	}
}
