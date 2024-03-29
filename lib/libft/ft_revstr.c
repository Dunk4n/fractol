/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_revstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 14:57:05 by niduches          #+#    #+#             */
/*   Updated: 2019/10/10 15:23:08 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*my_revstr(char *str)
{
	int		i;
	int		len;
	char	swap;

	i = 0;
	swap = '\0';
	len = 0;
	while (str[len])
		len++;
	len--;
	while (i < len / 2)
	{
		swap = str[i];
		str[i] = str[len - i];
		str[len - i] = swap;
		i++;
	}
	return (str);
}
