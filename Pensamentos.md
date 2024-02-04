# Pensamentos

### Parse do prompt
Cara to achando bem dificil pensar em um jeito de executar os prompts complexos (to chamando de prompt complexo qualquer prompt que vá ter pipes).
São muitos cenarios possiveis, e to tentando achar um jeito de fazer sem ficar enchendo de ifs. Tipo, o prompt pode ser:

```bash
echo "algo"
```

```bash
echo "algo" > file.txt
```

```bash
echo "algo" > file.txt | pwd
```

```bash
echo "algo" > file.txt | pwd > file2.txt
```

```bash
echo "algo" | env > file.txt | cd bin | echo "novamente" >> file | export VAR=test > file3.txt
```

São muitos cenários, tratar com muitos ifs não deve ser a maneira correta. Temos que pensar de um jeito de ir lendo o prompt e ir executando de forma
inteligente, mas parece bem dificil. Mas acho que o ideal seria algo como primeiro identificar se vai ser um comando simples (unico) ou complexo (com pipes),
e ai tratar.

Pro caso de comandos complexos, acho que o caminho é separar `lado esquerdo` e `lado direito`, pois ambos os lados podem ser comandos com OU sem argumentos, e
com OU sem redirections. E ai ir em um looping resolvendo cada lado direto/lado esquerdo, ai um `lado_esquerdo | lado_direito` vai virando o lado esquerdo
do proximo pipe, sacou? Acho que entender a pipex do azevedo vai ajudar bastante.

Acho que só depois de ter resolvido esse problemasso que deveriamos partir pra implementar as features do minishell (que sinceramente parecem ser o mais trivial do projeto).

### Path
To pensanso sobre o que o subject diz sobre ter a variavel PATH. Ele quer dizer que temos que ter o PATH do nosso minishell, né? Ou seja, no `env` teriamos
que ter uma variável `PATH=...`, mas to pensando em como fazear isso. Pq o path teria que ser absoluto, e funcionar em qualquer maquina ne? Teriamos que
pegar a informação de onde o minishell foi clonado? Acho que nem da pra fazer isso. Ou temos que assumir que o path vai ser sempre algo como `/home/pdrago/minishell/bin`?
Dificil...


