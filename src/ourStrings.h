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

	Arquivo que cont�m prot�tipos de fun��es / macros de tratamento de
	strings / caracteres.
	
******************************************************************************/

#ifndef _OURSTRINGS_H_
#define _OURSTRINGS_H_

#include "generalHeader.h"

// Defini��o do tipo string como ponteiro para uint8
typedef uint8* string;

// ourStrLen
// Retorno: uint16 - Tamanho da string SEM o caractere nulo ('\0')
// Par�metros: Ponteiro para (uint8) -- string
uint16 ourStrLen( string );

// ourStrCmp
// Retorno: int8 - (-1) Par�metro_1 < Par�metro_2; (0) Par�metro_1 == Par�metro_2; (1) Par�metro_1 > Par�metro_2
// Par�metros: Ponteiros para (uint8) -- strings; string Par�metro_1, string Par�metro_2
int8 ourStrCmp( string, string );

// ourStrConcat
// Retorno: Ponteiro para (uint8) -- string; Endere�o de mem�ria da string concatenada (P1)
// Par�metros: Ponteiros para (uint8) -- strings; string P1, string P2 (P2 ser� concatenada a P1)
string ourStrConcat( string, string );

// ourIsAllLetters
// Retorno: bool; (true) Todas as posi��es preenchidas com caracteres; (false) O oposto de true
// Par�metros: Ponteiro para (uint8) -- string
bool ourIsAllLetters( string );

// ourStrCpy
// Retorno: Ponteiro para (uint8) -- string; Endere�o de mem�ria da string final (P1)
// Par�metros: Ponteiros para (uint8) -- strings e inteiros (limite e tamanho de P1); string P1, string P2 (P2 ser� copiada em P1)
string ourStrCpyPartial( string, string, uint16, uint16 );

// ourStrIsIn
// Retorno: bool; (true) A string P1 est� contida em P2; (false) O oposto de true
// Par�metros: Ponteiros para (uint8) -- strings; string P1, string P2
bool ourStrIsIn( string, string );

// ourStrGetTok
// Retorno: Ponteiro para ponteiro para (uint8) -- Ponteiro para string; Ponteiro para a primeira token ou ponteiro nulo caso n�o haja nenhuma
// Par�metros: Ponteiro para (uint8) -- string e caractere delimitador;
string * ourStrGetTok( string, uint8 );

// ourGets
// Retorno: Ponteiro para (uint8) -- string
// Par�metros: void
#define ourGets(A) fgets( (A), ArrayLenght( (A) ), stdin )

// ourPuts
// Retorno: Ponteiro para (uint8) -- string
// Par�metros: void
#define ourPuts(A) fputs( (A), stdout )

// toUpper
// Retorno: uint8 - Caractere mai�sculo
// Par�metros: uint8 (caractere)
#define toUpper(A) ( ( (A) >= 'a' && (A) <= 'z' ) ? ( (A) + 'A' - 'a' ) : ( (A) ) )

// isNum
// Retorno: uint8 caso o caractere seja um algarismo ou -1 em caso contr�rio
// Par�metros: uint8 (caractere)
#define isNum(A) ( ( (A) >= '0' && (A) <= '9' ) ? ( (int8) UINT8_C( (A) - 48 ) ) : ( -1 ) )

// ourStrCpy
#define ourStrCpy(A, B) ourStrCpyPartial( (A), (B), UINT16_MAX, ArrayLenght( (A) ) )


#endif // _OURSTRINGS_H_
