#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
    char nome[50];
    int idade;
}usuario;

void inserir()
{
    FILE *file = fopen("usuarios.txt", "a");
    if(file == NULL){
        printf("Erro ao abrir o documento");
        return;
    }
    usuario user;
    printf("Digite o nome do usuario: ");
    scanf("%49s", &user.nome);
    printf("Digite a idade do usuario: ");
    scanf("%d", &user.idade);

    fprintf(file, "%s %d\n", user.nome, user.idade);
    fclose(file);
}

void mostrar()
{
    FILE *file = fopen("usuarios.txt", "r");
    if(file == NULL){
        printf("Erro ao abrir o documento");
        return;
    }
    usuario user;
    while(fscanf(file, "%s %d", &user.nome, &user.idade) != EOF){
        printf("Nome: %s Idade: %d\n", user.nome, user.idade);}
        fclose(file);
}
void editar()
{
   FILE *file = fopen("usuarios.txt", "r+");
   if(file == NULL){
    printf("Erro");
    return;
   }

   char nome[50];
   printf("Digite o nome a ser editado: ");
   scanf("%49s", &nome);

   usuario user;
   long pos;
   while((pos = ftell(file)) != -1 && fscanf(file, "%s %d", &user.nome, &user.idade) != EOF){
    if(strcmp(user.nome, nome)==0){
        printf("Digite a nova idade:");
    scanf("%d", &user.idade);

    fseek(file,pos, SEEK_SET);
        fprintf(file, "%s %d", user.nome, user.idade);
        break;
    }
   }
   fclose(file);

}
void excluir()
{
    FILE *file = fopen("usuarios.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if(file==NULL && temp==NULL){
        perror("Erro");
        return;
    }
    char nome[50];
    printf("Digite o nome a ser excluido: ");
    scanf("%49s", &nome);

    usuario user;
    while(fscanf(file, "%s %d", &user.nome, &user.idade) != EOF){
        if(strcmp(user.nome , nome) != 0){
            fprintf(temp, "%s %d", user.nome, user.idade);
        }

    }
    fclose(file);
    fclose(temp);

    remove("usuarios.txt");
    rename("temp.txt", "usuarios.txt");
    printf("excluido com sucesso");
}

main()
{
    int op;
    do
    {
        printf("Escolha\n");
        printf("1-Inserir\n2-Mostrar\n3-editar\n4-excluir\n5-sair\n");
        scanf("%d", &op);

    switch(op)
    {
    case 1:
        inserir();
        break;
             case 2:
                 mostrar();
        break;
             case 3:
                 editar();
        break;
             case 4:
                 excluir();
        break;
    }
    }
    while(op != 5);
}
