# Makefile para o trabalho I (Arvore Red-Black) de Algoritmos e Estruturas de Dados III
# Leonardo Kreusch GRR20245579 - Bacharelado em Ciencia da Computacao - UFPR
# Ultima modificacao em 20/04/2025

# Baseado no Makefile desenvolvido pelo Professor Dr. Carlos Maziero - DINF/UFPR
# Original disponivel em https://wiki.inf.ufpr.br/maziero/doku.php?id=c:theboys-2024-2 , mas nao adequado a este projeto

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -g -std=c99
LDLIBS  = -lm
MAIN    = myrb
ENTREGA = lk24

# Lista de arquivos de cabeçalho
HDR     = rb_tree.h

# Lista de arquivos-objeto 
OBJ     = rb_tree.o

# Regras de compilação

# Construir o executável principal
$(MAIN): $(MAIN).o $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

# Construir o arquivo principal
$(MAIN).o: $(MAIN).c $(HDR)

# Construir os TADs
rb_tree.o: rb_tree.c rb_tree.h
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
