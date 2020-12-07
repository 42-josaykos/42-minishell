# 42-minishell
42 cursus project: Write a simple shell like bash. Learning about process and file descriptors

## TODO:

- [ ] PATH variable. Buitlin commands should be execute through the PATH

- [ ] builtin command `echo`, with -n option
- [ ] builtin command `cd`, only with absolute or relative path
- [x] builtin command `pwd`, with no options
- [ ] builtin command `export`, with nooptions
- [ ] builtin command `unset`, with no options
- [ ] builtin command `env`, with no args nor options
- [ ] builtin command `exit`, with no options

- [ ] function to parse the commands
- [ ] function to parse the args and/or options of the command
- [ ] function to execute the right command with the options

- [ ] `;` implementation, multicommands separator
- [ ] `'` implementation
- [ ] `"` implementation

to be continued...

## Notes:

- A function to execute commands: the function should look in the PATH and 
execute the right executable.
>>>>>>> main
