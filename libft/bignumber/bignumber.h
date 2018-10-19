/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bignumber.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/25 16:29:25 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/05/25 18:07:11 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BIGNUMBER_H
# define BIGNUMBER_H
# include "../includes/libft.h"
# define BN_LIMIT 25
# define BN_ERROR -1
# define BN_MALLOC_ERROR -2
# define BN_BUFF_SIZE 16384
# define TRUE 1
# define FALSE 0


typedef char		t_bool;

typedef struct		s_bignumber
{
	char			*members;
	t_bool			is_float;
	size_t			length;
}					t_bignumber;

char	*bn_add(char *s1, char *s2);

#endif
