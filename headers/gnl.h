/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hardella <hardella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:40:17 by hardella          #+#    #+#             */
/*   Updated: 2022/02/26 17:18:40 by hardella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# include <stdlib.h>
# include <unistd.h>
# define BUFFER_SIZE 42

char		*ft_strjoin_gnl(char *s1, char *s2);
void		*ft_memcpy_gnl(void *dst, void *src, int n);
int			ft_strlcpy_gnl(char *dst, char *src, int dstsize);
char		*ft_strchr_gnl(char *s, int c);
int			ft_strlen_gnl(char *str);

char		*get_next_line(int fd);

#endif 