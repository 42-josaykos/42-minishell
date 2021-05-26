# 42-minishell

42 cursus project: Write a simple shell like bash. Learning about process and file descriptors

## TODO:

- ~~piped commands exit_codes + redir exit_codes~~
- ~~`export something` without key=value pair should do nothing~~
- ~~error syntax when just pipe symbol~~
- ~~handle export without args + export whithout value~~
- `echo '\'`
- `echo "hello\newline"`
- `export VARIABLE=value; echo VARIABLE`
- `echo "a\\ \ b c\" \'$SHELL\'"`
- fix has_syntax_error function
- `export TEST="ls -l | cat -e"`

- handle SIGINT and SIGTERM in parse_cmdline(). Test: `pwd; find /; date`
- ~~disable raw_mode when parsing~~
- ~~improve signal handler printing characters + g_sig.sigint flag is missing~~
- unset exit codes `unset "" test`

25/05:

- `echo bonjour >>> test`
- executable with absolut and relative path: `cd srcs/` and `../minishell` --> parsing/parse_path.c/is_exec_path()
- handle error 126 when not an executable: `./srcs` utils/error.c
- handle cd with nultiples env args: `cd $HOME/42cursus` --> parsing/interpreter.c/handle_variables()
- `export $VAR=value`

```bash
bash-5.1$ env | grep HELLO
HELLO=bonjour
bash-5.1$ export $HELLO=test
bash-5.1$ env | grep HELLO
HELLO=bonjour
bash-5.1$ env | grep bonjour
bonjour=test
HELLO=bonjour
```

- error message `export $VAR=value` if VAR doesn't exist in env
- `export "" test=a`
- `export test="ab[whitespaces]cd[whitespaces]ef"` --> `echo $test` --> test="ab cd ef"
- ~~`.` --> exit code 2~~
- ~~`..` --> exit code 127~~
- `echo "bip | bip ; coyotte > < \" "`
- `echo $USER$var\$USER$USER\$USERtest$USER`
- ~~`cat Makefile | grep pr | head -n 5 | cd file_not_exit` --> exit code in pipes~~
- ~~`ls | exit`~~
- ~~`pwd ; sleep 10 ; date` --> exit code~~
