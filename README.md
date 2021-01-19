# 42-minishell

42 cursus project: Write a simple shell like bash. Learning about process and file descriptors

## TODO:

- [x] PATH variable. Non-buitlin commands should be execute through the PATH

- [ ] builtin command `echo`, with -n option
- [x] builtin command `cd`, only with absolute or relative path
- [x] builtin command `pwd`, with no options
- [ ] builtin command `export`, with nooptions
- [ ] builtin command `unset`, with no options
- [ ] builtin command `env`, with no args nor options
- [x] builtin command `exit`, with no options

- [x] function to parse the commands
- [x] function to parse the args and/or options of the command
- [x] function to execute the right command with the options

- [ ] `;` implementation, multicommands separator
- [ ] `'` implementation
- [ ] `"` implementation

to be continued...

## Notes:

- Should handle backslash inside double quotes `"\\"` (escaping character).
- Handle `cd ~`, `cd -` and `cd /`, with absolute path from root `cd /home/user`
