RESET="\033[0m"
BLACK="\033[30m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"
CYAN="\033[36m"
WHITE="\033[37m"

BOLDBLACK="\033[1m\033[30m"
BOLDRED="\033[1m\033[31m"
BOLDGREEN="\033[1m\033[32m"
BOLDYELLOW="\033[1m\033[33m"
BOLDBLUE="\033[1m\033[34m"
BOLDMAGENTA="\033[1m\033[35m"
BOLDCYAN="\033[1m\033[36m"
BOLDWHITE="\033[1m\033[37m"

make -C ../ > /dev/null
cp ../minishell .
chmod 755 minishell
ok=0
all=0
function exec_test()
{
	TEST1=`./minishell -c "$@" 2>/dev/null`
	ES_1=$?
	TEST2=`bash -c "$@" 2>/dev/null`
	ES_2=$?
	all=$((all + 1))
  if [ "$all" -lt 10 ]; then
    printf " "
  fi
  printf "$all."
	if [ "$TEST1" == "$TEST2" ] && [ "$ES_1" == "$ES_2" ]; then
		printf " $BOLDGREEN%s$RESET" "✓ "
		ok=$((ok + 1))
	else
		printf " $BOLDRED%s$RESET" "✗ "
	fi
	printf "$CYAN \"$@\" $RESET"
	if [ "$TEST1" != "$TEST2" ]; then
		echo
		echo
		printf $BOLDRED"Your output : \n%.20s\n$BOLDRED$TEST1\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
		printf $BOLDGREEN"Expected output : \n%.20s\n$BOLDGREEN$TEST2\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
	fi
	if [ "$ES_1" != "$ES_2" ]; then
		echo
		echo
		printf $BOLDRED"Your exit status : $BOLDRED$ES_1$RESET\n"
		printf $BOLDGREEN"Expected exit status : $BOLDGREEN$ES_2$RESET\n"
	fi
	echo
	sleep 0.1
}

printf "$BOLDMAGENTA __  __ _____ _   _ _____  _____ _    _ ______ _      _      \n"
printf "|  \/  |_   _| \ | |_   _|/ ____| |  | |  ____| |    | |     \n"
printf "| \  / | | | |  \| | | | | (___ | |__| | |__  | |    | |     \n"
printf "| |\/| | | | | . \` | | |  \___ \|  __  |  __| | |    | |     \n"
printf "| |  | |_| |_| |\  |_| |_ ____) | |  | | |____| |____| |____ \n"
printf "|_|  |_|_____|_| \_|_____|_____/|_|  |_|______|______|______|\n$RESET"
echo

exec_test 'export = ; echo $?'
exec_test 'echo $?'
exec_test 'export str1 2str = _3str str4=str5'
exec_test 'ec"h"o $str1 $str4 $str2'
exec_test 'export q=e "w"=c e="h" r=o t=x "y"="p" u=r i=t'
exec_test '  e"x"port "t"$qs$i=hell$r'
exec_test 'echo "hello;"; $qc"h"o $test'
exec_test '$q$w$eo $PWD;   cd .. ;    $q"c"$eo $PWD    ;'
exec_test '$lkjlkjllkdfs$q$w$e$r "$e"$q"l"l$r;'
exec_test 'ec"ho;";pwd'
exec_test '>fil$q"1" e$w"ho" s$i"r"ing f$r$u file1'
exec_test 'pwd ; cat file1'
exec_test 'echo $?'
exec_test 'echo $?'
exec_test 'unset 11; echo $11'
exec_test 'unset PWD; echo $PWD'
exec_test 'ls; unset PATH; ls     ;'
exec_test 'export PATH=/  ; ls'
exec_test 'echo $PWD; unset PWD'
exec_test 'echo $PWD; export PWD=/ ; echo $PWD;'
exec_test 'pwd; echo $PWD'
exec_test '"echo f" hello'
exec_test '>"helo l" echo hell\ f'
exec_test '>>"helo l" echo hell\ f ; echo hell\ f'
exec_test 'cat "helo l"'


# ЗАПУСКАТЬ КУСОК ОТДЕЛЬНО, ОСТАЛЬНОЕ ЗАКОММЕНТИТЬ
# exec_test 'export t=n; echo -$t -n "-"n hello'
# exec_test "echo -$t '-n' '-''n' '-n;'         -n hello"

# exec_test 'cat /dev/random | head -c 100 | wc -c'
# exec_test 'ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls'
# exec_test 'echo test | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e'
# exec_test 'ls | ls | ls | ls | ls | ls | ls | ls | ls |ls|ls|ls|ls ls | ls | ls | ls | ls | ls | ls | ls | ls |ls|ls|ls|ls ls | ls | ls | ls | ls | ls | ls | ls | ls |ls|ls|ls|ls ls | ls | ls | ls | ls | ls | ls | ls | ls |ls|ls|ls|ls ls | ls | ls | ls | ls | ls | ls | ls | ls |ls|ls|ls|ls ls | ls | ls | ls | ls | ls | ls | ls | ls |ls|ls|ls|ls ls | ls | ls | ls | ls | ls | ls | ls | ls |ls|ls|ls|ls ls | ls | ls | ls | ls | ls | ls | ls | ls |ls|ls|ls|ls ls | ls | ls | ls | ls | ls | ls | ls | ls |ls|ls|ls|ls ls | ls | ls | ls | ls | ls | ls | ls | ls |ls|ls|ls|ls'