# To-do

- [ ] Remove unused headers
- [ ] heredoc do bash expande variaveis, vamos fazer isso no nosso? (N pede explicitamente na ficha)
- [ ] Norm
- [ ] valgrind
- [ ] `unset PWD` da merda por causa do prompt bonito. Mas pelo que investiguei é pq dentro de `cd` quando atualizamos PWD, usamos a referencia de uma variavel que deps toma free, e ai fode tudo. So que se a gnt dupar vai leakar. Eu ainda n entendo mto bem quando que nossos values de env sao dupados e quando n sao.

# Baseado na ficha de avaliacao
- [ ] `Check if multiple tries of the same redirections fail.` acredito que nosso comportamento se enquadre nisso. Mas, talvez valha conversarmos sobre o que isso quer dizer.
- [ ] `Check that $ is interpreted as an environment variable.` Não entendi muito bem.
