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

	Este arquivo contém informações genéricas sobre os eleitores e declaração
	de funções relativas àqueles.
	
******************************************************************************/


#ifndef _ELEITOR_H_
#define _ELEITOR_H_

#include "mainHeader.h"

// Variável global que armazena o título do próximo eleitor a ser cadastrado
static uint32 tituloEleitorGlobal = UINT32_MIN + 1;

// Estrutura que contém as informações dos eleitores
typedef struct _eleit
{
	
	uint32 tituloEleitor; // Código do Eleitor - Número inteiro iniciando em 1 e limitado em UINT32_MAX (vide generalHeader.h)
	
	// Informações pessoais do Eleitor
	struct {
	
		uint8 nomeCompleto[101]; // Nome completo do Candidato/Eleitor - máximo de 100 caracteres
		uint8 cidade[31]; // Nome da cidade do Candidato/Eleitor - até 30 caracteres
		uint8 estado[20]; // Nome do estado do Candidato/Eleitor - até 19 caracteres
		uint8 dataNascimento[11]; // Data de nascimento do Candidato/Eleitor - Máscara -> "XX/XX/XXXX"
		
	} pessoal;
	
	// O eleitor é, também, candidato?
	// Em caso afirmativo, este ponteiro contém o endereço de memória da estrutura que contém as informações do candidato.
	// Em caso negativo, contém uma referência nula (NULL).
	struct _cand *eleitorCandidato;
	
	// Implementação da Lista Ligada
	struct _eleit *proximo;
	struct _eleit *anterior;
	
} infoEleitores;

static infoEleitores *eleitor = NULL;
static infoEleitores *primeiroEleitor = NULL;

// Funções que serão chamadas pelo programa em tempo de execução
// Intuitivas
infoEleitores * cadastraEleitor();

// Argumentos: nome, cidade, estado, nascimento, título
infoEleitores * insereEleitor( string, string, string, string, uint32 );
void removeEleitor();
void editaEleitor();

//Argumentos:
uint32 * eleitorVota( infoEleitores *, uint8 );

// Argumentos:
// Tipo de Ordenação, Cidade, Estado
//
// Tipo de Ordenação:
// [1] Ordem Alfabética
// [2] Cidade
// [3] Estado
// [4] Código
void ordenaEleitores( uint8, uint8 *, uint8 * );
void listaEleitoresOrdenadamente( uint8 *, uint8 * ); // cidade, estado

// Funções de acesso a arquivos em disco
void saveBackUpPessoal();
void loadBackUpPessoal();

// Imprime informações de um eleitor na tela
void imprimeEleitor( infoEleitores * );

// buscaPorNome
// Retorno: void
// Parâmetros: Ponteiro para (uint8) -- string
void buscaPorNome( string );

infoEleitores * buscaEleitorPorCodigo( uint32 );

// Limpa a memória antes de finalizar o programa
void limpaMemoria();

// Funções de acesso externo
// Intuitivas
infoEleitores * retornaPrimeiroEleitor();

void atualizaPrimeiroEleitor( infoEleitores * );
void atualizaEleitor( infoEleitores * );

uint32 retornaTituloEleitorGlobal();

infoEleitores * retornaPrimeiroEleitor();
infoEleitores * retornaEleitor();



// Macros úteis
#define listaEleitoresGeral( A ) ordenaEleitores( A, NULL, NULL )
#define listaEleitoresCidade( A, B ) ordenaEleitores( A, B, NULL )
#define listaEleitoresEstado( A, B ) ordenaEleitores( A, NULL, B )

#define eleitorVotaMunicipal( A ) eleitorVota ( (A), 0 )
#define eleitorVotaNaoMunicipal( A ) eleitorVota ( (A), 1 )

#endif // _ELEITOR_H_
