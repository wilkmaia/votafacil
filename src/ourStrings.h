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

	Arquivo que contém protótipos de funções / macros de tratamento de
	strings / caracteres.
	
******************************************************************************/

#ifndef _OURSTRINGS_H_
#define _OURSTRINGS_H_

#include "generalHeader.h"

// Definição do tipo string como ponteiro para uint8
typedef uint8* string;

// ourStrLen
// Retorno: uint16 - Tamanho da string SEM o caractere nulo ('\0')
// Parâmetros: Ponteiro para (uint8) -- string
uint16 ourStrLen( string );

// ourStrCmp
// Retorno: int8 - (-1) Parâmetro_1 < Parâmetro_2; (0) Parâmetro_1 == Parâmetro_2; (1) Parâmetro_1 > Parâmetro_2
// Parâmetros: Ponteiros para (uint8) -- strings; string Parâmetro_1, string Parâmetro_2
int8 ourStrCmp( string, string );

// ourStrConcat
// Retorno: Ponteiro para (uint8) -- string; Endereço de memória da string concatenada (P1)
// Parâmetros: Ponteiros para (uint8) -- strings; string P1, string P2 (P2 será concatenada a P1)
string ourStrConcat( string, string );

// ourIsAllLetters
// Retorno: bool; (true) Todas as posições preenchidas com caracteres; (false) O oposto de true
// Parâmetros: Ponteiro para (uint8) -- string
bool ourIsAllLetters( string );

// ourStrCpy
// Retorno: Ponteiro para (uint8) -- string; Endereço de memória da string final (P1)
// Parâmetros: Ponteiros para (uint8) -- strings e inteiros (limite e tamanho de P1); string P1, string P2 (P2 será copiada em P1)
string ourStrCpyPartial( string, string, uint16, uint16 );

// ourStrIsIn
// Retorno: bool; (true) A string P1 está contida em P2; (false) O oposto de true
// Parâmetros: Ponteiros para (uint8) -- strings; string P1, string P2
bool ourStrIsIn( string, string );

// ourStrGetTok
// Retorno: Ponteiro para ponteiro para (uint8) -- Ponteiro para string; Ponteiro para a primeira token ou ponteiro nulo caso não haja nenhuma
// Parâmetros: Ponteiro para (uint8) -- string e caractere delimitador;
string * ourStrGetTok( string, uint8 );

// ourGets
// Retorno: Ponteiro para (uint8) -- string
// Parâmetros: void
#define ourGets(A) fgets( (A), ArrayLenght( (A) ), stdin )

// ourPuts
// Retorno: Ponteiro para (uint8) -- string
// Parâmetros: void
#define ourPuts(A) fputs( (A), stdout )

// toUpper
// Retorno: uint8 - Caractere maiúsculo
// Parâmetros: uint8 (caractere)
#define toUpper(A) ( ( (A) >= 'a' && (A) <= 'z' ) ? ( (A) + 'A' - 'a' ) : ( (A) ) )

// isNum
// Retorno: uint8 caso o caractere seja um algarismo ou -1 em caso contrário
// Parâmetros: uint8 (caractere)
#define isNum(A) ( ( (A) >= '0' && (A) <= '9' ) ? ( (int8) UINT8_C( (A) - 48 ) ) : ( -1 ) )

// ourStrCpy
#define ourStrCpy(A, B) ourStrCpyPartial( (A), (B), UINT16_MAX, ArrayLenght( (A) ) )


#endif // _OURSTRINGS_H_
