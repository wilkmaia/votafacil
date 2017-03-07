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

	Cabe�alho principal. Cont�m refer�ncias a bibliotecas necess�rias e
	defini��es cab�veis.
	
******************************************************************************/

#ifndef _MAINHEADER_H_
#define _MAINHEADER_H_

// Chamadas de bibliotecas padr�o somente ap�s todas as bibliotecas espec�ficas
// terem sido referidas.
// Evitar conflitos desnecess�rios.
#include <stdio.h>
#include <stdlib.h>
#include "conio2.h"
#include "generalHeader.h"
#include "ourStrings.h"
#include "eleitor.h"
#include "candidato.h"
#include "eleicoes.h"


// Fun��es de impress�o de menu / sa�da
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


// ------------------- Fun��es gerais -------------------

// Limpa a tela
void limpaTela();

// Pausa o programa at� que uma tecla seja digitada
void pausaPrograma();

// buscaPorCodigo
// Retorno: void
// Par�metros: C�digo do Candidato/Eleitor (uint32); Par�metro booleano (0 - Busca Candidato / 1 - Busca Eleitor)
void buscaPorCodigo( uint32, bool );


// ------------------- Vari�veis Globais -------------------

extern uint32 tituloEleitorGlobal;
extern uint32 codigoCandidatoGlobal;
extern uint16 anoEleicao;

extern infoEleitores *eleitor;
extern infoEleitores *primeiroEleitor;

extern infoCandidatos *candidato;
extern infoCandidatos *primeiroCandidato;


#endif // _MAINHEADER_H_
