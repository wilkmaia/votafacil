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

	Arquivo com as declarações de funções de tratamento de
	strings / caracteres.
	
******************************************************************************/

#include "mainHeader.h"

uint16 ourStrLen( string buf )
{
	uint16 x = 0;
	
	// Contagem da quantidade de caracteres na string
	for( ; *( buf + x ) != 0; ++x );
	
	return x;
}

int8 ourStrCmp( string str1, string str2 )
{
	uint16 x = 0;
	
	// Laço infinito
	for( ; ; )
	{
		// Caso str1 tenha fim
		if( *( str1 + x ) == 0 )
		{
			// str2 também teve fim, são iguais
			if( *( str2 + x ) == 0 )
				return 0;
			// str2 continua. Logo, str1 é menor
			else
				return -1;
		}
		
		// str1 não teve fim. str2 sim. Logo, str2 é menor.
		else if( *( str2 + x ) == 0 )
			return 1;
			
	
		// str1 é menor que str2 ?
		if( toUpper( *( str1 + x ) ) < toUpper( *( str2 + x ) ) )
			return -1;
		
		// str1 é maior que str2 ?
		else if( toUpper( *( str1 + x ) ) > toUpper( *( str2 + x ) ) )
			return 1;
		
		// Caso sejam iguais, na posição atual, incrementa a posição
		else
			++x;
	}
}

string ourStrConcat( string str1, string str2 )
{
	// Definição de variáveis e inicialização com o tamanho das strings parâmetro
	uint16 x = ourStrLen( str1 ), y = ourStrLen( str2 );
	
	// Contador
	uint16 n = 0;
	
	// Concatenação
	for( ; n <= y; ++x, ++n )
		*( str1 + x ) = *( str2 + n );
	
	// Retorno
	return str1;
}

bool ourIsAllLetters( string str )
{
	// Verificação
	for( ; *str != 0 ; str++ )
		// Caso o caractere da posição atual NÃO esteja entre a/A e z/Z
		if( !( toUpper(*(str)) >= 'A' && toUpper(*(str)) <= 'Z' ) )
			return false;
			
	// Caso contrário
	return true;
}

string ourStrCpyPartial( string str1, string str2, uint16 n, uint16 size )
{
	uint16 x = 0;
	
	// Copia enquanto n for maior que 0
	for( ; n > 0; ++x, --n )
	{
		// Se str2 finalizar, finaliza str1 e sai do laço
		if( *( str2 + x ) == 0 )
		{
			*( str1 + x ) = 0;
			break;
		}
		
		// Se str1 estourar, sai do laço
		else if( x >= size )
		{
			*( str1 + size ) = 0;
			break;
		}
		
		// Caso contrário, copia
		*( str1 + x ) = *( str2 + x );
	}
	
	// Retorno
	return str1;
}

bool ourStrIsIn( string str1, string str2 )
{
	// Declaração e inicialização das variáveis contendo o tamanho de cada string
	uint16 str1_len = ourStrLen( str1 ), str2_len = ourStrLen( str2 );
	// Variáveis auxiliares
	uint16 x = 0, y = 0;
	
	// Caso str1 seja maior que str2, com certeza não estará contida nela
	if( str1_len > str2_len )
		return 0;
	
	// Verificação
	for( ; y < str2_len; ++y )
	{
		if( toUpper( *( str1 + x ) ) == toUpper( *( str2 + y ) ) )
			++x;
		else
			x = 0;
		
		// Caso haja (str1_len) caracteres iguais, em sequencia, a substring está contida na string
		if( x == str1_len )
			return 1;
	}
	
	return 0;
}


// Tokens são pedaços menores, substrings, de uma string divididos por caracteres delimitadores
// Exemplo:
// "a,b,c,d" --> "a"; "b"; "c"; "d" são 4 tokens delimitados por ','
string * ourStrGetTok( string str, uint8 del )
{
	// Declaração de variáveis
	string *parser;
	uint16 n, x;
	
	// Determinação da quantidade de caracteres delimitadores dos tokens
	for( n = x = 0; str[n] != 0; ++n )
		if( str[n] == del )
			++x;
	
	// Alocação primária de memória para 'parser'
	parser = (string *) calloc( x+1, sizeof( string ) );
	if( parser == NULL )
	{
		ourPuts( "Erro! #0010" );
		pausaPrograma();
		exit( 1 );
	}
	
	// Divisão da string
	// A cada caractere 'del' encontrado, uma substring é gerada e armazenada numa das posições da array 'parser', à medida que esta é expandida.
	// Caso haja dois caracteres 'del' sequenciais, uma posição apontando a um ponteiro nulo é gerada
	for( n = x = 0; *str != 0; ++str, ++x )
		if( *str == del || *str == '\n' )
		{
			*( parser + n ) = (string) calloc( ( x + 1 ), sizeof( uint8 ) );
			if( *( parser + n ) == NULL )
			{
				ourPuts( "Erro! #0011" );
				pausaPrograma();
				exit( 1 );
			}

			if( x > 0 )
				ourStrCpyPartial( *( parser + n ), str - x, x, x + 1 );
			else
				*( parser + n ) = NULL;
			++n;
			x = -1;
		}
	
	// Retorno dos tokens
	return parser;
}

