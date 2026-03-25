all:
	gcc src/Agendamentos.c src/Funcoes_Consultas.c src/Funcoes_Gerais.c src/Funcoes_Medicas.c src/Funcoes_Pacientes.c -o AgendaJa

run:
	./AgendaJa

clean:
	rm AgendaJa