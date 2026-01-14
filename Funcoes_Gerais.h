#ifndef FUNCOES_GERAIS_H
#define FUNCOES_GERAIS_H

#include "Estruturas.h"

//Prototipos de funcoes
int Menu_Principal();
void Continuar();
void Horarizar(int a, int b);
void Menu_Consultas();
void Menu_Medicos();
void Menu_Pacientes();
void Menu_Extra();
bool Veri_Sobreposicao(Data Data_Nova, Horario Horario_Inicio, Horario Horario_Fim, int Sobreposicao,int Id_Medico);
void Inicialzar();
void Leitura();
void Aumentar_ID();
bool Verificacao_Horas(Horario *Destino);
bool Verificacao_Datas(Data *Destino);
int Veri_Int();
bool Verificacao_HMedico(int ID_Medico, Horario IInicio, Horario FFim);
void Atualizacao_Geral(Informacao FParametro);
void Limpeza_Composta();
bool Prioridade(int Id_Medico, Horario *Destino, Data Data_Pri);

//Prototipos de outros modulos (necessarios para os menus)
void Agendar_Consul();
void Lista_Consultas();
void Atua_Consulta();
void Cadas_Medico();
void Listar_Medicos();
void Atua_Medico();
void Remo_Medico();
void Agenda_Medico();
void Cadas_Paciente();
void Listar_Pacientes();
void Atua_Paciente();
void Remo_Paciente();


#endif // FUNCOES_GERAIS_H
