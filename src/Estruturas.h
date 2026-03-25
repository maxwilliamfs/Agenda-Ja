#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

//Bibbliotecas Necessarias
#include <stdlib.h>  //Para utilizar scanf e printf
#include <stdio.h> //Para fazer a alocacao de memoria dinamica
#include <string.h> //Para fazer operacoes com strings
#include <stdbool.h> //Para utilizar variaveis boleanas
#include <time.h> //Para fazer a agenda dos medicos

//Pre-Processamento
#define CLEAR system("clear");

//Variaveis e Ponteiros globais
extern int Id, *inter;
extern bool Aumentando;
extern bool Aumentando2;
extern bool Aumentando3;
extern int A_Horas, A_Minuto;

//Ponteiros FILE
extern FILE *arquivo_Geral; //Ponteiro que aponta para o arquivo com as quantidades e capacidades de medicos, pacientes e consultas
extern FILE *arquivo_Extra; //Ponteiro com informacoes extras
extern FILE *arquivo_Paci; //Ponteiro que apontara para o arquivo com os pacientes do programa
extern FILE *Copia_Paci; //Ponteiro que aponta para o arquivos temporaria de pacientes
extern FILE *arquivo_Consul; //Ponteiro que apontara para o arquivo com as consultas do programa
extern FILE *Copia_Consul; //Ponteiro que aponta para o arquivo temporario das consultas
extern FILE *Copia_Med; // Ponteiro que aponta para o arquivo temporario feito para remover o editar um medico
extern FILE *arquivo_Med; //Ponteiro que apontara para o arquivo com os medicos do programa


//ENUNS
typedef enum{
    Horas, Datas
} VerificacaoE;
extern VerificacaoE Parametro2;

typedef enum{
    Consulta,Medico,Paciente,Atualizacao_Capacidade,MedicoR,PacienteR,ConsultaR, Tempo_Padrao
} Informacao;
extern Informacao Parametro;

typedef enum{
    Especiali_Clinico, Especiali_Pediatra, Especiali_Dermato, Especiali_Cardio, Especiali_Outra
} Especialidade;

typedef enum{
    Consul_Agendada, Consul_Falta, Consul_Concluida, Consul_Cancelada,
} Status_Consulta;

//STRUCTS
typedef struct{
    int Dia,Mes,Ano;
} Data;

typedef struct{
    int Hora,Minuto;
} Horario;

typedef struct{
    int Dura_Consulta;
    int Sobreposicao;
    int Urgente;
} Politica_Agen;
extern Politica_Agen Padrao;

typedef struct{
    int ID;
    char Nome[64];
    Horario Ini_Manha,Fim_Manha,Ini_Tarde,Fim_Tarde;
    Especialidade especialidade;
} MedicoP;

typedef struct{
    int ID;
    char Nome[64];
    char Contato[64];
} PacienteP;

typedef struct{
    int ID,IDMedico,IDPaciente;
    Data data;
    Horario Inicio;
    Horario Fim;
    Status_Consulta Status;
    Politica_Agen Info_Extras;
} ConsultaP;

typedef struct{
    MedicoP *Medicos;
    int QTDE, Cap;
} PontMedicos;
extern PontMedicos Banco_Medicos;

typedef struct{
    PacienteP *Pacientes;
    int QTDE, Cap;
} PontPacientes;
extern PontPacientes Banco_Pacientes;

typedef struct{
    ConsultaP *Consultas;
    int QTDE,Cap;
} PontConsultas;
extern PontConsultas Banco_Consultas;

#endif // ESTRUTURAS_H
