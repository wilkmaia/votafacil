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

	Cabeçalho principal. Contém referências a bibliotecas necessárias e
	definições cabíveis.
	
******************************************************************************/

#ifndef _MAINHEADER_H_
#define _MAINHEADER_H_

// Chamadas de bibliotecas padrão somente após todas as bibliotecas específicas
// terem sido referidas.
// Evitar conflitos desnecessários.
#include <stdio.h>
#include <stdlib.h>
#include "conio2.h"
#include "generalHeader.h"
#include "ourStrings.h"
#include "eleitor.h"
#include "candidato.h"
#include "eleicoes.h"


// Funções de impressão de menu / saída
void infoBasica();
uint8 menuPrincipal();
void menuCadastrar();
void menuExcluir();
void menuAlterar();
void menuPesquisar();
void menuListar();
void menuIniciarEleicao();
void menuBackUps();
void imprimeSaida();


// ------------------- Funções gerais -------------------

// Limpa a tela
void limpaTela();

// Pausa o programa até que uma tecla seja digitada
void pausaPrograma();

// buscaPorCodigo
// Retorno: void
// Parâmetros: Código do Candidato/Eleitor (uint32); Parâmetro booleano (0 - Busca Candidato / 1 - Busca Eleitor)
void buscaPorCodigo( uint32, bool );


// ------------------- Variáveis Globais -------------------

extern uint32 tituloEleitorGlobal;
extern uint32 codigoCandidatoGlobal;
extern uint16 anoEleicao;

extern infoEleitores *eleitor;
extern infoEleitores *primeiroEleitor;

extern infoCandidatos *candidato;
extern infoCandidatos *primeiroCandidato;


#endif // _MAINHEADER_H_
