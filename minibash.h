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
#define IGNORE 0b00000010
#define REDIR_OUT 0b00000100
#define REDIR_APPEND 0b00001000
#define REDIR_IN 0b00010000
#define AMBIGUOUS 0b00000001
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

// struct for redirect chain, type - redirect type
typedef struct	s_redir_chain
{
	char					*path;
	unsigned char			type;
	struct s_redir_chain	*next;
}				t_redir_chain;

// splitted command with its argumnents
typedef struct	s_seq
{
	char					*run;
	char					**args;
	unsigned char			info;
	struct s_redir_chain	*redirect;
	struct s_redir_chain	*tmp_redir;
	struct s_seq			*pipe;
	struct s_seq			*next;
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
	int			after_space;
	int			split_len;
	t_quo_split	*split;
	char		*start;
	char		*end;
	int			slashes;
	int			last_slash;
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
	int			sep[2];
}				t_shell;

struct		s_list
{
	void			*content;
	struct s_list	*next;
};
typedef struct s_list	t_list;

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
int ft_in_set(const char *set, char ch);
t_list *put_to_sort_list(char *content, t_list *start);
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
char *ft_low_str(char *str);
char	*ft_strjoin_sym(char const *s1, char const *s2, char sym);
char *ft_genstr(char sym, int num);
char	*ft_strrchr(const char *s, int c);
int	ft_isdigit(int c);

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
int envp_set_value(t_shell *shell, char *param, char *value);
int envp_new_value(t_shell *shell, char *param, char *value);

// parser
void parser(t_shell *shell);
void	free_split(char ***split, t_shell *shell);
int	init_seq(t_seq **seq);
void parse_split(t_seq *tmp_seq, t_shell *shell, char sym, char *str);
void	parse_one(t_seq *tmp_seq, t_shell *shell);
int			is_builtin(char *s);
void parse_redirect(t_seq *tmp_seq, t_shell *shell, t_quo *quo);
int syntax_error(t_shell *shell, char sym);
void parse_quotes(t_seq *tmp_seq, t_shell *shell);
int init_quo_split(t_quo_split **new);
void free_quotes(t_quo **quo);
void error_quotes(t_quo **quo, t_shell **shell);
void fill_after_quotes(t_seq *tmp_seq, t_shell *shell, t_quo *quo);
int precheck_syntax(t_shell *shell);
void join_args(t_seq *tmp_seq, t_shell *shell, t_quo *quo, t_quo_split *tmp_split);
void join_one_sym(t_shell *shell, t_quo *quo, char **str, char *sym);
void join_routine(t_seq *tmp_seq, t_shell *shell, t_quo *quo, t_quo_split *tmp_split);
void parse_singleq(t_seq *tmp_seq, t_shell *shell, t_quo *quo, t_quo_split *tmp_split);
void parse_escape(t_seq *tmp_seq, t_shell *shell, t_quo *quo, t_quo_split *tmp_split);
void parse_doubleq(t_seq *tmp_seq, t_shell *shell, t_quo *quo, t_quo_split *tmp_split);
int even_escaped(char *start, char *str);
void parse_dollar(t_seq *tmp_seq, t_shell *shell, t_quo *quo, t_quo_split *tmp_split);
void redirect_join(t_seq *tmp_seq, t_shell *shell, t_quo *quo);
void join_args2(t_seq *tmp_seq, t_shell *shell, t_quo *quo, char **arg);
int cancel_escape(t_seq *tmp_seq, t_shell *shell, t_quo *quo, t_quo_split *tmp_split);
void what_parse(t_seq *tmp_seq, t_shell *shell, t_quo *quo, t_quo_split *tmp_split);

// executer
int run_one(t_seq *tmp_seq, t_shell *shell);
int run_pipe(t_seq *tmp_seq, t_shell *shell);
int run_redirect(t_seq *tmp_seq, t_shell *shell);

//builtins
char	*pwd(t_shell *shell, t_seq *tmp_seq);
int	builtins_pwd(t_shell *shell, t_seq *tmp_seq, char *str_low);
int	builtins_cd(t_shell *shell, t_seq *tmp_seq, char *str_low);
int builtins_env(t_shell *shell, t_seq *tmp_seq, char *str_low);
int	builtins_echo(t_shell *shell, t_seq *tmp_seq, char *str_low);
int builtins_unset_value(t_shell *shell, t_seq *tmp_seq, char *str_low, int flag);
int builtins_exit(t_shell *shell, t_seq *tmp_seq, char *str_low);
int builtins_export(t_shell *shell, t_seq *tmp_seq, char *str_low, int flag);
int	redir(t_shell *shell, t_seq *tmp_seq, char *str_low, int flag);
int	check_is_valid(t_seq *tmp_seq, int i, int flag);
#endif
