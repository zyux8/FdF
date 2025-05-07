/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:27:54 by ohaker            #+#    #+#             */
/*   Updated: 2025/04/29 16:59:21 by ohaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(GET_NEXT_LINE_H)
# define GET_NEXT_LINE_H
# include "../libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*ft_read_line(int fd);
char	*get_left(char *str);
char	*ft_get_line(char *str);
char	*ft_strjoin_gnl(char *str1, char *str2);
int		ft_strlen_gnl(char *str);
char	*ft_strchr_gnl(const char *str, char c);
char	*ft_strdup_gnl(char *s);

#endif // GET_NEXT_LINE_H
