/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:30:52 by gkrusta           #+#    #+#             */
/*   Updated: 2023/10/09 15:25:24 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char *input;
	char* username;

	username = getenv("USER"); 
	printf("\n\nUSER is: @%s", username); 
	input = readline("minishell "); 
	if (ft_strlen(input) > 0)
		add_history(input);
	printf("added to history: %s\n", input);
	return (0);
}