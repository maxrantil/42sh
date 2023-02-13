/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_sigchild.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:13:55 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/13 21:57:53 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//#include "ft_42sh.h"

//extern t_shell	*g_sh;

//// static int	print_fg_node(t_shell *sh)
//// {
//// 	pid_t	*tmp;
//// 	char	***ptr;
//// 	char	**dbl;

//// 	tmp = sh->fg_node->pid;
//// 	while (tmp && *tmp)
//// 		ft_printf("pid: %d\n", *(tmp++));
//// 	ptr = sh->fg_node->cmd;
//// 	while (ptr && *ptr)
//// 	{
//// 		dbl = *ptr;
//// 		while (*dbl)
////         {
//// 			ft_printf("cmd: %s\n", *dbl);
////             dbl++;
////         }
////         ptr++;
//// 	}
//// 	return (0);
//// }

//static bool	check_bg_pipeline(t_bg_jobs *job, pid_t pid)
//{
	//pid_t	*ptr;

	//ptr = job->pid;
	//while (*ptr)
	//{
		//if (*ptr == pid)
			//return (true);
		//ptr++;
	//}
	//return (false);
//}

//static void	change_process_status(t_bg_jobs *bg_node, pid_t pid, int status)
//{
	//t_bg_jobs	*job;

	//job = bg_node;
	//while (job)
	//{
		//if (check_bg_pipeline(job, pid))
			//break ;
        //job = job->next;
	//}
	//if (job)
		//job->status = status;
//}

//static void	check_fg_pipeline(t_shell *sh, pid_t pid)
//{
	//pid_t	*ptr;

	//if (!sh->fg_node->gpid)
		//return ;
	//ptr = sh->fg_node->pid;
	//while (ptr && *ptr)
	//{
		//if (*ptr == pid)
		//{
			//reset_fgnode(sh);
			//return ;
		//}
		//ptr++;
	//}
//}

//static void	signaled_from_background(t_bg_jobs *job, int status)
//{
	//while (job->next)
		//job = job->next;
	//job->status = status;
	//delete_from_queue(g_sh, job);
	//g_sh->process_count++;
	//ft_memmove(&g_sh->process_queue[1], \
	//&g_sh->process_queue[0], g_sh->process_count * sizeof(int));
	//g_sh->process_queue[0] = job->index;
//}

//void	handler_sigchild(int num)
//{
	//int		status;
	//pid_t	pid;

	//if (num == SIGCHLD)
	//{
		//pid = waitpid(-1, &status, WNOHANG);
		//if (pid)
		//{
			//while (pid > 0)
			//{
				//if (WIFSIGNALED(status))
				//{
					//if (WTERMSIG(status))
					//{
						//ft_putchar('\n');
						//check_fg_pipeline(g_sh, pid);
						//change_process_status(g_sh->bg_node, pid, TERMINATED);
						//g_sh->exit_stat = WTERMSIG(status) + 128;
					//}
				//}
				//else if (WIFEXITED(status))
				//{
					//g_sh->exit_stat = WEXITSTATUS(status);
					//if (g_sh->exit_stat == 127)
						//change_process_status(g_sh->bg_node, pid, EXITED);
					//else
						//change_process_status(g_sh->bg_node, pid, DONE);
				//}
				//pid = waitpid(-1, &status, WNOHANG);
			//}
		//}
		//else if (pid == 0 && !g_sh->fg_node->gpid)
		//{
			//ft_putchar('\n');
			//signaled_from_background(g_sh->bg_node, STOPPED);
			//display_suspended_job(g_sh);
		//}
	//}
//}
