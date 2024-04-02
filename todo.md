# To-do

- [ ] Error handling whole project!!!
    - [ ] stderror buffer.
- [ ] Leaks /  valgrind errors in every scenario
- [ ] Malloc erros
- [ ] Testar mais a fundo heredoc e input redirection
- [ ] Remove unused headers
- [ ] Norm
- [ ] Não pode terminar com tokens (exceto pipe | )
- [ ] Não pode ter dois tokens seguidos

# POS REVOLUCION
- [ ] Dar free na porra toda que precisa.
- [ ] Expandir variavies de ambiente (e remover aspas tb, alem de tambem expandir no heredoc).
- [ ] rever sistema de signals.
- [ ] Remover tudo da logica antiga (funcoes não utilizadas, campos de structs, etc)
- [ ] Double prompt quando da ctrl+c em um comando como cat, grep etc. Isso se da por conta dos multiplos waits acredito eu. Quando recebermos ctrl+c temos que dar kill em todos os pids filhos.
