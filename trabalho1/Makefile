SOURCES = main.c registro.c
HEADERS = registro.h
FLAGS = -Wall
PROGRAMA = programaTrab1

all: $(PROGRAMA)

$(PROGRAMA): $(SOURCES) $(HEADERS)
	@gcc $(FLAGS) $(SOURCES) -o $(PROGRAMA)

clean:
	@rm -rf *.o *~

run:
	./$(PROGRAMA)
