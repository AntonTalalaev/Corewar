/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champion_part_7.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 16:46:49 by tsimonis          #+#    #+#             */
/*   Updated: 2019/05/01 04:42:33 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

void		read_label_direct(char *line, int *index, t_main **new,
								int *num_args)
{
	int		prev_index;
	char	*tmp;

	prev_index = *index - 1;
	check_for_null(line, index);
	while (line[*index] && !ft_strchr(" \t", line[*index]) &&
	line[*index] != SEPARATOR_CHAR &&
	line[*index] != COMMENT_CHAR && line[*index] != ALT_COMMENT_CHAR)
		(*index)++;
	if (!(tmp = ft_strsub(line, prev_index + 2, *index - prev_index - 2)))
		error_exit(e_malloc_error, g_params->num_line, prev_index + 2 + 1);
	check_valid_label(tmp, prev_index + 2, e_dont_check_in_all_labels);
	free(tmp);
	if (!((*new)->args[(*num_args)++] = ft_strsub(line, prev_index,
													*index - prev_index)))
		error_exit(e_malloc_error, g_params->num_line, prev_index);
}

void		read_number_direct(char *line, int *index, t_main **new,
								int *num_args)
{
	int		prev_index;

	prev_index = *index - 1;
	if (line[*index] == '-')
		(*index)++;
	if (!(line[*index]) || !ft_strchr("0123456789", line[*index]))
		error_exit(e_incorrect_argument, g_params->num_line, *index + 1);
	while (line[*index] && ft_strchr("0123456789", line[*index]))
		(*index)++;
	if (!((*new)->args[(*num_args)++] = ft_strsub(line, prev_index,
													*index - prev_index)))
		error_exit(e_malloc_error, g_params->num_line, prev_index);
}

void		read_direct(t_main **new, int *num_args, int *index, char *line)
{
	if (!(g_op_tab[(*new)->num_of_op].args[*num_args] & T_DIR))
		error_exit(e_incorrect_argument, g_params->num_line, *index + 1);
	check_for_null(line, index);
	if (line[*index] == LABEL_CHAR)
		read_label_direct(line, index, new, num_args);
	else
		read_number_direct(line, index, new, num_args);
	(*new)->size_of_op += g_op_tab[(*new)->num_of_op].size_of_t_dir;
}

t_indexes	*indexes_init(int label_or_op_start)
{
	t_indexes	*indexes;

	if (!(indexes = (t_indexes *)malloc(sizeof(t_indexes))))
		error_exit(e_malloc_error, 0, 0);
	indexes->quit = 0;
	indexes->launch_gnl = 0;
	indexes->label_or_op_end = 0;
	indexes->label_or_op_start = label_or_op_start;
	return (indexes);
}

void		skip_spaces(char *line, int *index)
{
	while (line[*index] && ft_strchr(" \t", line[*index]))
		(*index)++;
}
