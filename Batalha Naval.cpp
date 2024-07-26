#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <locale>
#include <time.h>

using namespace std;

// Cabe�alho de fun��o.
void menuInicial();

void limpaTela(){
	system("CLS");
}

void iniciaTabuleiro(char tabuleiro [10] [10], char mascara [10] [10]){
	int linha, coluna;				// Vari�veis de navega��o.

	// Preenche o tabuleiro com �gua (A).
	for(linha = 0 ; linha < 10; linha ++ ){
		for(coluna = 0; coluna < 10; coluna ++){
			tabuleiro[linha] [coluna] = 'A';
			mascara[linha] [coluna] = '*';
		}
	}
}

void exibeMapa(){
	
	cout << "\n\nTABULEIRO\n\n";
	
	// Mapa indicadores de colunas
	int cont;
	
	for(cont = 0; cont < 10; cont ++){
		if(cont == 0){
			cout << "      ";
		}
		cout << cont << "   ";
	}
	cout << "\n";
	
	for(cont = 0; cont < 10; cont ++){
		if(cont == 0){
			cout << "      ";
		}
		cout << "|   ";
	}
	cout << "\n";
}

void exibeTabuleiro(char tabuleiro [10] [10], char mascara [10] [10], bool mostraGabarito){
	
	// Define as cores para alterar no tabuleiro.
	char blue[] = {0x1b, '[', '1', ';', '3', '4', 'm',0};
	char green[] = {0x1b, '[', '1', ';', '3', '2', 'm',0};
	char white[] = {0x1b, '[', '1', ';', '3', '9', 'm',0};
	
	int linha, coluna;				// Vari�veis de navega��o.
	
	// Exibe o tabuleiro no terminal.
	for(linha = 0 ; linha < 10; linha ++ ){
		cout << linha << " - ";
		for(coluna = 0; coluna < 10; coluna ++){
			switch (mascara[linha] [coluna]){
				case 'A':
					cout << blue << " " << "[" << mascara[linha] [coluna] << "]" << white;
					break;
				
				case 'P':
					cout << green << " " << "[" << mascara[linha] [coluna] << "]" << white;
					break;
				
				default:
					cout << " " << "[" << mascara[linha] [coluna] << "]";
					break;
		
			}
		}
		cout <<"\n";
	}
	
	if(mostraGabarito == true){
		for(linha = 0 ; linha < 10; linha ++ ){
			for(coluna = 0; coluna < 10; coluna ++){
				cout << " " << "[" << tabuleiro[linha] [coluna] << "]";
			}
		cout <<"\n";
	}

}
}
void posicionaBarcos(char tabuleiro [10] [10]){
	
	int cont, quantidade = 10, quantidadePosicionada = 0;
	
	while(quantidadePosicionada < quantidade){
		
		int	linhaAleatoria = rand() % 10;		// Gera n�mero aleat�rio de 0 a 9.
		int colunaAleatoria = rand() % 10;		// Gera n�mero aleat�rio de 0 a 9.
		
		if(tabuleiro [linhaAleatoria] [colunaAleatoria] == 'A'){
			
			tabuleiro [linhaAleatoria] [colunaAleatoria] = 'P'; // Posiciona 10 barcos aleat�riamente.
			
			quantidadePosicionada ++; // Aumenta o contador de barcos adicionados.
		}
	}
}

void verificaTiro(char tabuleiro [10] [10],	int linhaJogada, int colunaJogada, int *pontos, string *mensagem) {

		// Verifica quantos pontos adicionar.
		switch(tabuleiro [linhaJogada] [colunaJogada]){
			case 'P':
				*pontos = *pontos + 10;
				*mensagem = "\nVoc� acertou um barco pequeno! (10 pts)";
				break;		
			
			case 'A':
				*mensagem = "\nVoc� acertou a �gua!";
				break;
		}
}


void jogo(string nomeDoJogador){
	// Vari�veis gerais.
	char tabuleiro [10] [10], mascara [10] [10]; 				// Tabuleiro do jogo.
	int linha, coluna;											// Vari�veis de navega��o.
	int linhaJogada, colunaJogada;								// Valores digitados pelo jogador.
	int estadoDeJogo = 1;										// 1 = jogo acontecendo 0 = Fim de jogo.
	int pontos = 0;												// Pontua��o do jogador.
	int tentativas = 0, maximoDeTentativas = 10;				// Tentativas do jogador.
	int opcao;													// Op��es de fim de jogo.
	string mensagem;											// Feedback para o jogador.	
	
	
	
	iniciaTabuleiro(tabuleiro, mascara);
	
	posicionaBarcos(tabuleiro);

	
	while(tentativas < maximoDeTentativas){
		
		// Verifica��o de dados.
		linhaJogada = -1;
		colunaJogada = -1;
		
		while((linhaJogada < 0 || colunaJogada < 0) || (linhaJogada > 9 || colunaJogada > 9)){
			exibeMapa();
			exibeTabuleiro(tabuleiro, mascara, false);
			cout << "\nPontos: "<< pontos << "\n";
			cout << "Tentativas: " << maximoDeTentativas - tentativas;
			cout << mensagem;
			
			cout <<"\n" << nomeDoJogador <<", digite uma linha: ";
			cin >> linhaJogada;
			cout << "\n" << nomeDoJogador <<", digite uma coluna: ";
			cin >> colunaJogada;
			limpaTela();	
		}
		
		verificaTiro(tabuleiro, linhaJogada, colunaJogada, &pontos, &mensagem ); // Verifica se o jogador acertou a posi��o.
			
		mascara [linhaJogada] [colunaJogada] = tabuleiro [linhaJogada] [colunaJogada];	// Revela o que est� no tabuleiro.
		tentativas ++;
	}
	
	limpaTela();
	cout << "Acabaram suas chances, voc� perdeu.\n";
	cout << "\n 1 - Jogar novamente";
	cout << "\n 2 - Ir para o menu";
	cout << "\n 3 - Sair\n>";
	cin >> opcao;
	limpaTela();
	
	switch(opcao){
		case 1:
			jogo(nomeDoJogador);
			break;
		
		case 2:
			menuInicial();
			break;

		case 3:
			limpaTela();
			cout <<"\n\nAt� mais!";
			break;
	}
}


void menuInicial(){
	int opcao; 								// Armazena a op��o escolhida pelo jogador. 
	int voltar;								// Reiniciar o jogo.
	string nomeDoJogador;					// Nome do usu�rio.
	
	// Enquanto o jogador n�o digita uma op��o v�lida, mostra o menu novamente
	while(opcao < 1 || opcao > 3){
		
		limpaTela();
		
		cout << "\nBATALHA NAVAL\n\n";
		cout << "1 - JOGAR\n";
		cout << "2 - SOBRE\n";
		cout << "3 - SAIR\n";
		cout << "Escolha uma op��o e tecle ENTER: \n";
		cin >> opcao;
		
		switch(opcao){
			case 1:
				cout << "Nome do jogador: ";
				cin >> nomeDoJogador;
				limpaTela();
				jogo(nomeDoJogador);	
				break;
			
			case 2:
					limpaTela();
					cout << "INFORMA��ES DO JOGO\n\n";
					cout << "Jogo desenvolvido em 24/07/2024, por EDUARDO GRAMINHO MARQUES, a t�tulo de estudo.\n";
					cout << "Contato: (41) 9 91960198\n";
					cout << "\n1 - VOLTAR\n";
					cout << "2 - SAIR\n>";
					cin >> voltar;
					
					if(voltar == 1){
						menuInicial();
					}else{
						limpaTela();
						cout <<"At� mais!";
					}
				break;
			 case 3:
			 		limpaTela();
						cout <<"At� mais!";
				break;
		}
	}
}

int main (){
	setlocale(LC_ALL,"");
	srand((unsigned) time(NULL));

	menuInicial();


return 0;
}
