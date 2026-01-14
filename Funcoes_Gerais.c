#include "Funcoes_Gerais.h"
#include "Funcoes_Consultas.h"
#include "Funcoes_Medicas.h"
#include "Funcoes_Pacientes.h"

//Biblioteca com as funcoes genericas e principais do programa, que vai fazer a ligacao entre as outras bibliotecas e
//armazenar funcoes que vao ser utilizadas por todas as bibliotecas, diversas vezes

//Variaveis Globais (Definição)
bool Primeira_Inicializacao = true;
int A_Horas, A_Minuto;
//Ponteiros FILE
FILE *arquivo_Geral;
FILE *arquivo_Extra;
FILE *arquivo_Paci;
FILE *Copia_Paci;
FILE *arquivo_Consul;
FILE *Copia_Consul;
FILE *Copia_Med;
FILE *arquivo_Med;
//Variaveis de Estruturas.h
int Id, *inter;
bool Aumentando = true;
bool Aumentando2 = true;
bool Aumentando3 = true;
VerificacaoE Parametro2;
Informacao Parametro;
Politica_Agen Padrao;
PontMedicos Banco_Medicos;
PontPacientes Banco_Pacientes;
PontConsultas Banco_Consultas;


//Funcoes
int Menu_Principal(){
    //Principal funcao, sendo ela que vai levar para os outros submenus e colocar o resto do codigo "pra frente"
    Leitura();
    CLEAR
    int op;
    printf("Bem vindo ao Agenda Ja!\n");
    printf("Escolha a opcao desejada:\n");
    printf("\n--------------------------------------------------------------\n");
    printf("OBS: Informe o numero 0 para cancelar qualquer operacao!!!\n");
    printf("1 - Administracao das Consultas\n");
    printf("2 - Administracao dos Medicos\n");
    printf("3 - Administracao dos Pacientes\n");
    printf("4 - Configuracoes Extras\n"); // Adicionei o item 4 que faltava no print
    printf("5 - Fechar Programa");
    printf("\n--------------------------------------------------------------\n");
    op = Veri_Int();
    CLEAR
    //switch que vai levar para cada submenu ou fechar o programa
    switch (op){
        case 1:
            Menu_Consultas();
            break;
        case 2:
            Menu_Medicos();
            break;
        case 3:
            Menu_Pacientes();
            break;
        case 4:
            Menu_Extra();
            break;
        case 5:
            printf("Obrigado por utilizar o Agenda Ja!\n");
            printf("Ate a proxima!!!\n");
            exit(0);
            break;
        default:
            printf("Ops, Opcao invalida\n");
            printf("Escolha novamente\n\n");
            Menu_Principal();
            break;
    }
    return 0; // Adicionado retorno
}
void Menu_Consultas(){
    //Sub menu da consultas
    int op;
    printf("Escolha a opcao desejada:\n");
    printf("\n--------------------------------------------------------------\n");
    printf("OBS: Informe o numero 0 para cancelar qualquer operacao!!!\n");
    printf("1- Agendar Nova Consulta\n");
    printf("2- Listar Consultas\n");
    printf("3- Modificar Consulta\n");
    printf("4- Voltar ao Menu Principal");
    printf("\n--------------------------------------------------------------\n");
    op = Veri_Int();
    CLEAR
    switch (op){
        case 1:
            Agendar_Consul();
            break;
        case 2:
            Lista_Consultas();
            break;
        case 3:
            Atua_Consulta();
            break;
        case 4:
            Menu_Principal();
            break;
        default:
            printf("Ops, Opcao invalida\n");
            printf("Escolha novamente\n\n");
            Menu_Consultas();
            break;
    }
}
void Menu_Medicos(){
    //Sub menu dos medicos
    int op;
    printf("Escolha a opcao desejada:\n");
    printf("\n--------------------------------------------------------------\n");
    printf("OBS: Informe o numero 0 para cancelar qualquer operacao!!!\n");
    printf("1- Cadastrar Novo Medico\n");
    printf("2- Listar Medicos\n");
    printf("3- Modificar Dados De algum Medico\n");
    printf("4- Remover Medico\n");
    printf("5- Agenda Semanal\n");
    printf("6- Voltar ao Menu Principal");
    printf("\n--------------------------------------------------------------\n");
    op = Veri_Int();
    CLEAR
    switch (op){
        case 1:
            Cadas_Medico();
            break;
        case 2:
            Listar_Medicos();
            break;
        case 3:
            Atua_Medico();
            break;
        case 4:
            Remo_Medico();
            break;
        case 5:
            Agenda_Medico();
            break;
        case 6:
            Menu_Principal();
            break;
        default:
            printf("Ops, Opcao invalida\n");
            printf("Escolha novamente\n\n");
            Menu_Medicos();
            break;
    }
}
void Menu_Pacientes(){
    //sub menu dos pacientes
    int op;
    printf("Escolha a opcao desejada:\n");
    printf("\n--------------------------------------------------------------\n");
    printf("OBS: Informe o numero 0 para cancelar qualquer operacao!!!\n");
    printf("1- Cadastrar Novo Pacientes\n");
    printf("2- Listar Pacientes\n");
    printf("3- Modificar Dados de algum Paciente\n");
    printf("4- Remover Paciente\n");
    printf("5- Voltar ao Menu Principal");
    printf("\n--------------------------------------------------------------\n");
    op = Veri_Int();
    CLEAR
    switch (op){
        case 1:
            system("cls");
            Cadas_Paciente();
            break;
        case 2:
            Listar_Pacientes();
            break;
        case 3:
            Atua_Paciente();
            break;
        case 4:
            Remo_Paciente();
            break;
        case 5:
            Menu_Principal();
            break;
        default:
            printf("Ops, Opcao invalida\n");
            printf("Escolha novamente\n\n");
            Menu_Pacientes();
            break;
    }
}
void Menu_Extra(){
    //Sub Menu de funcionalidades extras do sistema
    int op,TEMP;
    printf("Escolha a opcao desejada:\n");
    printf("\n--------------------------------------------------------------\n");
    printf("1 - Modificar tempo padrao de atendimento\n");
    printf("2 - Voltar ao Menu Principal");
    printf("\n--------------------------------------------------------------\n");
    op = Veri_Int();
    switch (op){
        case 1:
            printf("Informe o Novo tempo Medio para um Consulta em Minutos:\n");
            scanf("%d", &TEMP);
            getchar(); //Limpa o buffer do scanf
            Padrao.Dura_Consulta = TEMP;
            Atualizacao_Geral(Parametro = Tempo_Padrao);
            Continuar();
            break;
        case 2:
            Continuar();
            break;
        default:
            printf("Opcao Invalida!!!\n");
            Menu_Extra();
            break;
    }
}
void Inicialzar(){
    //Funcao que verifica se o arquivo ja existe e se nao existir, cria-o e define o valor inicial de algumas variaveis
    arquivo_Med = fopen("Dados_Medicos.txt","r");
    if (arquivo_Med == NULL){
        // fclose(arquivo_Med); // Nao precisa fechar se for NULL
        //Se for o primeiro acesso ao programa, vai definir a duracao padrao das consultas como 30 minutos
        arquivo_Geral = fopen("Dados_Gerais.txt", "w");
        fprintf(arquivo_Geral,"0 10 0 10 0 10"); //Quantidade e Capcidade de Consultas, Medicos e Pacientes reespectivamente
        fclose(arquivo_Geral);
        //Dados Extras
        arquivo_Extra = fopen("Dados_Extras.txt", "w");
        fprintf(arquivo_Extra, "1 30");
        fclose(arquivo_Extra);
        //Medicos
        arquivo_Med = fopen("Dados_Medicos.txt", "w");
        fclose(arquivo_Med);
        //Pacientes
        arquivo_Paci = fopen("Dados_Pacientes.txt", "w");
        fclose(arquivo_Paci);
        //Consultas
        arquivo_Consul = fopen("Dados_Consultas.txt","w");
        fclose(arquivo_Consul);
    } else {
        fclose(arquivo_Med);
    }
    //Faz a primeira alocacao de memoria quando o programa eh inicializado
    if(Primeira_Inicializacao == true){
        arquivo_Geral = fopen("Dados_Gerais.txt", "r");
        fscanf(arquivo_Geral,"%d %d %d %d %d %d", &Banco_Consultas.QTDE, &Banco_Consultas.Cap, &Banco_Medicos.QTDE, &Banco_Medicos.Cap, &Banco_Pacientes.QTDE, &Banco_Pacientes.Cap);
        fclose(arquivo_Geral);
        Banco_Pacientes.Pacientes = calloc(Banco_Pacientes.Cap, sizeof(PacienteP));
        Banco_Medicos.Medicos = calloc(Banco_Medicos.Cap,sizeof(MedicoP));
        Banco_Consultas.Consultas = calloc(Banco_Consultas.Cap,sizeof(ConsultaP));
        Primeira_Inicializacao = false;
    }
}
void Leitura(){
    //Vai ler os arquivos para colocar suas informacoes onde podem ser acessadas pela memoria ram
    arquivo_Geral = fopen("Dados_Gerais.txt", "r");
    fscanf(arquivo_Geral,"%d %d %d %d %d %d", &Banco_Consultas.QTDE, &Banco_Consultas.Cap, &Banco_Medicos.QTDE, &Banco_Medicos.Cap, &Banco_Pacientes.QTDE, &Banco_Pacientes.Cap);
    fclose(arquivo_Geral);
    //Ler dados extras
    arquivo_Extra = fopen("Dados_Extras.txt", "r");
    fscanf(arquivo_Extra,"%d %d", &Id, &Padrao.Dura_Consulta);
    fclose(arquivo_Extra);
    //Fazer o aumento da alocacao de medicos
    if (Banco_Medicos.QTDE == Banco_Medicos.Cap && Aumentando == true){
        Banco_Medicos.Cap += 10;
        Atualizacao_Geral(Parametro = Atualizacao_Capacidade);
        Banco_Medicos.Medicos = realloc(Banco_Medicos.Medicos,sizeof(MedicoP) * (Banco_Medicos.Cap));
    }
    //Fazer a diminuicao da alocacao de medicos
    if (Banco_Medicos.QTDE < (Banco_Medicos.Cap - 10)){
        Banco_Medicos.Cap -= 10;
        Atualizacao_Geral(Parametro = Atualizacao_Capacidade);
        Banco_Medicos.Medicos = realloc(Banco_Medicos.Medicos,sizeof(MedicoP) * (Banco_Medicos.Cap));
    }
    //Fazer o aumento da alocacao de pacientes
    if (Banco_Pacientes.QTDE == Banco_Pacientes.Cap && Aumentando2 == true){
        Banco_Pacientes.Cap += 10;
        Atualizacao_Geral(Parametro = Atualizacao_Capacidade);
        Banco_Pacientes.Pacientes = realloc(Banco_Pacientes.Pacientes,sizeof(PacienteP) * (Banco_Pacientes.Cap));
    }
    //Fazer a diminuicao da alocacao de pacientes
    if (Banco_Pacientes.QTDE < (Banco_Pacientes.Cap - 10)){
        Banco_Pacientes.Cap -= 10;
        Atualizacao_Geral(Parametro = Atualizacao_Capacidade);
        Banco_Pacientes.Pacientes = realloc(Banco_Pacientes.Pacientes,sizeof(PacienteP) * (Banco_Pacientes.Cap));
    }
    //Fazer o aumento da alocacao de Consultas
    if (Banco_Consultas.QTDE == Banco_Consultas.Cap && Aumentando3 == true){
        Banco_Consultas.Cap += 10;
        Atualizacao_Geral(Parametro = Atualizacao_Capacidade);
        Banco_Consultas.Consultas = realloc(Banco_Consultas.Consultas,sizeof(ConsultaP) * (Banco_Consultas.Cap));
    }
    //Re ler agora com o aumento
    arquivo_Geral = fopen("Dados_Gerais.txt", "r"); // re-abre para garantir
    fscanf(arquivo_Geral,"%d %d %d %d %d %d", &Banco_Consultas.QTDE, &Banco_Consultas.Cap, &Banco_Medicos.QTDE, &Banco_Medicos.Cap, &Banco_Pacientes.QTDE, &Banco_Pacientes.Cap);
    fclose(arquivo_Geral);
    //Ler o medicos do arquivo e colocar no ponteiro
    arquivo_Med = fopen("Dados_Medicos.txt","r");
    for(int i=0;i<Banco_Medicos.QTDE;i++){
        fgets(Banco_Medicos.Medicos[i].Nome,64,arquivo_Med);
        Banco_Medicos.Medicos[i].Nome[strcspn(Banco_Medicos.Medicos[i].Nome, "\n")] = '\0'; //Retira o \n que o fgets acaba pegando
        fscanf(arquivo_Med,"%d %d %d:%d %d:%d %d:%d %d:%d\n",&Banco_Medicos.Medicos[i].ID,&Banco_Medicos.Medicos[i].especialidade,&Banco_Medicos.Medicos[i].Ini_Manha.Hora,&Banco_Medicos.Medicos[i].Ini_Manha.Minuto,&Banco_Medicos.Medicos[i].Fim_Manha.Hora,&Banco_Medicos.Medicos[i].Fim_Manha.Minuto, &Banco_Medicos.Medicos[i].Ini_Tarde.Hora, &Banco_Medicos.Medicos[i].Ini_Tarde.Minuto, &Banco_Medicos.Medicos[i].Fim_Tarde.Hora, &Banco_Medicos.Medicos[i].Fim_Tarde.Minuto);
    }
    fclose(arquivo_Med);
    //Ler o arquivo dos pacientes e colocar no ponteiro
    arquivo_Paci = fopen("Dados_Pacientes.txt","r");
    for(int i =0;i<Banco_Pacientes.QTDE;i++){
        fgets(Banco_Pacientes.Pacientes[i].Nome,64,arquivo_Paci);
        Banco_Pacientes.Pacientes[i].Nome[strcspn(Banco_Pacientes.Pacientes[i].Nome,"\n")] = '\0';
        fscanf(arquivo_Paci,"%d\n",&Banco_Pacientes.Pacientes[i].ID);
        fgets(Banco_Pacientes.Pacientes[i].Contato,64,arquivo_Paci);
        Banco_Pacientes.Pacientes[i].Contato[strcspn(Banco_Pacientes.Pacientes[i].Contato,"\n")] = '\0';
    }
    fclose(arquivo_Paci);
    //Ler o arquivo das Consultas e colocar no ponteiro
    arquivo_Consul = fopen("Dados_Consultas.txt","r");
    //ID, ID_M, ID_P, Data, Horario Inicio, Horario Fim, Status, Prioridade, Sobreposicao
    for(int i = 0; i<Banco_Consultas.QTDE;i++){
        fscanf(arquivo_Consul, "%d %d %d %d/%d/%d %d:%d %d:%d %d %d %d\n", &Banco_Consultas.Consultas[i].ID, &Banco_Consultas.Consultas[i].IDMedico, &Banco_Consultas.Consultas[i].IDPaciente, &Banco_Consultas.Consultas[i].data.Dia, &Banco_Consultas.Consultas[i].data.Mes, &Banco_Consultas.Consultas[i].data.Ano, &Banco_Consultas.Consultas[i].Inicio.Hora, &Banco_Consultas.Consultas[i].Inicio.Minuto, &Banco_Consultas.Consultas[i].Fim.Hora, &Banco_Consultas.Consultas[i].Fim.Minuto, &Banco_Consultas.Consultas[i].Status, &Banco_Consultas.Consultas[i].Info_Extras.Urgente, &Banco_Consultas.Consultas[i].Info_Extras.Sobreposicao);
    }
    fclose(arquivo_Consul);
}
void Aumentar_ID(){
    //Funcao responsavel por apenas aumentar o id sempre que necessario e atualizar nos arquivos
    arquivo_Extra = fopen("Dados_Extras.txt","w");
    fprintf(arquivo_Extra,"%d %d", (Id+1), Padrao.Dura_Consulta);
    fclose(arquivo_Extra);
}
void Atualizacao_Geral(Informacao FParametro){
    //Funcao responsavel por atualizar as quantidades e capacidade dos pacientes,medicos e consultas no arquivo
    switch (FParametro){
        case Consulta:
            arquivo_Geral = fopen("Dados_Gerais.txt","w");
            fprintf(arquivo_Geral,"%d %d %d %d %d %d", (Banco_Consultas.QTDE+1), Banco_Consultas.Cap, Banco_Medicos.QTDE, Banco_Medicos.Cap, Banco_Pacientes.QTDE, Banco_Pacientes.Cap);
            fclose(arquivo_Geral);
            Aumentando3 = true;
            break;
        case Medico:
            arquivo_Geral = fopen("Dados_Gerais.txt","w");
            fprintf(arquivo_Geral,"%d %d %d %d %d %d", Banco_Consultas.QTDE, Banco_Consultas.Cap, (Banco_Medicos.QTDE+1), Banco_Medicos.Cap, Banco_Pacientes.QTDE, Banco_Pacientes.Cap);
            fclose(arquivo_Geral);
            Aumentando = true;
            break;
        case Paciente:
            arquivo_Geral = fopen("Dados_Gerais.txt","w");
            fprintf(arquivo_Geral,"%d %d %d %d %d %d", Banco_Consultas.QTDE, Banco_Consultas.Cap, Banco_Medicos.QTDE, Banco_Medicos.Cap, (Banco_Pacientes.QTDE+1), Banco_Pacientes.Cap);
            fclose(arquivo_Geral);
            Aumentando2 = true;
            break;
        case Atualizacao_Capacidade:
            arquivo_Geral = fopen("Dados_Gerais.txt","w");
            fprintf(arquivo_Geral,"%d %d %d %d %d %d", Banco_Consultas.QTDE, Banco_Consultas.Cap, Banco_Medicos.QTDE, (Banco_Medicos.Cap),Banco_Pacientes.QTDE, Banco_Pacientes.Cap);
            fclose(arquivo_Geral);
            break;
        case MedicoR:
            arquivo_Geral = fopen("Dados_Gerais.txt","w");
            fprintf(arquivo_Geral,"%d %d %d %d %d %d", Banco_Consultas.QTDE, Banco_Consultas.Cap, (Banco_Medicos.QTDE-1), Banco_Medicos.Cap, Banco_Pacientes.QTDE, Banco_Pacientes.Cap);
            fclose(arquivo_Geral);
            Aumentando = false;
            break;
        case PacienteR:
            arquivo_Geral = fopen("Dados_Gerais.txt","w");
            fprintf(arquivo_Geral,"%d %d %d %d %d %d", Banco_Consultas.QTDE, Banco_Consultas.Cap, Banco_Medicos.QTDE, Banco_Medicos.Cap, (Banco_Pacientes.QTDE-1), Banco_Pacientes.Cap);
            fclose(arquivo_Geral);
            Aumentando2 = false;
            break;
        case Tempo_Padrao:
            arquivo_Extra = fopen("Dados_Extras.txt", "w");
            fprintf(arquivo_Extra, "%d %d", Id, Padrao.Dura_Consulta);
            fclose(arquivo_Extra);
    }
}
void Continuar(){
    //Funcao responsavel por mandar o usuario de volta para o menu principal
    printf("\nPressione qualquer tecla para voltar ao Menu Principal\n");
    getchar();
    Menu_Principal();
}
void Horarizar(int a, int b){
    //funcao que define o horario final de uma consulta baseado no inicial
    while (b >= 60){
        b -= 60;
        a += 1;
    }
    while (a >= 24){
        a -= 24;
    }
    A_Horas = a;
    A_Minuto = b;
}
void Limpeza_Composta(){
    //Funcao para limpar a tela sem voltar para o menu
    printf("\nPressione Qualquer Tecla para Continuar...\n");
    getchar();
    CLEAR
}
bool Verificacao_Horas(Horario *Destino){
    //Funcao que verifica se o horario informado pelo usuario esta correto
    int X,H = 1,M = -99,R;
    char C;
    while(1){
        R = scanf("%d:%d%c", &H,&M,&C);
        if (R == 3 && C == '\n'){
            if (H < 0 || H > 23 || M < 0 || M > 59){
                printf("Horario Invalido!!!\n");
                printf("Informe um Horario Valido:\n");
            } else {
                Destino->Hora = H;
                Destino->Minuto = M;
                return true;
            }
        } else {
        //Lógica de cancelamento "0"
        if (R == 1 && H == 0) {
            while ((X = getchar()) != '\n' && X != EOF); //Limpa o Buffer
            Continuar();
        }
        
        printf("Formato incorreto!!!!\n");
        printf("Informe um Horario no formato HH:MM\n");
        while ((X = getchar()) != '\n' && X != EOF); //Limpa o Buffer
        }
    }
}
bool Verificacao_Datas(Data *Destino){
    //funcao que verifica se a data informada pelo usuario esta correta
    int X,D = -1,M,A,R;
    char C;
    while(1){
        R = scanf("%d/%d/%d%c", &D,&M,&A,&C);
        if (R == 4 && C == '\n'){
            if (D < 1 || D > 31 || M < 1 || M > 12 || A < 2025){
                printf("Data Invalida!!!\n");
                printf("Informe uma Data Valida:\n");
            } else {
                Destino->Dia = D;
                Destino->Mes = M;
                Destino->Ano = A;
                return true;
            }
        } else {
        //Lógica de cancelamento "0"
        if (R >= 1 && D == 0){
             while ((X = getchar()) != '\n' && X != EOF); //Limpa o Buffer
            Continuar();
        }

        printf("Formato incorreto!!!!\n");
        printf("Informe uma Data no formato DD/MM/AAAA\n");
        while ((X = getchar()) != '\n' && X != EOF); //Limpa o Buffer
        }
    }
}
int Veri_Int(){
    //funcao que verifica que o usuario informou um inteiro valido
    int Valor, Retorno, X;
    char Char;
    while(1){
        Retorno = scanf("%d%c",&Valor,&Char);
        if (Retorno == 2 && Char == '\n'){
            if (Valor == 0){
                Continuar();
            } else {
                return Valor;
            }
        }
        printf("Valor Invalido!!!!!\n");
        printf("Informe Novamente:\n");
        while ((X = getchar()) != '\n' && X != EOF); //Limpa o Buffer
    }

}
bool Veri_Sobreposicao(Data Data_Nova, Horario Horario_Inicio, Horario Horario_Fim, int Sobreposicao,int Id_Medico){
    //Funcao para ver se ja tem consulta desse medico no dia e no horario e confirmar com a sobreposicao
    for (int i = 0; i<Banco_Consultas.QTDE; i++){
        if (Banco_Consultas.Consultas[i].IDMedico == Id_Medico &&
            Banco_Consultas.Consultas[i].data.Dia == Data_Nova.Dia && Banco_Consultas.Consultas[i].data.Mes == Data_Nova.Mes &&
            Banco_Consultas.Consultas[i].data.Ano == Data_Nova.Ano && Banco_Consultas.Consultas[i].Inicio.Hora == Horario_Inicio.Hora &&
            Banco_Consultas.Consultas[i].Inicio.Minuto == Horario_Inicio.Minuto && Banco_Consultas.Consultas[i].Fim.Hora ==
            Horario_Fim.Hora && Banco_Consultas.Consultas[i].Fim.Minuto == Horario_Fim.Minuto){
                //Se as duas permitem sobreposica
                if(Banco_Consultas.Consultas[i].Info_Extras.Sobreposicao == 1 && Sobreposicao == 1){
                    return true;
                } else {
                    printf("Ja Existe Consulta Marcada para tal data e horario!!!!\n");
                    printf("Uma ou as Duas Consultas nao permite(m) Sobreposicao!!!!\n");
                    Limpeza_Composta();
                    Menu_Consultas();
                }
            }
    }
    return true; // Retorna true se nao houver sobreposicao
}
bool Prioridade(int Id_Medico, Horario *Destino, Data Data_Pri){
    //funcao que "derruba" todas as consultas de um dia para mais tarde se tiver alguma urgente
    int Pos_M = Busca_Medico(Id_Medico) - 1, Linha;
    Horario Ini_Pri, Busca;
    Ini_Pri.Hora = Banco_Medicos.Medicos[Pos_M].Ini_Manha.Hora;
    Ini_Pri.Minuto = Banco_Medicos.Medicos[Pos_M].Ini_Manha.Minuto;
    Destino->Hora = Ini_Pri.Hora;
    Destino->Minuto = Ini_Pri.Minuto;
    Busca.Hora = Ini_Pri.Hora;
    Busca.Minuto = Ini_Pri.Minuto;
    
    for(int i=0;i<Banco_Consultas.QTDE;i++){
        if (Banco_Consultas.Consultas[i].IDMedico == Id_Medico &&
            Banco_Consultas.Consultas[i].data.Dia == Data_Pri.Dia &&
            Banco_Consultas.Consultas[i].data.Mes == Data_Pri.Mes &&
            Banco_Consultas.Consultas[i].data.Ano == Data_Pri.Ano){
                //Horarizar
                Banco_Consultas.Consultas[i].Inicio.Minuto += 30;
                Horarizar(Banco_Consultas.Consultas[i].Inicio.Hora, Banco_Consultas.Consultas[i].Inicio.Minuto);
                Banco_Consultas.Consultas[i].Inicio.Hora = A_Horas;
                Banco_Consultas.Consultas[i].Inicio.Minuto = A_Minuto;
                Horarizar(Banco_Consultas.Consultas[i].Inicio.Hora, Banco_Consultas.Consultas[i].Inicio.Minuto+30);
                Banco_Consultas.Consultas[i].Fim.Hora = A_Horas;
                Banco_Consultas.Consultas[i].Fim.Minuto = A_Minuto;
                //--------------------Mudar no arquivo------------------------
                //Variaveis para a copia e cola
                int iddd,ID_M,ID_P, Stts, pri, sob;
                char Lixo[64];
                Horario Copia_Pri, Copia_Pri3;
                Data Copia_Pri2;
                //Codigo
                Linha = Busca_Consulta(Banco_Consultas.Consultas[i].ID);
                Copia_Consul = fopen("Consultas_Temporarias.txt","w");
                fclose(Copia_Consul);
                Copia_Consul = fopen("Consultas_Temporarias.txt","a");
                arquivo_Consul = fopen("Dados_Consultas.txt","r");
                for(int j = 0;j<Banco_Consultas.QTDE;j++){
                    if ((j+1) == Linha){
                        fgets(Lixo,64,arquivo_Consul);
                        fprintf(Copia_Consul, "%d %d %d %d/%d/%d %d:%d %d:%d %d %d %d\n", Banco_Consultas.Consultas[i].ID, Banco_Consultas.Consultas[i].IDMedico, Banco_Consultas.Consultas[i].IDPaciente, Banco_Consultas.Consultas[i].data.Dia, Banco_Consultas.Consultas[i].data.Mes, Banco_Consultas.Consultas[i].data.Ano, Banco_Consultas.Consultas[i].Inicio.Hora, Banco_Consultas.Consultas[i].Inicio.Minuto, Banco_Consultas.Consultas[i].Fim.Hora, Banco_Consultas.Consultas[i].Fim.Minuto, Banco_Consultas.Consultas[i].Status, Banco_Consultas.Consultas[i].Info_Extras.Urgente, Banco_Consultas.Consultas[i].Info_Extras.Sobreposicao);
                    } else {
                        fscanf(arquivo_Consul, "%d %d %d %d/%d/%d %d:%d %d:%d %d %d %d\n", &iddd, &ID_M, &ID_P, &Copia_Pri2.Dia, &Copia_Pri2.Mes, &Copia_Pri2.Ano, &Copia_Pri.Hora, &Copia_Pri.Minuto, &Copia_Pri3.Hora, &Copia_Pri3.Minuto, &Stts, &pri, &sob);
                        fprintf(Copia_Consul, "%d %d %d %d/%d/%d %d:%d %d:%d %d %d %d\n", iddd, ID_M, ID_P, Copia_Pri2.Dia, Copia_Pri2.Mes, Copia_Pri2.Ano, Copia_Pri.Hora, Copia_Pri.Minuto, Copia_Pri3.Hora, Copia_Pri3.Minuto, Stts, pri, sob);
                    }
                }
                fclose(arquivo_Consul);
                fclose(Copia_Consul);
                remove("Dados_Consultas.txt");
                rename("Consultas_Temporarias.txt", "Dados_Consultas.txt");
                arquivo_Consul = Copia_Consul;
                Copia_Consul = NULL;
        }
    }
    return true;
}
bool Verificacao_HMedico(int ID_Medico, Horario IInicio, Horario FFim){
    //Verifica se o medico trabalha no horario informado
    for(int i = 0; i<Banco_Medicos.QTDE;i++){
        if (Banco_Medicos.Medicos[i].ID == ID_Medico){
            int TIM = (Banco_Medicos.Medicos[i].Ini_Manha.Hora * 60) + Banco_Medicos.Medicos[i].Ini_Manha.Minuto;
            int TFM = (Banco_Medicos.Medicos[i].Fim_Manha.Hora * 60) + Banco_Medicos.Medicos[i].Fim_Manha.Minuto;
            int TIT = (Banco_Medicos.Medicos[i].Ini_Tarde.Hora * 60) + Banco_Medicos.Medicos[i].Ini_Tarde.Minuto;
            int TFT = (Banco_Medicos.Medicos[i].Fim_Tarde.Hora * 60) + Banco_Medicos.Medicos[i].Fim_Tarde.Minuto;
            //
            int Ti =  (IInicio.Hora * 60) + IInicio.Minuto;
            int Tf =  (FFim.Hora * 60) + FFim.Minuto;
            if ( (Ti >= TIM && Ti <= TFM && Tf >= TIM && Tf <= TFM) || (Ti >= TIT && Ti <= TFT && Tf >= TIT && Tf <= TFT) ){
                return true;
            } else {
                printf("O Medico informado nao Trabalha nesse Horario!!!!\n");
                Limpeza_Composta();
                Menu_Consultas();
            }
        }
    }
    return false; // Caso medico nao seja encontrado (embora Busca_Medico deva impedir isso)
}
