/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disassemble_part_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 01:57:33 by tsimonis          #+#    #+#             */
/*   Updated: 2019/04/30 17:53:49 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

void			read_champion_name(int fd_input, t_header **header)
{
	unsigned char	bytes[PROG_NAME_LENGTH];

	if (read(fd_input, bytes, PROG_NAME_LENGTH) < PROG_NAME_LENGTH)
		error_exit(e_cor_file_is_too_short, 1, 4);
	(*header)->prog_name = ft_strjoin((char *)bytes, "\0");
}

void			read_null_before(int fd_input)
{
	unsigned char	bytes[4];

	if (read(fd_input, bytes, 4) < 4)
		error_exit(e_cor_file_is_too_short, 1, 4 + PROG_NAME_LENGTH);
	if ((bytes[0] << 24) + (bytes[1] << 16) + (bytes[2] << 8) + bytes[3] != 0)
		error_exit(e_incorrect_null_sequence, 1, 4 + PROG_NAME_LENGTH);
}

unsigned int	read_champion_exec_code_size(int fd_input)
{
	unsigned int	size;
	unsigned char	bytes[4];

	if (read(fd_input, bytes, 4) < 4)
		error_exit(e_cor_file_is_too_short, 1, 4 + PROG_NAME_LENGTH + 4);
	size = ((bytes[0] << 24) + (bytes[1] << 16) + (bytes[2] << 8) + bytes[3]);
	if (size > CHAMP_MAX_SIZE)
		error_exit(e_exec_code_size_is_too_big, 1, 4 + PROG_NAME_LENGTH + 4);
	return (size);
}

void			read_champion_comment(int fd_input, t_header **header)
{
	unsigned char	bytes[COMMENT_LENGTH];

	if (read(fd_input, bytes, COMMENT_LENGTH) < COMMENT_LENGTH)
		error_exit(e_cor_file_is_too_short, 1, 4 + PROG_NAME_LENGTH + 4 + 4);
	(*header)->comment = ft_strjoin((char *)bytes, "\0");
}

void			read_null_after(int fd_input)
{
	unsigned char	bytes[4];

	if (read(fd_input, bytes, 4) < 4)
		error_exit(e_cor_file_is_too_short, 1, 4 + PROG_NAME_LENGTH);
	if ((bytes[0] << 24) + (bytes[1] << 16) + (bytes[2] << 8) + bytes[3] != 0)
		error_exit(e_incorrect_null_sequence, 1,
					4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH);
}
