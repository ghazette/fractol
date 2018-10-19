/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bn_add.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/25 16:36:25 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/05/25 18:51:33 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "bignumber.h"

static size_t	decompose(t_bignumber *bn, char *str)
{
	size_t	len;
	size_t	i;
	size_t	j;

	j = 0;
	i = 1;

	len = ft_strlen(str);
	if (!(bn->members = malloc(sizeof(char) * (len + 1))))
		return (BN_MALLOC_ERROR);
	bn->members[0] = BN_LIMIT;
	while (j < len)
	{
		bn->members[i] = (str[j] - 48);
		i++;
		j++;
	}
	return (len);
}

static void		reverse(char *str, size_t i)
{
	size_t	j;
	char	tmp;

	j = 0;
	while (j < i)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		i--;
		j++;
	}
}

char			*bn_add(char *s1, char *s2)
{
	t_bignumber bn1;
	t_bignumber bn2;
	t_bool		accu;
	char		ret[BN_BUFF_SIZE];
	size_t		i;
	char		nb;

	i = 0;
	if (!(bn1.length = decompose(&bn1, s1)) ||
		!(bn2.length = decompose(&bn2, s2)))
		return (NULL);
	while (bn1.members[bn1.length] != BN_LIMIT ||
			bn2.members[bn2.length] != BN_LIMIT)
	{
		nb = 0 + accu;
		if (bn1.members[bn1.length] != BN_LIMIT)
			nb += bn1.members[bn1.length];
		if (bn2.members[bn2.length] != BN_LIMIT)
			nb += bn2.members[bn2.length];
		if (accu == TRUE)
			accu = FALSE;
		if (nb >= 10)
			accu = TRUE;
		ret[i] = nb + 48 - ((accu == TRUE) ? 10 : 0);
		bn1.length -= (bn1.members[bn1.length] == BN_LIMIT) ? 0 : 1;
		bn2.length -= (bn2.members[bn2.length] == BN_LIMIT) ? 0 : 1;
		i++;
	}
	ret[i] = '\0';
	reverse(ret, i - 1);
	printf("len : %zu\n", strlen(ret));
	if (strstr("994464646428278272828737937997979797979797979797979797497912972192712791279722723265673627362362783623623623623678362782786567826782668716716268672686768136726762866767868627862686727861678247727272726726727041100733921907904403979520415651130531730587566576531733533146751130008187062548", ret))
		printf("ret : %s\n", ret);
	free(bn1.members);
	free(bn2.members);
	return (NULL);
}