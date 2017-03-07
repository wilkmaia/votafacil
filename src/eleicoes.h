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

	Arquivo que contém definições relativas aos sistemas de eleições.
	
******************************************************************************/

#ifndef _ELEICOES_H_
#define _ELEICOES_H_

#include "mainHeader.h"

// Variável global que armazena o ano da eleicao atual (incrementada de 2 unidades a cada eleicao)
static uint16 anoEleicao = 2012;

// Funções de votação
void sistemaVotacao();

// Funções de resultado das eleições
void apuraResultado( uint16 );

// Função de contagem dos votos de cada candidato
// Argumentos:
// ano da eleição, ponteiro para ponteiro de estruturas de candidatos, cargo
infoCandidatos ** contaVotos( uint16, infoCandidatos **, uint8 );

// Função para verificação das localidades da eleição
// Argumentos:
// ano da eleição, ponteiro para string, cargo
string * verificaLocais( uint16, string *, uint8 );

// Funções de uso externo
// Intuitivas
void alteraAnoEleicao( uint16 );
uint16 retornaAnoEleicao();

// true -> Ano de eleição de vereadores e prefeitos
// false -> Ano de eleição de deputados, senadores, governadores e presidente
bool eleicaoMunicipal( uint16 );


#endif // _ELEICOES_H_

