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

	Arquivo principal.
	
******************************************************************************/

#include "mainHeader.h"

int main()
{
	infoBasica();
	
	// Laço infinito. Encerra apenas com o return na opção 8 do menu principal.
	for( ; ; )
	{		
        // Trabalhando com o valor retornado
		switch( menuPrincipal() )
		{
			case '1':
                ourPuts( "\n\n\t\tMenu de Cadastro\n\n" );
				menuCadastrar();
			break;
			
			case '2':
                ourPuts( "\n\n\t\tMenu de Exclusao\n\n" );
				menuExcluir();
			break;
			
			case '3':
                ourPuts( "\n\n\t\tMenu de Edicao\n\n" );
				menuAlterar();
			break;
			
			case '4':
                ourPuts( "\n\n\t\tMenu de Pesquisa\n\n" );
				menuPesquisar();
			break;
			
			case '5':
                ourPuts( "\n\n\t\tMenu de Listagem\n\n" );
				menuListar();
			break;
			
			case '6':
                ourPuts( "\n\n\t\tMenu de Eleicao\n\n" );
				menuIniciarEleicao();
			break;

			case '7':
                menuBackUps();
			break;
			
			case '8':
                imprimeSaida();
				limpaMemoria();
				return 0;
			
			default:
				// Caso a opção escolhida pelo usuario não esteja na lista, repetir.
                continue;
		}
	}
}

// Funções de impressão de menu
uint8 menuPrincipal()
{
	limpaTela();
    ourPuts( "\t\tMenu Principal:\n" );
	ourPuts( "[1] Cadastrar\n[2] Excluir\n[3] Alterar\n[4] Pesquisar\n[5] Listar\n[6] Iniciar Eleicao\n[7] BackUps\n[8] Sair\n\n" );
	ourPuts( "Escolha uma opcao valida (de 1 a 8): " );
	
	// Retorno do valor digitado
	return getche();
}

void menuCadastrar()
{
	for( ; ; )
	{
		limpaTela();
        ourPuts( "\nInforme o tipo de cadastro que voce deseja realizar:\n" );
		ourPuts( "[1] Cadastro de Eleitor\n[2] Cadastro de Candidato\n[3] Voltar\n\n" );
		ourPuts( "Escolha uma opcao valida (de 1 a 3): " );
	
		switch( getche() )
		{
			uint8 x;
			// Chama a função de cadastro de eleitor
			case '1':
				limpaTela();
                ourPuts( "\nEste eleitor sera, tambem, candidato?\n" );
				ourPuts( "Em caso afirmativo, tecle 's'. Caso contrario, tecle qualquer outra letra.\n" );
				x = getch();
				if( toUpper( x ) == 'S' )
				{
					cadastraCandidato();
					break;
				}
				cadastraEleitor();
			break;
		
			// Chama a função de cadastro de candidato
			case '2':
				cadastraCandidato();
			break;
		
			// Escape
			case '3':
				return;
		
			// Valor inválido, repetir.
			default:
				continue;
		}
	}
}

void menuExcluir()
{
	for( ; ; )
	{
		limpaTela();
        ourPuts( "Informe o tipo de cadastro que voce deseja excluir:\n" );
		ourPuts( "[1] Cadastro de Eleitor\n[2] Cadastro de Candidato\n[3] Voltar\n\n" );
		ourPuts( "Escolha uma opcao valida (de 1 a 3): " );
	
		switch( getche() )
		{
			// Chama a função de remoção de eleitor
			case '1':
				removeEleitor();
			break;
		
			// Chama a função de remoção de candidato
			case '2':
				removeCandidato();
			break;
		
			// Escape
			case '3':
				return;
		
			// Valor inválido, repetir.
			default:
				continue;
		}
	}
}

void menuAlterar()
{
	for( ; ; )
	{
		limpaTela();
        ourPuts( "Informe o tipo de cadastro que voce deseja alterar:\n" );
		ourPuts( "[1] Cadastro de Eleitor\n[2] Cadastro de Candidato\n[3] Voltar\n\n" );
		ourPuts( "Escolha uma opcao valida (de 1 a 3): " );
	
		switch( getche() )
		{
			// Chama a função de edição de eleitor
			case '1':
				editaEleitor();
			break;
			
			// Chama a função de edição de candidato
			case '2':
				editaCandidato();
			break;
		
			// Escape
			case '3':
				return;
		
			// Valor inválido
			default:
				continue;
		}
	}
}

void menuPesquisar()
{
	for( ; ; )
	{
		ourPuts( "Informe o tipo de pesquisa que voce deseja realizar:\n" );
		ourPuts( "[1] Pesquisa por nome\n[2] Pesquisa por codigo unico\n[3] Voltar\n\n" );
		ourPuts( "Escolha uma opcao valida (de 1 a 3): " );
		
		switch( getche() )
		{
			// Pesquisa por nome
			case '1':
			{
				uint8 nome[101], x;
				for( ; ; )
				{
					ourPuts( "\nDigite o nome da pessoa a pesquisar: " );
					ourGets( nome ); // Leitura do nome
					nome[ ourStrLen( nome ) - 1 ] = 0; // ourGets atribui '\n' quando a tecla ENTER é pressionada.
					printf( "O nome esta correto? (%s)\nEm caso afirmativo, tecle 's'. Em caso negativo, tecle outra tecla.\n", nome );
					x = getch();
					if( toUpper( x ) == 'S' )
						break;
				}
				
				// Efetua, efetivamente, a busca
				buscaPorNome( nome );
			}
			break;
			
			// Pesquisa por codigo
			case '2':
			{
				uint32 codigo = 0; // Inicializado para evitar problemas
				bool tipo = 0; // Padrão: Candidato
				for( ; codigo != UINT32_MAX; )
				{	
					limpaTela();
                    ourPuts( "\n\nVoce deseja pesquisar por um candidato ou eleitor?\n" );
					ourPuts( "[1] Candidato\n[2] Eleitor\n[3] Voltar\n\n" );
					ourPuts( "Escolha uma opcao valida (de 1 a 3): " );

					switch( getche() )
					{
						// Padrão 0
						case '1':
						break;
						
						case '2':
							tipo = 1; // Eleitor
						break;
						
						// Escape
						case '3':
							codigo = UINT32_MAX;
							continue;
						
						// Opção inválida? Retorno ao início do laço
						default:
							continue;
					}
					
					printf( "\nAgora, digite o codigo do %s", ( tipo ? "eleitor: " : "candidato: " ) );
					scanf( "%u", &codigo ); // Leitura de valor sem sinal
					
					// Busca efetiva.
					buscaPorCodigo( codigo, tipo );
					pausaPrograma();
				}
			}
			break;
			
			// Escape
			case '3':
				return;
			
			// Valor invalido
			default:
				continue;
		}
	}
}

void menuListar()
{
	for( ; ; )
	{
		limpaTela();
        ourPuts( "Informe o tipo de listagem desejada:\n" );
		ourPuts( "[1] Lista de Candidatos\n[2] Lista de Eleitores\n[3] Voltar\n\n" );
		ourPuts( "Escolha uma opcao valida (de 1 a 3): " );
		
		switch( getche() )
		{
			// Listagem de Candidatos
			case '1':
			{
				uint8 x = 0; // Inicializado para evitar problemas
				uint8 str[3][8] = { "Cidade", "Partido", "Cargo" }, str2[51];
				for( ; x != '0'; )
				{
					ourPuts( "\n\nInforme o tipo de ordenacao:\n" );
					ourPuts( "[1] Ordem Alfabetica\n[2] Cidade\n[3] Estado\n[4] Ordem Crescente de Codigo\n[5] Partido\n[6] Cargo\n[7] Cidade Especifica\n[8] Partido Especifico\n[9] Cargo Especifico\n[0] Voltar\n\n" );
					ourPuts( "Escolha uma opcao valida (de 0 a 9): " );
					
					// Escape
					if( ( x = getche() ) == '0' )
						break;
						
					// Valor Inválido, repetir.
					else if ( ( x < '0' || x > '9' ) )
						continue;

					// Listagem efetiva
					if( x <= '6' )
					{
						listaCandidatosGeral( (x - 48) );
						pausaPrograma();
                    }
					else
					{
						printf( "\nDigite %c %s: ", (x - '7') % 1 ? 'a' : 'o', str[ x - '7' ] );
						
						if( x != '9' )
						{
							ourGets( str2 );
							str2[ ourStrLen( str2 ) - 1 ] = 0;
						}
						else
						{
							ourPuts( "\n[1] Vereador\n[2] Prefeito\n[3] Deputado Estadual\n[4] Deputado Federal\n[5] Senador\n[6] Governador\n[7] Presidente\n" );
							for( *str2 = getche() - 48; *str2 < 1 || *str2 > 7; *str2 = getche() - 48 )
								ourPuts( "\nCargo inexistente. Tente novamente: " );
						}
						
						switch( x )
						{
							case '7':
								listaCandidatosCidade( 4, str2 );
								pausaPrograma();
							break;
							
							case '8':
								listaCandidatosPartico( 4, str2 );
								pausaPrograma();
							break;
							
							case '9':
								listaCandidatosCargo( 4, *str2 );
								pausaPrograma();
							break;
						}
					}
					break;
				}
			}
			break;
			
			// Listagem de Eleitores
			case '2':
			{
				uint8 x = 0; // Inicializado para evitar problemas
				uint8 str[3][7] = { "Cidade", "Estado" }, str2[31];
				for( ; x != '7'; )
				{
					ourPuts( "\n\nInforme o tipo de ordenacao:\n" );
					ourPuts( "[1] Ordem Alfabetica\n[2] Cidade\n[3] Estado\n[4] Codigo\n[5] Cidade Especifica\n[6] Estado Especifico\n[7] Voltar\n\n" );
					ourPuts( "Escolha uma opcao valida (de 1 a 7): " );
					
					// Escape
					if( ( x = getche() ) == '7' )
						break;
						
					// Valor Inválido
					else if ( ( x < '1' || x > '7' ) )
						continue;

					// Listagem efetiva
					if( x <= '4' )
					{
						listaEleitoresGeral( (x - 48) );
						pausaPrograma();
                    }
					else
					{
						printf( "\nDigite %c %s: ", (x - '5') % 1 ? 'a' : 'o', str[ x - '5' ] );
						ourGets( str2 );
						str2[ ourStrLen( str2 ) - 1 ] = 0;
						
						switch( x )
						{
							case '5':
								listaEleitoresCidade( 1, str2 );
								pausaPrograma();
							break;
							
							case '6':
								listaEleitoresEstado( 1, str2 );
								pausaPrograma();
							break;
						}
					}
					break;
				}
			}
			break;
			
			// Escape
			case '3':
				return;
			
			// Valor inválido
			default:
				continue;
		}
	}
}

void menuIniciarEleicao()
{
	for( ; ; )
	{
		limpaTela();
        ourPuts( "Informe a opcao desejada:\n" );
		printf( "[1] Realizar votacao\n[2] Apurar resultado\n[3] Alterar ano (ano atual: %d)\n[4] Voltar\n\n", retornaAnoEleicao() );
		ourPuts( "Escolha uma opcao valida (de 1 a 4): " );
		
		switch( getche() )
		{
			// Votação
			case '1':
				limpaTela();
                ourPuts( "\n\nIniciando sistema de votacao...\n" );
				sistemaVotacao();
				ourPuts( "\n\nSistema de votacao encerrado\n" );
				pausaPrograma();
			break;
			
			// Apuração
			case '2':
				limpaTela();
                ourPuts( "\n\nApurando o resultado das eleicoes...\n" );
				apuraResultado( retornaAnoEleicao() );
				ourPuts( "\n\nFim da apuracao do resultado\n" );
				pausaPrograma();
			break;
			
			// Alteração do ano atual
			case '3':
			{
				for( ; ; )
				{
					uint16 x = 0;
					limpaTela();
					ourPuts( "\nDigite o novo ano:\n" );
					ourPuts( "Info I: Apenas anos superiores a 2010 e pares (anos impares nao tem eleicao).\n" );
					printf( "Info II: Valores acima de %hu podem gerar resultados inesperados.\n", UINT16_MAX );
					scanf( "%hu", &x );
					
					if( x <= 2010 || (x % 2) != 0 ) // Apenas anos superiores a 2010 e pares (anos ímpares não possuem eleição)
						continue;
					alteraAnoEleicao( x );
					pausaPrograma();
					break;
				}
			}
			break;
			
			// Escape
			case '4':
				return;
			
			// Valor invalido, repetir.
			default:
				continue;
		}
	}
}

void menuBackUps()
{
	for( ; ; )
	{
		limpaTela();
		ourPuts( "\n\n\t\tMenu de BackUps\n\n" );
        ourPuts( "\nInforme a opcao desejada:\n" );
		ourPuts( "[1] Salvar as informacoes em disco\n[2] Carregar as informacoes do disco\n[3] Voltar\n" );
		ourPuts( "Escolha uma opcao valida (de 1 a 3): " );
	
		switch( getche() )
		{
			case '1':
				saveBackUpPessoal();
				
				// Pausa, caso retorne para uma função que limpe a tela.
                pausaPrograma();

			break;

			case '2':
				loadBackUpPessoal();
				
				// Pausa, caso retorne para uma função que limpe a tela.
                pausaPrograma();
			break;

			case '3':
				// Escape da função
                return;
			
			default:
				// Caso o valor inserido não esteja na lista, repetir.
                continue;
		}
		
	}
}

void infoBasica()
{
	ourPuts( "\t\tVota Facil!\n" );
	ourPuts( "Programa de simulacao de Urnas Eletronicas.\n" );
	ourPuts( "Seja bem-vindo.\n\n\n" );
	pausaPrograma();
	return;
}

void imprimeSaida()
{
	limpaTela();
    ourPuts( "\n\nObrigado por ter utilizado o sistema de eleicoes VotaFacil!\n\n" );
    pausaPrograma();
}

// Limpeza de tela de acordo com o S.O. OU utilizando uma biblioteca
void limpaTela()
{
#ifdef _NORMALCURSOR // conio2.h
	clrscr();
#else

#	ifdef WIN32
		system( "cls" );
#	else // WIN32
		system( "clear" );
#	endif // WIN32

#endif// _NORMALCURSOS
}

void pausaPrograma()
{
    ourPuts( "\nPressione qualquer tecla para continuar . . . \n" );
	getch();		
}

// Busca por código geral
// type == 1 : Eleitor
// type == 2 : Candidato
void buscaPorCodigo( uint32 cod, bool type )
{
	if( type )
		imprimeEleitor( buscaEleitorPorCodigo( cod ) );
	else
		imprimeEleitor( buscaCandidatoPorCodigo( cod ) );
	return;
}

