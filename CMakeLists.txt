cmake_minimum_required(VERSION 3.10)
project(AgendaJa)
set(CMAKE_C_STANDARD 11)
add_executable(AgendaJa src/Agendamentos.c src/Funcoes_Consultas.c src/Funcoes_Gerais.c src/Funcoes_Medicas.c src/Funcoes_Pacientes.c)