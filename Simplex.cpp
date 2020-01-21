#include<bits/stdc++.h>

using namespace std;

char *ARQUIVO = "exemplo 01.txt"; // escolhe o arquivo para ser aberto

void alocaInt(int **p,int tam);
void alocaChar(char **p,int tam);
int qtdeLinhas(int *m, int **num); // pega a quantidade de linhas no arquivo, qual o tamanho da maior linha e quantos numeros por linha


main(){
	
	int linhas = 0,maior = 0, *qtdNum = NULL;
	linhas = qtdeLinhas(&maior,&qtdNum);
	
	char lista[linhas][maior], letra, *aux = NULL;
	FILE *fptr=NULL;
	int colunas = *qtdNum + linhas, tamlinha=0, linha=0;
	float matriz[linhas][colunas];
	
	
	//inicio leitura do arquivo     
	if((fptr=fopen(ARQUIVO,"r"))==NULL) //abre o arquivo
		printf("\nErro ao abrir o arquivo\n");
	else
	{
		while((letra = fgetc(fptr)) != EOF){  // pega as letras até o fim do arquivo
		    
			if(letra == '\n')    //se a letra for \n significa que acabou a linha, então ele muda a linha do vetor
			{ 
				lista[linha][tamlinha]= '\0';
				tamlinha = 0;
  				linha++;             
			}
			else // senão ele adiciona a letra na vetor
			{
				lista[linha][tamlinha++] = letra;
			}
		}
		
		lista[linha][tamlinha] = '\0';

	}
	fclose(fptr);
	//fim da leitura do arquivo
	
		
	//inicio converção de char para float e construção da matriz
	
	int j,k,l,m = *qtdNum - 1, auxInt; 
	for(int i = 0; i < linhas; i++){ //for para ir mudandando a linha da matriz e da lista de char
		j = 0;   // var para mudar a letra da lista
		k = 0;   // var para mudar a coluna da matriz 
		l = 0;   // var para incrementar o tamanho da var aux de char
		
		while(lista[i][j] != '\0'){  // verifica se acabou a linha da lista
			if(lista[i][j] == ' '){  // se a letra da lista for um espaço ira converter o char para int e depois inserir na matriz como float
				
				if(i == 0){ // caso seja a primeira linha, que corresponde ao z, irá passar o numero negativo
					
					auxInt = strtol(aux, NULL, 10) * (-1);
					matriz[i][k] = auxInt;
					k++;
				}
				else{
					
					auxInt = strtol(aux, NULL, 10);
					matriz[i][k] = auxInt;
					k++;
					if(k == *(qtdNum + i) - 1 ){ // insere os 0 ou 1 nas posições de X não decisivos
						for(k; k < colunas - 1; k++){
							if(k == m){
								matriz[i][k] = 1;
							}
							else	
								matriz[i][k] = 0;
						}							
					}	
				}
				
				l = 0;
				*aux = NULL;
				aux=NULL;
			}
			else{     //enquanto a letra não for espaço, armazena em uma var aux para poder pegar o numero inteiro
				alocaChar(&aux,l+2);
				*(aux+l) = lista[i][j];
				l++;
				*(aux+l) = '\0';
			}

			j++;	
		}
		if(i == 0){  // insere o ultimo valor antes de acabar a linha, no caso da linha 0 correspondente ao Z 
			auxInt = strtol(aux, NULL, 10) * (-1);
			matriz[i][k] = auxInt;
			for(++k; k < colunas; k++){  // insere os 0 nas posições de X não decisivos
				matriz[i][k] = 0;
			}
			l=0;
			*aux = NULL;
			aux=NULL;
		}
		else{ // insere o ultimo valor antes de acabar a linha, como corresponde a coluna B, ficara na ultima coluna da matriz
			auxInt = strtol(aux, NULL, 10);
			matriz[i][k] = auxInt;
			
			aux=NULL;
			l=0;
		}
		m++;
	}
	//fim converção de char para float
	
	
	printf("\n\n"); 
	cout<<"Tabela Inicial:"<<endl;
	for(int i = 0; i < linhas; i ++){   //mosta a matriz inicial
		for(j = 0; j < colunas; j++){
			printf("%.1f\t",matriz[i][j]);
		}
		printf("\n");
	}
	

	//inicio calculo da matriz
	int posMenorZ = 0,posMenorX, posicoes[linhas];
	float menorZ = matriz[0][0], menorX, divisor, multiplicador;
	
	for(int i = 1; i < linhas; i++){     //guarda a posição dos Xs na matriz
		posicoes[i] = *qtdNum + i;
	}

	for(int i = 0; i < colunas; i++){ // encontra o menor Z
		if(matriz[0][i] < menorZ){
			menorZ = matriz[0][i];
			posMenorZ = i;
		}
	}

	l=1;

	while(menorZ < 0){
		// começa a encontrar o menor X para substituir
		k = 1;
		while(matriz[k][posMenorZ] == 0)
		{
			k++;
		}
		
		menorX = matriz[k][colunas-1] / matriz[k][posMenorZ];
		posMenorX = k;
		
		for(int i = 1; i < linhas; i++){            //vai passando por todos os valores diferentes de 0, e armazena o valor e posição do menor
			if(matriz[i][posMenorZ] != 0){
				if((matriz[i][colunas-1] / matriz[i][posMenorZ]) < menorX){
					menorX = (matriz[i][colunas-1] / matriz[i][posMenorZ]); 
					posMenorX = i;
				}
			
			}
		}
		
		//encontrou o menor X
		posicoes[posMenorX] = posMenorZ+1; // guarda a mudança de posição do X

		//transforma em identidade
		divisor = matriz[posMenorX][posMenorZ];
		for(int i = 0; i < colunas; i ++){  // divide toda a linha do menor X pera deixa-lo com o valor 1
			if(matriz[posMenorX][i] != 0)
				matriz[posMenorX][i] = matriz[posMenorX][i] / divisor;
		}

		
		
		for(int i = 0; i < linhas; i ++){  // zera as outras linhas da coluna correspondente ao menor X e altera os valores das linhas zeradas conforme a formula de resolução 
			if(i != posMenorX){
				multiplicador = matriz[i][posMenorZ];
				for(int j = 0; j < colunas; j++){
					if(matriz[posMenorX][j] != 0)
						matriz[i][j] -= matriz[posMenorX][j] * multiplicador;
				}
			}
				
		}
				
		menorZ = 0;
		
		for(int i = 0; i < colunas; i++){ // encontra o menor Z
			if(matriz[0][i] < menorZ){
				menorZ = matriz[0][i];
				posMenorZ = i;
			}
		}
		
	printf("\n\n"); 
	cout<<"Tabela "<<l++<<endl;
	for(int i = 0; i < linhas; i ++){   //mosta a matriz que esta sendo resolvida
		for(j = 0; j < colunas; j++){
			printf("%.1f\t",matriz[i][j]);
		}
		printf("\n");
	}
	system("pause");
		
	}
	//fim calculo matriz
	
	cout<<endl<<endl<<"Z = "<<matriz[0][colunas-1]<<endl;
	for(int i = 1; i < linhas; i ++){
		cout<<"X"<<posicoes[i]<<" = "<<matriz[i][colunas-1]<<endl;
	}
	cout<<"Os outros Xs valem 0"<<endl<<endl<<endl;
	
	system("pause");
	return(0);
}

void alocaInt(int **p,int tam)
{
if((*p=(int*)realloc(*p,tam*sizeof(int)))==NULL)
  exit(1);
}//aloca

void alocaChar(char **p,int tam)
{
if((*p=(char*)realloc(*p,tam*sizeof(char)))==NULL)
  exit(1);
}//aloca

int qtdeLinhas(int *maior, int **num){
	
	FILE *fptr=NULL;
	int cont = 0, cont2 = 0;
	char letra;
	alocaInt(num,1);
	**num = 1;
	if((fptr=fopen(ARQUIVO,"r"))==NULL)   // abre o arquivo
  		printf("\nErro ao abrir o arquivo\n");
	else
  	{
  		while((letra = fgetc(fptr)) != EOF){  //passa por todas a letras até o fim do arquivo
    		
    		if(letra == '\n'){        // se for \n significa que acabou a linha, então aumenta o contador de linhas
    			
      			cont++;
      			alocaInt(num,cont+1);
      			*(*num+cont) = 1;
      			
				if(cont2 >= *maior)  // verifica se é a linha com maior qtd de numeros
					*maior = cont2+1;
			
			cont2 = 0;             
    		}
    		cont2++;
    		
    		if(letra == ' ')  // se houver espaço significa que é outro numero, então aumenta o contador de numeros
    			*(*num+(cont)) += 1;
    		
  		}
  		
  	}
  	fclose(fptr);
  	return cont+1;
	
}
