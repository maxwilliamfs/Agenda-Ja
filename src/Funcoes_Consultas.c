#include "Funcoes_Consultas.h"
#include "Funcoes_Gerais.h"
#include "Funcoes_Medicas.h"
#include "Funcoes_Pacientes.h"

//Funcoes
void Atua_Consulta(){
    //Variaveis da modificacao
    int IDD, idMedicoNovo, idPacienteNovo, SttsNovo, PrioNovo, SobrepNovo;
    Data Nova_Data;
    Horario NovoHInicio, NovoHFim;
    //Variaveis para copia do arquivo
    char Lixo[64];
    int Linha, iddd;
    int ID_M,ID_P,Stts,pri,sob;
    Data Atua_Consu;
    Horario AIni_Con,AFim_Con;
    //Codigo Principal
    printf("Informe o ID da Consulta:\n");
    //Verifica se realmente eh um valor inteiro
    IDD = Veri_Int();
    Linha = Busca_Consulta(IDD);
    //Se nao existir consulta com esse ID
    if (Linha == 0){
        printf("Nao existe Consulta com esse ID!!!!\n");
        Limpeza_Composta();
        Atua_Consulta();
    }
    printf("Informe o Codigo Identificador (ID) do Novo Medico que realizara a Consulta:\n");
    idMedicoNovo = Veri_Int();
    if (Busca_Medico(idMedicoNovo) == 0){
        printf("\nNao existe Medico com esse ID!!!\n");
        Limpeza_Composta();
        Atua_Consulta();
    }
    printf("Informe o Codigo Identificador (ID) do Novo Paciente que realizara a Consulta:\n");
    idPacienteNovo = Veri_Int();
    if (Busca_Paciente(idPacienteNovo) == 0){
        printf("\nNao existe Paciente com esse ID!!!\n");
        Limpeza_Composta();
        Atua_Consulta();
    }
    printf("Informe a Nova Data da Consulta no formato: DD/MM/AAAA (10/03/2025, por exemplo):\n");
    Verificacao_Datas(&Nova_Data);
    printf("Escolha a opcao sobre o novo Status da Consulta:\n");
    printf("1 - Agendada\n");
    printf("2 - Houve Falta do Medico ou Paciente\n");
    printf("3 - Concluida\n");
    printf("4 - Cancelada\n");
    SttsNovo = Veri_Int();
    if (SttsNovo < 1 || SttsNovo > 4){
        printf("Opcao Invalida!!!!!\n");
        Limpeza_Composta();
        Atua_Consulta();
    }
    printf("Escolha a opcao sobre a Nova Gravidade da Consulta:\n");
    printf("1 - Urgente\n");
    printf("2 - Eletiva (Nao tem urgencia)\n");
    PrioNovo = Veri_Int();
    if (PrioNovo != 1 && PrioNovo != 2){
        Limpeza_Composta();
        printf("Opcao invalida!!!");
        Atua_Consulta();
    }
    if (PrioNovo == 2){
        printf("Informe o Novo Horario de inicio da Consulta no formato: HH:MM (10:30, por exemplo):\n");
        Verificacao_Horas(&NovoHInicio);
        Horarizar(NovoHInicio.Hora, NovoHInicio.Minuto+Padrao.Dura_Consulta);
        NovoHFim.Hora = A_Horas;
        NovoHFim.Minuto = A_Minuto;
        Verificacao_HMedico(idMedicoNovo, NovoHInicio, NovoHFim);
        printf("Escolha a opcao sobre a Nova Possibilidade de Sobreposicao da Consulta\n");
        printf("1 - Permite Sobreposicao\n");
        printf("2 - Nao Permite Sobreposicao\n");
        SobrepNovo = Veri_Int();
        if (SobrepNovo != 1 && SobrepNovo != 2){
            Limpeza_Composta();
            printf("Escolha invalida!!!");
            Atua_Consulta();
        }
        Veri_Sobreposicao(Nova_Data, NovoHInicio, NovoHFim, SobrepNovo, idMedicoNovo);
    } else {
        SobrepNovo = 2;
        Prioridade(idMedicoNovo, &NovoHInicio, Nova_Data);
        Horarizar(NovoHInicio.Hora, NovoHInicio.Minuto+Padrao.Dura_Consulta);
        NovoHFim.Hora = A_Horas;
        NovoHFim.Minuto = A_Minuto;
    }
    //Armazena o horario previsto para fim baseado na duracao padrao
    //Manipulacao de Arquivos
    Copia_Consul = fopen("Consultas_Temporarias.txt","w");
    fclose(Copia_Consul);
    Copia_Consul = fopen("Consultas_Temporarias.txt","a");
    arquivo_Consul = fopen("Dados_Consultas.txt","r");
    for(int i = 0;i<Banco_Consultas.QTDE;i++){
        if ((i+1) == Linha){
            fgets(Lixo,64,arquivo_Consul);
            fprintf(Copia_Consul, "%d %d %d %d/%d/%d %d:%d %d:%d %d %d %d\n", IDD, idMedicoNovo, idPacienteNovo, Nova_Data.Dia, Nova_Data.Mes, Nova_Data.Ano, NovoHInicio.Hora, NovoHInicio.Minuto, NovoHFim.Hora, NovoHFim.Minuto, SttsNovo, PrioNovo, SobrepNovo);
        } else {
            fscanf(arquivo_Consul, "%d %d %d %d/%d/%d %d:%d %d:%d %d %d %d\n", &iddd, &ID_M, &ID_P, &Atua_Consu.Dia, &Atua_Consu.Mes, &Atua_Consu.Ano, &AIni_Con.Hora, &AIni_Con.Minuto, &AFim_Con.Hora, &AFim_Con.Minuto, &Stts, &pri, &sob);
            fprintf(Copia_Consul, "%d %d %d %d/%d/%d %d:%d %d:%d %d %d %d\n", iddd, ID_M, ID_P, Atua_Consu.Dia, Atua_Consu.Mes, Atua_Consu.Ano, AIni_Con.Hora, AIni_Con.Minuto, AFim_Con.Hora, AFim_Con.Minuto, Stts, pri, sob);
        }
    }
    fclose(arquivo_Consul);
    fclose(Copia_Consul);
    remove("Dados_Consultas.txt");
    rename("Consultas_Temporarias.txt", "Dados_Consultas.txt");
    arquivo_Consul = Copia_Consul;
    Copia_Consul = NULL;
    printf("Modificacao feita com Sucesso!!!!\n");
    Leitura();
    int OP;
    printf("\nDeseja Modificar os Ddos de Mais uma Consulta? (1-Sim) (2-Nao)\n");
    OP = Veri_Int();
    if (OP == 1){
        Limpeza_Composta();
        Atua_Consulta();
    } else{
        Continuar();
    }
}
void Agendar_Consul(){
    int ID_M,ID_P,Stts,pri,sob;
    Data Agen_Consu;
    Horario Ini_Con,Fim_Con;
    printf("Informe o Codigo Identificador (ID) do Medico que realizara a Consulta:\n");
    ID_M = Veri_Int();
    if (Busca_Medico(ID_M) == 0){
        printf("\nNao existe Medico com esse ID!!!\n");
        Limpeza_Composta();
        Agendar_Consul();
    }
    printf("Informe o Codigo Identificador (ID) do Paciente que realizara a Consulta:\n");
    ID_P = Veri_Int();
    if (Busca_Paciente(ID_P) == 0){
        printf("\nNao existe Paciente com esse ID!!!\n");
        Limpeza_Composta();
        Agendar_Consul();
    }
    printf("Informe a data da Consulta no formato: DD/MM/AAAA (10/03/2025, por exemplo):\n");
    Verificacao_Datas(&Agen_Consu);
    printf("Escolha a opcao sobre a gravidade da Consulta:\n");
    printf("1 - Urgente\n");
    printf("2 - Eletiva (Nao tem urgencia)\n");
    pri = Veri_Int();
    if (pri != 1 && pri != 2){
        printf("Escolha invalida!!!");
        Limpeza_Composta();
        Agendar_Consul();
    }
    if (pri == 2){
        printf("Escolha a opcao sobre possibilidade de sobreposicao da Consulta\n");
        printf("1 - Permite Sobreposicao\n");
        printf("2 - Nao Permite Sobreposicao\n");
        sob = Veri_Int();
        if (sob != 1 && sob != 2){
            printf("Escolha invalida!!!");
            Limpeza_Composta();
            Agendar_Consul();
        }
        printf("Informe o Horario de inicio da Consulta no formato: HH:MM (10:30, por exemplo):\n");
        Verificacao_Horas(&Ini_Con);
        Horarizar(Ini_Con.Hora, Ini_Con.Minuto+Padrao.Dura_Consulta);
        Fim_Con.Hora = A_Horas;
        Fim_Con.Minuto = A_Minuto;
        Verificacao_HMedico(ID_M, Ini_Con,Fim_Con);
        //Parte de Sobreposicao
        Veri_Sobreposicao(Agen_Consu, Ini_Con, Fim_Con, sob, ID_M);
        Stts = 1; //O status dela eh agendada
    } else {
        sob = 2;
        Stts = 1;
        Prioridade(ID_M, &Ini_Con, Agen_Consu);
        Horarizar(Ini_Con.Hora, Ini_Con.Minuto+Padrao.Dura_Consulta);
        Fim_Con.Hora = A_Horas;
        Fim_Con.Minuto = A_Minuto;
    }
    arquivo_Consul = fopen("Dados_Consultas.txt","a");
    fprintf(arquivo_Consul, "%d %d %d %d/%d/%d %d:%d %d:%d %d %d %d\n", Id, ID_M, ID_P, Agen_Consu.Dia, Agen_Consu.Mes, Agen_Consu.Ano, Ini_Con.Hora, Ini_Con.Minuto, Fim_Con.Hora, Fim_Con.Minuto, Stts, pri, sob);
    //ID, ID_M, ID_P, Data, Horario Inicio, Horario Fim, Status, Prioridade, Sobreposicao
    fclose(arquivo_Consul);
    printf("O ID dessa Consulta eh %d\n", Id);
    printf("Consulta Agendada com Sucesso!!!\n");
    Aumentar_ID();
    Leitura();
    Atualizacao_Geral(Parametro = Consulta);
    int OP;
    printf("\nDeseja Agendar Mais uma Consulta? (1-Sim) (2-Nao)\n");
    OP = Veri_Int();
    if (OP == 1){
        Limpeza_Composta();
        Agendar_Consul();
    } else{
        Continuar();
    }
}
void Lista_Consultas(){
    int op;
    printf("\nEscolhar o criterio para listar as Consultas:\n");
    printf("OBS: Informe o numero 0 para cancelar qualquer operacao!!!\n");
    printf("\n1 - Listar Todas as Consultas\n");
    printf("2 - Listar Consultas por ID\n");
    printf("3 - Listar Consultas por Horario\n");
    printf("4 - Listar Consultas por Data\n");
    printf("5 - Listar Consultas por Medico\n");
    printf("6 - Listar Consultas por Paciente\n");
    printf("7 - Listar Consultas por Status\n");
    printf("8 - Listar Consultas por Gravidade\n");
    printf("9 - Listar Consultas por Sobreposicao\n");
    printf("10 - Exibir Quantidade de Consultas Cadastradas\n");
    printf("11 - Voltar ao Menu Principal\n");
    op = Veri_Int();
    CLEAR
    Listamento(op);
}
void Saida_Stts(int a){
    //Funcao para imprimir na tela o status da consulta
    switch (a){
        case 1:
            printf("Consulta Agendada\n");
            break;
        case 2:
            printf("Consulta Nao Concluida, pois houve falta do Medico ou do Paciente\n");
            break;
        case 3:
            printf("Consulta Concluida\n");
            break;
        case 4:
            printf("Consulta Cancelada\n");
            break;
    }
}
int Busca_Consulta(int IDD){
    //Funcao que busca a posicao da consulta no ponteiro consultas
    for(int i = 0;i<Banco_Consultas.QTDE;i++){
        if (Banco_Consultas.Consultas[i].ID == IDD){
            return i+1;
        }
    }
    return 0;
}
//Funcoes da Listagem
void Listamento(int a){
    Leitura();
    int id, Pos, Total, STTS, Urge, Sobrep;
    Data Lista1;
    Horario Lista2;
    bool flag = false;
    switch (a){
        case 1:
            for(int i=0;i<Banco_Consultas.QTDE;i++){
                PRINTACAO_CP(i);
            }
            if (Banco_Consultas.QTDE == 0){
                printf("Nao ha Consultas Cadastradas!!!!\n");
            }
            Continuar();
            break;
        case 2:
            printf("Para Finalizar a Operacao de Busca por ID, informe o ID: 0\n");
            printf("Informe o ID da consulta\n");
            id = Veri_Int();
            Pos = Busca_Consulta(id) -1;
            if (Pos == -1){
                printf("\nNao existe consulta com esse ID!!!!\n\n");
                Lista_Consultas(); // CORRIGIDO: Volta ao Menu de Listagem
            }
            printf("\nID da Consulta: %d\n", Banco_Consultas.Consultas[Pos].ID);
            printf("ID do Medico: %d\n", Banco_Consultas.Consultas[Pos].IDMedico);
            printf("ID do Paciente: %d\n", Banco_Consultas.Consultas[Pos].IDPaciente);
            printf("Data: %d/%d/%d\n", Banco_Consultas.Consultas[Pos].data.Dia, Banco_Consultas.Consultas[Pos].data.Mes, Banco_Consultas.Consultas[Pos].data.Ano);
            printf("Horario de Inicio da Consulta: %d:%d\n", Banco_Consultas.Consultas[Pos].Inicio.Hora, Banco_Consultas.Consultas[Pos].Inicio.Minuto);
            printf("Horario Previsto para Fim da Consulta: %d:%d\n", Banco_Consultas.Consultas[Pos].Fim.Hora, Banco_Consultas.Consultas[Pos].Fim.Minuto);
            Saida_Stts(Banco_Consultas.Consultas[Pos].Status);
            (Banco_Consultas.Consultas[Pos].Info_Extras.Urgente == 1) ? printf("Consulta Urgente\n") : printf("Consulta Leviana\n");
            (Banco_Consultas.Consultas[Pos].Info_Extras.Sobreposicao == 1) ? printf("Permite Sobreposicao\n") : printf("Nao Permite Sobreposicao\n");
            Limpeza_Composta();
            Lista_Consultas(); // CORRIGIDO: Volta ao Menu de Listagem
            break;
        case 3:
            printf("Para Finalizar a Operacao de Busca por Horario, informe o Digito: 0\n");
            printf("Informe o horario no formato HH:MM (10:30, por exemplo):\n");
            Verificacao_Horas(&Lista2);
            Total = (Lista2.Hora * 60) + Lista2.Minuto;
            for(int i = 0;i<Banco_Consultas.QTDE;i++){
                int TI = (Banco_Consultas.Consultas[i].Inicio.Hora * 60) + Banco_Consultas.Consultas[i].Inicio.Minuto;
                int TF = (Banco_Consultas.Consultas[i].Fim.Hora * 60) + Banco_Consultas.Consultas[i].Fim.Minuto;
                if (Total >= TI && Total <= TF){
                    flag = true;
                    PRINTACAO_CP(i);
                }
            }
            if (flag == false){
                printf("\nNao ha Consultas Nesse horario!!!!\n\n");
            }
            Limpeza_Composta();
            Lista_Consultas(); // CORRIGIDO: Volta ao Menu de Listagem
            break;
        case 4:
            printf("Para Finalizar a operacao de Busca por Datas, informe o digito: 0\n");
            printf("Informe a Data no formato DD/MM/AAAA (15/11/2018, por exemplo):\n");
            Verificacao_Datas(&Lista1);
            //Verificacao
            for(int i = 0;i<Banco_Consultas.QTDE;i++){
                if (Banco_Consultas.Consultas[i].data.Dia == Lista1.Dia && Banco_Consultas.Consultas[i].data.Mes == Lista1.Mes && Banco_Consultas.Consultas[i].data.Ano == Lista1.Ano){
                    PRINTACAO_CP(i);
                    flag = true;
                }
            }
            if (!flag){
                printf("Nao existe Consulta com a Data informada!!!\n");
            }
            Limpeza_Composta();
            Lista_Consultas(); // CORRIGIDO: Volta ao Menu de Listagem
            break;
        case 5:
            printf("Para Finalizar a operacao de Busca por Medico, informe o digito: 0\n");
            printf("Informe o Codigo Identificador do Medico:\n");
            id = Veri_Int();
            for(int i=0;i<Banco_Consultas.QTDE;i++){
                if (Banco_Consultas.Consultas[i].IDMedico == id){
                    flag = true;
                    PRINTACAO_CP(i);
                }
            }
            if (!flag){
                printf("Nao existe nenhuma Consulta cadastrada com esse Medico!!!!\n");
            }
            Limpeza_Composta();
            Lista_Consultas(); // CORRIGIDO: Volta ao Menu de Listagem
            break;
        case 6:
            printf("Para Finalizar a operacao de Busca por Paciente, informe o digito: 0\n");
            printf("Informe o Codigo Identificador do Paciente:\n");
            id = Veri_Int();
            for(int i=0;i<Banco_Consultas.QTDE;i++){
                if (Banco_Consultas.Consultas[i].IDPaciente == id){
                    flag = true;
                    PRINTACAO_CP(i);
                }
            }
            if (!flag){
                printf("Nao existe nenhuma Consulta cadastrada com esse Paciente!!!!\n");
            }
            Limpeza_Composta();
            Lista_Consultas(); // CORRIGIDO: Volta ao Menu de Listagem
            break;
        case 7:
            printf("Para Finalizar a operacao de Busca por Status, informe o digito: 0\n");
            printf("Escolha a opcao do Status da Consulta:\n");
            printf("1 - Consulta Agendada\n");
            printf("2 - Consulta Cancelada\n");
            printf("3 - Consulta Concluida\n");
            printf("4 - Houve Falta na Consulta\n");
            STTS = Veri_Int();
            if (STTS < 0 || STTS > 4){
                printf("\nOpcao Invalida!!!!!\n");
                Lista_Consultas(); // CORRIGIDO: Volta ao Menu de Listagem
            }
            for(int i=0;i<Banco_Consultas.QTDE;i++){
                if (Banco_Consultas.Consultas[i].Status == STTS){
                    flag = true;
                    PRINTACAO_CP(i);
                }
            }
            if (!flag){
                printf("Nao existe nenhuma Consulta cadastrada com esse status!!!!\n");
            }
            Limpeza_Composta();
            Lista_Consultas(); // CORRIGIDO: Volta ao Menu de Listagem
            break;
        case 8:
            printf("Para Finalizar a operacao de Busca por Status, informe o digito: 0\n");
            printf("Escolha a opcao da Gravidade da Consulta:\n");
            printf("1 - Urgente\n");
            printf("2 - Leviana\n");
            Urge = Veri_Int();
            if (Urge != 1 && Urge != 2){
                printf("\nOpcao Invalida!!!!!\n");
                Limpeza_Composta();
                Lista_Consultas(); // CORRIGIDO: Volta ao Menu de Listagem
            }
            for(int i=0;i<Banco_Consultas.QTDE;i++){
                if (Banco_Consultas.Consultas[i].Info_Extras.Urgente == Urge){
                    flag = true;
                    PRINTACAO_CP(i);
                }
            }
            if (!flag){
                printf("Nao existe nenhuma Consulta cadastrada com essa Gravidade!!!!\n");
            }
            Limpeza_Composta();
            Lista_Consultas(); // CORRIGIDO: Volta ao Menu de Listagem
            break;
        case 9:
            printf("Para Finalizar a operacao de Busca por Sobreposicao, informe o digito: 0\n");
            printf("Escolha a opcao da Sobreposicao da Consulta:\n");
            printf("1 - Permite Sobreposicao\n");
            printf("2 - Nao Permite Sobreposicao\n");
            Sobrep = Veri_Int();
            if (Sobrep != 1 && Sobrep != 2){
                printf("\nOpcao Invalida!!!!!\n");
                Limpeza_Composta();
                Lista_Consultas(); // CORRIGIDO: Volta ao Menu de Listagem
            }
            for(int i=0;i<Banco_Consultas.QTDE;i++){
                if (Banco_Consultas.Consultas[i].Info_Extras.Sobreposicao == Sobrep){
                    flag = true;
                    PRINTACAO_CP(i);
                }
            }
            if (!flag){
                printf("Nao existe nenhuma Consulta cadastrada com essa Sobreposicao!!!\n");
            }
            Limpeza_Composta();
            Lista_Consultas(); // CORRIGIDO: Volta ao Menu de Listagem
            break;
        case 10:
            printf("\nAte o Momento existem %d Consulta(s) Cadastrada(s)\n", Banco_Consultas.QTDE);
            Limpeza_Composta();
            break; // CORRIGIDO: Adicionado break
        case 11:
            Menu_Principal();
            break; // Adicionado break
        default:
            printf("\nOpcao Invalida!!!!\n");
            Limpeza_Composta();
            Lista_Consultas();
    }

}
void PRINTACAO_CP (int idx){
    printf("\nID da Consulta: %d\n", Banco_Consultas.Consultas[idx].ID);
    printf("ID do Medico: %d\n", Banco_Consultas.Consultas[idx].IDMedico);
    printf("ID do Paciente: %d\n", Banco_Consultas.Consultas[idx].IDPaciente);
    printf("Data: %d/%d/%d\n", Banco_Consultas.Consultas[idx].data.Dia, Banco_Consultas.Consultas[idx].data.Mes, Banco_Consultas.Consultas[idx].data.Ano);
    printf("Horario de Inicio da Consulta: %02d:%02d\n", Banco_Consultas.Consultas[idx].Inicio.Hora, Banco_Consultas.Consultas[idx].Inicio.Minuto);
    printf("Horario Previsto para Fim da Consulta: %02d:%02d\n", Banco_Consultas.Consultas[idx].Fim.Hora, Banco_Consultas.Consultas[idx].Fim.Minuto);
    Saida_Stts(Banco_Consultas.Consultas[idx].Status);
    (Banco_Consultas.Consultas[idx].Info_Extras.Urgente == 1) ? printf("Consulta Urgente\n") : printf("Consulta Leviana\n");
    (Banco_Consultas.Consultas[idx].Info_Extras.Sobreposicao == 1) ? printf("Permite Sobreposicao\n") : printf("Nao Permite Sobreposicao\n");
}
