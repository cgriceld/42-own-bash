#ifndef MINIBASH_H
# define MINIBASH_H

#include <term.h>
#include <unistd.h>
#include <string.h>
#include <curses.h>
#include <stdlib.h>
#include <stdio.h>
#include <termcap.h>
#include <strings.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

// errors
#define WRONG_ARGS "wrong input arguments, should be : ./minishell"

// reader defines
#define PROMPT "\033[1;36mminibash\033[0m : "
#define UP "\e[A"
#define DOWN "\e[B"
#define LEFT "\e[C"
#define RIGHT "\e[D"
#define DEL "\x7f"
#define CTRLD "\04"

// external commands paths
#define FULL_PATH 1
#define SHORT_PATH 0

// global variable, exit code of last command
int ret_status;

// terminal modes
typedef enum	e_modes
{
	NOT_CANON,
	CANON,
	WAS_SIGN,
	NO_SIGN
}				t_modes;

// envp list
typedef struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

// history, doubly linked list
typedef struct	s_history
{
	char				*command;
	char				*cache;
	size_t				len;
	size_t				cache_len;
	struct s_history	*prev;
	struct s_history	*next;
}				t_history;

// shell struct with main info
typedef struct	s_shell
{
	t_history	*history;
	t_history	*hist_ptr;
	t_history	*hist_curr;
	ssize_t		read_len;
	t_env		*env;
	size_t		env_size;
}				t_shell;

// utils
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_putchar(int c);
size_t	ft_strlen(const char *s);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *b, int c, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
char		*ft_itoa(int n);
int			ft_atoi(const char *str);
char		**ft_split(char const *s, char c);
void	ft_twodarr_free(char ***arr, size_t len);
size_t	ft_twodarr_len(char **arr);

// errors
void lite_error(char *comment);
void free_shell(t_shell **shell);
void free_error(char *comment, t_shell **shell);

// readline
void ft_readline(t_shell *shell);
void set_mode(int type);
void prompt(void);
void init_hist(t_shell *shell);
void handle_up(t_shell *shell);
void handle_down(t_shell *shell);
void handle_del(t_shell *shell);
void handle_execute(t_shell *shell);
void		deal_cache(t_shell *shell);
void			find_external(t_shell *shell);

// signals
void set_signals(void);
int *signal_tracker(void);

// envp
void		envp_to_list(char **envp, t_shell *shell);
char		**envp_to_arr(t_shell *shell);
char	*envp_get_value(t_shell *shell, char *match);

#endif
