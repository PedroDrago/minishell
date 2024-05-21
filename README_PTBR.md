# Minishell

<p align="center">
    <img src="./assets/printscreen.png"/>
</p>

<p align="center"> Este projeto foi sobre criar nosso próprio shell em C, inspirado no Bash.</p>

---
<p align="center">
    <img src="./assets/printscreen2.png"/>
</p>

<h3 align="center">Sobre a nossa Jornada</h3>
Este projeto foi, sem dúvida, o empreendimento mais desafiador e maior que realizamos até agora no 42 Common Core. Abordamos esta tarefa do nosso próprio jeito: sem nenhum tipo de guia. Portanto, a resolução que você observa em nosso código reflete as batalhas que nossas mentes travaram contra os inúmeros problemas encontrados ao longo de nossa jornada. No final, o produto é um shell bastante bom, embora com um código que não seja tão bom assim.

---
### Terminal VS Shell VS Prompt
Entender a diferença entre esses três softwares diferentes é crucial:

- Terminal: O nome correto seria Emulador de Terminal, já que um terminal real era uma máquina física dedicada a acessar recursos de um mainframe e atua como uma interface para os usuários trabalharem com esses recursos. Então, o emulador de terminal é o software que usamos para emular esse comportamento em computadores modernos. Basicamente, o emulador de terminal é o aplicativo gráfico que executa o shell. Alguns exemplos são Gnome Terminal, Alacritty, Terminator, etc.

- Shell: Shell é um interpretador de comandos que permite ao usuário instruir o kernel a realizar tarefas como listar arquivos no diretório de trabalho atual, criar um arquivo, alterar permissões de arquivos e todas as outras ações que o kernel permite que os usuários realizem. Alguns exemplos de shells são Bash, Zsh, Fish, PowerShell, etc.

- Prompt: O prompt é o comando que você fornece ao shell para interpretação. `$ ls | grep a` é um exemplo de um prompt no Bash.

### Processes
Quando um programa é executado no Linux, ele pode ser chamado de processo, e os processos vêm com vários atributos, como permissões, um PID (Identificador de Processo), uma tabela de descritores de arquivo e outros dados. Então, quando você executa `$ ls` no seu shell, o que realmente está acontecendo é que o kernel está executando um binário localizado no **PATH** do seu sistema como um processo.

Os processos podem criar outros processos; isso é chamado de fork (`man fork`). Os processos podem ser referidos como Processo Pai (para o processo que está gerando outro processo) e Processo Filho (para o processo que foi gerado). A execução de um processo filho começa no mesmo momento em que a chamada de sistema `fork()` é chamada.
```c
int main()
{
    int pid;

    pid = fork();
    if (pid == 0)
    {
        printf("Processo Filho: %i\n", getpid());
        exit(1);
    }
    else
    {
        printf("Processo Pai: %i\n", getpid());
        exit(0);
    }
}
```

O exemplo acima demonstra a ramificação que o `fork()` causa, pois há dois blocos de código diferentes no mesmo programa, mas cada processo executa apenas um deles.

### ENV
Env pode ser descrito como a coleção de variáveis de ambiente que o sistema possui ou como o comando de shell `man env`. Vamos focar no primeiro conceito:

Sistemas Unix mantêm variáveis úteis que todo programa executado pode acessar através de um parâmetro chamado `envp`, localizado na função principal (`int main(int argc, char *argv[], char *envp[])`). Existem variáveis como o nome de usuário atual, o diretório home do usuário atual, etc. Você pode verificar a lista atual de variáveis de ambiente com o comando `env`, adicionar novas variáveis de ambiente com o comando `export` e deletar variáveis de ambiente existentes com o comando `unset`.
### PATH
Antes de entendermos o conceito de Path, precisamos entender como programas e comandos são executados no Linux. Se você navegar para os diretórios `/bin` ou `/usr/bin`, verá que há muitos executáveis dentro desses diretórios, como `ls`, `echo`, `pwd` e outros comandos que você provavelmente conhece. Quando você digita `ls` no shell, ele procurará em alguns diretórios preselecionados por um binário executável chamado `ls`. Nesse caso, `/bin/ls` ou `/usr/bin/ls` seriam procurados, e quando o shell o encontrar, ele será executado.

O `$PATH` é a variável de ambiente que contém os diretórios preselecionados que o sistema procurará por executáveis para você. É uma variável de ambiente como as outras, onde você pode mudar seu valor ou até mesmo deletá-la (experimente, não tenha medo; quando você reiniciar seu shell, a variável PATH será criada novamente).
### Pipe
Um pipe em um shell ocorre quando você instrui um comando a ler a saída de outro comando: `ls | grep x`. Aqui, o comando `ls` exibe todos os arquivos no diretório atual, então `grep x` lê essa saída e imprime na tela apenas as linhas que contêm a letra `x`.

Nota: Você pode usar pipe em quantos comandos quiser em uma pipeline. Apenas tenha em mente que nem todos os comandos leem a entrada; alguns deles apenas recebem argumentos de linha de comando, como `echo`.

Em C, podemos usar a chamada de sistema `pipe()` para recriar esse comportamento, mas não é tão simples quanto `pipe(comando1, comando2)`. A única coisa que essa função faz é receber um array de inteiros de tamanho 2 (`int arr[2]`) e então criar dois descritores de arquivo conectados: um para leitura (que será colocado no índice `0` do array) e um para escrita (que será colocado no índice `1` do array). É isso.

```c
int main()
{
    int pipe_fd[2];
    char buff[19];

    pipe(pipe_fd);
    write(pipe_fd[1], "Escrevendo uma Mensagem\n", 19);
    read(pipe_fd[0], buff, 19);
    printf("%s\n", buff);
}
```
O exemplo acima não é um código útil, mas pode demonstrar o que a função `pipe()` está realmente fazendo. Criamos nosso array com pipe, escrevemos uma string no índice `1` e depois lemos do índice `0`. O uso real dessa função pode ser alcançado quando a combinamos com `dup2()`, que nos permite substituir um descritor de arquivo padrão de um processo por um descritor de arquivo do pipe que criamos. Esse não é o único uso, mas é o que você verá com mais frequência em um projeto como um shell.

```c
int main()
{
    int pipe_fd[2];
    char buff[49];
    int pid;

    pipe(pipe_fd);
    pid = fork();
    if (pid == 0)
    {
        dup2(pipe_fd[1], 1);
        printf("Message being written to this process new STDOUT");
        exit(0);
    }
    else
    {
        waitpid(pid, NULL, 0);
        read(pipe_fd[0], buff, 49);
        printf("%s\n", buff);
    }

}
```

### Minishell Project
Aqui estão algumas recomendações para o projeto Minishell:

1. Estude como montar corretamente um Lexer, Parser e Executor. (Não fizemos isso, e o tempo perdido não pode ser medido.)
2. Entenda muito bem o que acontece com os descritores de arquivo quando um processo é bifurcado (descritores de arquivo criados por `pipe()` e os descritores de arquivo padrão). Experimente bastante com `dup()`, `dup2()`, e `pipe()`.
3. Compreenda muito bem como funcionam os recursos do bash antes de começar a implementá-los. Provavelmente, você não conhece detalhes importantes sobre heredocs, redirecionamentos, pipes, comandos internos, etc. Tentar implementar esses detalhes no meio de uma lógica antiga será difícil. (Sabemos disso porque fizemos isso.)
4. Você não precisa fazer uma cópia perfeita do bash. Tentamos o nosso melhor para fazer isso, e novamente, o tempo perdido não pode ser medido. Foque no assunto e pense em como defender suas escolhas de design (mas tente pelo menos nunca ter um segfault).
5. Aprenda sobre arquivos de supressão do Valgrind.
