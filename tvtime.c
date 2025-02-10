#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// TV Time
// O usuário pode fazer as seguintes funcionalidades:
// 1) Cadastro e Login: Os dados requisitados para o usuário devem ser pelo
// menos um login e uma senha, mas podem ser requisitadas outras
// informações adicionais. Ex:
// Cadastro:
// Login: rafaelivo
// Senha: *****
// Nome: Rafael
// 2) Cadastro de filmes: Um usuário especial (administrador) pode cadastrar filmes novos. Cada filme deve conter
// diversas informações, mas o mínimo deve ser: nome, tempo de duração, gênero. Ex:
// Cadastro de filme:
// Nome: The Matrix
// Duração: 2:16
// Gênero: Ficcção científica
// Ano de lançamento: 1999
// 3) Assistiu filme: Um usuário comum pode inserir que assistiu um dos filmes cadastrado na aplicação. Ex:
// Eu assisti o filme:
// Nome: Esqueceram de Mim
// Onde: Netflix
// Quando: 25/12/2024
// 4) Listar meus filmes assistidos: Um usuário comum pode exibir todos os filmes que ele cadastrou. Ex:
// Filmes que assisti:
// Esqueceram de Mim (Ano de lançamento: 1990, Duração: 1h43min, Assistido: 25/12/2024 em Netflix)
// Homem de Ferro (Ano de lançamento: 2008, Duração: 2h6min, Assistido: 25/01/2025 em Disney+)
// The Matrix (Ano de lançamento: 1999, Duração: 2h16min, Assistido: 01/02/2025 em HBO Max)
// 5) Estatísticas: O usuário pode visualizar estatísticas sobre os filmes que assistiu. Uma delas deve ser o tempo total dos
// filmes assistidos