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

exec_test ';; test'
exec_test '| test'
exec_test 'echo > <'
exec_test 'echo | |'
exec_test '/bin/ls'
exec_test 'bin/ls'
exec_test 'bin/ls'
exec_test 'bin/ls/'
exec_test 'ls/'
exec_test '/ls'
exec_test './ls'
exec_test '../ls'
exec_test '/..'
exec_test '/bin/ls --l'
exec_test 'ls --l'
touch f1
exec_test 'f1/'
exec_test '/f1'
exec_test './f1'
exec_test '../f1'
exec_test 'bu/f1'
rm f1
mkdir f1
exec_test 'f1/'
exec_test '/f1'
exec_test './f1'
exec_test '../f1'
exec_test 'bu/f1'
rm -rf f1
exec_test '/bin/ls -l'
exec_test '/bin/ls --l'
exec_test '/bin/ls -l-a'
exec_test '/bin/ls -l -a'
exec_test '/ls -l'
exec_test 'ls --l'
exec_test 'ls -l-a'
exec_test 'ls -l -a'
exec_test '\l\s \-l \-a'
exec_test 'ls \\\>| wc'
exec_test 'ls \\>| wc'
exec_test 'ls \>| wc'
exec_test 'ls >| wc'
exec_test "ls '>|' wc"
exec_test "ls '>\\|""' wc"
rm wc
exec_test 'ls "$\P\A\T\H"'
exec_test "ls '$\P\A\T\H'"
exec_test 'ls $\P\A\T\H'
exec_test '\l\s'
exec_test 'l\s'
exec_test '"ls"'
exec_test "'ls'"
exec_test 'ls\'
exec_test ' ls\ '
exec_test '\  \  \\'
exec_test 'ls \; \|'
exec_test 'ls \; ; grep bla'
exec_test 'ls \; ; | grep bla'
exec_test 'ls;'
exec_test ';ls'
exec_test 'ls;;;'
exec_test 'ls ";" -la'
exec_test "ls -l '-'a"
exec_test "'l''s'"
exec_test "ls ''"
exec_test "ls >''"
exec_test "ls > '' "
exec_test "l''s"
exec_test "ls '' -l"
exec_test "ls -l''"
exec_test "ls ''-l"
exec_test 'l""s'
exec_test 'ls ""'
exec_test 'ls >""'
exec_test 'ls > "" '
exec_test 'l""s'
exec_test 'ls "" -l'
exec_test 'ls -l""'
exec_test 'ls ""-l'
exec_test '    ls;;   ;     '
exec_test 'ls | grep bla'
exec_test 'ls | grep min'
exec_test 'blabla | grep min | grep shell'
exec_test 'blabla | ls | grep min'
exec_test 'ls | blabla | grep min'
exec_test 'ls | grep min | blabla'
exec_test 'grep | ls'
exec_test 'ls | grep'
exec_test 'ls | blabla | wc'
exec_test 'ls -la | grep min | grep shell | wc'
exec_test 'ls -la | grep min | grep shell | wc | blabla'
exec_test 'ls -la wrong | grep min | grep shell | wc | blabla'
exec_test 'ls -la wrong | grep min | grep shell | wc'
exec_test 'grep min | wc | ls -la wrong'
exec_test 'grep | wc | ls -la wrong'
exec_test 'grep | ls -la wrong | wc'
exec_test '|ls'
exec_test '| ls'
exec_test 'ls     |'
exec_test '     ls     |'
exec_test '   |    ls     |'
exec_test 'ls|||||||'
exec_test '  ls \|'
exec_test '  ls "\" \\\\'
exec_test "  ls $ '$'$"
exec_test '   ls |||||||'
exec_test   'ls|||||||     '
exec_test   'ls||  ||||  |     '
exec_test   'ls||  ||>||  |     '
exec_test     'ls||||  pwd|||     '
exec_test 'ls|   ls  |  |    '
exec_test 'ls > fil1.txt; blabla ||| ; wc'
exec_test 'ls > fil1.txt; cat fil1.txt'
exec_test '|>|'
exec_test '|>|l s'
exec_test 'ls>file1.txt'
exec_test 'ls>file1.txt <file2.txt -la'
exec_test 'ls>file2.txt -la'
exec_test 'ls><file1.txt'
exec_test 'ls<>file1.txt'
exec_test 'ls>file1.txt -l a<file1.txt'
exec_test 'ls<>'
exec_test '< ls'
exec_test '> ls'
exec_test ' < ls '
exec_test ' > ls '
exec_test 'ls >   '
exec_test '  ls  <   '
exec_test '>'
exec_test '<'
exec_test '>\>'
exec_test '> file1.txt ls'
exec_test "ls > 'pwd'"\"""
exec_test 'ls >\|;wc'
exec_test 'ls >\| pwd'
exec_test 'ls >| pwd'
exec_test 'ls >| | pwd'
exec_test 'ls ; ls>  " \"| p " bla' # all good, but tester may show error, delete file after first run
exec_test 'ls ; ls>  " \"| p "' # same
exec_test 'ls>  " \| p "'
exec_test "ls>' | p '"
exec_test 'ls> | p'
exec_test 'ls>|'
exec_test 'ls >|||pwd$'
exec_test 'ls >|\|\|pwd$'
exec_test 'ls > $$$$\\'
exec_test 'ls $'
exec_test 'ls $$'
exec_test 'ls $$$'
exec_test '/bin/ls $ $$'
exec_test 'ls $b$l$$a'
exec_test 'ls $b$l$a'
exec_test 'ls <| wc'
exec_test '> f1 ls bla'
exec_test 'ls <> ll'
exec_test 'ls < <>'
exec_test 'ls < <> f1'
exec_test 'ls < <>'
exec_test 'ls <><mm'
exec_test 'ls <>>tt'
exec_test 'ls <>>< y'
exec_test 'ls < > > < p'
exec_test 'ls < $bll'
exec_test 'ls< no_file > huhu'
exec_test 'ls < $bll$bu'
exec_test 'ls < $bll$bu\l'
exec_test 'ls < $bl\el$bu'
exec_test 'ls $bla'
exec_test 'ls < $TERM\el$bu'
exec_test '> $PATH'
exec_test '> $TERM'
exec_test 'ls > $PATH'
exec_test 'ls $PATH'
exec_test 'ls > $b$u > f1'
exec_test 'ls > $b$u>f1'
exec_test 'ls >$b$u>f1'
exec_test 'ls $?bu'
exec_test 'ls > f1>$b'
exec_test 'ls $?$"b"u'
exec_test "echo $?'$?'"
exec_test 'ls ???$?'
exec_test 'ls ?\??\$?'
exec_test 'ls <>> rr'
exec_test 'ls > file1.txt ; < file1.txt grep ls > file2.txt min'
exec_test '"<" file1.txt grep > file2.txt min'
exec_test '< "f"ile1."txt" \grep > file2.txt min'
exec_test '> file1.txt ; pwd'
exec_test 'ls -l > file3.txt -a'
exec_test 'ls l > file3.txt -a'
exec_test 'ls l > file3.txt -a ; ls > file3.txt'
exec_test 'ls < f2.txt | grep min'
exec_test '   " ls |   " \; pwd'
exec_test "'ls' > f1.txt -la"
exec_test 'ls $PWD -l'
exec_test 'ls <> > ll'
#rm f2
exec_test '> f2 l\s -la' # !!
exec_test '> f2 \ls -la'
exec_test '> f1 l\ s -l'
exec_test '\\l\$?'
exec_test 'pwd | > | ls'
exec_test '    " ls |   " \; pwd'
exec_test "'ls' > f7.txt -la"
exec_test '/bin/ls ..'
# exec_test echo " hi '$PWD'" верно, но в тестере не работает из-за кавычек
exec_test '/bin/pwd'
exec_test 'echo test tout'
exec_test 'echo test      tout'
exec_test 'echo -n test tout'
exec_test 'echo -n -n -n test tout'
exec_test 'echo $ '$'$'
exec_test 'echo \" $PWD \"'
exec_test 'echo \$?'
exec_test 'echo 2 6'
exec_test 'echo 2'
exec_test 'ECHO 1 1  ff'
exec_test 'echo " \"\"\"  "'
exec_test 'echo " hi \"  "'
exec_test 'echo "  "hi"  "'
exec_test "echo 'hi \'''"
exec_test "echo 'hi \''\;'"
exec_test "echo 'hi \''|'"
exec_test "echo '''b'''"
exec_test "echo '\''\\''\;'"
exec_test 'echo \   $PWD'
exec_test 'echo test     \    test'
exec_test 'echo \"test'
exec_test 'echo $TEST'
exec_test 'echo "$TEST"'
exec_test "echo '$TEST'"
exec_test 'echo "$TEST$TEST$TEST"'
exec_test 'echo "$TEST$TEST=lol$TEST"'
exec_test 'echo "   $TEST lol $TEST"'
exec_test 'echo $TEST$TEST$TEST'
exec_test 'echo $TEST$TEST=lol$TEST""lol'
exec_test 'echo    $TEST lol $TEST'
exec_test 'echo test "" test "" test'
exec_test 'echo "\$TEST"'
exec_test 'echo "$=TEST"'
exec_test 'echo "$"'
exec_test 'echo "$?TEST"'
exec_test 'echo $TEST $TEST'
exec_test 'echo "$1TEST"'
exec_test 'echo "$T1TEST"'
exec_test 'echo $1TERM'
exec_test 'echo $1bla$TERM'
exec_test 'echo $1PATH$PATH'
exec_test 'echo -n ll'
exec_test 'echo ls -la'

exec_test 'exit > new.t'
rm new.t
exec_test 'exit 42'
exec_test 'exit 42 53 68'
exec_test 'exit 259'
exec_test 'exit 9223372036854775807'
exec_test 'exit -9223372036854775808'
exec_test 'exit 9223372036854775808'
exec_test 'exit -9223372036854775810'
exec_test 'exit -4'
exec_test 'exit wrong'
exec_test 'exit wrong_command'

exec_test 'gdagadgag'
exec_test 'ls -Z'
exec_test 'cd gdhahahad'
exec_test 'ls -la | wtf'

exec_test 'env | grep -e OLDPWD'
exec_test 'env | grep -e PWD'
exec_test 'cd /Users/sbrenton/Documents/Study/minish/ ; pwd'
exec_test 'env | grep -e OLDPWD'
exec_test 'env | grep -e PWD'
exec_test 'cd ./parser ; pwd'
exec_test 'cd /Users/sbrenton/Documents/Study/minish/parser/ ; pWd'

exec_test 'cd ./bad | pwd'
exec_test 'cd bla ..'
exec_test 'cd . ; pwd'
exec_test 'cd .. ; pwd'
exec_test 'CD ; pwd'
exec_test 'cd ; pwd'
exec_test 'pwd'
exec_test 'PWD'
exec_test 'export g7 hj k9'
exec_test 'export g7 hj k9'
exec_test 'export hh=jjj'
exec_test 'env | grep -e hh'
exec_test 'cd /Users/sbrenton/Documents/Study/tester/ | pwd'
exec_test 'cd .. ; pwd'
exec_test 'cd /Users ; pwd'
exec_test 'cd ; pwd'
exec_test 'mkdir test_dir ; cd test_dir ; rm -rf ../test_dir ; cd . ; pwd ; cd . ; pwd ; cd .. ; pwd'

exec_test 'echo "in test" > txt.txt | echo  "in test" < txt.txt'
exec_test 'echo "in test" > txt.txt | echo < txt.txt'
exec_test 'echo "in test" >> txt.txt ; echo < txt.txt'
exec_test 'echo "in test" > txt.txt | echo  "in test" < txt.txt'
exec_test 'echo pwd >> txt.txt ; echo < txt.txt'
rm txt.txt
exec_test 'pwd > txt.txt | echo < txt.txt'
rm txt.txt
exec_test 'echo test > ls ; cat ls'
exec_test 'echo test > ls >> ls >> ls ; echo test >> ls; cat ls'
exec_test 'cat < ls'
exec_test 'cat < ls > ls'
exec_test '> lol echo test lol; cat lol'
exec_test '>lol echo > test>lol>test>>lol>test mdr >lol test >test; cat test'
exec_test 'echo testing multi ; echo "test 1 ; | and 2" ; cat tests/lorem.txt | grep Lorem'

# exec_test 'unset 11'
# exec_test 'export var=42 ; echo $var'
# exec_test 'pwd ; export bu=haha 11 ; echo $1bu$haha'
# exec_test 'unset var bu'
# exec_test 'ls | echo $bu$var$\l$? | export var=21 | echo $var'

# ENV_SHOW="env | sort | grep -v SHLVL | grep -v _="
# EXPORT_SHOW="export | sort | grep -v SHLVL | grep -v _= | grep -v OLDPWD"
# exec_test 'export ='
# exec_test 'export 1TEST= ;' $ENV_SHOW
# exec_test 'unset HOME ;' $ENV_SHOW
# exec_test 'export ""="" ; ' $ENV_SHOW
# exec_test 'export TES=T="" ;' $ENV_SHOW
# exec_test 'export TE+S=T="" ;' $ENV_SHOW
# exec_test 'export TEST=LOL ; echo $TEST ;' $ENV_SHOW
# exec_test 'export TEST=LOL ; echo $TEST$TEST$TEST=lol$TEST'
# exec_test $ENV_SHOW
# exec_test $EXPORT_SHOW
# exec_test 'export TEST="ls       -l     - a" ; echo $TEST ; $LS ; ' $ENV_SHOW

## порядок не понятен, поэтому сравнение не получается (  Вопросы надо ли править
#exec_test 'ENV'
#exec_test 'env'
#exec_test 'env > txt.txt ; echo < txt.txt'
#rm txt.txt


#exec_test 'export'


echo ==============================================
echo $ok / $all