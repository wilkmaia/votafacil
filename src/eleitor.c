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

	Arquivo com fun��es e defini��es gerais acerca de eleitores.
	
******************************************************************************/

#include "mainHeader.h"

infoEleitores * cadastraEleitor()
{
	// Declara��o e inicializa��o de vari�veis
	uint8 a[101] = {}, b[31] = {}, c[20] = {}, d[11] = {}, x = 0;
	
	for( ; ; )
	{
		a[0] = b[0] = c[0] = 0;
	
		// Limpa a tela
		limpaTela();
		
		// Recebe as informa��es do eleitor
		ourPuts( "\t**\tSistema de Cadastro de Eleitores\t**\n" );
		ourPuts( "Digite o nome completo do eleitor: " );
		for( ; a[0] == 0 || a[0] == '\n'; )
			ourGets( a );
		a[ ourStrLen( a ) - 1 ] = 0;
		
		ourPuts( "Digite a cidade do eleitor: " );
		for( ; b[0] == 0 || b[0] == '\n'; )
			ourGets( b );
		b[ ourStrLen( b ) - 1 ] = 0;
		
		ourPuts( "Digite o estado do eleitor: " );
		for( ; c[0] == 0 || c[0] == '\n'; )
			ourGets( c );
		c[ ourStrLen( c ) - 1 ] = 0;
		
		// M�scara de nascimento, utilizando getch e havendo a possibilidade de utilizar o BACKSPACE.
		ourPuts( "Digite a data de nascimento do eleitor (Formato: DD/MM/AAAA): " );
		for( x = 0 ; x < 10; ++x )
		{
			if( x == 2 || x == 5 )
				d[x] = '/';
			else
			{
				d[x] = getch();
				
				// Se o caractere n�o for um n�mero nem a tecla BACKSPACE, a posi��o no vetor ser� retornada.
				if( isNum( d[x] ) == -1 && d[x] != 8 )
				{
					--x;
					continue;
				}
				
				// Se o caractere pressionado for BACKSPACE.
				if( d[x] == 8 )
				{
					// Se foi pressionado na primeira posi��o do vetor.
                    if( x == 0 )
					{
						--x;
						continue;
					}
					
					// Se for um caractere ap�s um '/', deve retornar 2 posi��es no vetor, apagando o que foi impresso.
					if( x == 3 || x == 6 )
					{
						gotoxy( wherex()-1, wherey() );
						putch( ' ' );
						gotoxy( wherex()-2, wherey() );
						putch( ' ' );
						gotoxy( wherex()-1, wherey() );
						x -= 3;
						continue;
					}
					
                    // Se n�o for depois de um '/', voltar apenas uma posi��o no vetor e apagar o que foi impresso.
                    gotoxy( wherex()-1, wherey() );
					putch( ' ' );
					gotoxy( wherex()-1, wherey() );
					x -= 2;
					continue;
				}
			}
			
			putch( d[x] );
		}
		
		// Verifica��o se h� necessidade de uma repeti��o.
		ourPuts( "As informacoes digitadas estao corretas?\n" );
		ourPuts( "Em caso afirmativo, tecle 's'. Em caso negativo, qualquer outra tecla.\n" );
		x = getch();
		if( toUpper( x ) == 'S' )
			break;
	}
	
	// Atribui as informa��es lidas na fun��o para um registro na mem�ria.
	insereEleitor( a, b, c, d, tituloEleitorGlobal );
	
	// Incremento da vari�vel que determina o t�tulo de eleitor.
	++tituloEleitorGlobal;
    
	// Retorna um ponteiro que aponta para a estrutura do eleitor.   
	return eleitor;
}

infoEleitores * insereEleitor( string a, string b, string c, string d, uint32 e )
{
	// Aloca��o da mem�ria que ser� utilizada para armazenar os dados do eleitor.
    infoEleitores *novoEleitor = (infoEleitores *) calloc( 1, sizeof( infoEleitores ) );
	
	// Verifica��o de falha na aloca��o, caso n�o haja espa�o na mem�ria
    // a fun��o calloc retorna um ponteiro apontando para NULL.
    if( novoEleitor == NULL )
	{
		ourPuts( "\n\t\tErro! #0002\n" );
		exit(1);
	}
	
	// Atribui��o dos valores lidos na fun��o cadastraEleitor() na mem�ria alocada
	novoEleitor->tituloEleitor = e;
	ourStrCpy( novoEleitor->pessoal.nomeCompleto, a );
	ourStrCpy( novoEleitor->pessoal.cidade, b );
	ourStrCpy( novoEleitor->pessoal.estado, c );
	ourStrCpy( novoEleitor->pessoal.dataNascimento, d );
	novoEleitor->eleitorCandidato = NULL;
	novoEleitor->proximo = NULL;
	
	// Caso seja o primeiro eleitor cadastrado, n�o apontar� para um anterior.
	if( e == 1 )
	{
		novoEleitor->anterior = NULL;
		primeiroEleitor = novoEleitor;
	}
	
	// Caso n�o seja o primeiro, o ultimo eleitor cadastrado ser� o anterior ao novo eleitor.
	// Como a lista � duplamente encadeada, o ultimo eleitor cadastrado tamb�m apontar� para o novo eleitor.
	else
	{
		eleitor->proximo = novoEleitor;
		novoEleitor->anterior = eleitor;
	}
	
	// Incremento da posi��o do ultimo eleitor cadastrado.
	eleitor = novoEleitor;
	
	// A fun��o retorna um ponteiro apontando para o ultimo eleitor cadastrado.
	return eleitor;
}

void imprimeEleitor( infoEleitores *node )
{
    // Retornar erro na busca caso o ponteiro passado para a fun��o aponte para NULL.
    if( node == NULL )
	{
		ourPuts( "\n\nA busca nao gerou resultado.\n" );
		return;
	}
	
	// Imprime as informa��es do eleitor na tela.
	printf( "\nCodigo: %d\tNome Completo: %s\n", node->tituloEleitor, node->pessoal.nomeCompleto );
	printf( "Cidade: %s\tEstado: %s\n", node->pessoal.cidade, node->pessoal.estado );
	printf( "Data de Nascimento: %s\n", node->pessoal.dataNascimento );
	
	// Se o eleitor for tamb�m candidato, imprimir as informa��es do candidato.
	if( node->eleitorCandidato != NULL )
		imprimeCandidato( node->eleitorCandidato );
}

void removeEleitor()
{
	// Declara��o e inicializa��o de vari�veis
	uint32 cod;
	infoEleitores *auxNode = eleitor;
	
	ourPuts( "\t**\tSistema de Remocao de Eleitores\t**\n" );
	
	// Busca de eleitor por nome, caso o usuario n�o conhe�a o c�digo.
	ourPuts( "Voce conhece o codigo do eleitor a ser removido?\nCaso conheca, tecle 's'. Caso contrario, tecle outra letra.\n" );
	cod = getch();
	if( toUpper( cod ) != 'S' )
		menuPesquisar();
	
    // Leitura do t�tulo do eleitor a ser removido.
	ourPuts( "\nDigite o titulo do eleitor a ser removido: " );
	scanf( "%d", &cod );
	
	// Mudan�a dos ponteiros das estruturas anterior e seguinte � estrutura removida
	for( ; auxNode != NULL; )
	{
		// Verifica��o se o eleitor atual � o desejado.
        if( auxNode->tituloEleitor == cod )
		{
			if( auxNode == primeiroEleitor )
				primeiroEleitor = auxNode->proximo;
			if( auxNode == eleitor )
				eleitor = auxNode->anterior;
			
			if( auxNode->proximo != NULL )
				auxNode->proximo->anterior = auxNode->anterior;
			if( auxNode->anterior != NULL )
				auxNode->anterior->proximo = auxNode->proximo;
			
			// Desvincula��o dos ponteiros do registro do candidato, caso seja.
			if( auxNode->eleitorCandidato != NULL )
			{
				if( auxNode->eleitorCandidato->proximo != NULL )
					auxNode->eleitorCandidato->proximo->anterior = auxNode->eleitorCandidato->anterior;
				if( auxNode->eleitorCandidato->anterior != NULL )
					auxNode->eleitorCandidato->anterior->proximo = auxNode->eleitorCandidato->proximo;
				
				// Remo��o do cadastro de candidato, caso o eleitor seja tamb�m candidato.
				free( auxNode->eleitorCandidato );
			}
			
			// Remo��o do eleitor de fato, desaloca��o da mem�ria reservada para ele.
			free( auxNode );
			
		    ourPuts( "\nEleitor removido.\n" );
		
		    // Pausa, caso retorne para uma fun��o que limpe a tela.
            pausaPrograma();
		
            return;	
		}
		
		// Caso o eleitor atual n�o seja o desejado, trocar pelo anterior dele.
		auxNode = auxNode->anterior;
		

	}
	
	// Resposta caso percorra toda a lista e n�o encontre eleitores com este t�tulo.
	ourPuts( "\nNao ha eleitor registrado com este titulo.\n" );
	
	// Pausa, caso retorne para uma fun��o que limpe a tela.
    pausaPrograma();
    
	return;
}

void editaEleitor()
{
	// Declara��o e inicializa��o de vari�veis
	uint32 cod;
	infoEleitores *auxNode = eleitor;
	uint8 opt, campo[4][19] = { "Nome Completo", "Cidade", "Estado", "Data de Nascimento" };
	uint8 new[101], x;
	
	ourPuts( "\t**\tSistema de Edicao de Eleitores\t**\n" );
	
	// Busca de eleitor por nome caso o usu�rio n�o saiba o titulo do eleitor que ser� alterado.
	ourPuts( "Voce conhece o codigo do eleitor a ser editado?\nCaso conheca, tecle 's'. Caso contrario, tecle outra letra.\n" );
	cod = getch();
	if( toUpper( cod ) != 'S' )
		menuPesquisar();
		
	// Leitura do t�tulo do eleitor a ser alterado.
	ourPuts( "\nDigite o titulo do eleitor a ser editado: " );
	scanf( "%u", &cod );
	
	for( ; auxNode != NULL; )
	{
		// Busca do eleitor que possui este t�tulo.
        if( auxNode->tituloEleitor != cod )
		{
			// Caso n�o seja o eleitor, verificar o anterior at� que seja o eleitor escolhido.
            auxNode = auxNode->anterior;
			continue;
		}
		
		for( ; ; )
		{
			// Caso se repita n�o encher muito a tela.
            limpaTela();
			
            // Imprime as informa��es do eleitor encontrado na tela.
            imprimeEleitor( auxNode );
			
			ourPuts( "\nQual campo voce deseja editar?\nDigite o numero correspondente a opcao escolhida.\n" );
			ourPuts( "[1] Nome\n[2] Cidade\n[3] Estado\n[4] Data de Nascimento\n[5] Cancelar Edicao\n" );
			opt = getch() - 48;
			
			// Op��o de escape
			if( opt == 5 )
				return;
			
			// Caso a op��o escolhida n�o esteja na lista, repetir.
			else if( opt < 1 || opt > 5 )
				continue;

			printf( "Digite %c %s %s: ", ( (opt % 2) ? 'o':'a' ), ( (opt % 2) ? "novo":"nova" ), ( campo[opt-1] ) );

			// Se a op��o n�o for a da data de nascimento, ler uma string (Nome ,cidade ou estado).
            if( opt != 4 )
			{
				ourGets( new );
				new[ ourStrLen( new ) - 1 ] = 0;
			}
			
			// M�scara de nascimento
            else
   	            for( opt = 0 ; opt < 10; ++opt )
				{
					if( opt == 2 || opt == 5 )
						new[opt] = '/';
					else
					{
						new[opt] = getch();
				
						if( isNum( new[opt] ) == -1 )
						{
							--opt;
							continue;
						}
					}
			
					putch( new[opt] );
				}
			
			printf( "%s %s: \"%s\"\nDeseja realmente alterar?\nTecle 's' em caso afirmativo ou qualquer outra letra em caso negativo.\n", ( (opt % 2) ? "Novo":"Nova" ), ( campo[opt-1] ), new );
			
			// Verifica��o de necessidade de repeti��o.
			cod = getch();
			if( toUpper( cod ) != 'S' )
				continue;
			
			// Atribui��o do valor inserido no registro do eleitor.
			switch( opt )
			{
				case 1:
					ourStrCpy( auxNode->pessoal.nomeCompleto, new );
				break;
				
				case 2:
					ourStrCpy( auxNode->pessoal.cidade, new );
				break;
				
				case 3:
					ourStrCpy( auxNode->pessoal.estado, new );
				break;
				
				case 4:
					ourStrCpy( auxNode->pessoal.dataNascimento, new );
				break;
			}
		}
	}
	
	ourPuts( "\nEleitor editado.\n" );
	
	// Pausa, caso retorne para uma fun��o que limpe a tela.
    pausaPrograma();
	
	return;
}


void ordenaEleitores( uint8 tipo, string cidade, string estado )
{
	// Declara��o e inicializa��o de vari�veis
	infoEleitores *mainNode = primeiroEleitor, *auxNode;
	uint32 x = 1;
	
	// La�o para ordena��o de eleitores, de acordo com o tipo recebido como par�metro
	// Mais informa��es no prot�tipo da fun��o
	// Haver� dois ponteiros percorrendo todas as estruturas e realizando as compara��es e trocas de posi��es, se necess�rio for
	for( ; x < tituloEleitorGlobal; ++x )
		for( mainNode = primeiroEleitor; mainNode != NULL; mainNode = mainNode->proximo )
			for( auxNode = mainNode->proximo; auxNode != NULL; auxNode = auxNode->proximo )
				switch( tipo )
				{
					case 1:
						// Procedimento padr�o:
						// Verifica��o da ordena��o
						if( ourStrCmp( mainNode->pessoal.nomeCompleto, auxNode->pessoal.nomeCompleto ) == 1 )
						{
							// Macro [generalHeader.h] para troca das posi��es
							swapP( mainNode, auxNode );
							
							// Organiza o Primeiro e o �ltimo elementos
							if( mainNode == primeiroEleitor )
								primeiroEleitor = auxNode;
							if( auxNode == eleitor )
								eleitor = mainNode;
						}
					break;
	
					case 2:
						if( ourStrCmp( mainNode->pessoal.cidade, auxNode->pessoal.cidade ) == 1 )
						{
							swapP( mainNode, auxNode );
							
							if( mainNode == primeiroEleitor )
								primeiroEleitor = auxNode;
							if( auxNode == eleitor )
								eleitor = mainNode;
						}
					break;
	
					case 3:
						if( ourStrCmp( mainNode->pessoal.estado, auxNode->pessoal.estado ) == 1 )
						{
							swapP( mainNode, auxNode );
							
							if( mainNode == primeiroEleitor )
								primeiroEleitor = auxNode;
							if( auxNode == eleitor )
								eleitor = mainNode;
						}
					break;
			
					case 4:
						if( mainNode->tituloEleitor > auxNode->tituloEleitor )
						{
							swapP( mainNode, auxNode );
							
							if( mainNode == primeiroEleitor )
								primeiroEleitor = auxNode;
							if( auxNode == eleitor )
								eleitor = mainNode;
						}
					break;
				}
			// end-for
		// end-for
	// end-for
	
	// Chamada � fun��o de listagem
	listaEleitoresOrdenadamente( cidade, estado );
	
	return;
}

void listaEleitoresOrdenadamente( string cidade, string estado )
{
	// Declara��o e inicializa��o da vari�vel com ponteiro para o primeiro eleitor da lista
	infoEleitores *node = primeiroEleitor;
	
	// La�o para listagem
	for( ; node != NULL; node = node->proximo )
	{
		// Verifica��o da exist�ncia de par�metros v�lidos e compara��o com os dados do eleitor
		if( ( cidade != NULL && ourStrCmp( node->pessoal.cidade, cidade ) != 0 )
		 || ( estado != NULL && ourStrCmp( node->pessoal.estado, estado ) != 0 ) )
			// Caso o eleitor n�o cumpra os requisitos
			continue;
		
		// Exibi��o
		printf( " [#%d] %s \t %s \t %s\n", node->tituloEleitor, node->pessoal.nomeCompleto, node->pessoal.cidade, node->pessoal.estado );
	}
	
	return;
}

void buscaPorNome( string nome )
{
	// Declara��o e inicializa��o de vari�veis
	infoEleitores *auxNode = primeiroEleitor;
	uint32 cont = 0;
	
	ourPuts( "\n\t**\tRealizando busca...\t**\n" );
	
	// Varredura das estruturas da lista
	for( ; auxNode != NULL; auxNode = auxNode->proximo )
		// Caso a substring digitada esteja contida no nome do eleitor
		if( ourStrIsIn( nome, auxNode->pessoal.nomeCompleto ) == 1 )
		{
			// Incremento da vari�vel de contagem e exibi��o de informa��es do Eleitor
			++cont;
			printf( "Titulo Eleitor: %d  *  Nome: %s  *  Cidade: %s  *  Candidato? %s\n", auxNode->tituloEleitor, auxNode->pessoal.nomeCompleto, auxNode->pessoal.cidade, (auxNode->eleitorCandidato == NULL ? "Nao" : "Sim") );
		}
	
	// Caso n�o haja registros encontrados.
	if( cont == 0 )
	{
		ourPuts( "\nNao foram encontrados registros.\n" );
		pausaPrograma();
		return;
	}
	
	// Caso haja registros.
	printf( "\nForam encontrados %d registros.\n", cont );
	pausaPrograma();
	return;
}

infoEleitores * buscaEleitorPorCodigo( uint32 cod )
{
	// Inicializa��o no primeiro registro de Eleitor.
    infoEleitores *auxNode1 = primeiroEleitor;
    
	// Incremento de registro (Passagem para o pr�ximo apontado). 
	for( ; auxNode1 != NULL; auxNode1 = auxNode1->proximo )
	
        // Verifica��o se o eleitor possui o t�tulo inserido.
		if( auxNode1->tituloEleitor == cod )
			return auxNode1;
	
	// Caso n�o encontre, retorna um ponteiro apontando para NULL.
    return NULL;
}

void limpaMemoria()
{
	// Declara��o de vari�vel auxiliar
	infoEleitores *auxNode;
	
	// La�o para limpeza da mem�ria de armazenamento das estruturas
	for( ; eleitor != NULL; )
	{
		// Atribui��o a auxNode com a posi��o para a �ltima estrutura de eleitor
		auxNode = eleitor;
		
		// Caso o eleitor seja candidato, as informa��es de candidato dele devem ser apagadas
		if( auxNode->eleitorCandidato != NULL )
		{
			// Caso haja hist�rico de elei��o associado.
			if( auxNode->eleitorCandidato->historico != NULL )
			{
				// Declara��o e inicializa��o de vari�veis
				historicoCandidato *auxNode1, *auxNode2 = auxNode->eleitorCandidato->historico;
				
				// Limpeza do hist�rico de elei��es
				for( ; auxNode2 != NULL; )
				{
					auxNode1 = auxNode2;
					auxNode2 = auxNode2->anterior;
					free( auxNode1 );
				}
			}
			
			// Limpeza das informa��es de candidato
			free( auxNode->eleitorCandidato );
		}
		
		// eleitor aponta para a posi��o anterior e limpeza da posi��o atual
		eleitor = eleitor->anterior;
		free( auxNode );
	}
	return;
}

void saveBackUpPessoal()
{
	FILE *f = fopen( "pessoal.dat", "wb" );
	
	// Garantia de espa�o suficiente
	// Informa��es de Eleitor: 173 bytes
	// Informa��es de Candidato: 60 bytes
	// Informa��es de Hist�rico de Elei��o: 15 bytes (por elei��o)
	//
	// V�rgulas:
	//  - Informa��es de Eleitor: 4 bytes
	//  - Informa��es de Candidato: 4 bytes
	//  - Hist�rico de Elei��o: 3 bytes (por elei��o)
	//
	// Caractere final do buffer - quebra de linha: 1 byte
	// Caractere nulo: 1 byte
	string buffer = (string) calloc( 173 + 4 + 2, sizeof( uint8 ) );
	
	infoEleitores *auxNode = primeiroEleitor;
	
	if( f == NULL )
	{
		ourPuts( "Erro! #0007" );
		pausaPrograma();
		exit( 1 );
	}
	
	if ( buffer == NULL )
	{
		ourPuts( "Erro! #0012" );
		pausaPrograma();
		exit( 1 );
	}
	
	// Varredura das estruturas de eleitor
	for( ; auxNode != NULL; auxNode = auxNode->proximo )
	{
		// M�scara:
		// TituloEleitor,Nome,Cidade,Estado,Nascimento{,CodigoCandidato,NomePartido,SiglaPartido,Cargo{,AnoEleicao01,Votos01,Cargo01,AnoEleicao02,Votos02,Cargo02,...}}
		
		// Armazenar em buffer as informa��es de eleitor
		sprintf( buffer, "%d,%s,%s,%s,%s", auxNode->tituloEleitor, auxNode->pessoal.nomeCompleto, auxNode->pessoal.cidade, auxNode->pessoal.estado, auxNode->pessoal.dataNascimento);
		
		// Caso o eleitor seja candidato
		if( auxNode->eleitorCandidato != NULL )
		{
			infoCandidatos *__cand = auxNode->eleitorCandidato;
			
			// Realoca��o de mem�ria para buffer
			if( ( buffer = (string) realloc( buffer, ( 173 + 60 + 8 + 2 ) * sizeof( uint8 ) ) ) == NULL )
			{
				ourPuts( "Erro! #0008" );
				pausaPrograma();
				exit( 1 );
			}
			
			// Armazenar em buffer as informa��es de candidato TAMB�M
			sprintf( buffer, "%s,%d,%s,%s,%d", buffer, __cand->codigoCandidato, __cand->partido.nome, __cand->partido.sigla, __cand->partido.cargo );
			
			// Caso haja hist�rico associado ao candidato
			if( __cand->historico != NULL )
			{
				historicoCandidato *__hist = __cand->historico;
				uint16 n = 1;
				
				// Varredura de todos os hist�ricos
				for( ; __hist != NULL; __hist = __hist->anterior, ++n )
				{
					// Realica��o de mem�ria para buffer
					if( ( buffer = (string) realloc( buffer, ( 173 + 60 + 8 + n*( 15 + 3 ) + 2 ) * sizeof( uint8 ) ) ) == NULL )
					{
						ourPuts( "Erro! #0009" );
						pausaPrograma();
						exit( 1 );
					}
					
					// Armazenar em buffer as informa��es de hist�rico TAMB�M
					sprintf( buffer, "%s,%d,%d,%d", buffer, __hist->ano, __hist->votos, __hist->cargo );
				}
			}
			// Padr�o
			sprintf( buffer, "%s,,,", buffer );
		}
		else
			// Caso o eleitor n�o seja candidato
			sprintf( buffer, "%s,,,,,,,", buffer );
		
		// Adiciona uma quebra de linha ao fim de buffer e imprime no arquivo
		ourStrConcat( buffer, "\n" );
		fputs( buffer, f );
	}
	
	ourPuts( "\n\nInformacoes salvas com sucesso.\n" );
	
	// Libera��o de mem�ria e fechamento do arquivo
	free( buffer );
	fclose( f );
	
	return;
}

void loadBackUpPessoal()
{
	FILE *f = fopen( "pessoal.dat", "rb" );
	
	// Garantia de espa�o suficiente
	// Informa��es de Eleitor: 173 bytes
	// Informa��es de Candidato: 60 bytes
	// Informa��es de Hist�rico de Elei��o: 15 bytes (por elei��o)
	//
	// V�rgulas:
	//  - Informa��es de Eleitor: 4 bytes
	//  - Informa��es de Candidato: 4 bytes
	//  - Hist�rico de Elei��o: 3 bytes (por elei��o)
	//
	// Caractere final do buffer - quebra de linha: 1 byte
	// Caractere nulo: 1 byte
	string buffer = (string) calloc( 233 + 8 + 900 + 2, sizeof( uint8 ) ); // Suficiente para at� 50 inst�ncias de hist�rico de elei��o por candidado
	
	infoEleitores *auxEle;
	infoCandidatos *auxCand;
	historicoCandidato *auxHist;
	uint32 n_e = 1, n_c = 1, x, n = 0, kkk = 0;
	
	if( f == NULL )
	{
		ourPuts( "Erro! #0013" );
		pausaPrograma();
		exit( 1 );
	}
	
	if ( buffer == NULL )
	{
		ourPuts( "Erro! #0014" );
		pausaPrograma();
		exit( 1 );
	}
	
	// Leitura do arquivo linha a linha
	for( fgets( buffer, 883 + 8 + 150 + 2, f ); !feof( f ); fgets( buffer, 883 + 8 + 150 + 2, f ), ++n )
	{
		// M�scara:
		// TituloEleitor,Nome,Cidade,Estado,Nascimento{,CodigoCandidato,NomePartido,SiglaPartido,Cargo{,AnoEleicao01,Votos01,Cargo01{,AnoEleicao02,Votos02,Cargo02{,...}}}}
		
		// Divis�o da informa��o em tokens (partes menores) divididos por v�rgulas
		string *tok = ourStrGetTok( buffer, ',' );
		// N� auxiliar
		infoEleitores *auxNode1 = primeiroEleitor;
		
		// Caso o T�tulo j� esteja sendo utilizado por algum elemento presente na mem�ria
		for( ; auxNode1 != NULL; auxNode1 = auxNode1->proximo )
			if( auxNode1->tituloEleitor == atoi( tok[0] ) )
			{
				printf( "\nO titulo de eleitor %d ja estava sendo utilizado. A priridade foi dada ao eleitor existente na memoria.\n", atoi( tok[0] ) );
				break;
			}
		if( auxNode1 != NULL )
			continue;
		
		// caso o C�digo de Candidato j� esteja sendo utilizado por algum elemento presente na mem�ria
		if( verificaCodigoCandidatoEmUso( atoi( tok[5] ) ) )
			continue;
		
		// Caso o formato da linha esteja incompat�vel com o padr�o
		if( tok[4] == NULL || ( tok[5] != NULL && tok[8] == NULL ) )
		{
			printf( "\nA linha %d do arquivo pessoal.dat esta num formato desconhecido.", n+1 );
			pausaPrograma();
			continue;
		}
		
		// Verifica��o acerca do t�tulo de eleitor e inser��o do eleitor na mem�ria
		n_e = max( atoi( tok[0] ), n_e );
		auxEle = insereEleitor( tok[1], tok[2], tok[3], tok[4], atoi( tok[0] ) );

		
		//
		// Informa��es de Candidato
		//
		
		// Caso haja informa��es de candidato
		if( tok[5] != NULL )
		{	
			// Verifica��o acerca do c�digo de candidato e inser��o do candidato na mem�ria
			n_c = max( atoi( tok[5] ), n_c );
			auxCand = insereCandidato( atoi( tok[5] ), tok[6], tok[7], atoi( tok[8] ) );
			auxCand->eleitor = auxEle;
			auxEle->eleitorCandidato = auxCand;
			
			// Historico Candidato
			for( x = 0; tok[9 + 3*x] != NULL; ++x )
				// Inser��o de hist�ricos de candidato enquanto existirem na linha lida (limite de 50)
				auxHist = insereHistorico( auxCand, atoi( tok[9 + 3*x] ), atoi( tok[10 + 3*x] ), atoi( tok[11 + 3*x] ) );
		}
		
	}
	
	// Corre��o do T�tulo de Eleitor e C�digo de Candidato, de acordo com o m�ximo existente
	tituloEleitorGlobal = max( tituloEleitorGlobal, n_e + 1 );
	atualizaCodigoCandidatoGlobal( n_c + 1 );
	
	ourPuts( "\n\nInformacoes carregadas com sucesso.\n" );
	
	// Limpeza da mem�ria armazenada para buffer e fechamento do arquivo
	free( buffer );
	fclose( f );
	
	return;
}


uint32 * eleitorVota( infoEleitores *node, uint8 tipo )
{
	// Declara��o e inicializa��o de vari�veis
	// tipo == 1 : Elei��es a n�vel estadual / nacional
	// tipo == 0 : Elei��es a n�vel municipal
	uint32 *escolha = (uint32 *) calloc( ( tipo ? 5 : 2 ), sizeof( uint32 ) ), *quant = (uint32 *) calloc( ( tipo ? 5 : 2 ), sizeof( uint32 ) );
	infoEleitores *cand;
	infoCandidatos *aux;
	uint8 k;
	
	// Verifica��o da quantidade de candidatos por cidade / estado e inicializa��o das posi��es de 'escolha' com valor padr�o
	for( k = 0; k < ( tipo ? 5 : 2 ); ++k )
	{
		for( aux = retornaPrimeiroCandidato(); aux != NULL; aux = aux->proximo )
			if( ( tipo == 1 && ourStrCmp( aux->eleitor->pessoal.estado, node->pessoal.estado ) == 0 && aux->partido.cargo == k + 3 )
			 || ( tipo == 0 && ourStrCmp( aux->eleitor->pessoal.cidade, node->pessoal.cidade ) == 0 && aux->partido.cargo == k + 1 ) )
				( *( quant + k ) )++;
		*( escolha + k ) = UINT32_MAX;
	}
	
	cand = NULL;
	
	// Elei��es a n�vel Estadual / Federal
	if( tipo )
	{
		ourPuts( "\n\t\t ** Listagem de candidatos permitidos: **\n\n" );
		// Cargos Estaduais
		ordenaCandidatos( 4, NULL, NULL, 3, node->pessoal.estado );
		ordenaCandidatos( 4, NULL, NULL, 4, node->pessoal.estado );
		ordenaCandidatos( 4, NULL, NULL, 5, node->pessoal.estado );
		ordenaCandidatos( 4, NULL, NULL, 6, node->pessoal.estado );
		
		// Presidente
		listaCandidatosCargo( 4, 7 );
		ourPuts( "\n\nFim da listagem." );
		
		// Informa��es do eleitor a votar e instru��es
		printf( "\n\nEleitor: %s\t\t(Titulo: #%d)\n\n", node->pessoal.nomeCompleto, node->tituloEleitor );
		ourPuts( "\nDigite os codigos dos candidatos escolhidos, a medida que os nomes dos cargos aparecerem.\nSomente os candidatos listados acima podem ser escolhidos pelo eleitor.\n\n" );
		
		// Modelo padr�o para os seguintes
		
		// Caso haja candidatos a este cargo
		if( *( quant + 0 ) )
		{
			ourPuts( "\t * Deputado Estadual * \n\n" );
			
			// Recebimento do voto
			for( ; ; )
			{
				// Listagem de candidatos aptos a serem escolhidos e c�digos pass�veis de vota��o
				ordenaCandidatos( 4, NULL, NULL, 3, node->pessoal.estado );
				ourPuts( "[#0] Branco\t[#-1] Nulo\n" );
				ourPuts( "\nCodigo: " );
				scanf( "%d", escolha );
				
				// Voto Branco || Nulo - Sai do la�o
				if( *( escolha ) == 0 || *( escolha ) == UINT32_MAX )
					break;
				
				// Candidato inv�lido || Cargo inv�lido || Localidade inv�lida
				cand = buscaCandidatoPorCodigo( *escolha );
				if( cand == NULL || cand->eleitorCandidato->partido.cargo != 3 || ourStrCmp( node->pessoal.estado, cand->pessoal.estado ) )
				{
					ourPuts( "Voto invalido!\n\n" );
					
					// Volta ao in�cio do la�o
					continue;
				}
				
				// Sai do la�o
				break;
			}
		}
		
		if( *( quant + 1 ) )
		{
			ourPuts( "\t * Deputado Federal * \n\n" );
			for( ; ; )
			{
				ordenaCandidatos( 4, NULL, NULL, 4, node->pessoal.estado );
				ourPuts( "Branco: 0\tNulo: -1\n" );
				ourPuts( "\nCodigo: " );
				scanf( "%d", escolha + 1 );
				
				if( *( escolha + 1 ) == 0 || *( escolha + 1 ) == UINT32_MAX )
					break;
				
				cand = buscaCandidatoPorCodigo( *( escolha + 1 ) );
				if( cand == NULL || cand->eleitorCandidato->partido.cargo != 4 || ourStrCmp( node->pessoal.estado, cand->pessoal.estado ) )
				{
					ourPuts( "Voto invalido!\n\n" );
					continue;
				}
				break;
			}
		}
		
		if( *( quant + 2 ) )
		{
			ourPuts( "\t * Senador * \n\n" );
			for( ; ; )
			{
				ordenaCandidatos( 4, NULL, NULL, 5, node->pessoal.estado );
				ourPuts( "Branco: 0\tNulo: -1\n" );
				ourPuts( "\nCodigo: " );
				scanf( "%d", escolha + 2 );
				
				if( *( escolha + 2 ) == 0 || *( escolha + 2 ) == UINT32_MAX )
					break;
				
				cand = buscaCandidatoPorCodigo( *( escolha + 2 ) );
				if( cand == NULL || cand->eleitorCandidato->partido.cargo != 5 || ourStrCmp( node->pessoal.estado, cand->pessoal.estado ) )
				{
					ourPuts( "Voto invalido!\n\n" );
					continue;
				}
				break;
			}
		}
		
		
		if( *( quant + 3 ) )
		{
			ourPuts( "\t * Governador * \n\n" );
			for( ; ; )
			{
				ordenaCandidatos( 4, NULL, NULL, 6, node->pessoal.estado );
				ourPuts( "Branco: 0\tNulo: -1\n" );
				ourPuts( "\nCodigo: " );
				scanf( "%d", escolha + 3 );
				
				if( *( escolha + 3 ) == 0 || *( escolha + 3 ) == UINT32_MAX )
					break;
				
				cand = buscaCandidatoPorCodigo( *( escolha + 3 ) );
				if( cand == NULL || cand->eleitorCandidato->partido.cargo != 6 || ourStrCmp( node->pessoal.estado, cand->pessoal.estado ) )
				{
					ourPuts( "Voto invalido!\n\n" );
					continue;
				}
				break;
			}
		}
		
		
		if( *( quant + 4 ) )
		{
			ourPuts( "\t * Presidente * \n\n" );
			for( ; ; )
			{
				ordenaCandidatos( 4, NULL, NULL, 7, NULL );
				ourPuts( "Branco: 0\tNulo: -1\n" );
				ourPuts( "\nCodigo: " );
				scanf( "%d", escolha + 4 );
				
				if( *( escolha + 4 ) == 0 || *( escolha + 4 ) == UINT32_MAX )
					break;
				
				cand = buscaCandidatoPorCodigo( *( escolha + 4 ) );
				if( cand == NULL || cand->eleitorCandidato->partido.cargo != 7 )
				{
					ourPuts( "Voto invalido!\n\n" );
					continue;
				}
				break;
			}
		}
		
		// Libera��o da mem�ria armazenada em quant e retorno do endere�o de mem�ria de 'escolha'.
		free( quant );
		return escolha;
	}
	
	// Elei��o a n�vel municipal - mesmo modelo das elei��es a n�vel estadual / nacional
	
	ourPuts( "\n\t\t ** Listagem de candidatos permitidos: **\n\n" );
	
	// Cargos Municipais
	ordenaCandidatos( 4, node->pessoal.cidade, NULL, 1, NULL );
	ordenaCandidatos( 4, node->pessoal.cidade, NULL, 2, NULL );
	
	ourPuts( "\n\nFim da listagem." );
	
	printf( "\n\nEleitor: %s\t\t(Titulo: #%d)\n\n", node->pessoal.nomeCompleto, node->tituloEleitor );
	ourPuts( "\nDigite os codigos dos candidatos escolhidos, a medida que os nomes dos cargos aparecerem.\nSomente os candidatos listados acima podem ser escolhidos pelo eleitor.\n\n" );
	
	if( *( quant + 0 ) )
	{
		ourPuts( "\n\t * Vereador * \n\n" );
		for( ; ; )
		{
			ordenaCandidatos( 4, node->pessoal.cidade, NULL, 1, NULL );
			ourPuts( "Branco: 0\tNulo: -1\n" );
			ourPuts( "\nCodigo: " );
			scanf( "%d", escolha );
			
			if( *( escolha ) == 0 || *( escolha ) == UINT32_MAX )
				break;
			
			cand = buscaCandidatoPorCodigo( *escolha );
			if( cand == NULL || cand->eleitorCandidato->partido.cargo != 1 || ourStrCmp( node->pessoal.estado, cand->pessoal.estado ) )
			{
				ourPuts( "Voto invalido!\n\n" );
				continue;
			}
			break;
		}
	}
	
	if( *( quant + 1 ) )
	{
		ourPuts( "\n\t * Prefeito * \n\n" );
		for( ; ; )
		{
			ordenaCandidatos( 4, node->pessoal.cidade, NULL, 2, NULL );
			ourPuts( "Branco: 0\tNulo: -1\n" );
			ourPuts( "\nCodigo: " );
			scanf( "%d", escolha + 1 );
			
			if( *( escolha + 1 ) == 0 || *( escolha + 1 ) == UINT32_MAX )
				break;
			
			cand = buscaCandidatoPorCodigo( *( escolha + 1 ) );
			if( cand == NULL || cand->eleitorCandidato->partido.cargo != 2 || ourStrCmp( node->pessoal.estado, cand->pessoal.estado ) )
			{
				ourPuts( "Voto invalido!\n\n" );
				continue;
			}
			break;
		}
	}
	
	free( quant );
	return escolha;
}


// Fun��es �teis para acesso de outros arquivos
// Intuitivas

void atualizaPrimeiroEleitor( infoEleitores *node )
{
	primeiroEleitor = node;
}

void atualizaEleitor( infoEleitores *node )
{
	eleitor = node;
}

uint32 retornaTituloEleitorGlobal()
{
	return tituloEleitorGlobal;
}

infoEleitores * retornaPrimeiroEleitor()
{
	return primeiroEleitor;
}

infoEleitores * retornaEleitor()
{
	return eleitor;
}

