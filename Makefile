all:
	gcc Agendamentos.c Funcoes_Consultas.c Funcoes_Gerais.c Funcoes_Medicas.c Funcoes_Pacientes.c -o AgendaJa

run:
	./AgendaJa

clean:
	rm AgendaJa