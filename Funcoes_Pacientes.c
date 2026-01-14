#include "Funcoes_Pacientes.h"
#include "Funcoes_Gerais.h"

//Funcoes
void Cadas_Paciente(){
    //Apenas recebe as informacoes do paciente e coloca no arquivo
    int id;
    char Nome[64],Contato[64];
    printf("Informe o nome do Paciente:\n");
    fgets(Nome,64,stdin);
    (strcmp(Nome, "0\n")) == 0 ? Continuar() : NULL;
    Nome[strcspn(Nome,"\n")] = '\0'; //Retirar o \n do final do nome
    printf("Informe algum dado para contato (Email ou Numero de telefone, por exemplo)\n");
    fgets(Contato,64,stdin);
    Contato[strcspn(Contato,"\n")] = '\0'; //Retirar o \n do final do Contato
    (strcmp(Contato, "0\n")) == 0 ? Continuar() : NULL;
    id = Id;
    printf("O Codigo Identificador do Paciente informado eh %d\n",id);
    Aumentar_ID();
    Leitura();
    //Mechando com arquivo
    arquivo_Paci = fopen("Dados_Pacientes.txt","a");
    fprintf(arquivo_Paci,"%s\n",Nome);
    fprintf(arquivo_Paci,"%d\n",id);
    fprintf(arquivo_Paci,"%s\n",Contato);
    fclose(arquivo_Paci);
    Atualizacao_Geral(Parametro = Paciente);
    printf("Paciente Cadastrado com Sucesso!!!!\n");
    int OP;
    printf("\nDeseja Cadastrar Mais um Paciente? (1-Sim) (2-Nao)\n");
    OP = Veri_Int();
    if (OP == 1){
        Limpeza_Composta();
        Cadas_Paciente();
    } else{
        Continuar();
    }
}
void Remo_Paciente(){
    //Nessa funcao vou criar um arquivo temporario com os dados do arquivo original porem sem o paciente que quero apagar
    //Ai depois apago o original e renomeio a copia como o original e defino o ponteiro do original para apontar para copia
    //e a copia apontar para o nada (NULL)
    int Idd,Posicao,Linha,Identif;
    char Nome[64],Contato[64];
    printf("Informe o Codigo Indentificador (ID) do Paciente a ser removido:\n");
    Identif = Veri_Int();
    Posicao = Busca_Paciente(Identif);
    //Se nao achar nenhum paciente com o ID informado
    if (Posicao == 0){
        printf("Nao existe paciente com esse ID!!!!\n");
        Limpeza_Composta();
        Remo_Paciente();
    }
    //Linha onde fica o nome do paciente a ser excluido
    for(int i=0;i<Posicao;i++){
        if (i == 0)
            Linha = 1;
        else
            Linha += 3;
    }
    //Mexer com os arquivos
    Copia_Paci = fopen("Pacientes_Temporarios.txt","w");
    fclose(Copia_Paci);
    Copia_Paci = fopen("Pacientes_Temporarios.txt","a");
    arquivo_Paci = fopen("Dados_Pacientes.txt","r");
    for(int i = 1;i<=(3 * Banco_Pacientes.QTDE);i+=3){
        if (i == Linha){
            fgets(Nome,64,arquivo_Paci);
            fgets(Nome,64,arquivo_Paci);
            fgets(Nome,64,arquivo_Paci);
        } else {
            for(int j = 0;j<3;j++){
                if (j == 0){
                    fgets(Nome,64,arquivo_Paci);
                    Nome[strcspn(Nome,"\n")] = '\0';
                    fprintf(Copia_Paci,"%s\n",Nome);
                } else if (j == 1){
                    fscanf(arquivo_Paci,"%d\n",&Idd);
                    fprintf(Copia_Paci, "%d\n", Idd);
                } else {
                    fgets(Contato,64,arquivo_Paci);
                    Contato[strcspn(Contato,"\n")] = '\0';
                    fprintf(Copia_Paci,"%s\n",Contato);
                }
            }
        }
    }
    fclose(arquivo_Paci);
    fclose(Copia_Paci);
    remove("Dados_Pacientes.txt");
    rename("Pacientes_Temporarios.txt", "Dados_Pacientes.txt");
    arquivo_Paci = Copia_Paci;
    Copia_Paci = NULL;
    Atualizacao_Geral(Parametro = PacienteR);
    printf("Paciente Removido com Sucesso!!!\n");
    Leitura();
    int OP;
    printf("\nDeseja Remover Mais um Paciente? (1-Sim) (2-Nao)\n");
    OP = Veri_Int();
    if (OP == 1){
        Limpeza_Composta();
        Remo_Paciente();
    } else{
        Continuar();
    }
}
int Busca_Paciente(int IDD){
    //Funcao que busca a posicao do paciente no ponteiro pacientes
    for(int i = 0;i<Banco_Pacientes.QTDE;i++){
        if (Banco_Pacientes.Pacientes[i].ID == IDD){
            return i+1;
        }
    }
    return 0;
}
void Atua_Paciente(){
    //Vai atualizar os dados de algum Paciente escolhido
    int iddd, Pos, Linha, Idd;
    char NovoNome[64], NovoContato[64], Nome[64], Contato[64];
    printf("Informe o Codigo Identificador (ID) do Paciente a ser modificado:\n");
    iddd = Veri_Int();
    Pos = Busca_Paciente(iddd);
    //Quando nao existe paciente com o ID informado
    if (Pos == 0){
        printf("Nao existe Paciente com esse ID!!!\n");
        Limpeza_Composta();
        Atua_Paciente();
    }
    printf("Informe o novo Nome do Paciente\n");
    fgets(NovoNome,64,stdin);
    (strcmp(NovoNome, "0\n")) == 0 ? Continuar() : NULL;
    NovoNome[strcspn(NovoNome,"\n")] = '\0';
    printf("Informe o novo Contato do Paciente\n");
    fgets(NovoContato,64,stdin);
    (strcmp(NovoContato, "0\n")) == 0 ? Continuar() : NULL;
    NovoContato[strcspn(NovoContato,"\n")] = '\0';
    //Informa a linha do Paciente no arquivo
    for(int i=0;i<Pos;i++){
        if (i == 0)
            Linha = 1;
        else
            Linha += 3;
    }
    //Procedimento dos arquivos
    Copia_Paci = fopen("Pacientes_Temporarios.txt","w");
    fclose(Copia_Paci);
    Copia_Paci = fopen("Pacientes_Temporarios.txt","a");
    arquivo_Paci = fopen("Dados_Pacientes.txt","r");
    for(int i = 1;i<=(3 * Banco_Pacientes.QTDE);i+=3){
        if (i == Linha){
            fgets(Nome,64,arquivo_Paci);
            fgets(Nome,64,arquivo_Paci);
            fgets(Nome,64,arquivo_Paci);
            fprintf(Copia_Paci,"%s\n", NovoNome);
            fprintf(Copia_Paci, "%d\n", iddd);
            fprintf(Copia_Paci,"%s\n", NovoContato);
        } else {
            for(int j = 0;j<3;j++){
                if (j == 0){
                    fgets(Nome,64,arquivo_Paci);
                    Nome[strcspn(Nome,"\n")] = '\0';
                    fprintf(Copia_Paci,"%s\n",Nome);
                } else if (j == 1){
                    fscanf(arquivo_Paci,"%d\n",&Idd);
                    fprintf(Copia_Paci, "%d\n", Idd);
                } else {
                    fgets(Contato,64,arquivo_Paci);
                    Contato[strcspn(Contato,"\n")] = '\0';
                    fprintf(Copia_Paci,"%s\n",Contato);
                }
            }
        }
    }
    fclose(arquivo_Paci);
    fclose(Copia_Paci);
    remove("Dados_Pacientes.txt");
    rename("Pacientes_Temporarios.txt", "Dados_Pacientes.txt");
    arquivo_Paci = Copia_Paci;
    Copia_Paci = NULL;
    Leitura();
    printf("\nDados do Paciente Modificados com sucesso!\n");
    int OP;
    printf("\nDeseja Moficar os Dados de Mais um Paciente? (1-Sim) (2-Nao)\n");
    OP = Veri_Int();
    if (OP == 1){
        Limpeza_Composta();
        Atua_Paciente();
    } else{
        Continuar();
    }
}
void Listar_Pacientes(){
    //Informa os criterios para listar os pacientes
    int op; // Variavel 'idd' declarada mas nao utilizada
    printf("Escolha o criterio para listar os Pacientes:\n");
    printf("OBS: Informe o numero 0 para cancelar qualquer operacao!!!\n");
    printf("1 - Listar todos os Pacientes\n");
    printf("2 - Listar Pacientes por Codigo identificador (ID):\n");
    printf("3 - Quantidade de Pacientes Cadastrados\n");
    op = Veri_Int();
    CLEAR
    Listamento_P(op);
}
void Listamento_P(int a){
    //Lista os pacientes
    Leitura();
    int idd;
    switch (a){
        case 1:
            for(int i = 0;i<Banco_Pacientes.QTDE;i++){
                printf("\nNome do Paciente: %s\n", Banco_Pacientes.Pacientes[i].Nome);
                printf("Codigo de Identificacao: %d\n", Banco_Pacientes.Pacientes[i].ID);
                printf("Contato do Paciente: %s\n", Banco_Pacientes.Pacientes[i].Contato);
            }
            if (Banco_Pacientes.QTDE == 0){
                printf("Nao ha Pacientes Cadastrados!!!!\n");
            }
            break;
        case 2:
            printf("Para Terminar a busca por Identificacao, informe o Digito: 0\n");
            while(1){
                printf("\nInforme o Codigo de Identificacao do Paciente:\n");
                idd = Veri_Int();
                int Posicao = (Busca_Paciente(idd)-1);
                if (Posicao == -1){
                    printf("\nNao existe Paciente com esse ID!!\n");
                } else {
                    printf("\nNome do Paciente: %s\n", Banco_Pacientes.Pacientes[Posicao].Nome);
                    printf("Codigo de Identificacao: %d\n", Banco_Pacientes.Pacientes[Posicao].ID);
                    printf("Contato do Paciente: %s\n", Banco_Pacientes.Pacientes[Posicao].Contato);
                }
                Limpeza_Composta();
                continue; // CORRIGIDO: Troca recursao por 'continue'
            }
            break;
        case 3:
            printf("Ate o Momento ha registro de %d Paciente(s)\n", Banco_Pacientes.QTDE);
            break;
        default:
            printf("Opcao Invalida!!\n");
            Listar_Pacientes();
            break;
    }
    Continuar();
}
