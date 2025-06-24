# Makefile para o trabalho II (Cuckoo Hash) de Algoritmos e Estruturas de Dados III
# Leonardo Kreusch GRR20245579 - Bacharelado em Ciencia da Computacao - UFPR
# Ultima modificacao em 21/06/2025

# Baseado no Makefile desenvolvido pelo Professor Dr. Carlos Maziero - DINF/UFPR
# Original disponivel em https://wiki.inf.ufpr.br/maziero/doku.php?id=c:theboys-2024-2 , mas nao adequado a este projeto

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -g -std=c99
LDLIBS  = -lm
MAIN    = myht
ENTREGA = lk24

# Lista de arquivos de cabecalho
HDR     = hash_table.h

# Lista de arquivos-objeto 
OBJ     = hash_table.o

# Regras de compilacao

# Construir o executavel principal
$(MAIN): $(MAIN).o $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

# Construir o arquivo principal
$(MAIN).o: $(MAIN).c $(HDR)

# Construir os TADs
hash_table.o: hash_table.c hash_table.h
	$(CC) $(CFLAGS) -c $<

# Regras adicionais

# Executar o programa
run: $(MAIN)
	./$(MAIN)

# Testar no Valgrind
valgrind: $(MAIN)
	valgrind --leak-check=full --track-origins=yes ./$(MAIN)

# Gerar arquivo TGZ para entrega
tgz: clean
	@mkdir -p /tmp/$(USER)/$(ENTREGA)
	@chmod 0700 /tmp/$(USER)/$(ENTREGA)
	cp *.c *.h Makefile /tmp/$(USER)/$(ENTREGA)
	cp $(ENTREGA).pdf /tmp/$(USER)/$(ENTREGA)
	tar czvf $(ENTREGA).tgz -C /tmp/$(USER) $(ENTREGA)
	rm -rf /tmp/$(USER)
	@echo "Arquivo $(ENTREGA).tgz criado para entrega"

targz: clean
	@mkdir -p /tmp/$(USER)/$(ENTREGA)
	@chmod 0700 /tmp/$(USER)/$(ENTREGA)
	cp *.c *.h Makefile /tmp/$(USER)/$(ENTREGA)
	cp $(ENTREGA).pdf /tmp/$(USER)/$(ENTREGA)
	tar czvf $(ENTREGA).tar.gz -C /tmp/$(USER) $(ENTREGA)
	rm -rf /tmp/$(USER)
	@echo "Arquivo $(ENTREGA).tar.gz criado para entrega"

# Limpar arquivos temporarios
clean:
	rm -f *~ $(OBJ) $(MAIN).o $(MAIN) $(ENTREGA).tgz $(ENTREGA).tar.gz


TESTS := 1 2 3 4

.PHONY: test_all
test_all: $(addprefix test_, $(TESTS))

# Pretty test rule
test_%: myht
	@echo ""
	@echo "====================[ TEST $* ]===================="
	@echo ""
	@./myht < tests/teste$*.in > a$*.try
	@diff -u a$*.try tests/teste$*.out || \
		(echo ""; echo "❌ Test $* FAILED!"; echo "")
	@echo ""
	@echo "✅ Test $* PASSED!"
	@echo "===================================================="
	@echo ""
