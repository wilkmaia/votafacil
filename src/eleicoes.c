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

	Arquivo que contém declaração de funções e tratamento de dados relativos
	aos sistemas de eleições.
	
******************************************************************************/

#include "mainHeader.h"

void sistemaVotacao()
{
	// Declaração e inicialização de variáveis
	infoEleitores *eleNode = retornaPrimeiroEleitor(), *auxEle;
	infoCandidatos *candNode = retornaPrimeiroCandidato(), *auxCand;

	historicoCandidato *histCand;
	uint32 x = 1, *codigoCand, n;

	if( eleNode == NULL )
	{
		ourPuts( "\nNao ha eleitores registrados no sistema.\n" );
		return;
	}

	// Ordenação dos eleitores em ordem crescente de título - processo idêntico ao das funções de ordenação
	for( ; x < retornaTituloEleitorGlobal(); ++x )
		for( ; eleNode != NULL; eleNode = eleNode->proximo )
			for( auxEle = eleNode->proximo; auxEle != NULL; auxEle = auxEle->proximo )
				if( eleNode->tituloEleitor > auxEle->tituloEleitor )
					{
						swapP( eleNode, auxEle );

						if( eleNode == primeiroEleitor )
							atualizaPrimeiroEleitor( auxEle );
						if( auxEle == eleitor )
							atualizaEleitor( eleNode );
					}
			// end-for
		// end-for
	// end-for

	// Votação

	// Determinação do tipo de eleição (Municipal || Estadual / Nacional) de acordo com o ano
	if( eleicaoMunicipal( anoEleicao ) == true )
		n = 2;
	else
		n = 5;

	// Inserção/Limpeza de históricos do ano em questão para todos os candidatos
	for( auxCand = retornaPrimeiroCandidato(); auxCand != NULL; auxCand = auxCand->proximo )
		insereHistorico( auxCand, anoEleicao, 0, auxCand->partido.cargo );
	
	// Laço de votação
	// Varredura de todos os eleitores
	for( eleNode = retornaPrimeiroEleitor(); eleNode != NULL; eleNode = eleNode->proximo )
	{
		// Votação do eleitor em questão
		// Resultado armazenado em uma array (vetor)
		codigoCand = ( n == 2 ? eleitorVotaMunicipal( eleNode ) : eleitorVotaNaoMunicipal( eleNode ) );
		
		// Efetivação dos votos
		for( x = 0; x < n; ++x )
		{
			// Não há eleitores / Voto Nulo || Voto Branco
			if( codigoCand[x] == UINT32_MAX || codigoCand[x] == 0 )
				continue;
			
			// Encontemos o candidato
			for( auxCand = retornaPrimeiroCandidato(); auxCand != NULL; auxCand = auxCand->proximo )
				if( auxCand->codigoCandidato == codigoCand[x] )
					break;
			
			// Caso o candidato não exista
			if( auxCand == NULL )
			{
				ourPuts( "\nErro! #0016\n" );
				pausaPrograma();
				return;
			}

			// Caso o candidato exista mas não possua histórico para o ano da eleição (não deve acontecer)
			if( auxCand->historico == NULL || auxCand->historico->ano != anoEleicao )
				insereHistorico( auxCand, anoEleicao, 0, auxCand->partido.cargo );
			
			// Efetivação do voto
			histCand = auxCand->historico;
			++(histCand->votos);
		}

		// Liberação da memória de codigoCand (alocada na função 'eleitorVota')
		free( codigoCand );
	}

	return;
}

void apuraResultado( uint16 ano )
{
	// Declaração e inicialização de variáveis
	uint8 x, y, z, w;
	uint32 n_par, n_tot;
	infoCandidatos **cand = NULL, *aux;
	infoEleitores *auxE;
	
	printf( "\n\n\t\t ** Apuracao do resultado das eleicoes (%d) **\n\n", ano );
	
	// Verificação da quantidade de cargos disputados (de acordo com o ano da eleição)
	x = ( eleicaoMunicipal( ano ) ? 2 : 5 );
	
	// Laço para apuração dos resultados, de acordo com o cargo
	for( y = 0; y < x; ++y )
	{
		string *local;
		
		printf( "\n\t\t * %s *\n", id2Cargo( ( x == 2 ) ? y + 1 : y + 3 ) );

		// Contagem de votos dos candidatos (de acordo com o ano da eleição)
		cand = contaVotos( ano, cand, ( x == 2 ) ? y + 1 : y + 3 );
		
		// Verificação de todas as localidades (cidades / estados, de acordo com o ano da eleição)
		local = verificaLocais( ano, local, ( x == 2 ) ? y + 1 : y + 3 );
		if( cand == NULL )
		{
			ourPuts( "Erro! #0019\n" );
			pausaPrograma();
			return;
		}
		if( local == NULL )
		{
			ourPuts( "Erro! #0020\n" );
			pausaPrograma();
			return;
		}

		// Varredura das localidades
		for( z = 0; *( local + z ) != NULL; ++z )
		{
			// Determina a quantidade total de votos computados na localidade
			for( n_tot = 0, auxE = retornaPrimeiroEleitor(); auxE != NULL; auxE = auxE->proximo )
				if( ( x == 2 && ourStrCmp( auxE->pessoal.cidade, *( local + z ) ) == 0 ) ||
					( x == 5 && ourStrCmp( auxE->pessoal.estado, *( local + z ) ) == 0 ) )
					++n_tot;
			
			// Tipo de resultado (Cidade / Estado / Nacional)
			if( y == 4 )
				ourPuts( "\t -- Nacional -- \n" );
			else
				printf( "\t -- %s: %s -- \n", ( x == 2 ? "Cidade" : "Estado" ), *( local + z ) );
			
			// Destaca o primeiro colocado
			if( ( *( cand ) )->historico->votos > 0 )
				ourPuts( " ** " );
			
			// Varredura dos candidatos
			// Imprime os eleitores daquela região / localidade
			for( w = n_par = 0, aux = *( cand ); aux != NULL; aux = *( cand + (++w) ) )
			{
				// Se o cargo for de presidente, a localidade não importa
				if( aux->partido.cargo == 7 )
					*( local + z ) = ( x == 2 ? aux->eleitor->pessoal.cidade : aux->eleitor->pessoal.estado );

				// Caso o candidato em questão não faça parte da localidade atual
				if( ( x == 2 && ourStrCmp( aux->eleitor->pessoal.cidade, *( local + z ) ) != 0 ) ||
					( x == 5 && ourStrCmp( aux->eleitor->pessoal.estado, *( local + z ) ) != 0 ) ||
					( ( ( x == 2 ) ? y + 1 : y + 3 ) != aux->partido.cargo ) )
					// Volta ao início deste laço
					continue;

				// Exibição dos votos do candidato (percentual e bruto)
				printf( "%s - %.02f%% (%d votos)\n", aux->eleitor->pessoal.nomeCompleto, 100 * (aux->historico->votos / (float) n_tot), aux->historico->votos );
				
				// Atualização da quantidade de votos parcial
				n_par += aux->historico->votos;
			}
			// Exibição da quantidade de votos inválidos (brancos e nulos) - (percentual e bruta)
			printf( "Brancos / Nulos - %.02f%% (%d votos)\n", 100 * ( n_tot - n_par ) / (float) n_tot, ( n_tot - n_par ) );
		}
		
		// Liberação da memória armazenada para as localidades
		free( local );
	}
	
	// Liberação da memória armazenada para os candidatos
	free( cand );
	
	return;
}

infoCandidatos ** contaVotos( uint16 ano, infoCandidatos **cand, uint8 cargo )
{
	// Declaração e inicialização de variáveis
	uint32 x = retornaCodigoCandidatoGlobal(), n, count = 0;
	infoCandidatos *mainNode, *auxNode;
	
	// Laço para a inserção de históricos, caso os candidatos não possuam, relativos ao ano do resultado
	// Também organiza os candidatos do cargo recebido como parâmetro em ordem decrescente de votos
	for( n = 0; x > 1; --x, ++n )
		for( mainNode = retornaPrimeiroCandidato(); mainNode != NULL; mainNode = mainNode->proximo )
		{
			if( cargo != mainNode->partido.cargo )
				continue;
				
			for( auxNode = mainNode->proximo; auxNode != NULL; auxNode = auxNode->proximo )
			{
				historicoCandidato *aux;

				for( aux = mainNode->historico; aux != NULL; aux = aux->anterior )
				{
					if( aux->ano != ano )
						continue;

					swapP( aux, mainNode->historico );
					mainNode->historico = aux;
					break;	
				}
				if( aux == NULL )
					insereHistorico( mainNode, ano, 0, mainNode->partido.cargo );

				for( aux = auxNode->historico; aux != NULL; aux = aux->anterior )
				{
					if( aux->ano != ano )
						continue;

					swapP( aux, auxNode->historico );
					auxNode->historico = aux;
					break;
				}
				if( aux == NULL )
					insereHistorico( auxNode, ano, 0, auxNode->partido.cargo );

				if( mainNode->historico->votos < auxNode->historico->votos )
				{
					swapP( mainNode, auxNode );

					if( mainNode == retornaPrimeiroCandidato() )
						atualizaPrimeiroCandidato( auxNode );
					if( auxNode == retornaCandidato() )
						atualizaCandidato( mainNode );
				}
			}
		}
	// end-for

	// Varredura da lista e armazenamento dos candidatos do cargo desejado na array 'cand'
	for( mainNode = retornaPrimeiroCandidato(); mainNode != NULL; mainNode = mainNode->proximo )
	{
		if( mainNode->partido.cargo != cargo )
			continue;

		// (Re)Alocação de memória, à medida que seja necessário
		if( count == 0 && cand == NULL )
			cand = (infoCandidatos **) calloc( ++count + 1, sizeof( infoCandidatos * ) );
		else
			cand = (infoCandidatos **) realloc( cand, (++count + 1) * sizeof( infoCandidatos * ) );
			
		if( cand == NULL )
		{
			ourPuts( "Erro! #0017\n" );
			pausaPrograma();
			return;
		}
		
		*( cand + count - 1 ) = mainNode;
		*( cand + count ) = NULL;
	}
	
	// Retorno da array
	return cand;
}

string * verificaLocais( uint16 ano, string *local, uint8 cargo )
{
	// Declaração e inicialização de variáveis
	uint32 x = 0, n, y = retornaCodigoCandidatoGlobal();
	infoCandidatos *mainNode, *auxNode;
	
	local = (string *) calloc( 1, sizeof( string ) );
	if( local == NULL )
	{
		ourPuts( "Erro! #0026\n" );
		pausaPrograma();
		return NULL;
	}
	
	// Laço para a inserção das localidades na array, para os candidatos de cargo desejado (parâmetro)
	for( n = 0; y > 1; --y, ++n )
	{
		*( local + x ) = NULL;
		
		for( mainNode = retornaPrimeiroCandidato(); mainNode != NULL; mainNode = mainNode->proximo )
		{
			if( cargo != mainNode->partido.cargo )
				continue;

			for( auxNode = mainNode; auxNode != NULL; auxNode = auxNode->proximo )
			{
				if( *( local ) == NULL )
				{
					*( local ) = ( eleicaoMunicipal( ano ) ? mainNode->eleitor->pessoal.cidade : mainNode->eleitor->pessoal.estado );
					++x;
				}
				else
				{
					for( n = 0; n < x; ++n )
						if( ourStrCmp( *( local + n ), ( eleicaoMunicipal( ano ) ? mainNode->eleitor->pessoal.cidade : mainNode->eleitor->pessoal.estado ) ) == 0 )
							break;

					if( n == x )
					{
						local = (string *) realloc( local, (++x) * sizeof( string ) );

						if( local == NULL )
						{
							ourPuts( "Erro! #0027\n" );
							pausaPrograma();
							return NULL;
						}

						*( local + n ) = ( eleicaoMunicipal( ano ) ? mainNode->eleitor->pessoal.cidade : mainNode->eleitor->pessoal.estado );
					}
				}
			}
		}
	}
	
	return local;
}

// Verificação do tipo de eleição em função do ano
// Anos múltiplos de 4 (2012; 2016; ...) possuem eleições a nível municipal
bool eleicaoMunicipal( uint16 ano )
{
	return ( ! ( ano % 4 ) );
}


// Funções de uso externo
// Intuitivas

void alteraAnoEleicao( uint16 ano )
{
	anoEleicao = ano;
}

uint16 retornaAnoEleicao()
{
	return anoEleicao;
}


