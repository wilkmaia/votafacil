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

	Este arquivo cont�m informa��es gen�ricas sobre os eleitores e declara��o
	de fun��es relativas �queles.
	
******************************************************************************/


#ifndef _ELEITOR_H_
#define _ELEITOR_H_

#include "mainHeader.h"

// Vari�vel global que armazena o t�tulo do pr�ximo eleitor a ser cadastrado
static uint32 tituloEleitorGlobal = UINT32_MIN + 1;

// Estrutura que cont�m as informa��es dos eleitores
typedef struct _eleit
{
	
	uint32 tituloEleitor; // C�digo do Eleitor - N�mero inteiro iniciando em 1 e limitado em UINT32_MAX (vide generalHeader.h)
	
	// Informa��es pessoais do Eleitor
	struct {
	
		uint8 nomeCompleto[101]; // Nome completo do Candidato/Eleitor - m�ximo de 100 caracteres
		uint8 cidade[31]; // Nome da cidade do Candidato/Eleitor - at� 30 caracteres
		uint8 estado[20]; // Nome do estado do Candidato/Eleitor - at� 19 caracteres
		uint8 dataNascimento[11]; // Data de nascimento do Candidato/Eleitor - M�scara -> "XX/XX/XXXX"
		
	} pessoal;
	
	// O eleitor �, tamb�m, candidato?
	// Em caso afirmativo, este ponteiro cont�m o endere�o de mem�ria da estrutura que cont�m as informa��es do candidato.
	// Em caso negativo, cont�m uma refer�ncia nula (NULL).
	struct _cand *eleitorCandidato;
	
	// Implementa��o da Lista Ligada
	struct _eleit *proximo;
	struct _eleit *anterior;
	
} infoEleitores;

static infoEleitores *eleitor = NULL;
static infoEleitores *primeiroEleitor = NULL;

// Fun��es que ser�o chamadas pelo programa em tempo de execu��o
// Intuitivas
infoEleitores * cadastraEleitor();

// Argumentos: nome, cidade, estado, nascimento, t�tulo
infoEleitores * insereEleitor( string, string, string, string, uint32 );
void removeEleitor();
void editaEleitor();

//Argumentos:
uint32 * eleitorVota( infoEleitores *, uint8 );

// Argumentos:
// Tipo de Ordena��o, Cidade, Estado
//
// Tipo de Ordena��o:
// [1] Ordem Alfab�tica
// [2] Cidade
// [3] Estado
// [4] C�digo
void ordenaEleitores( uint8, uint8 *, uint8 * );
void listaEleitoresOrdenadamente( uint8 *, uint8 * ); // cidade, estado

// Fun��es de acesso a arquivos em disco
void saveBackUpPessoal();
void loadBackUpPessoal();

// Imprime informa��es de um eleitor na tela
void imprimeEleitor( infoEleitores * );

// buscaPorNome
// Retorno: void
// Par�metros: Ponteiro para (uint8) -- string
void buscaPorNome( string );

infoEleitores * buscaEleitorPorCodigo( uint32 );

// Limpa a mem�ria antes de finalizar o programa
void limpaMemoria();

// Fun��es de acesso externo
// Intuitivas
infoEleitores * retornaPrimeiroEleitor();

void atualizaPrimeiroEleitor( infoEleitores * );
void atualizaEleitor( infoEleitores * );

uint32 retornaTituloEleitorGlobal();

infoEleitores * retornaPrimeiroEleitor();
infoEleitores * retornaEleitor();



// Macros �teis
#define listaEleitoresGeral( A ) ordenaEleitores( A, NULL, NULL )
#define listaEleitoresCidade( A, B ) ordenaEleitores( A, B, NULL )
#define listaEleitoresEstado( A, B ) ordenaEleitores( A, NULL, B )

#define eleitorVotaMunicipal( A ) eleitorVota ( (A), 0 )
#define eleitorVotaNaoMunicipal( A ) eleitorVota ( (A), 1 )

#endif // _ELEITOR_H_
