#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nome[50];
    char email[100];
    int idade;
}Info_Candidato;

Info_Candidato candidato;


void cadastrar();
void listar();
void alterar();
void excluir();
void pesquisar();
void salvar(Info_Candidato f);


int main(){
    int op;

    do{
        system("cls");
        printf("\n\tMENU\n");
        printf("\n0-Sair\n1-Cadastrar\n2-listar\n3-Atualizar\n4-Excluir Cadastro\n5-pesquisar candidato\nEscolha: ");
        scanf("%d",&op);
        getchar();
        switch(op){
            case 1:
                cadastrar();
                break;
            case 2:
                listar();
                break;
            case 3:
                alterar();
                break;
            case 4:
                excluir();
                break;
            case 5:
                pesquisar();
                break;
            default:
                if(op != 0){
                    printf("\nEscolha invalida\n");
                    getchar();
                }               
        }
    }while(op != 0);  
    
    return 0;
}

void cadastrar(){
int i = 1,op;
do{
    system("cls");
    printf("Candidato %d\n",i);
    printf("Nome: ");
    scanf("%49[^\n]",candidato.nome);
    getchar();
    printf("Email: ");
    scanf("%99[^\n]",candidato.email);
    getchar();
    printf("Idade: ");
    scanf("%i",&candidato.idade);
    getchar();
    printf("1 - continuar 0 - sair: ");
    scanf("%i",&op);
    getchar();
    i++;
    salvar(candidato);
}while(op != 0);

}
void listar(){
    system("cls");
    FILE *file = fopen("Candidatos.dat","rb");
    int i = 1;
    if(file){
        printf("\n\tLISTA DE CANDIDATOS\n");
        while(fread(&candidato,sizeof(Info_Candidato),1,file)){
            printf("\nCandidato %d\n",i);
            printf("Nome: %s\n",candidato.nome);
            printf("Email: %s\n",candidato.email);
            printf("Idade: %d\n",candidato.idade);
            i++;
        }
        
        getchar();
    }else{
        printf("\nERRO NA ABERTURA\n");
        getchar();
    }
    fclose(file);
}
void alterar(){
    FILE *file = fopen("Candidatos.dat","r+b");
    int indice;
    if(file){
        listar();
        printf("\nDigite o indice do candidato para alterar: ");
        scanf("%d",&indice);
        getchar();
        indice--;
        fseek(file,indice * sizeof(Info_Candidato),SEEK_SET);
        printf("\n\tAgora digite os novos dados\n");
        printf("\nNome: ");
        scanf("%49[^\n]",candidato.nome);
        getchar();
        printf("Email: ");
        scanf("%99[^\n]",candidato.email);
        getchar();
        printf("Idade: ");
        scanf("%i",&candidato.idade);
        fwrite(&candidato,sizeof(Info_Candidato),1,file);

    }else{
        printf("\nERRO NA ABERTURA\n");
        getchar();
    }
    fclose(file);
}
void salvar(Info_Candidato f){
    FILE *file = fopen("Candidatos.dat","a+b");
    if(file){
        fwrite(&f,sizeof(Info_Candidato),1,file);
    }else{
        printf("\nERRO AO SALVAR\n");
    }
    fclose(file);
}
void excluir(){
    FILE *file = fopen("Candidatos.dat", "r+b");
    FILE *tempFile = fopen("TempCandidatos.dat", "wb");
    int indice;
    int i = 0;
    int encontrou = 0;

    if (file && tempFile) {
        listar();
        printf("\nDigite o indice do candidato para excluir: ");
        scanf("%d", &indice);
        getchar();
        indice--;

        while (fread(&candidato, sizeof(Info_Candidato), 1, file)) {
            if (i != indice) {
                fwrite(&candidato, sizeof(Info_Candidato), 1, tempFile);
            } else {
                encontrou = 1;
            }
            i++;
        }

        fclose(file);
        fclose(tempFile);

        if (encontrou) {
            remove("Candidatos.dat");
            rename("TempCandidatos.dat", "Candidatos.dat");
            printf("\nCadastro excluido com sucesso.\n");
        } else {
            remove("TempCandidatos.dat");
            printf("\nIndice de cadastro inválido.\n");
        }

        getchar();
    } else {
        printf("\nERRO NA ABERTURA\n");
        getchar();
    }
}

void pesquisar(){
    FILE *file = fopen("Candidatos.dat","rb");
    char nome[50];
    int encontrou = 0;

    if(file){
        system("cls");
        printf("Digite o nome do candidato: ");
        scanf("%49[^\n]",nome);
        getchar();
        while(fread(&candidato,sizeof(Info_Candidato),1,file)){
            if(strstr(candidato.nome,nome)!= NULL){
                system("cls");
                printf("\tInformacoes do candidato\n\n");
                printf("Nome: %s",candidato.nome);
                printf("\nEmail: %s",candidato.email);
                printf("\nIdade: %d",candidato.idade);
                getchar();
                encontrou = 1;
            }
        }
        if(encontrou == 0){
            printf("\nNome de candidato nao encontrado nos cadastros\n");
            getchar();
        }
    }else{
        printf("\nERRO NA ABERTURA\n");
        getchar();
    }
    fclose(file);
}
