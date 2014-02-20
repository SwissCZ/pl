GXX=g++
OPTS=-Wall -pedantic -std=c++11
NAME=pl
BUILD=build
DIST=dist
SRC=src
FILES=formula.o main.o parse.o syntax_exception.o

# Toto je zde pouze kvůli NetBeans, které tento cíl volají.
all: $(NAME)

# Vyčistí pomocné soubory potřebné k sestavení programu.
clean:
	rm -f $(DIST)/$(NAME) $(BUILD)/*.o $(BUILD)/*.o.d

prepare:
	mkdir -p $(BUILD)
	mkdir -p $(DIST)

# Výchozí cíl pro spuštění 'make' bez cíle.
$(NAME): prepare $(FILES)
	cd $(BUILD); $(GXX) $(FILES) -o ../$(DIST)/$(NAME) $(OPTS)

# Univerzální pravidlo pro kompilaci kteréhokoliv zdrojového '*.cpp' souboru.
%.o: $(SRC)/%.cpp
	$(GXX) $(OPTS) -c -MMD -MP -MF $(BUILD)/$@.d $< -o $(BUILD)/$@
