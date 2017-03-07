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

	Arquivo com fun��es e defini��es gerais acerca de candidatos.
	
******************************************************************************/

#include "mainHeader.h"

void imprimeCandidato( infoCandidatos *cand )
{
	// Exibe as informa��es do candidato na tela.
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
		
		// Recebe as informa��es do candidato
		ourPuts( "\t**\tSistema de Cadastro de Candidatos\t**\n" );
		ourPuts( "Digite o nome completo do partido do candidato: " );
		ourGets( nome );
		nome[ ourStrLen( nome ) - 1 ] = 0;
		ourPuts( "Digite a sigla do partido do candidato: " );
		ourGets( sigla );
		sigla[ ourStrLen( sigla ) - 1 ] = 0;
		ourPuts( "Escolha o cargo ao qual o candidato concorrera:\n" );
		ourPuts( "[1] Vereador\n[2] Prefeito\n[3] Deputado Estadual\n[4] Deputado Federal\n[5] Senador\n[6] Governador\n[7] Presidente\n" );
		
		// Leitura e repeti��o at� que o valor inserido esteja no intervalo.
		for( cargo = getche() - 48; cargo < 1 || cargo > 7; cargo = getche() - 48 )
			ourPuts( "\nCargo inexistente. Tente novamente: " );
		
		// Verifica��o para uma poss�vel repeti��o.
		ourPuts( "\n\nAs informacoes digitadas estao corretas?\n" );
		ourPuts( "Em caso afirmativo, tecle 's'. Em caso negativo, qualquer outra tecla.\n" );
		x = getch();
		if( toUpper( x ) == 'S' )
			break;
	}
	
	// Atribui as informa��es lidas na fun��o para um registro na mem�ria
	insereCandidato( codigoCandidatoGlobal, nome, sigla, cargo );
	
	// Incremento da vari�vel que determina o c�digo do candidato
    ++codigoCandidatoGlobal;
	
	// Cadastro das informa��es do candidato como eleitor
	ourPuts( "\n\n\t**\tInformacoes pessoais do candidato\t**\n" );
	candidato->eleitor = cadastraEleitor();
	candidato->eleitor->eleitorCandidato = candidato;
	
	// Pausa, caso retorne para uma fun��o que limpe a tela.
    pausaPrograma();
	
	// Retorna um ponteiro que aponta para a estrutura do candidato
	return candidato;
}

infoCandidatos * insereCandidato( uint32 codigo, string nome, string sigla, uint8 cargo )
{
	// Aloca��o da mem�ria que ser� utilizada para armazenar os dados do candidato.
    infoCandidatos *novoCandidato = (infoCandidatos *) calloc( 1, sizeof( infoCandidatos ) );
	
    // Verifica��o de falha na aloca��o, caso n�o haja espa�o na mem�ria
    // a fun��o calloc retorna um ponteiro apontando para NULL.
    if( novoCandidato == NULL )
	{
		ourPuts( "\n\t\tErro! #0005\n" );
		exit(1);
	}
	
	// Atribui��o dos valores lidos na fun��o cadastraCandidado() na mem�ria alocada.
	novoCandidato->codigoCandidato = codigo;
	ourStrCpy( novoCandidato->partido.nome, nome );
	ourStrCpy( novoCandidato->partido.sigla, sigla );
	novoCandidato->partido.cargo = cargo;
	novoCandidato->proximo = NULL;
	
	// Caso seja o primeiro candidato cadastrado, n�o apontar� para um anterior.
	if( codigo == 1 )
	{
		novoCandidato->anterior = NULL;
		primeiroCandidato = novoCandidato;
	}
	
	// Caso n�o seja o primeiro, o ultimo candidato cadastrado ser� o anterior ao novo candidato.
	// Como a lista � duplamente encadeada, o ultimo candidato cadastrado tamb�m apontar� para o novo candidato.
	else
	{
		novoCandidato->anterior = candidato;
		if( candidato != NULL )
			candidato->proximo = novoCandidato;
		else
			primeiroCandidato = novoCandidato;
	}

	// Incremento da posi��o do ultimo candidato cadastrado.
	candidato = novoCandidato;
	
	// A fun��o retorna um ponteiro apontando para o ultimo candidato cadastrado.
	return candidato;
}

void removeCandidato()
{
	uint32 cod;
	infoCandidatos *auxNode = candidato;
	
	ourPuts( "\t**\tSistema de Remocao de Candidatos\t**\n" );
	
	// Busca de candidato por nome, caso o usuario n�o conhe�a o c�digo.
	ourPuts( "Voce conhece o codigo do candidato a ser removido?\nCaso conheca, tecle 's'. Caso contrario, tecle outra letra.\n" );
	cod = getch();
	if( toUpper( cod ) != 'S' )
		menuPesquisar();

    // Leitura do c�digo do candidato a ser removido
	ourPuts( "\nDigite o codigo do candidato a ser removido: " );
	scanf( "%d", &cod );
	
	// Mudan�a dos ponteiros das estruturas anterior e seguinte � estrutura removida
	for( ; auxNode != NULL; )
	{
		// Verifica��o se o candidato atual � o desejado.
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
			
			// Remo��o do candidato de fato, desaloca��o da mem�ria reservada para ele.
			free( auxNode->eleitor );
			free( auxNode );
			
			ourPuts( "\nCandidato removido.\n" );
			
			// Pausa, caso retorne para uma fun��o que limpe a tela.
            pausaPrograma();
            
			return;
		}
		
		// Caso o candidato atual n�o seja o desejado, trocar pelo anterior dele.
		auxNode = auxNode->anterior;
	}
	
	// Resposta caso percorra toda a lista e n�o encontre candidatos com este cod.
	ourPuts( "\nNao ha candidato registrado com este codigo.\n" );
	
	// Pausa, caso retorne para uma fun��o que limpe a tela.
    pausaPrograma();
    
	return;
}

void editaCandidato()
{
	uint32 cod;
	infoCandidatos *auxNode = candidato;
	uint8 opt, campo[3][18] = { "Nome do Partido", "Sigla do Partido", "Cargo a Disputar" };
	
	// Aloca��o de um vetor que servir� para armazenar uma informa��o que ir� sobrescrever um dado.
    string new = (string)calloc( 51, sizeof( uint8 ) );

    // Se ouver falha na aloca��o da mem�ria retorna um erro.
	if( new == NULL )
	{
		ourPuts( "\n\t\tErro! #0006\n" );
		exit(1);
	}
	
	ourPuts( "\t**\tSistema de Edicao de Candidatos\t**\n" );
	
	// Busca do candidato por nome caso o usu�rio n�o saiba o c�digo do candidato a ser alterado.
	ourPuts( "Voce conhece o codigo do eleitor a ser editado?\nCaso conheca, tecle 's'. Caso contrario, tecle outra letra.\n" );
	cod = getch();
	if( toUpper( cod ) != 'S' )
		menuPesquisar();
	
    // Leitura do c�digo do candidato a ser alterado.	
	ourPuts( "\nDigite o codigo do eleitor a ser editado: " );
	scanf( "%u", &cod );
	
	for( ; auxNode != NULL; )
	{
		// Busca do candidato que possui este c�digo
        if( auxNode->codigoCandidato != cod )
		{
			// Caso n�o seja o candidato, verificar o anterior at� que seja o candidato escolhido.
            auxNode = auxNode->anterior;
			continue;
		}
		
		for( ; ; )
		{
			// Caso se repita n�o encher muito a tela.
            limpaTela();
			
            // Imprime as informa��es do candidato encontrado na tela.
            imprimeCandidato( auxNode );
			
			ourPuts( "\nQual campo voce deseja editar?\nDigite o numero correspondente a opcao escolhida.\n" );
			ourPuts( "[1] Nome do Paritod\n[2] Sigla do Partido\n[3] Cargo a Disputar\n[4] Cancelar Edicao\n" );
			opt = getch() - 48;
			
			// Op��o de escape
			if( opt == 4 )
				return;
			
			// Caso a op��o escolhida n�o esteja na lista, repetir.
			else if( opt < 1 || opt > 4 )
				continue;

			printf( "Digite %c %s %s: ", ( (opt % 2) ? 'o':'a' ), ( (opt % 2) ? "novo":"nova" ), ( campo[opt-1] ) );
			
			// Se a op��o n�o for a do cargo, ler uma string (Nome ou sigla do partido).
			if( opt != 3 )
			{
				ourGets( new );
				new[ ourStrLen( new ) - 1 ] = 0;
			}
			
			// Se for alterar o cargo, apresentar as op��es e pedir que insira o novo cargo.
			else
			{
				ourPuts( "\n[1] Vereador\n[2] Prefeito\n[3] Deputado Estadual\n[4] Deputado Federal\n[5] Senador\n[6] Governador\n[7] Presidente\n" );
				
                // Verifica��o se a op��o escolhida est� no intervalo, caso n�o esteja, repita.
                for( *new = getche() - 48; *new < 1 || *new > 7; *new = getche() - 48 )
					ourPuts( "\nCargo inexistente. Tente novamente: " );
			}

			printf( "\n%s %s: \"%s\"\nEsta correto?\nTecle 's' em caso afirmativo ou qualquer outra letra em caso negativo.\n", ( (opt % 2) ? "Novo":"Nova" ), ( campo[opt-1] ), ( (opt == 3) ? id2Cargo(*new) : new ) );
			
			// Pergunta para uma poss�vel corre��o (Repeti��o da fun��o).
			cod = getch();
			if( toUpper( cod ) != 'S' )
				continue;
			
			// Atribui��o do valor inserido no registro do candidato.
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
	
    // Desaloca��o da mem�ria reservada ao vetor.
    free( new );
    
    // Pausa, caso retorne para uma fun��o que limpe a tela.
    pausaPrograma();
	return;
}


void ordenaCandidatos( uint8 tipo, string cidade, string partido, uint8 cargo, string estado )
{
	// Declara��o e inicializa��o de vari�veis
	infoCandidatos *mainNode = primeiroCandidato, *auxNode, *auxNode2 = primeiroCandidato;
	uint32 x = 1;
		
	// La�o para ordena��o de eleitores, de acordo com o tipo recebido como par�metro
	// Mais informa��es no prot�tipo da fun��o
	// Haver� dois ponteiros percorrendo todas as estruturas e realizando as compara��es e trocas de posi��es, se necess�rio for
	for( ; x < codigoCandidatoGlobal; ++x )
		for( mainNode = primeiroCandidato; mainNode != NULL; mainNode = mainNode->proximo )
			for( auxNode = mainNode->proximo; auxNode != NULL; auxNode = auxNode->proximo )
				switch( tipo )
				{
					case 1:
						// Procedimento padr�o:
						// Verifica��o da ordena��o
						if( ourStrCmp( mainNode->eleitor->pessoal.nomeCompleto, auxNode->eleitor->pessoal.nomeCompleto ) == 1 )
						{
							// Macro [generalHeader.h] para troca das posi��es
							swapP( mainNode, auxNode );
						
							// Organiza o Primeiro e o �ltimo elementos
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
	
	// Chamada � fun��o de listagem
	listaCandidatosOrdenadamente( cidade, partido, cargo, estado );
	
	return;
}

void listaCandidatosOrdenadamente( string cidade, string partido, uint8 cargo, string estado )
{
	// Declara��o e inicializa��o da vari�vel com ponteiro para o primeiro eleitor da lista
	infoCandidatos *node = primeiroCandidato;
	
	// La�o para listagem
	for( ; node != NULL; node = node->proximo )
	{
		// Verifica��o da exist�ncia de par�metros v�lidos e compara��o com os dados do eleitor
		if( ( cidade != NULL && ourStrCmp( node->eleitor->pessoal.cidade, cidade ) != 0 )
		 || ( partido != NULL && ourStrCmp( node->partido.nome, partido ) != 0 )
		 || ( cargo != 0 && node->partido.cargo != cargo )
		 || ( estado != NULL && ourStrCmp( node->eleitor->pessoal.estado, estado ) != 0 ) )
			// Caso o eleitor n�o cumpra os requisitos
			continue;
		
		// Exibi��o
		printf( " [#%d] %s \t %s \t %s \t %s\n", node->codigoCandidato, node->eleitor->pessoal.nomeCompleto, node->eleitor->pessoal.cidade, node->eleitor->pessoal.estado, id2Cargo( node->partido.cargo ) );
	}

	return;
}

infoEleitores * buscaCandidatoPorCodigo( uint32 cod )
{
	// Declara��o e inicializa��o de vari�vel auxiliar
	infoCandidatos *auxNode1 = primeiroCandidato;
	
	// Varredura da lista em busca do c�digo recebido como par�metro
	for( ; auxNode1 != NULL; auxNode1 = auxNode1->proximo )
		if( auxNode1->codigoCandidato == cod )
			// Caso seja encontrado, ser� retornado
			return auxNode1->eleitor;
	
	// Caso n�o seja encontrado, um ponteiro nulo � retornado
	return NULL;
}

uint8 * id2Cargo( uint8 id )
{
	// Convers�o do cargo de ID para Nome
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
	// Declara��o e inicializa��o de vari�veis
	historicoCandidato *newNode, *auxNode;
	
	// Varredura das estruturas de hist�rico de elei��es
	for( auxNode = node->historico; auxNode != NULL; auxNode = auxNode->anterior )
		// Caso o ano recebido como par�metro seja o mesmo encontrado em alguma inst�ncia, n�o ser� criada uma nova
		if( auxNode->ano == ano )
		{
			// Atualiza��o dos dados
			auxNode->cargo = cargo;
			auxNode->votos = votos;
			
			// Este n� passar� a ser o n� ligado diretamente � estrutura do candidato
			
			if( auxNode->anterior != NULL )
				auxNode->anterior->proximo = auxNode->proximo;
			
			if( auxNode->proximo != NULL )
				auxNode->proximo->anterior = auxNode->anterior;
			
			node->historico->proximo = auxNode;
			
			auxNode->anterior = node->historico;
			auxNode->proximo = NULL;
			
			node->historico = auxNode;
			
			// Retorna a estrutura em quest�o
			return auxNode;
		}
	
	// Caso n�o haja estrutura com mesmo ano que o par�metro recebido, uma nova ser� criada
	
	// Aloca��o de mem�ria
	newNode = (historicoCandidato*) calloc( 1, sizeof( historicoCandidato ) );
	if( newNode == NULL )
	{
		ourPuts( "Erro! #0015\n" );
		pausaPrograma();
		return NULL;
	}
	
	// Inser��o das informa��es e ajustes para que esta seja ligada diretamente � estrutura do candidato
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
	// Declara��o e inicializa��o de vari�vel auxiliar
	infoCandidatos *auxNode1 = primeiroCandidato;
	
	// Verifica��o da exist�ncia de candidato com tal c�digo
	if( buscaCandidatoPorCodigo( cod ) != NULL )
	{
		// Caso haja, mensagem na tela e retorno apropriado
		printf( "O codigo de candidato %d ja estava sendo utilizado. A priridade foi dada ao candidato existente na memoria.\n" );
		return true;
	}
	
	// Caso n�o haja
	return false;
}


// Fun��es de uso externo
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

