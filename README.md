# 42-own-bash

42 Unix project. The code is written in accordance with The Norm (42 coding style).\
The project was done in a team with [Elena Kiseleva](https://github.com/Justlesia), it contains lots of parsing, signal and error handling and process management (fork, execve, etc.).

<img width="405" alt="demo" src="https://user-images.githubusercontent.com/62188694/122681378-aed39e00-d1fc-11eb-9973-03fb7026f58b.png">

## what *`minibash`* supports:
* navigate through command history using up and down arrows (done using termcap);
* modification of current or previous commands using backspace (not supports movement with left and right arrows);
* ctrl-C, ctrl-D and ctrl-\ signals;
* $?;
* environment variables;
* pipes (except for multiline commands);
* \>, < and >> redirections (except for file descriptor aggregation);
* semicolon;
* single, double quotes and \\;
* builtins commands : 
  * `echo` with `-n` option;
  * `cd` with relative or absolute path;
  * `pwd`, `export`, `unset` and `exit` without any options;
  * `env` without any options and any arguments;
* external commands launch through execve.

##  usage

In the root of repository run `make` and launch executable -- `./minishell`.

## project structure

* *`builtins` folder* -- builtins commands code.
* *`envp` folder* -- code for manipulating envp array/list.
* *`parser` folder* -- code for parsing and launching (where all the magic happens, basically).
* *`readline` folder* -- reading via termcap.
* *`utils` folder* -- utils functions (some from own [C library](https://github.com/linpoa/libft), some specific for project).

***Makefile***
* *`make`* -- compiles `minishell` executable.
* *`clean`* -- deletes object files.
* *`fclean`* -- deletes object files and `minishell`.
* *`re`* -- runs `fclean` and recompiles.
