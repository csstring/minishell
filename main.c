#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
//ctrl_c 시그널 핸들링
void	sig_handler(int signum)
{
	if (signum != SIGINT)
		return ;
	write(STDOUT_FILENO, "\n", 1);
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 1);
	rl_redisplay();
}
//return : 입력한 명령어 한줄
//prompt 출력
char	*ft_prompt(void)
{
	char	*line;

	line = readline("ss_shell$ ");
	if (line == NULL)
	{
		printf("\033[1A");
		printf("\033[10C");
		printf("exit\n");
		exit(-1);
	}
	else
	{
		add_history(line);
		return (line);
	}
}

int	main(void)
{
	char	*line;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = ft_prompt();
		printf("%s\n", line);
		free(line);
	}
}
