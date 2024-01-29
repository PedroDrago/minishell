# minishell
Oh shit, where we go. MiniHell do Rafael e do Drago.

version: 7.1
# Proposta de Colaboração
Eu acho que a melhor forma de fazermos as coisas seria cada um trabalhar em uma Branch separada, e ambos fazerem Pull Request. Eu adicionei uma proteção na mainbranch que pra dar merge 1 pessoa que não for o autor do código precisa aprovar o PR, adicionei mais pra ir testando essas configs e ir aprendendo do que qualquer outra coisa, se você preferir da pra desligar de boa.

Ai o workflow seria:
1. Criar branch
2. Desenvolver + commitar
3. Dar push
4. Abrir Pull Request
5. Fazermos Code Review
6. Merge

# Estrutura de pastas 
Eu sugiro uma pasta `src` para todos os arquivos `.c`, uma pasta `includes` para todos os arquivos `.h` e uma pasta `bin` para todos os binários (acredito que cada comando tipo `pwd`, `cd` etc vamos ter que fazer um binário pra ele).

OBS: Adicionei minha libft no projeto ja, mas se preferir a sua n tem prob tb. Tenho na minha libft algumas estruturas de dados que fiz num tempo livre (linked list, fila, pilha, hashmap) mas seguem meu tipo de implementação que tem structs separadas pra Node e Fila/Pilha/Fila.

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
