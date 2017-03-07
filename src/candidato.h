/*****************************************************************************

						Vota Fácil! - Eleições 2012
				  Projeto Final - Técnicas de Programação
		
******************************************************************************

	Projeto Final - Técnicas de Progmração
	Copyright © 2011  Lenilson Lima & Wilk Maia
	Licensed under GNU GPL
	
	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
	
	Contact:
		Lenilson Lima - l.lima94@hotmail.com
		Wilk Maia - wilkmaia@gmail.com

******************************************************************************

	Este arquivo contém informações genéricas sobre os candidatos e declaração
	de funções relativas àqueles.
	
******************************************************************************/


#ifndef _CANDIDATO_H_
#define _CANDIDATO_H_

#include "mainHeader.h"

// Variável global que armazena o código do próximo candidato a ser cadastrado
static uint32 codigoCandidatoGlobal = UINT32_MIN + 1;


// Estrutura que contém as informações de histórico de eleições do candidato
typedef struct _hist
{

	uint16 ano; // Ano da eleição em questão
	uint32 votos; // Quantidade de votos obtidos pelo candidato no ano em questão
	uint8 cargo; // Cargo ao qual o Candidato concorreu - máximo de 17 caracteres
	
	struct _hist *proximo;
	struct _hist *anterior;
	
} historicoCandidato;

// Estrutura que contém as informações do candidato
typedef struct _cand
{

	uint32 codigoCandidato; // Código do Candidato - Número inteiro iniciando em 1 e limitado em UINT32_MAX (vide generalHeader.h)
	
	struct _eleit *eleitor; // Informações acerca do candidato enquanto eleitor
	
	struct {
	
		uint8 nome[51]; // Nome do partido - até 50 caracteres
		uint8 sigla[8]; // Sigla do Partido - máximo de 7 caracteres
		
		uint8 cargo; // Cargo ao qual o Candidato concorre
		// 1 - Vereador
		// 2 - Prefeito
		// 3 - Dep. Estadual
		// 4 - Dep. Federal
		// 5 - Senador
		// 6 - Governador
		// 7 - Presidente
		
	} partido;
	
	struct _hist *historico; // Ponteiro para a estrutura de histórico das eleições de cada candidato
	
	// Implementação da Lista Ligada
	struct _cand *proximo;
	struct _cand *anterior;
	
} infoCandidatos;

static infoCandidatos *candidato = NULL;
static infoCandidatos *primeiroCandidato = NULL;

// Funções que serão chamadas pelo programa em tempo de execução
infoCandidatos * cadastraCandidato();
infoCandidatos * insereCandidato( uint32 codigo, uint8 * nome, uint8 * sigla, uint8 cargo );
void removeCandidato();
void editaCandidato();

// Argumentos:
// Tipo de Ordenação, Cidade, Partido, Cargo, Estado
//
// Tipo de Ordenação:
// [1] Ordem Alfabética
// [2] Cidade
// [3] Estado
// [4] Código
// [5] Partido
// [6] Cargo
void ordenaCandidatos( uint8, uint8 *, uint8 *, uint8, uint8 * );
void listaCandidatosOrdenadamente( uint8 *, uint8 *, uint8, uint8 * );


// Imprime informações de um candidato na tela
// Argumento:
// Estrutura para candidato
void imprimeCandidato( infoCandidatos * );

// Busca um candidato a partir do código, retornando o
// ponteiro para o endereço da estrutura do candidato encontrado
// Caso não seja encontrado nenhum candidato, um ponteiro nulo é retornado
// Argumento:
// Código do Candidato
infoEleitores * buscaCandidatoPorCodigo( uint32 );

// Conversão do cargo de ID para seu Nome
// Argumento:
// Código do Cargo
// 1 - Vereador
// 2 - Prefeito
// 3 - Deputado Estadual
// 4 - Deputado Federal
// 5 - Senador
// 6 - Governador
// 7 - Presidente
uint8 * id2Cargo( uint8 );

// Função para inserção de histórico de eleição
// Argumentos:
// Ponteiro para estrutura de candidato, ano da eleição, quantidade de votos, cargo disputado
historicoCandidato * insereHistorico( infoCandidatos *, uint16, uint32, uint8 );

// Funções de uso externo
// Intuitivas

void atualizaCodigoCandidatoGlobal( uint32 );

uint32 retornaCodigoCandidatoGlobal();
bool verificaCodigoCandidatoEmUso( uint32 );

infoCandidatos * retornaPrimeiroCandidato();
infoCandidatos * retornaCandidato();

void atualizaPrimeiroCandidato( infoCandidatos * );
void atualizaCandidato( infoCandidatos * );



// Macros úteis
#define listaCandidatosGeral( A ) ordenaCandidatos( A, NULL, NULL, 0, NULL )
#define listaCandidatosCidade( A, B ) ordenaCandidatos( A, B, NULL, 0, NULL )
#define listaCandidatosPartico( A, B ) ordenaCandidatos( A, NULL, B, 0, NULL )
#define listaCandidatosCargo( A, B ) ordenaCandidatos( A, NULL, NULL, B, NULL )

#endif // _CANDIDATO_H_
