/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine_part_2_flags_2.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 16:15:27 by mwunsch           #+#    #+#             */
/*   Updated: 2019/05/01 03:41:17 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

int			skip_flags(char **argv, int i)
{
	if (argv[i][1] == 'a' || argv[i][1] == 'v' || argv[i][1] == 'i')
		return (1);
	else if (argv[i][1] == 'd')
		return (2);
	else if (argv[i][1] == 'n')
		return (3);
	error_exit(e_incorrect_flag, 0, 0);
	return (0);
}

void		num_bots_checker(t_vm *vm)
{
	int		i;

	i = -1;
	while (++i < MAX_PLAYERS)
		if (!(vm->bot[i].weapon))
			break ;
	vm->num_bots = i;
	while (++i < MAX_PLAYERS)
		if (vm->bot[i].weapon)
			error_exit(e_inconsistent_bot_order, 0, 0);
}
