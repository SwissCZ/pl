# Variables definition
GXX=g++
OPTS=-Wall -pedantic -g -std=c++11
NAME=pl
BUILD=build
DIST=dist
SRC=src
FILES=formula.o main.o parse.o parse_exception.o settings.o syntax_exception.o

# NetBeans workaround
all: $(NAME)

# Build files cleanup
clean:
	rm -f $(DIST)/$(NAME) $(BUILD)/*.o $(BUILD)/*.o.d
	rm -rf doc

doc: doxygen Doxyfile

prepare:
	mkdir -p $(BUILD)
	mkdir -p $(DIST)

# Default make target
$(NAME): prepare $(FILES)
	cd $(BUILD); $(GXX) $(FILES) -o ../$(DIST)/$(NAME) $(OPTS)

# Universal *.cpp file compilation rule
%.o: $(SRC)/%.cpp
	$(GXX) $(OPTS) -c -MMD -MP -MF $(BUILD)/$@.d $< -o $(BUILD)/$@
