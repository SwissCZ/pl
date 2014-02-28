########################
# Variables definition #
########################

GXX=g++
OPTS=-Wall -pedantic -g -std=c++11
NAME=pl
BUILD=build
DIST=dist
DOC=doc
SRC=src
FILES=formula.o main.o parse.o parse_exception.o settings.o syntax_exception.o

################
# User targets #
################

# Build the program
build: .build_pre $(FILES)
	cd $(BUILD); $(GXX) $(FILES) -o ../$(DIST)/$(NAME) $(OPTS)

# Build the program and create the documentation
all: build doc

# Remove the build files
clean:
	rm -rf $(BUILD) $(DIST)

# Create doxygen documentation
doc:
	mkdir $(DOC)
	doxygen Doxyfile

# Install the program
install: build .site clean

# Uninstall the program
uninstall:
	sudo sh -c "rm -f /bin/pl /usr/share/man/man1/$(NAME).1.gz"

######################
# Supporting targets #
######################

# Create required folders
.build_pre:
	mkdir -p $(BUILD) $(DIST)

# Site the installation files
.site:
	sudo sh -c "gzip $(NAME).1; mv $(DIST)/$(NAME) /bin; mv $(NAME).1.gz /usr/share/man/man1"

# Universal *.cpp file compilation rule
%.o: $(SRC)/%.cpp
	$(GXX) $(OPTS) -c -MMD -MP -MF $(BUILD)/$@.d $< -o $(BUILD)/$@
