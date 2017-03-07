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

	Arquivo com funções e definições gerais acerca de candidatos.
	
******************************************************************************/

#include "mainHeader.h"

void imprimeCandidato( infoCandidatos *cand )
{
	// Exibe as informações do candidato na tela.
    printf( "\nCodigo Candidato: %d\n", cand->codigoCandidato );
	printf( "\t* Partido *\nNome: %s\tSigla: %s\tCargo a Disputar: %s\n", cand->partido.nome, cand->partido.sigla, id2Cargo( cand->partido.cargo ) );
}

infoCandidatos * cadastraCandidato()
{
	uint8 nome[51], sigla[8], cargo, x;
	
	for( ; ; )
	{
		// Limpa a tela
		limpaTela();
		
		// Recebe as informações do candidato
		ourPuts( "\t**\tSistema de Cadastro de Candidatos\t**\n" );
		ourPuts( "Digite o nome completo do partido do candidato: " );
		ourGets( nome );
		nome[ ourStrLen( nome ) - 1 ] = 0;
		ourPuts( "Digite a sigla do partido do candidato: " );
		ourGets( sigla );
		sigla[ ourStrLen( sigla ) - 1 ] = 0;
		ourPuts( "Escolha o cargo ao qual o candidato concorrera:\n" );
		ourPuts( "[1] Vereador\n[2] Prefeito\n[3] Deputado Estadual\n[4] Deputado Federal\n[5] Senador\n[6] Governador\n[7] Presidente\n" );
		
		// Leitura e repetição até que o valor inserido esteja no intervalo.
		for( cargo = getche() - 48; cargo < 1 || cargo > 7; cargo = getche() - 48 )
			ourPuts( "\nCargo inexistente. Tente novamente: " );
		
		// Verificação para uma possível repetição.
		ourPuts( "\n\nAs informacoes digitadas estao corretas?\n" );
		ourPuts( "Em caso afirmativo, tecle 's'. Em caso negativo, qualquer outra tecla.\n" );
		x = getch();
		if( toUpper( x ) == 'S' )
			break;
	}
	
	// Atribui as informações lidas na função para um registro na memória
	insereCandidato( codigoCandidatoGlobal, nome, sigla, cargo );
	
	// Incremento da variável que determina o código do candidato
    ++codigoCandidatoGlobal;
	
	// Cadastro das informações do candidato como eleitor
	ourPuts( "\n\n\t**\tInformacoes pessoais do candidato\t**\n" );
	candidato->eleitor = cadastraEleitor();
	candidato->eleitor->eleitorCandidato = candidato;
	
	// Pausa, caso retorne para uma função que limpe a tela.
    pausaPrograma();
	
	// Retorna um ponteiro que aponta para a estrutura do candidato
	return candidato;
}

infoCandidatos * insereCandidato( uint32 codigo, string nome, string sigla, uint8 cargo )
{
	// Alocação da memória que será utilizada para armazenar os dados do candidato.
    infoCandidatos *novoCandidato = (infoCandidatos *) calloc( 1, sizeof( infoCandidatos ) );
	
    // Verificação de falha na alocação, caso não haja espaço na memória
    // a função calloc retorna um ponteiro apontando para NULL.
    if( novoCandidato == NULL )
	{
		ourPuts( "\n\t\tErro! #0005\n" );
		exit(1);
	}
	
	// Atribuição dos valores lidos na função cadastraCandidado() na memória alocada.
	novoCandidato->codigoCandidato = codigo;
	ourStrCpy( novoCandidato->partido.nome, nome );
	ourStrCpy( novoCandidato->partido.sigla, sigla );
	novoCandidato->partido.cargo = cargo;
	novoCandidato->proximo = NULL;
	
	// Caso seja o primeiro candidato cadastrado, não apontará para um anterior.
	if( codigo == 1 )
	{
		novoCandidato->anterior = NULL;
		primeiroCandidato = novoCandidato;
	}
	
	// Caso não seja o primeiro, o ultimo candidato cadastrado será o anterior ao novo candidato.
	// Como a lista é duplamente encadeada, o ultimo candidato cadastrado também apontará para o novo candidato.
	else
	{
		novoCandidato->anterior = candidato;
		if( candidato != NULL )
			candidato->proximo = novoCandidato;
		else
			primeiroCandidato = novoCandidato;
	}

	// Incremento da posição do ultimo candidato cadastrado.
	candidato = novoCandidato;
	
	// A função retorna um ponteiro apontando para o ultimo candidato cadastrado.
	return candidato;
}

void removeCandidato()
{
	uint32 cod;
	infoCandidatos *auxNode = candidato;
	
	ourPuts( "\t**\tSistema de Remocao de Candidatos\t**\n" );
	
	// Busca de candidato por nome, caso o usuario não conheça o código.
	ourPuts( "Voce conhece o codigo do candidato a ser removido?\nCaso conheca, tecle 's'. Caso contrario, tecle outra letra.\n" );
	cod = getch();
	if( toUpper( cod ) != 'S' )
		menuPesquisar();

    // Leitura do código do candidato a ser removido
	ourPuts( "\nDigite o codigo do candidato a ser removido: " );
	scanf( "%d", &cod );
	
	// Mudança dos ponteiros das estruturas anterior e seguinte à estrutura removida
	for( ; auxNode != NULL; )
	{
		// Verificação se o candidato atual é o desejado.
        if( auxNode->codigoCandidato == cod )
		{
			if( auxNode == primeiroCandidato )
				primeiroCandidato = auxNode->proximo;
			if( auxNode == candidato )
				candidato = auxNode->anterior;
				
			if( auxNode->eleitor == primeiroEleitor )
				primeiroEleitor = auxNode->eleitor->proximo;
			if( auxNode->eleitor == eleitor )
				eleitor = auxNode->eleitor->anterior;
		
			if( auxNode->proximo != NULL )
				auxNode->proximo->anterior = auxNode->anterior;
			if( auxNode->anterior != NULL )
				auxNode->anterior->proximo = auxNode->proximo;
			
			if( auxNode->historico != NULL )
			{
				historicoCandidato *auxNode1, *auxNode2 = auxNode->historico;
				
				for( ; auxNode2 != NULL; )
				{
					auxNode1 = auxNode2;
					auxNode2 = auxNode2->anterior;
					free( auxNode1 );
				}
			}
			
			// Remoção do candidato de fato, desalocação da memória reservada para ele.
			free( auxNode->eleitor );
			free( auxNode );
			
			ourPuts( "\nCandidato removido.\n" );
			
			// Pausa, caso retorne para uma função que limpe a tela.
            pausaPrograma();
            
			return;
		}
		
		// Caso o candidato atual não seja o desejado, trocar pelo anterior dele.
		auxNode = auxNode->anterior;
	}
	
	// Resposta caso percorra toda a lista e não encontre candidatos com este cod.
	ourPuts( "\nNao ha candidato registrado com este codigo.\n" );
	
	// Pausa, caso retorne para uma função que limpe a tela.
    pausaPrograma();
    
	return;
}

void editaCandidato()
{
	uint32 cod;
	infoCandidatos *auxNode = candidato;
	uint8 opt, campo[3][18] = { "Nome do Partido", "Sigla do Partido", "Cargo a Disputar" };
	
	// Alocação de um vetor que servirá para armazenar uma informação que irá sobrescrever um dado.
    string new = (string)calloc( 51, sizeof( uint8 ) );

    // Se ouver falha na alocação da memória retorna um erro.
	if( new == NULL )
	{
		ourPuts( "\n\t\tErro! #0006\n" );
		exit(1);
	}
	
	ourPuts( "\t**\tSistema de Edicao de Candidatos\t**\n" );
	
	// Busca do candidato por nome caso o usuário não saiba o código do candidato a ser alterado.
	ourPuts( "Voce conhece o codigo do eleitor a ser editado?\nCaso conheca, tecle 's'. Caso contrario, tecle outra letra.\n" );
	cod = getch();
	if( toUpper( cod ) != 'S' )
		menuPesquisar();
	
    // Leitura do código do candidato a ser alterado.	
	ourPuts( "\nDigite o codigo do eleitor a ser editado: " );
	scanf( "%u", &cod );
	
	for( ; auxNode != NULL; )
	{
		// Busca do candidato que possui este código
        if( auxNode->codigoCandidato != cod )
		{
			// Caso não seja o candidato, verificar o anterior até que seja o candidato escolhido.
            auxNode = auxNode->anterior;
			continue;
		}
		
		for( ; ; )
		{
			// Caso se repita não encher muito a tela.
            limpaTela();
			
            // Imprime as informações do candidato encontrado na tela.
            imprimeCandidato( auxNode );
			
			ourPuts( "\nQual campo voce deseja editar?\nDigite o numero correspondente a opcao escolhida.\n" );
			ourPuts( "[1] Nome do Paritod\n[2] Sigla do Partido\n[3] Cargo a Disputar\n[4] Cancelar Edicao\n" );
			opt = getch() - 48;
			
			// Opção de escape
			if( opt == 4 )
				return;
			
			// Caso a opção escolhida não esteja na lista, repetir.
			else if( opt < 1 || opt > 4 )
				continue;

			printf( "Digite %c %s %s: ", ( (opt % 2) ? 'o':'a' ), ( (opt % 2) ? "novo":"nova" ), ( campo[opt-1] ) );
			
			// Se a opção não for a do cargo, ler uma string (Nome ou sigla do partido).
			if( opt != 3 )
			{
				ourGets( new );
				new[ ourStrLen( new ) - 1 ] = 0;
			}
			
			// Se for alterar o cargo, apresentar as opções e pedir que insira o novo cargo.
			else
			{
				ourPuts( "\n[1] Vereador\n[2] Prefeito\n[3] Deputado Estadual\n[4] Deputado Federal\n[5] Senador\n[6] Governador\n[7] Presidente\n" );
				
                // Verificação se a opção escolhida está no intervalo, caso não esteja, repita.
                for( *new = getche() - 48; *new < 1 || *new > 7; *new = getche() - 48 )
					ourPuts( "\nCargo inexistente. Tente novamente: " );
			}

			printf( "\n%s %s: \"%s\"\nEsta correto?\nTecle 's' em caso afirmativo ou qualquer outra letra em caso negativo.\n", ( (opt % 2) ? "Novo":"Nova" ), ( campo[opt-1] ), ( (opt == 3) ? id2Cargo(*new) : new ) );
			
			// Pergunta para uma possível correção (Repetição da função).
			cod = getch();
			if( toUpper( cod ) != 'S' )
				continue;
			
			// Atribuição do valor inserido no registro do candidato.
			switch( opt )
			{
				case 1:
					ourStrCpy( auxNode->partido.nome, new );
				break;
				
				case 2:
					ourStrCpy( auxNode->partido.sigla, new );
				break;
				
				case 3:
					auxNode->partido.cargo = *new;
				break;
			}
		}
	}
	
	ourPuts( "\nCandidato editado.\n" );
	
    // Desalocação da memória reservada ao vetor.
    free( new );
    
    // Pausa, caso retorne para uma função que limpe a tela.
    pausaPrograma();
	return;
}


void ordenaCandidatos( uint8 tipo, string cidade, string partido, uint8 cargo, string estado )
{
	// Declaração e inicialização de variáveis
	infoCandidatos *mainNode = primeiroCandidato, *auxNode, *auxNode2 = primeiroCandidato;
	uint32 x = 1;
		
	// Laço para ordenação de eleitores, de acordo com o tipo recebido como parâmetro
	// Mais informações no protótipo da função
	// Haverá dois ponteiros percorrendo todas as estruturas e realizando as comparações e trocas de posições, se necessário for
	for( ; x < codigoCandidatoGlobal; ++x )
		for( mainNode = primeiroCandidato; mainNode != NULL; mainNode = mainNode->proximo )
			for( auxNode = mainNode->proximo; auxNode != NULL; auxNode = auxNode->proximo )
				switch( tipo )
				{
					case 1:
						// Procedimento padrão:
						// Verificação da ordenação
						if( ourStrCmp( mainNode->eleitor->pessoal.nomeCompleto, auxNode->eleitor->pessoal.nomeCompleto ) == 1 )
						{
							// Macro [generalHeader.h] para troca das posições
							swapP( mainNode, auxNode );
						
							// Organiza o Primeiro e o Último elementos
							if( mainNode == primeiroCandidato )
								primeiroCandidato = auxNode;
							if( auxNode == candidato )
								candidato = mainNode;
						}
					break;
	
					case 2:
						if( ourStrCmp( mainNode->eleitor->pessoal.cidade, auxNode->eleitor->pessoal.cidade ) == 1 )
						{
							swapP( mainNode, auxNode );
						
							if( mainNode == primeiroCandidato )
								primeiroCandidato = auxNode;
							if( auxNode == candidato )
								candidato = mainNode;
						}
					break;
	
					case 3:
						if( ourStrCmp( mainNode->eleitor->pessoal.estado, auxNode->eleitor->pessoal.estado ) == 1 )
						{
							swapP( mainNode, auxNode );
						
							if( mainNode == primeiroCandidato )
								primeiroCandidato = auxNode;
							if( auxNode == candidato )
								candidato = mainNode;
						}
					break;
			
					case 4:
						if( mainNode->codigoCandidato > auxNode->codigoCandidato )
						{
							swapP( mainNode, auxNode );
						
							if( mainNode == primeiroCandidato )
								primeiroCandidato = auxNode;
							if( auxNode == candidato )
								candidato = mainNode;
						}
					break;
					
					case 5:
						if( ourStrCmp( mainNode->partido.nome, auxNode->partido.nome ) == 1 )
						{
							swapP( mainNode, auxNode );
						
							if( mainNode == primeiroCandidato )
								primeiroCandidato = auxNode;
							if( auxNode == candidato )
								candidato = mainNode;
						}
					break;
					
					case 6:
						if( ourStrCmp( id2Cargo( mainNode->partido.cargo ), id2Cargo( auxNode->partido.cargo ) ) == 1 )
						{
							swapP( mainNode, auxNode );
						
							if( mainNode == primeiroCandidato )
								primeiroCandidato = auxNode;
							if( auxNode == candidato )
								candidato = mainNode;
						}
					break;
				}
			// end-for
		// end-for
	// end-for
	
	// Chamada à função de listagem
	listaCandidatosOrdenadamente( cidade, partido, cargo, estado );
	
	return;
}

void listaCandidatosOrdenadamente( string cidade, string partido, uint8 cargo, string estado )
{
	// Declaração e inicialização da variável com ponteiro para o primeiro eleitor da lista
	infoCandidatos *node = primeiroCandidato;
	
	// Laço para listagem
	for( ; node != NULL; node = node->proximo )
	{
		// Verificação da existência de parâmetros válidos e comparação com os dados do eleitor
		if( ( cidade != NULL && ourStrCmp( node->eleitor->pessoal.cidade, cidade ) != 0 )
		 || ( partido != NULL && ourStrCmp( node->partido.nome, partido ) != 0 )
		 || ( cargo != 0 && node->partido.cargo != cargo )
		 || ( estado != NULL && ourStrCmp( node->eleitor->pessoal.estado, estado ) != 0 ) )
			// Caso o eleitor não cumpra os requisitos
			continue;
		
		// Exibição
		printf( " [#%d] %s \t %s \t %s \t %s\n", node->codigoCandidato, node->eleitor->pessoal.nomeCompleto, node->eleitor->pessoal.cidade, node->eleitor->pessoal.estado, id2Cargo( node->partido.cargo ) );
	}

	return;
}

infoEleitores * buscaCandidatoPorCodigo( uint32 cod )
{
	// Declaração e inicialização de variável auxiliar
	infoCandidatos *auxNode1 = primeiroCandidato;
	
	// Varredura da lista em busca do código recebido como parâmetro
	for( ; auxNode1 != NULL; auxNode1 = auxNode1->proximo )
		if( auxNode1->codigoCandidato == cod )
			// Caso seja encontrado, será retornado
			return auxNode1->eleitor;
	
	// Caso não seja encontrado, um ponteiro nulo é retornado
	return NULL;
}

uint8 * id2Cargo( uint8 id )
{
	// Conversão do cargo de ID para Nome
	switch( id )
	{
		case 1:
			return "Vereador";
		case 2:
			return "Prefeito";
		case 3:
			return "Deputado Estadual";
		case 4:
			return "Deputado Federal";
		case 5:
			return "Senador";
		case 6:
			return "Governador";
		case 7:
			return "Presidente";
		
		default:
			return NULL;
	}
}

historicoCandidato * insereHistorico( infoCandidatos *node, uint16 ano, uint32 votos, uint8 cargo )
{
	// Declaração e inicialização de variáveis
	historicoCandidato *newNode, *auxNode;
	
	// Varredura das estruturas de histórico de eleições
	for( auxNode = node->historico; auxNode != NULL; auxNode = auxNode->anterior )
		// Caso o ano recebido como parâmetro seja o mesmo encontrado em alguma instância, não será criada uma nova
		if( auxNode->ano == ano )
		{
			// Atualização dos dados
			auxNode->cargo = cargo;
			auxNode->votos = votos;
			
			// Este nó passará a ser o nó ligado diretamente à estrutura do candidato
			
			if( auxNode->anterior != NULL )
				auxNode->anterior->proximo = auxNode->proximo;
			
			if( auxNode->proximo != NULL )
				auxNode->proximo->anterior = auxNode->anterior;
			
			node->historico->proximo = auxNode;
			
			auxNode->anterior = node->historico;
			auxNode->proximo = NULL;
			
			node->historico = auxNode;
			
			// Retorna a estrutura em questão
			return auxNode;
		}
	
	// Caso não haja estrutura com mesmo ano que o parâmetro recebido, uma nova será criada
	
	// Alocação de memória
	newNode = (historicoCandidato*) calloc( 1, sizeof( historicoCandidato ) );
	if( newNode == NULL )
	{
		ourPuts( "Erro! #0015\n" );
		pausaPrograma();
		return NULL;
	}
	
	// Inserção das informações e ajustes para que esta seja ligada diretamente à estrutura do candidato
	auxNode = node->historico;
	
	newNode->ano = ano;
	newNode->votos = votos;
	newNode->cargo = cargo;
	
	newNode->proximo = NULL;
	newNode->anterior = auxNode;
	
	if( auxNode != NULL )
		auxNode->proximo = newNode;
	
	node->historico = newNode;
	
	
	// Retorna a nova estrutura
	return newNode;
}

bool verificaCodigoCandidatoEmUso( uint32 cod )
{
	// Declaração e inicialização de variável auxiliar
	infoCandidatos *auxNode1 = primeiroCandidato;
	
	// Verificação da existência de candidato com tal código
	if( buscaCandidatoPorCodigo( cod ) != NULL )
	{
		// Caso haja, mensagem na tela e retorno apropriado
		printf( "O codigo de candidato %d ja estava sendo utilizado. A priridade foi dada ao candidato existente na memoria.\n" );
		return true;
	}
	
	// Caso não haja
	return false;
}


// Funções de uso externo
// Intuitivas

uint32 retornaCodigoCandidatoGlobal()
{
	return codigoCandidatoGlobal;
}

infoCandidatos * retornaPrimeiroCandidato()
{
	return primeiroCandidato;
}

infoCandidatos * retornaCandidato()
{
	return candidato;
}

void atualizaCodigoCandidatoGlobal( uint32 x )
{
	codigoCandidatoGlobal = max( x, codigoCandidatoGlobal );
}

void atualizaPrimeiroCandidato( infoCandidatos *node )
{
	primeiroCandidato = node;
}

void atualizaCandidato( infoCandidatos *node )
{
	candidato = node;
}

