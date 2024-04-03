# To-do

- [ ] Norm
- [ ] Dar free na porra toda que precisa.
- [ ] Expandir variaveis no heredoc.
- [ ] rever sistema de signals.
- [ ] Double prompt quando da ctrl+c em um comando como cat, grep etc. Isso se da por conta dos multiplos waits acredito eu. Quando recebermos ctrl+c temos que dar kill em todos os pids filhos??? seila.
- [ ] Remove unused headers
- [ ] Saida do shell esta problematica, tanto com exit quanto com `CTRL+d`. Segfaults em alguns cenarios.
- [ ] Talvez refazer todas as funcoes/structs de processos/pids, ta muito confuso (remover comando da mensagem de erro simplificaria muito esse processo)
- [ ] Segfault: builtin rediectionado para arquivo e pipe depois: `pwd > arquivo.txt | wc`
- [ ] local exec
