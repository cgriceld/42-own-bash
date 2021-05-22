# 42-own-bash

42 Unix project. The code is written in accordance with The Norm (42 coding style).\
The project was done in a team with [Elena Kiseleva](https://github.com/Justlesia).

What *`minibash`* supports:
* navigate through command history using up and down arrows (done using termcap);
* modification of current or previous commands using backspace (not supports movement with left and right arrows);
* ctrl-C, ctrl-D and ctrl-\ signals;
* $?;
* environment variables;
* pipes (except for multiline commands);
* \>, < and >> redirections (except for file descriptor aggregation);
* semicolon;
* single, double quotes and \\;
* builtins command : 
  * `echo` with `-n` option;
  * `cd` with relative or absolute path;
  * `pwd` without any options;
  * `export` without any options;
  * `unset` without any options;
  * `env` without any options and any arguments;
  * `exit` without any options
* external commands launch through execve.
