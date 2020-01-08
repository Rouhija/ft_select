/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 12:02:09 by srouhe            #+#    #+#             */
/*   Updated: 2020/01/08 10:32:49 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		printnbr(int nbr)
{
	return (write(2, &nbr, 1));
}

void	column_count(void)
{
	int				limit;
	int				cols;
	struct winsize	w;

	limit = COLUMN_W;
	ioctl(1, TIOCGSIZE, &w);
	while (g_sel.max_w >= limit)
		limit += COLUMN_W;
	g_sel.pad = limit;
	g_sel.cols = w.ws_col / limit;
	g_sel.rows = g_sel.ac > g_sel.cols ? g_sel.ac / g_sel.cols : 0;
}

void	cursor_move(int x, int y)
{
	ft_putstr_fd(tgoto(CM, x, y), 0);
	g_sel.x = x;
	g_sel.y = y;
	g_sel.args->coord.x = x / g_sel.pad + 1;
	g_sel.args->coord.y = y + 1;
}