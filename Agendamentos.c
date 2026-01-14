//Bibbliotecas Necessarias
#include "Estruturas.h" // Arquivo.h com as estruturas e enuns do programa
#include "Funcoes_Gerais.h" // Arquivo.h com as funcoes principais do programa
#include "Funcoes_Medicas.h" // Arquivo.h com as funcoes dos medicos do programa
#include "Funcoes_Pacientes.h" //Arquivo.h com as funcoes dos Pacientes do programa
#include "Funcoes_Consultas.h" //Arquivo.h com as funcoes das Consultas do programa

//Funcao Main
//Arquivo .c que eh a base do sistema, quem liga todas as bibliotecas e todas funcoes
int main(){
    Inicialzar();
    Menu_Principal();
    return 0;
}
