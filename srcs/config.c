/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 12:01:39 by srouhe            #+#    #+#             */
/*   Updated: 2020/01/14 16:55:43 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

/*
** OPOST:	If this bit isn’t set, the characters are transmitted as-is.
** ECHO:	Don't print out keypresses.
** ICANON:	Input is processed in noncanonical mode.
*/

void	initial_config(void)
{
	int		r;
	char	*term;
	char	buf[BUF_SIZE + 1];

	if (!isatty(OUTPUT))
		exit_program(4, 0);
	if (!(term = getenv("TERM")))
		exit_program(7, 0);
	r = tgetent(buf, term);
	if (r == -1)
		exit_program(5, 0);
	else if (r == 0)
		exit_program(6, 0);
	tcgetattr(OUTPUT, &g_sel.attr);
	tcgetattr(OUTPUT, &g_sel.def);
	g_sel.attr.c_oflag &= ~OPOST;
	g_sel.attr.c_lflag &= ~(ECHO | ICANON);
	g_sel.attr.c_cc[VMIN] = 0;
	g_sel.attr.c_cc[VTIME] = 1;
	tcsetattr(OUTPUT, TCSANOW, &g_sel.attr);
	tputs(TI, 1, printnbr);
	tputs(VI, 1, printnbr);
}

void	reset_config(void)
{
	tcsetattr(OUTPUT, TCSANOW, &g_sel.def);
	tputs(VE, 1, printnbr);
	tputs(TE, 1, printnbr);
}
