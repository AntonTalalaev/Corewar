/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champion_part_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:53:26 by bsprigga          #+#    #+#             */
/*   Updated: 2019/05/02 11:49:49 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

static void	parsing_line_by_line_ext(char *line)
{
	free(line);
	g_params->num_line++;
}

static int	skip_spaces_tabs(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_strchr(" \t", line[i]))
		i++;
	return (i);
}

void		free_and_check_existence(char *ln, t_main_header *main_header,
									t_header **header, int i)
{
	free(ln);
	free(main_header);
	check_prog_name_and_comment_existence(*header, i);
}

/*
**	ln = line (shortened to meet norm)
*/

static void	parsing_line_by_line(int fd_input, t_header **header,
								t_main **main)
{
	char			*ln;
	int				i;
	t_main_header	*main_header;

	main_header = vars_init(header, main, &ln, &i);
	while (get_next_line(fd_input, &ln) > 0)
	{
		i = skip_spaces_tabs(ln);
		if (!(ln[i]) || ln[i] == COMMENT_CHAR || ln[i] == ALT_COMMENT_CHAR)
		{
			if (!((*header)->prog_name) || !((*header)->comment))
				check_slash_zero(fd_input, ft_strlen(ln) + 1);
			else if (check_slash_zero_exit(fd_input, ft_strlen(ln) + 1, *main))
				break ;
		}
		else
		{
			name_comment_parsing(&ln, i, main_header, fd_input);
			if (check_slash_zero_exit(fd_input, ft_strlen(ln) + 1, *main))
				break ;
		}
		parsing_line_by_line_ext(ln);
	}
	free_and_check_existence(ln, main_header, header, i);
}

void		champion_file_parsing(char *filename, int annotated_version)
{
	int			fd_input;
	t_header	*header;
	t_main		*main;

	if ((fd_input = open(filename, O_RDONLY)) < 0)
		error_exit(e_open_error, 0, 0);
	if (!(header = (t_header *)malloc(sizeof(t_header))))
		error_exit(e_malloc_error, 0, 0);
	if (!(main = (t_main *)malloc(sizeof(t_main))))
		error_exit(e_malloc_error, 0, 0);
	parsing_line_by_line(fd_input, &header, &main);
	close(fd_input);
	if (main->num_of_op == -1)
		error_exit(e_no_exec_code, g_params->num_line, 1);
	reverse_main_list(&main);
	replace_labels_with_numbers(&main);
	if (annotated_version)
		dump_champion(header, main);
	else
		translate_to_byte_code(header, main, filename);
	exit(0);
}
