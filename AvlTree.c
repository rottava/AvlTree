/*FEITO POR EDSON J. ROTTAVA JR.
#########COMPILAR EM VISUAL STUDIO PARA SUPORTCOM A BIBLIOTECA ADICIONAL#########
##############QUE OFERECE SUPORTE AO TESTE DE VAZAMENTO DE MEMORIA!##############
######################### https://vld.codeplex.com/ ############################*/
#include <stdio.h>
#include <stdlib.h>
#include <vld.h> //MEMORY LEAK TEST!
//NO
typedef struct node{
    int val, bal;
    struct node *lef;
    struct node *rig;
}node;
//MH=ATURA MAXIMA //MW=LARGURA MAXIMA
#define mh 4
#define mw 15
//VARIAVEIS GLOBAIS
node *root;
int array[mh][mw], aw[mw], aux;
//FUNCOES
int menu();
void opt();
void ini(node **root);
void auxIn();
void in(node **root, int num);
void show(node *root);
void show1(node *root);
void auxOut();
node *helpOut(node **root);
void out(node **root, int num);
void balance(node **root);
int height(node *root); 
void rotLeft(node **root);
void rotRight(node **root);
void dRotLeft(node **root);
void dRotRight(node **root);
void manualprint(int array[mh][mw]);
void del(node *root);
//MAIN
int main(){
	int y;
    ini(&root);
    do{
        y=menu();
        opt(y);}
	while(y!=0);
    return 0;
}
//MENU
int menu(){
	int z;
	system("cls");
	printf("Escolha a opcao\n");
	printf("1: Inserir elementos\n");
    printf("2: Remover elementos\n");
	printf("3: Mostrar elementos\n");
	printf("0. Encerar programa\n");
	printf("Opcao: ");
	scanf_s(" %d", &z);
	system("cls");
	return z;
}
//OPCAO MENU
void opt(int z){
	switch(z){
        case 0:
            del(root);
            break;
		case 1:
		    auxIn();
		    printf("Elemento(s) Inserido(s)!\n");
			getchar();
			break;
        case 2:
		    auxOut();
		    printf("Elemento(s) Removido(s)!\n");
			getchar();
			break;
		case 3:
			if(root != NULL){
				show(root);
				fflush(stdin);
				getchar();} 
            else{
            	printf("A arvore esta vazia!\n");
				fflush(stdin);
				getchar();}
            break;
		default:
			printf("Comando invalido\n");
			getchar();
			getchar();
	}
}
//INICIALIZA
void ini(node **root){
    *root = NULL;
}
//CHAMA INSERCAO
void auxIn(){
    int x;
    char z;
    printf("Digite o(s) Elemento(s) a ser(em) inserido(s): ");
    fflush(stdin);
	while ((z=getchar()) != '\n'){
		if((z >= '0') && (z <= '9')){
			x = atoi(&z);
			while (((z=getchar()) >='0') && (z <= '9')){//PARA MAIS DE UM ELEMENTO
				x=(x*10)+(atoi(&z));}
			in(&(root), x);
        }
    }
}
//INSERE
void in(node **root, int num){
    if(*root == NULL){
        *root = (node *)malloc(sizeof(node));
        (*root)->lef = NULL;
        (*root)->rig = NULL;
        (*root)->val = num;
        (*root)->bal = 0;
     }else{
         if(num <(*root)->val)
              in(&(*root)->lef, num);
         if(num >(*root)->val)
              in(&(*root)->rig, num);
		 balance(&(*root));
     }
 }
//IMPRIME ARVORE
void show (node *root){
    int i,j;
    //int k;
    for(j=0;j <= mw; j++){//ZERA A MATRIZ
        for(i=0;i <= mh; i++){
            array[i][j] = 0;}
        aw[j] = 0;}
    aux = -1;
    show1(root);
    manualprint(array);
}
//COPIA ARVORE PARA UMA MATRIZ
void show1(node *root){
    if(root != NULL){
        aux++;
        show1(root->lef);
        show1(root->rig);
        array[aux][aw[aux]] = (root->val);
        aw[aux]++;
        aux--;
    }
    if(root == NULL){
        if (aux == 0){
            aw[aux+1]=aw[aux+1]+1;
            aw[aux+2]=aw[aux+2]+2;
            aw[aux+3]=aw[aux+3]+4;
            aw[aux+4]=aw[aux+4]+8;
        }
        if (aux == 1){
            aw[aux+1]=aw[aux+1]+1;
            aw[aux+2]=aw[aux+2]+2;
            aw[aux+3]=aw[aux+3]+4;
        }
        if (aux == 2){
            aw[aux+1]=aw[aux+1]+1;
            aw[aux+2]=aw[aux+2]+2;
        }
        if (aux == 3){
            aw[aux+1]=aw[aux+1]+1;
        }
    }
}
//CHAMA REMOCAO
void auxOut(){
    int x;
    char z;
    printf("Digite o(s) Elemento(s) a ser(em) removido(s): ");
    fflush(stdin);
	while ((z=getchar()) != '\n'){
		if((z >= '0') && (z <= '9')){
			x = atoi(&z);
			while (((z=getchar()) >='0') && (z <= '9')){//PARA MAIS DE UM ELEMENTO
				x=(x*10)+(atoi(&z));}
			out(&(root), x);
        }
    }
}
//AUXILIAR DE REMOCAO
node *helpOut(node **root){
    if((*root)->rig != NULL)
       return helpOut(&(*root)->rig);
    else{
       node *art = *root;
       if((*root)->lef != NULL)
          *root = (*root)->lef;
       else
          *root = NULL;
       return art;
       }
}
//REMOCAO
void out(node **root, int num){
    if(*root == NULL) //NAO EXISTE
       return;
    if(num < (*root)->val) //MENOR QUE A RAIZ
       out(&(*root)->lef, num);
    else
       if(num > (*root)->val)//MAIOR QUE A RAIZ
          out(&(*root)->rig, num);
       else{//E A RAIZ
          node *art = *root;
          if (((*root)->lef == NULL) && ((*root)->rig == NULL)){ // SEM FILHOS
                free(art);
                (*root) = NULL;
               }
          else{//FILHO A DIREITA
             if ((*root)->lef == NULL){
                (*root) = (*root)->rig;
                art->rig = NULL;
                free(art); art = NULL;
                }
             else{//FILHO A ESQUERDA
                if ((*root)->rig == NULL){
                    (*root) = (*root)->lef;
                    art->lef = NULL;
                    free(art); art = NULL;
                    }
                else{//ORDENACAO FINAL
                   art = helpOut(&(*root)->lef);
                   art->lef = (*root)->lef;
                   art->rig = (*root)->rig;
                   (*root)->lef = (*root)->rig = NULL;
                   free((*root));  *root = art;  art = NULL;
                }
            }
        }
	balance(&(*root));
    }
}
//BALANCEAMENTO
void balance(node **root){
    if((*root) == NULL) return;
	(*root)->bal = (height((*root)->lef)) - (height((*root)->rig));
	if((((*root)->bal) >= -1) && (((*root)->bal) <= 1)) return;
	if(((*root)->bal) == 2) {
		if((height((*root)->lef->lef)) > (height((*root)->lef->rig)) )
			 rotLeft(&(*root));
		else dRotLeft(&(*root));
	}
	else {
		if((height((*root)->rig->rig)) > (height((*root)->rig->lef)))
			rotRight(&(*root));
		else dRotRight(&(*root));
    }
}
//ROTACAO A ESQUERDA
void rotLeft(node **root) {
  node *art = (*root)->lef;
  (*root)->lef = art->rig;
  art->rig = (*root);
  art->bal = (height(art->lef)) - (height(art->rig));
  (*root) = art;
}
//ROTACAO A DIREITA
void rotRight(node **root) {
  node *art = (*root)->rig;
  (*root)->rig = art->lef;
  art->lef = (*root);
  art->bal = (height(art->lef)) - (height(art->rig));
  (*root) = art;
}
//ROTACAO DUPLA A ESQUERDA
void dRotLeft(node **root) {
  rotRight(&(*root)->lef);
  rotLeft(&(*root));
}
//ROTACAO DUPLA A DIREITA
void dRotRight(node **root) {
  rotLeft(&(*root)->rig);
  rotRight(&(*root));
}
//ALTURA DO NO
int height(node *root) {
    int left, right;
    if (root == NULL) return -1;
	left = height(root->lef);
	right = height(root->rig);
    if (left > right) return (left+1);
    else return (right+1);
}
//IMPRESSAO MANUAL
void manualprint(int array[mh][mw]){
printf("                   +------------------|%2i|------------------+\n",array[0][0]);
printf("         +-------|%2i|-------+                     +-------|%2i|-------+\n",array[1][0],array[1][1]);
printf("     +-|%2i|-+            +-|%2i|-+           +-|%2i|-+           +-|%2i|-+\n",array[2][0],array[2][1],array[2][2],array[2][3]);
printf("   |%2i|    |%2i|       |%2i|    |%2i|       |%2i|    |%2i|       |%2i|    |%2i|\n",array[3][0],array[3][1],array[3][2],array[3][3],array[3][4],array[3][5],array[3][6],array[3][7]);
printf("|%2i||%2i| |%2i||%2i|  |%2i||%2i| |%2i||%2i|  |%2i||%2i| |%2i||%2i|  |%2i||%2i| |%2i||%2i|\n",array[4][0],array[4][1],array[4][2],array[4][3],array[4][4],array[4][5],array[4][6],array[4][7],array[4][8],array[4][9],array[4][10],array[4][11],array[4][12],array[4][13],array[4][14],array[4][15]);
}
//ELIMINA ARVORE
void del(node *root){
    if(root != NULL){
        del(root->lef);
        del(root->rig);
        free(root);
    }
}