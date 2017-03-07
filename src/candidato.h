/*****************************************************************************

						Vota F�cil! - Elei��es 2012
				  Projeto Final - T�cnicas de Programa��o
		
******************************************************************************

	Projeto Final - T�cnicas de Progmra��o
	Copyright � 2011  Lenilson Lima & Wilk Maia
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

	Este arquivo cont�m informa��es gen�ricas sobre os candidatos e declara��o
	de fun��es relativas �queles.
	
******************************************************************************/


#ifndef _CANDIDATO_H_
#define _CANDIDATO_H_

#include "mainHeader.h"

// Vari�vel global que armazena o c�digo do pr�ximo candidato a ser cadastrado
static uint32 codigoCandidatoGlobal = UINT32_MIN + 1;


// Estrutura que cont�m as informa��es de hist�rico de elei��es do candidato
typedef struct _hist
{

	uint16 ano; // Ano da elei��o em quest�o
	uint32 votos; // Quantidade de votos obtidos pelo candidato no ano em quest�o
	uint8 cargo; // Cargo ao qual o Candidato concorreu - m�ximo de 17 caracteres
	
	struct _hist *proximo;
	struct _hist *anterior;
	
} historicoCandidato;

// Estrutura que cont�m as informa��es do candidato
typedef struct _cand
{

	uint32 codigoCandidato; // C�digo do Candidato - N�mero inteiro iniciando em 1 e limitado em UINT32_MAX (vide generalHeader.h)
	
	struct _eleit *eleitor; // Informa��es acerca do candidato enquanto eleitor
	
	struct {
	
		uint8 nome[51]; // Nome do partido - at� 50 caracteres
		uint8 sigla[8]; // Sigla do Partido - m�ximo de 7 caracteres
		
		uint8 cargo; // Cargo ao qual o Candidato concorre
		// 1 - Vereador
		// 2 - Prefeito
		// 3 - Dep. Estadual
		// 4 - Dep. Federal
		// 5 - Senador
		// 6 - Governador
		// 7 - Presidente
		
	} partido;
	
	struct _hist *historico; // Ponteiro para a estrutura de hist�rico das elei��es de cada candidato
	
	// Implementa��o da Lista Ligada
	struct _cand *proximo;
	struct _cand *anterior;
	
} infoCandidatos;

static infoCandidatos *candidato = NULL;
static infoCandidatos *primeiroCandidato = NULL;

// Fun��es que ser�o chamadas pelo programa em tempo de execu��o
infoCandidatos * cadastraCandidato();
infoCandidatos * insereCandidato( uint32 codigo, uint8 * nome, uint8 * sigla, uint8 cargo );
void removeCandidato();
void editaCandidato();

// Argumentos:
// Tipo de Ordena��o, Cidade, Partido, Cargo, Estado
//
// Tipo de Ordena��o:
// [1] Ordem Alfab�tica
// [2] Cidade
// [3] Estado
// [4] C�digo
// [5] Partido
// [6] Cargo
void ordenaCandidatos( uint8, uint8 *, uint8 *, uint8, uint8 * );
void listaCandidatosOrdenadamente( uint8 *, uint8 *, uint8, uint8 * );


// Imprime informa��es de um candidato na tela
// Argumento:
// Estrutura para candidato
void imprimeCandidato( infoCandidatos * );

// Busca um candidato a partir do c�digo, retornando o
// ponteiro para o endere�o da estrutura do candidato encontrado
// Caso n�o seja encontrado nenhum candidato, um ponteiro nulo � retornado
// Argumento:
// C�digo do Candidato
infoEleitores * buscaCandidatoPorCodigo( uint32 );

// Convers�o do cargo de ID para seu Nome
// Argumento:
// C�digo do Cargo
// 1 - Vereador
// 2 - Prefeito
// 3 - Deputado Estadual
// 4 - Deputado Federal
// 5 - Senador
// 6 - Governador
// 7 - Presidente
uint8 * id2Cargo( uint8 );

// Fun��o para inser��o de hist�rico de elei��o
// Argumentos:
// Ponteiro para estrutura de candidato, ano da elei��o, quantidade de votos, cargo disputado
historicoCandidato * insereHistorico( infoCandidatos *, uint16, uint32, uint8 );

// Fun��es de uso externo
// Intuitivas

void atualizaCodigoCandidatoGlobal( uint32 );

uint32 retornaCodigoCandidatoGlobal();
bool verificaCodigoCandidatoEmUso( uint32 );

infoCandidatos * retornaPrimeiroCandidato();
infoCandidatos * retornaCandidato();

void atualizaPrimeiroCandidato( infoCandidatos * );
void atualizaCandidato( infoCandidatos * );



// Macros �teis
#define listaCandidatosGeral( A ) ordenaCandidatos( A, NULL, NULL, 0, NULL )
#define listaCandidatosCidade( A, B ) ordenaCandidatos( A, B, NULL, 0, NULL )
#define listaCandidatosPartico( A, B ) ordenaCandidatos( A, NULL, B, 0, NULL )
#define listaCandidatosCargo( A, B ) ordenaCandidatos( A, NULL, NULL, B, NULL )

#endif // _CANDIDATO_H_
