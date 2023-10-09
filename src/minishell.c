/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:30:52 by gkrusta           #+#    #+#             */
/*   Updated: 2023/10/09 13:26:51 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char *str;
	char* username;

	username = getenv("USER"); 
	printf("\n\nUSER is: @%s", username); 
	str = readline("minishell "); 
	if (str)
		add
	123
	return (0);
}