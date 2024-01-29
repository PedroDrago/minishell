# minishell
Oh shit, where we go. MiniHell do Rafael e do Drago.

# Proposta de Colaboração
Eu acho que a melhor forma de fazermos as coisas seria cada um trabalhar em uma Branch separada, e ambos fazerem Pull Request. Eu adicionei uma proteção na mainbranch que pra dar merge 1 pessoa que não for o autor do código precisa aprovar o PR, adicionei mais pra ir testando essas configs e ir aprendendo do que qualquer outra coisa, se você preferir da pra desligar de boa.

Ai o workflow seria:
1. Criar branch
2. Desenvolver + commitar
3. Dar push
4. Abrir Pull Request
5. Fazermos Code Review
6. Merge

# To-do
- [ ] Prompt
- [ ] History
- [ ] `$PATH` for executing right executables
- [ ] Don't interpret unclosed quotes or special characters (`\` or `;`)
- [ ] Redirects (`<`,`>`,`<<`,`>>`)
- [ ] Pipes (`|`)
- [ ] Environment Variables
- [ ] Single Quotes `'`
- [ ] Double Quotes `"`
- [ ] ctrl-C, ctrl-D and ctrl-\
- [ ] `echo` with `-n`
- [ ] `cd` with **relative** or **absolute** path
- [ ] `pwd`
- [ ] `export`
- [ ] `unset`
- [ ] `env`
- [ ] `exit`

# Estrutura de pastas 
Eu sugiro uma pasta `src` para todos os arquivos `.c`, uma pasta `includes` para todos os arquivos `.h` e uma pasta `bin` para todos os binários (acredito que cada comando tipo `pwd`, `cd` etc vamos ter que fazer um binário pra ele).

# Functions
- `readline(const char *prompt)`: Literalmente mostra o prompt e lê o que o usuario digita, e retorna isso como uma string. (tem que adicionar `-lreadline` na compilação)
- `rl_clear_history()`: ?
- `rl_on_new_line()`: ?
- `rl_replace_line(const char *text, int clear_undo)`: ?
- `rl_redisplay()`: ?
- `add_history(const char *string)`: ?
- `access(const char *name, int type)`: ?
- `open(const char *file, int oflag, ...)`: ?
- `fork()`: ?
- `wait(int *stat_loc)`: ?
- `wait3(int *stat_loc, int options, struct rusage *usage)`: ?
- `wait4(__pid_t pid, int *stat_loc, int options, struct rusage *usage)`: ?
- `waitpid(__pid_t pid, int *stat_loc, int options)`: ?
- `sigemptyset(sigset_t *set)`: ?
- `sigaddset(sigset_t *set, int signo)`: ?
- `getcwd(char *buf, size_t size)`: Pega o path atual que o programa ta rodando, tipo rodar um `pwd`. A função guarda o path no `buffer` que tem tamanho `size`.Buff e size são argumentos semelhantes aos de `read()`.
- `chdir(const char *path)`: Semelhante a um `cd`, na real é igual, a gente passa um path (absoluto ou relativo) e o programa passa a estar rodando nesse path.
- `stat(const char *restrict file, struct stat *restrict buf)`: ?
- `lstat(const char *restrict file, struct stat *restrict buf)`: ?
- `fstat(int fd, struct stat *buf)`: ?
- `unlink(const char *name)`: ?
- `execve(const char *path, char *const *argv, char *const *envp)`: ?
- `dup(int fd)`: ?
- `dup2(int fd, int fd2)`: ?
- `pipe(int *pipedes)`: ?
- `isatty(int fd)`: ?
- `ttyname(int fd)`: ?
- `ttyslot()`: ?
- `ioctl(int fd, unsigned long request, ...)`: ?
- `getenv(const char *name)`: ?
- `tcsetattr(int fd, int optional_actions, const struct termios *termios_p)`: ?
- `tcgetattr(int fd, struct termios *termios_p)`: ?
- `tgetent(char *bp, const char *name)`: ?
- `tgetflag(const char *id)`: ?
- `tgetnum(const char *id)`: ?
- `tgetstr(const char *id, char **area)`: ?
- `tgoto(const char *cap, int col, int row)`: ?
- `tputs(const char *str, int affcnt, int (*putc)(int))`: ?
