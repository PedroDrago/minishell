# To-do

- [ ] Remove unused headers
- [ ] heredoc do bash expande variaveis, vamos fazer isso no nosso? (N pede explicitamente na ficha)
- [ ] Norm
- [ ] valgrind
- [ ] Tem alguma merda dando com o unset. Tipo, a merda da com o prompt bonitinho, se a gnt da `unset` em PWD da ruim e tal, mas tipo, eu acho que tem coisa errada com nosso env. Eu
sinto que a gnt ta usando de forma inconsistente, em alguns lugares a gente dupa, em outros não, e isso da uma cagada de double free e/ou leak dependendo. a gente precisa rever toda logica de export e unset, pra deixar mais consistente. Ou parar de usar a string no prompt, mas acho que isso da mo charme legal pro nosso projeto.

# Baseado na ficha de avaliacao
- [ ] `Check if multiple tries of the same redirections fail.` acredito que nosso comportamento se enquadre nisso. Mas, talvez valha conversarmos sobre o que isso quer dizer.
- [ ] `Check that $ is interpreted as an environment variable.` Não entendi muito bem.
