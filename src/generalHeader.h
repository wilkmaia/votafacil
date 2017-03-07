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

	Este arquivo contém definições de funções, macros e tipos utilizados no
	programa e alguns comentários acerca destas definições, além de chamadas a
	algumas bibliotecas.
	
******************************************************************************/

#ifndef _GENERALHEADER_H_
#define _GENERALHEADER_H_


// Definição da plataforma utilizada
// MacOS é Unix-based, então pode-se verificar somente se a plataforma utilizada é Windows

#if (defined(__WIN32__) || defined(__WIN32) || defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER) || defined(__BORLANDC__)) && !defined(WIN32)
#	define WIN32
#endif // WIN32


// Necessários para a <stdint.h>

// Utilizando tal biblioteca para a definição das constantes numéricas
// através das funções UINTX_C, onde X é a quantidade de bits do tipo e
// para o uso dos tipos [u]intN_t
// ANSI C
#ifdef __cplusplus
#	define __STDC_LIMIT_MACROS
#endif // __cplusplus

#include <stdint.h>


// Definição de tipos principais
// Tipos inteiros com tamanho definido
// Signed / Unsigned

typedef int8_t		int8;
typedef int16_t	int16;
typedef int32_t	int32;
typedef int64_t	int64;

typedef uint8_t	uint8;
typedef uint16_t	uint16;
typedef uint32_t	uint32;
typedef uint64_t	uint64;

// Por precaução, antes de definir as constantes, removemo-las.

#undef UINT8_MIN
#undef UINT8_MAX
#undef INT8_MIN
#undef INT8_MAX
#define UINT8_MIN ( (uint8) UINT8_C(0x00) )	// 0
#define UINT8_MAX ( (uint8) UINT8_C(0xFF) )	// 255
#define INT8_MIN ( (int8) INT8_C(0x80) )	// -128
#define INT8_MAX ( (int8) INT8_C(0x7F) )	// 127

#undef UINT16_MIN
#undef UINT16_MAX
#undef INT16_MIN
#undef INT16_MAX
#define UINT16_MIN ( (uint16) UINT16_C(0x0000) )	// 0
#define UINT16_MAX ( (uint16) UINT16_C(0xFFFF) )	// 65535
#define INT16_MIN ( (int16) INT16_C(0x8000) ) 		// -32768
#define INT16_MAX ( (int16) INT16_C(0x7FFF) ) 		// 32767

#undef UINT32_MIN
#undef UINT32_MAX
#undef INT32_MIN
#undef INT32_MAX
#define UINT32_MIN ( (uint32) UINT32_C(0x00000000) )	// 0
#define UINT32_MAX ( (uint32) UINT32_C(0xFFFFFFFF) )	// 4294967295
#define INT32_MIN ( (int32) INT32_C(0x80000000) ) 		// -2147483648
#define INT32_MAX ( (int32) INT32_C(0x7FFFFFFF) )		// 2147483647

#undef UINT64_MIN
#undef UINT64_MAX
#undef INT64_MIN
#undef INT64_MAX
#define UINT64_MIN ( (uint64) UINT64_C(0x0000000000000000) )	// 0
#define UINT64_MAX ( (uint64) UINT64_C(0xFFFFFFFFFFFFFFFF) )	// 18446744073709551615
#define INT64_MIN ( (int64) INT64_C(0x8000000000000000) )		// -9223372036854775808
#define INT64_MAX ( (int64) INT64_C(0x7FFFFFFFFFFFFFFF) )		// 9223372036854775807

 
 
 
// Algumas outras utilidades

// Regalias de C++
#ifndef __cplusplus
	typedef uint8_t bool;
#	define false ( 1 == 0 )
#	define true  ( 1 == 1 )
#endif // __cplusplus

// Trocas
#define swap( a, b ) if( a != b ) ( ( a ^= b; b ^= a; a ^= b ) ) // Se a == b, não há por que inverter os valores
#define swapPointer( a, b ) if ( b != a ) { void *c; c = a; a = b; b = c; }

#define swapP( a, b )\
	if( a->proximo == b )\
	{\
		if( b->proximo != NULL )\
			b->proximo->anterior = a;\
		if( a->anterior != NULL )\
			a->anterior->proximo = b;\
		a->proximo = b->proximo;\
		b->anterior = a->anterior;\
		a->anterior = b;\
		b->proximo = a;\
	}\
	else if( a->anterior == b )\
	{\
		if( a->proximo != NULL )\
			a->proximo->anterior = b;\
		if( b->anterior != NULL )\
			b->anterior->proximo = a;\
		a->anterior = b->anterior;\
		b->proximo = a->proximo;\
		a->proximo = b;\
		b->anterior = a;\
	}\
	else\
	{\
		if( a->anterior != NULL )\
			a->anterior->proximo = b;\
		if( a->proximo != NULL )\
			a->proximo->anterior = b;\
		if( b->anterior != NULL )\
			b->anterior->proximo = a;\
		if( b->proximo != NULL )\
			b->proximo->anterior = a;\
		swapPointer( a->proximo, b->proximo );\
		swapPointer( a->anterior, b->anterior );\
	}
	

#ifndef max
#	define max( a, b ) ( ( (a) >= (b) ) ? (a) : (b) )
#endif // max
#ifndef min
#	define min( a, b ) ( ( (a) >= (b) ) ? (b) : (a) )
#endif // min

// Ponteiro nulo - Já deve existir!
#ifndef NULL
#	define NULL ( (void *) 0 )
#endif // NULL

// Comprimento de um vetor de tipo genérico
#define ArrayLenght(X) ( ( sizeof( (X) ) ) / ( sizeof( (X)[0] ) ) )
#define TamanhoVetor(X) ( ArrayLenght( (X) ) )



#endif // _GENERALHEADER_H_
