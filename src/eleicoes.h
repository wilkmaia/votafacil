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

	Arquivo que cont�m defini��es relativas aos sistemas de elei��es.
	
******************************************************************************/

#ifndef _ELEICOES_H_
#define _ELEICOES_H_

#include "mainHeader.h"

// Vari�vel global que armazena o ano da eleicao atual (incrementada de 2 unidades a cada eleicao)
static uint16 anoEleicao = 2012;

// Fun��es de vota��o
void sistemaVotacao();

// Fun��es de resultado das elei��es
void apuraResultado( uint16 );

// Fun��o de contagem dos votos de cada candidato
// Argumentos:
// ano da elei��o, ponteiro para ponteiro de estruturas de candidatos, cargo
infoCandidatos ** contaVotos( uint16, infoCandidatos **, uint8 );

// Fun��o para verifica��o das localidades da elei��o
// Argumentos:
// ano da elei��o, ponteiro para string, cargo
string * verificaLocais( uint16, string *, uint8 );

// Fun��es de uso externo
// Intuitivas
void alteraAnoEleicao( uint16 );
uint16 retornaAnoEleicao();

// true -> Ano de elei��o de vereadores e prefeitos
// false -> Ano de elei��o de deputados, senadores, governadores e presidente
bool eleicaoMunicipal( uint16 );


#endif // _ELEICOES_H_

