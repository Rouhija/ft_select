/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 12:01:39 by srouhe            #+#    #+#             */
/*   Updated: 2020/01/07 12:40:07 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	initial_config(void)
{
	int		r;
	char	buf[BUF_SIZE + 1];

	r = tgetent(buf, getenv("TERM"));
	if (r < 1)
		exit_program(NULL, 2, 0);
	tcgetattr(2, &g_sel.attr);
	tcgetattr(2, &g_sel.def);
	// g_sel.attr.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
					// | INLCR | IGNCR | ICRNL | IXON);
	g_sel.attr.c_oflag &= ~OPOST;
	g_sel.attr.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	// g_sel.attr.c_cflag &= ~(CSIZE | PARENB);
	// g_sel.attr.c_cflag |= CS8;
	tcsetattr(2, TCSANOW, &g_sel.attr);
	tputs(CL, 1, printnbr);
	tputs(TI, 1, printnbr);
	tputs(VI, 1, printnbr);
}

void	reset_config(void)
{
	tcsetattr(2, TCSANOW, &g_sel.def);
	tputs(VE, 1, printnbr);
	tputs(TE, 1, printnbr);
}