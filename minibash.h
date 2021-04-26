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
#include <fcntl.h>

#define ZERO 0b00000000
#define PIPE 0b00000001
#define SYNTAX_ERR 0b00000010
#define REDIR_OUT 0b00000100
#define REDIR_APPEND 0b00001000
#define REDIR_IN 0b00010000
#define QUOTED 0b00100000
#define SINGLE 0b00100000
#define DOUBLED 0b01000000
#define ESCAPED 0b10000000

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

// splitted command with its argumnents
typedef struct	s_seq
{
	char			*run;
	char			**args;
	unsigned char	info;
	char			*input;
	char			*output;
	struct s_seq	*pipe;
	struct s_seq	*next;
}				t_seq;

// list analog of tmp_seq->args
typedef struct	s_quo_split
{
	char				*arg;
	struct s_quo_split	*next;
}				t_quo_split;

// quotes structure
typedef struct	s_quo
{
	int			single_q;
	int			double_q;
	int			after_space;
	int			split_len;
	t_quo_split	*split;
	char		*start;
	char		*end;
}				t_quo;

// shell struct with main info
typedef struct	s_shell
{
	t_history	*history;
	t_history	*hist_ptr;
	t_history	*hist_curr;
	t_env		*env;
	size_t		env_size;
	t_seq		*seq;
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
char	*ft_strtrim(char const *s1, char const *set);
size_t		ft_numchstr(char *s, char ch);
char	*ft_strchrset(char *s, char *set);
char	*ft_strjoin_space(char const *s1, char const *s2);
int		ft_strempty(char *s);

// errors
void lite_error(char *comment);
void free_error(char *comment, t_shell **shell);
void		free_seq(t_seq **seq);

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
int envp_set_value(t_env *env, char *param, char *value);

// parser
void parser(t_shell *shell);
void	free_split(char ***split, t_shell *shell);
int	init_seq(t_seq **seq);
void parse_split(t_seq *tmp_seq, t_shell *shell, char sym, char *str);
void	parse_one(t_seq *tmp_seq, t_shell *shell);
int			is_builtin(char *s);
void	parse_redirect(t_seq *tmp_seq, t_shell *shell);
int syntax_error(t_shell *shell, char sym);
void parse_quotes(t_seq *tmp_seq, t_shell *shell);
int init_quo_split(t_quo_split **new);
void free_quotes(t_quo **quo);
void error_quotes(t_quo **quo, t_shell **shell);
void fill_after_quotes(t_seq *tmp_seq, t_shell *shell, t_quo *quo);
int is_ignored(char *start, char *ptr, t_shell *shell);
int precheck_quotes(t_shell *shell);

// executer
int run_one(t_seq *tmp_seq, t_shell *shell);
int run_pipe(t_seq *tmp_seq, t_shell *shell);
int redirect_out(t_seq *tmp_seq, t_shell *shell);
int redirect_in(t_seq *tmp_seq, t_shell *shell);

//builtins
char	*pwd(t_shell *shell);
int	builtins_pwd(t_shell *shell);
int	builtins_cd(t_shell *shell);
int builtins_env(t_shell *shell);
int	builtins_echo(t_shell *shell);
int builtins_unset_value(t_shell *shell);
int builtins_exit(t_shell *shell);
int builtins_export(t_shell *shell);
#endif
