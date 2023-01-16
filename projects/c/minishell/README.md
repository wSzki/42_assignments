



# MINISHELL

## Authorized functions
```
| ---         | ---              | ---            | ---             | ---          |
| readline    | rl_clear_history | rl_on_new_line | rl_replace_line | rl_redisplay |
| add_history | printf           |                |                 |              |
| malloc      | free             |                |                 |              |
| write       | open             | read           | close           |              |
| fork        | wait             | waitpid        | wait3           | wait4        |
| isatty      | ttyname          | ttyslot        | ioctl           | getenv       |
| signal      | kill             | exit           |                 |              |
| getcwd      | chdir            | stat           | lstat           | fstat        |
| unlink      | execve           | dup            | dup2            | pipe         |
| opendir     | readdir          | closedir       | strerror        | perror       |
| tcsetattr   | tcgetattr        | tgetent        | tgetflag        | tgetnum      |
| tgetstr     | tgoto            | tputs          |                 |              |
```
## Builtins

> With opitons
echo with option -n
cd with only relative or absolute path

> Without options
pwd
export
unset
env
exit

## Redirections
```

'<' should redirect input.`
'>' should redirect output.
'<<' read input from the current source until a line containing only the de-limiter is seen. it doesn’t need to update history!
'>>' should redirect output with append mode.

```
## Misc
```

• Not interpret unclosed quotes or unspecified special characters like \ or ;.
• Not use more than one global variable, think about it and be ready to explain why you do it.
• Show a prompt when waiting for a new command.
• Have a working History.
• ’ inhibit all interpretation of a sequence of characters.
• " inhibit all interpretation of a sequence of characters except for $.
• Pipes | The output of each command in the pipeline is connected via a pipe to the input of the next command.
• Environment variables ($ followed by characters) should expand to their values.
• $? should expand to the exit status of the most recently executed foreground pipeline.
• ctrl-C ctrl-D ctrl-\ should work like in bash.

• When interactive:
◦ ctrl-C print a new prompt on a newline.
◦ ctrl-D exit the shell.
◦ ctrl-\ do nothing.

```
## Reserved words
```
+-------+----------+------+
| while | until    | time |
+-------+----------+------+
| then  | select   | in   |
+-------+----------+------+
| if    | function | for  |
+-------+----------+------+
| fi    | esac     | else |
+-------+----------+------+
| elif  | done     | Do   |
+-------+----------+------+
| case  | ]]       | [[   |
+-------+----------+------+
|       | !        |      |
+-------+----------+------+
```
