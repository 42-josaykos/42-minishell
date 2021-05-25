# 42-minishell

42 cursus project: Write a simple shell like bash. Learning about process and file descriptors

## TODO:

- piped commands exit_codes + redir exit_codes
- `export something` without key=value pair should do nothing
- error syntax when just pipe symbol
- handle export without args + export whithout value
- `echo '\'`
- `echo "hello\newline"`
- `export VARIABLE=value; echo VARIABLE`
- `echo "a\\ \ b c\" \'$SHELL\'"`
- fix has_syntax_error function
- `export TEST="ls -l | cat -e"`

- handle SIGINT and SIGTERM in parse_cmdline(). Test: `pwd; find /; date`
- disable raw_mode when parsing
- improve signal handler printing characters + g_sig.sigint flag is missing
- `./file_that_is_not_an_executable`
- `echo bonjour >>> test`
- unset exit codes `unset "" test`
