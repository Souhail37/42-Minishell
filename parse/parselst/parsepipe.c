/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsepipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababouel <ababouel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 02:38:39 by ababouel          #+#    #+#             */
/*   Updated: 2022/07/23 17:58:59 by ababouel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_data	*parse_pipe(t_lsdata *lsdata, t_data *data)
{
	t_data	*new_dt;

	new_dt = NULL;
	piped(data->pipe.pfd);
	if (lsdata->size == 0)
		data->pipe.statpipe = START;
	else if (lsdata->size < lsdata->nupipe)
		data->pipe.statpipe = UPDATE;
	ins_next_data(lsdata, data);
	new_dt = init_dt();
	data = NULL;
	return (new_dt);
}
