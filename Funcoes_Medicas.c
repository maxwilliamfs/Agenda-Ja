#include "Funcoes_Medicas.h"
#include "Funcoes_Gerais.h"
#include "Funcoes_Pacientes.h" // Para Agenda_Medico -> Busca_Paciente

//Funcoes
void Cadas_Medico(){
    //Essa Funcao vai apenas ler as informacoes do medico e colocar no arquivo
    typedef struct {
        int H,Min;
    } Hor;
    Hor IM,FM,IT,FT;
    int id,Espe;
    // int op; // Variavel 'op' declarada mas nao utilizada
    char nome[64]; // Variavel 'X' declarada mas nao utilizada
    printf("Informe o Nome do Medico:\n");
    fgets(nome,64,stdin);
    (strcmp(nome, "0\n")) == 0 ? Continuar() : NULL;
    nome[strcspn(nome, "\n")] = '\0';
    printf("Escolha a Opcao da Especialidade do Medico:\n");
    printf("1 - Clinico\n");
    printf("2 - Pediatra\n");
    printf("3 - Dermatologista\n");
    printf("4 - Cardiologista\n");
    printf("5 - Outra Especialidade\n");
    Espe = Veri_Int();
    printf("Para as proximas perguntas escreva no formato: HH:MM, por exemplo, 10:30\n");
    printf("Informe o horario de inicio do turno de atendimento do medico na parte da manha:\n");
    Verificacao_Horas(&IM);
    printf("Informe o horario que finaliza o turno de atendimento do medico na parte da manha:\n");
    Verificacao_Horas(&FM);
    printf("Informe o horario de inicio do turno de atendimento do medico na parte da tarde:\n");
    Verificacao_Horas(&IT);
    printf("Informe o horario de inicio do turno de atendimento do medico na parte da tarde:\n");
    Verificacao_Horas(&FT);
    id = Id;
    printf("O medico informado tem o ID: %d\n", id);
    Aumentar_ID();
    Leitura();
    //Passar essas informacoes para o arquivo dos medicos
    arquivo_Med = fopen("Dados_Medicos.txt", "a");
    fprintf(arquivo_Med,"%s\n", nome);
    fprintf(arquivo_Med, "%d %d %d:%d %d:%d %d:%d %d:%d\n",id,Espe,IM.H,IM.Min,FM.H,FM.Min,IT.H,IT.Min,FT.H,FT.Min);
    fclose(arquivo_Med);
    Atualizacao_Geral(Parametro = Medico);
    printf("Medico Cadastrado com Sucesso!!!\n");
    int OP;
    printf("\nDeseja Cadastrar Mais um Medico? (1-Sim) (2-Nao)\n");
    OP = Veri_Int();
    if (OP == 1){
        Limpeza_Composta();
        Cadas_Medico();
    } else{
        Continuar();
    }
}
void Remo_Medico(){
    //Nessa funcao vou criar um arquivo temporario com os dados do arquivo original porem sem o medico que quero apagar
    //Ai depois apago o original e renomeio a copia como o original e defino o ponteiro do original para apontar para copia
    //e a copia apontar para o nada (NULL)
    int Identifi, Posicao, Linha;
    char Nome[64]; // Variavel 'X' declarada mas nao utilizada
    int IDD,Espee;
    typedef struct{
        int H,Min;
    } Horr;
    Horr IM,FM,IT,FT;
    printf("Informe o ID do medico a ser removido:\n");
    Identifi = Veri_Int();
    Posicao = Busca_Medico(Identifi);
    if (Posicao == 0){
        printf("\nNao existe Medico com esse ID!!!!\n");
        Limpeza_Composta();
        Atua_Medico();
    }
    Linha = Posicao + Posicao - 1; //Linha do arquivo que esta o medico para ser removido
    //Procedimento dos arquivos
    Copia_Med = fopen("Medicos_Temporarios.txt","w");
    fclose(Copia_Med);
    Copia_Med = fopen("Medicos_Temporarios.txt","a");
    arquivo_Med = fopen("Dados_Medicos.txt","r");
    for(int i = 0;i<(Banco_Medicos.QTDE*2);i++){
        if ((i+1) == Linha){
            fgets(Nome,64,arquivo_Med);
            fgets(Nome,64,arquivo_Med);
            i++;
        } else {
            if ((i+1) % 2 != 0){
                fgets(Nome,64,arquivo_Med);
                Nome[strcspn(Nome,"\n")] = '\0';
                fprintf(Copia_Med,"%s\n",Nome);
            }
            else{
                fscanf(arquivo_Med,"%d %d %d:%d %d:%d %d:%d %d:%d\n", &IDD,&Espee,&IM.H,&IM.Min,&FM.H,&FM.Min,&IT.H,&IT.Min,&FT.H,&FT.Min);
                fprintf(Copia_Med,"%d %d %d:%d %d:%d %d:%d %d:%d\n", IDD,Espee,IM.H,IM.Min,FM.H,FM.Min,IT.H,IT.Min,FT.H,FT.Min);
            }
        }
    }
    fclose(arquivo_Med);
    fclose(Copia_Med);
    remove("Dados_Medicos.txt");
    rename("Medicos_Temporarios.txt", "Dados_Medicos.txt");
    arquivo_Med = Copia_Med;
    Copia_Med = NULL;
    Atualizacao_Geral(Parametro = MedicoR);
    printf("Medico Removido com Sucesso!!!\n");
    Leitura();
    int OP;
    printf("\nDeseja Remover Mais um Medico? (1-Sim) (2-Nao)\n");
    OP = Veri_Int();
    if (OP == 1){
        Limpeza_Composta();
        Remo_Medico();
    } else{
        Continuar();
    }
}
void Atua_Medico(){
    //Nessa funcao vou criar um arquivo temporario com os dados do arquivo original porem com dados diferentes do medico que
    //quero modificar Ai depois apago o original e renomeio a copia como o original e defino o ponteiro do original para apontar
    //para copia e a copia apontar para o nada (NULL)

    //Variaveis para a leitura das Modificacoes
    char NovoNome[64];
    int Nova_Espe;
    //Variaveis para a copia do arquivo e identificacao do medico
    int Identifi, Posicao, Linha;
    char Nome[64]; // Variavel 'X' declarada mas nao utilizada
    int IDD,Espee;
    Horario IM,FM,IT,FT,NIM,NFM,NIT,NFT;
    //Codigo principal
    printf("Informe o ID do medico:\n");
    Identifi = Veri_Int();
    Posicao = Busca_Medico(Identifi);
    if (Posicao == 0){
        printf("\nNao existe Medico com esse ID!!!!\n");
        Limpeza_Composta();
        Atua_Medico();
    }
    Linha = Posicao + Posicao - 1; //Linha do arquivo que esta o medico para ser modificado
    //Leitura das novas Informacoes do medico
    printf("Informe o Novo Nome do Medico:\n");
    fgets(NovoNome,64,stdin);
    (strcmp(NovoNome, "0\n")) == 0 ? Continuar() : NULL;
    NovoNome[strcspn(NovoNome, "\n")] = '\0'; //Remove o \n do final da string
    printf("Escolha a opcao para a nova especialidade do Medico:\n");
    printf("1 - Clinico\n");
    printf("2 - Pediatra\n");
    printf("3 - Dermatologista\n");
    printf("4 - Cardiologista\n");
    printf("5 - Outra Especialidade\n");
    Nova_Espe = Veri_Int();
    printf("Para as proximas perguntas escreva no formato: HH:MM, por exemplo, 10:30\n");
    printf("Informe o novo horario de inicio do turno de atendimento do medico na parte da manha:\n");
    Verificacao_Horas(&NIM);
    printf("Informe o novo horario que finaliza o turno de atendimento do medico na parte da manha:\n");
    Verificacao_Horas(&NFM);
    printf("Informe o novo horario de inicio do turno de atendimento do medico na parte da tarde:\n");
    Verificacao_Horas(&NIT);
    printf("Informe o novo horario de inicio do turno de atendimento do medico na parte da tarde:\n");
    Verificacao_Horas(&NFT);
     //Atualizacao do arquivo
    Copia_Med = fopen("Medicos_Temporarios.txt","w");
    fclose(Copia_Med);
    Copia_Med = fopen("Medicos_Temporarios.txt","a");
    arquivo_Med = fopen("Dados_Medicos.txt","r");
    for(int i = 0;i<(Banco_Medicos.QTDE*2);i++){
        if ((i+1) == Linha){
            fgets(Nome,64,arquivo_Med);
            fgets(Nome,64,arquivo_Med);
            fprintf(Copia_Med,"%s\n",NovoNome);
            fprintf(Copia_Med,"%d %d %d:%d %d:%d %d:%d %d:%d\n", Identifi,Nova_Espe,NIM.Hora,NIM.Minuto,NFM.Hora,NFM.Minuto,NIT.Hora,NIT.Minuto,NFT.Hora,NFT.Minuto);
            i++;
        } else {
            if ((i+1) % 2 != 0){
                fgets(Nome,64,arquivo_Med);
                Nome[strcspn(Nome,"\n")] = '\0';
                fprintf(Copia_Med,"%s\n",Nome);
            }
            else{
                fscanf(arquivo_Med,"%d %d %d:%d %d:%d %d:%d %d:%d\n", &IDD,&Espee,&IM.Hora,&IM.Minuto,&FM.Hora,&FM.Minuto,&IT.Hora,&IT.Minuto,&FT.Hora,&FT.Minuto);
                fprintf(Copia_Med,"%d %d %d:%d %d:%d %d:%d %d:%d\n", IDD,Espee,IM.Hora,IM.Minuto,FM.Hora,FM.Minuto,IT.Hora,IT.Minuto,FT.Hora,FT.Minuto);
            }
        }
    }
    fclose(arquivo_Med);
    fclose(Copia_Med);
    remove("Dados_Medicos.txt");
    rename("Medicos_Temporarios.txt", "Dados_Medicos.txt");
    arquivo_Med = Copia_Med;
    Copia_Med = NULL;
    printf("Modificacao feita com Sucesso!!!!\n");
    int OP;
    Leitura();
    printf("\nDeseja Modificar Mais um Medico? (1-Sim) (2-Nao)\n");
    OP = Veri_Int();
    if (OP == 1){
        Limpeza_Composta();
        Atua_Medico();
    } else{
        Continuar();
    }
}
void Listar_Medicos(){
    //Funcao que vai listar os medicos baseado em certos criterios
    int opp;
    printf("Escolha o criterio para listar os Medicos:\n");
    printf("OBS: Informe o numero 0 para cancelar qualquer operacao!!!\n");
    printf("1 - Todos os Medicos\n");
    printf("2 - Por ID\n");
    printf("3 - Por especialidade\n");
    printf("4 - Pelos Horarios de Atendimento\n");
    printf("5 - Quantidade de Medicos\n");
    printf("6 - Voltar para o Menu Principal\n");
    opp = Veri_Int();
    CLEAR
    Listamento_M(opp);
}
void Saida_Espe(int a){
    //Apenas vai printar a especialidade do medico
    switch(a){
        case 1:
            printf("Clinico\n");
            break;
        case 2:
            printf("Pediatra\n");
            break;
        case 3:
            printf("Demartologista\n");
            break;
        case 4:
            printf("Cardiologista\n");
            break;
        case 5:
            printf("Outras\n");
            break;
    }
}
void Listamento_M(int a){
    //Lista os medicos de acordo com o criterio informado
    Leitura();
    int Ide,Ide2,Espeee,Total;
    Horario Lista;
    Lista.Minuto = -99;
    bool flag = false;
    switch (a){
        case 1:
            //Lista todos os medicos
            for(int i = 0;i<Banco_Medicos.QTDE;i++){
                printf("\nNome do Medico: %s\n", Banco_Medicos.Medicos[i].Nome);
                printf("Codigo de Identificacao: %d\n", Banco_Medicos.Medicos[i].ID);
                printf("Especialidade:");
                Saida_Espe(Banco_Medicos.Medicos[i].especialidade);
                printf("Horario Padrao de Funcionamento de Manha: %02d:%02d - %02d:%02d\n", Banco_Medicos.Medicos[i].Ini_Manha.Hora,Banco_Medicos.Medicos[i].Ini_Manha.Minuto, Banco_Medicos.Medicos[i].Fim_Manha.Hora, Banco_Medicos.Medicos[i].Fim_Manha.Minuto);
                printf("Horario Padrao de Funcionamento de Tarde: %02d:%02d - %02d:%02d\n", Banco_Medicos.Medicos[i].Ini_Tarde.Hora,Banco_Medicos.Medicos[i].Ini_Tarde.Minuto, Banco_Medicos.Medicos[i].Fim_Tarde.Hora, Banco_Medicos.Medicos[i].Fim_Tarde.Minuto);
            }
            if (Banco_Medicos.QTDE == 0){
                printf("Nao ha Medicos Cadastrados!!!!\n");
            }
            break;
        case 2:
            //Lista todos os medicos pelo ID ate que seja digitado 0
            while (1){
                printf("Para Terminar a busca por Identificacao, informe o Digito: 0\n");
                printf("Informe o Codigo de Identificacao do Medico:\n\n");
                Ide = Veri_Int();
                (Ide == 0) ? Continuar() : NULL;
                Ide2 = Busca_Medico(Ide) - 1;
                if (Ide2 == -1){
                    printf("Nao existe Medico com esse Identificador!!!!\n");
                } else {
                    printf("\nNome do Medico: %s\n", Banco_Medicos.Medicos[Ide2].Nome);
                    printf("Codigo de Identificacao: %d\n", Banco_Medicos.Medicos[Ide2].ID);
                    printf("Especialidade:");
                    Saida_Espe(Banco_Medicos.Medicos[Ide2].especialidade);
                    printf("Horario Padrao de Funcionamento de Manha: %02d:%02d - %02d:%02d\n", Banco_Medicos.Medicos[Ide2].Ini_Manha.Hora,Banco_Medicos.Medicos[Ide2].Ini_Manha.Minuto, Banco_Medicos.Medicos[Ide2].Fim_Manha.Hora, Banco_Medicos.Medicos[Ide2].Fim_Manha.Minuto);
                    printf("Horario Padrao de Funcionamento de Tarde: %02d:%02d - %02d:%02d\n", Banco_Medicos.Medicos[Ide2].Ini_Tarde.Hora,Banco_Medicos.Medicos[Ide2].Ini_Tarde.Minuto, Banco_Medicos.Medicos[Ide2].Fim_Tarde.Hora, Banco_Medicos.Medicos[Ide2].Fim_Tarde.Minuto);
                }
                Limpeza_Composta();
                continue; // CORRIGIDO: Troca recursao por 'continue'
            }
            break;
        case 3:
            //Percorre todos os medicos e lista os que tem a especialidade informada
            while(1){
                printf("Para Terminar a busca por Especialidade, informe o Digito: 0\n");
                printf("Escolha a opcao da especialidade desejada:\n");
                printf("1 - Clinico\n");
                printf("2 - Pediatra\n");
                printf("3 - Dermatologista\n");
                printf("4 - Cardiologista\n");
                printf("5 - Outra Especialidade\n\n");
                Espeee = Veri_Int();
                (Espeee == 0) ? Continuar() : NULL;
                if (Espeee < 1 || Espeee > 5){
                    printf("Opcao Invalida!!!!\n");
                } else {
                    for(int i = 0;i<Banco_Medicos.QTDE;i++){
                        if (Banco_Medicos.Medicos[i].especialidade == Espeee){
                            printf("\nNome do Medico: %s\n", Banco_Medicos.Medicos[i].Nome);
                            printf("Codigo de Identificacao: %d\n", Banco_Medicos.Medicos[i].ID);
                            printf("Especialidade:");
                            Saida_Espe(Banco_Medicos.Medicos[i].especialidade);
                            printf("Horario Padrao de Funcionamento de Manha: %02d:%02d - %02d:%02d\n", Banco_Medicos.Medicos[i].Ini_Manha.Hora,Banco_Medicos.Medicos[i].Ini_Manha.Minuto, Banco_Medicos.Medicos[i].Fim_Manha.Hora, Banco_Medicos.Medicos[i].Fim_Manha.Minuto);
                            printf("Horario Padrao de Funcionamento de Tarde: %02d:%02d - %02d:%02d\n", Banco_Medicos.Medicos[i].Ini_Tarde.Hora,Banco_Medicos.Medicos[i].Ini_Tarde.Minuto, Banco_Medicos.Medicos[i].Fim_Tarde.Hora, Banco_Medicos.Medicos[i].Fim_Tarde.Minuto);
                            flag = true;
                        }
                    }
                    if (flag == false){
                        printf("Nao existe medico com esse especialidade!!!\n");
                    }
                }
                Limpeza_Composta();
                continue; // CORRIGIDO: Troca recursao por 'continue'
            }
            break;
        case 4:
            //Pega a quantidade total de minutos de um horario e ve se esta no no intervalo do total de minutos dos medicos
            while(1){
                printf("Para Terminar a busca por Horario, informe o Digito: 0\n");
                printf("Informe  no formato HH:MM (10:30, por exemplo)o horario de atendimento desejado:\n");
                Verificacao_Horas(&Lista);
                //Verificacao
                Total = (Lista.Hora * 60) + Lista.Minuto;
                for(int i = 0;i<Banco_Medicos.QTDE;i++){
                    int TIM = (Banco_Medicos.Medicos[i].Ini_Manha.Hora * 60) + Banco_Medicos.Medicos[i].Ini_Manha.Minuto;
                    int TFM = (Banco_Medicos.Medicos[i].Fim_Manha.Hora * 60) + Banco_Medicos.Medicos[i].Fim_Manha.Minuto;
                    int TIT = (Banco_Medicos.Medicos[i].Ini_Tarde.Hora * 60) + Banco_Medicos.Medicos[i].Ini_Tarde.Minuto;
                    int TFT = (Banco_Medicos.Medicos[i].Fim_Tarde.Hora * 60) + Banco_Medicos.Medicos[i].Fim_Tarde.Minuto;
                    if (Total >= TIM && Total <= TFM || Total >= TIT && Total <= TFT){
                        flag = true;
                        printf("\nNome do Medico: %s\n", Banco_Medicos.Medicos[i].Nome);
                        printf("Codigo de Identificacao: %d\n", Banco_Medicos.Medicos[i].ID);
                        printf("Especialidade:");
                        Saida_Espe(Banco_Medicos.Medicos[i].especialidade);
                        printf("Horario Padrao de Funcionamento de Manha: %02d:%02d - %02d:%02d\n", Banco_Medicos.Medicos[i].Ini_Manha.Hora,Banco_Medicos.Medicos[i].Ini_Manha.Minuto, Banco_Medicos.Medicos[i].Fim_Manha.Hora, Banco_Medicos.Medicos[i].Fim_Manha.Hora);
                        printf("Horario Padrao de Funcionamento de Tarde: %02d:%02d - %02d:%02d\n", Banco_Medicos.Medicos[i].Ini_Tarde.Hora,Banco_Medicos.Medicos[i].Ini_Tarde.Minuto, Banco_Medicos.Medicos[i].Fim_Tarde.Hora, Banco_Medicos.Medicos[i].Fim_Tarde.Hora);
                    }
                }
                if (flag == false){
                    printf("\nNao ha medico que atenda nesse horario!!!!\n");
                }
                Limpeza_Composta();
                continue; // CORRIGIDO: Troca recursao por 'continue'
            }
            break;
        case 5:
            printf("Atualmente no sistema estao cadastrados %d medicos\n", Banco_Medicos.QTDE);
            break;
        case 6:
            Continuar();
        default:
            printf("Opcao invalida!!!\n");
            Listar_Medicos();
            break;
    }
    Continuar();
}
int Busca_Medico(int Identi){
    //Funcao para procurar qual a posicao do medico no vetor do medicos
    for(int i=0;i<Banco_Medicos.QTDE;i++){
        if (Banco_Medicos.Medicos[i].ID == Identi){
            return i+1;
        }
    }
    return 0;
}
void Agenda_Medico(){
    //Funcao que printa a agenda do medico
    int ID, Posicao;
    Data Data_Temp;
    Horario Agendaa;
    Agendaa.Hora = 8;
    Agendaa.Minuto = 0;
    int Time_Inicial;
    time_t Time_Temp;
    int Pos_P;
    struct tm Agenda = {0};
    struct tm Semanais[5];
    printf("Informe o ID do Medico:\n");
    ID = Veri_Int();
    //Faz um ponteiro de ponteiros para as strings
    char **P = malloc(5 * sizeof(char *));
    for(int i = 0; i <5;i++){
        P[i] = malloc(sizeof(char[27])); // Aumentado para 27 para caber 26 chars + \0
    }
    //
    Posicao = Busca_Medico(ID);
    if (Posicao == 0){
        printf("\nNao existe Medico com esse ID!!!!\n");
        Limpeza_Composta();
        Agenda_Medico();
    }
    printf("Informe a Data do Inicio da Semana no formato DD/MM/AAAA (15/11/2015, por exemplo):\n");
    Verificacao_Datas(&Data_Temp);
    Agenda.tm_mday = Data_Temp.Dia;
    Agenda.tm_mon = Data_Temp.Mes - 1;
    Agenda.tm_year = Data_Temp.Ano - 1900;
    Time_Inicial = mktime(&Agenda);
    //Coloca as datas subsequentes no vetor Semanais
    for (int i = 0;i<5;i++){
        Time_Temp = Time_Inicial + (i * 86400);
        Semanais[i] = *localtime(&Time_Temp);
        Semanais[i].tm_mon += 1;
        Semanais[i].tm_year += 1900;
    }

    //Printar a agenda
    for(int i=0;i<30;i++){
        if (i == 0){
            printf("\n|         HORARIOS         |         SEGUNDA          |          TERCA           |          QUARTA          |          QUINTA          |           SEXTA          |\n");
        } else {
            for(int j = 0;j<5;j++){
                strcpy(P[j],"           VAGO           ");
            }
            //Verificar se tem paciente ou nao
            for(int k = 0;k<5;k++){
                bool flag = false;
                for(int j = 0;j<Banco_Consultas.QTDE;j++){
                    if(Banco_Consultas.Consultas[j].IDMedico == ID){
                        if(Banco_Consultas.Consultas[j].data.Dia == Semanais[k].tm_mday &&
                           Banco_Consultas.Consultas[j].data.Mes == Semanais[k].tm_mon &&
                           Banco_Consultas.Consultas[j].data.Ano == Semanais[k].tm_year &&
                           Banco_Consultas.Consultas[j].Inicio.Hora == Agendaa.Hora &&
                           Banco_Consultas.Consultas[j].Inicio.Minuto == Agendaa.Minuto){
                                if (flag == false){
                                    flag = true;
                                    Pos_P = Busca_Paciente(Banco_Consultas.Consultas[j].IDPaciente) - 1;
                                    if(Pos_P != -1){ // Verifica se paciente existe
                                        strncpy(P[k],Banco_Pacientes.Pacientes[Pos_P].Nome,26);
                                        P[k][26] = '\0'; // Corrigido para 26
                                    } else {
                                        strcpy(P[k],"   PACIENTE NAO ENCONTRADO  ");
                                    }
                                } else {
                                    strcpy(P[k],"    MAIS DE UM PACIENTE   ");
                                    break;
                                }
                           }
                    }
                }
            }
            //Printar na tela
            printf("|           %02d:%02d          |%-26s|%-26s|%-26s|%-26s|%-26s|\n",Agendaa.Hora,Agendaa.Minuto, P[0], P[1], P[2], P[3], P[4]);
        }
        Agendaa.Minuto += 30;
        if (i % 2 == 0){
            Agendaa.Hora += 1;
            Agendaa.Minuto = 0;
        }
        printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    }
    
    //Liberar memoria alocada para P
    for(int i = 0; i <5;i++){
        free(P[i]);
    }
    free(P);

    Continuar();
}
