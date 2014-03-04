########################
# Variables definition #
########################

PREFIX=/usr/local
BINDIR=$(PREFIX)/bin
MANDIR=$(PREFIX)/man/man1
GXX=g++
OPTS=-Wall -pedantic -std=c++11
NAME=pl
BUILD=build
DIST=dist
DOC=doc
SRC=src
FILES=configuration.o formula.o main.o parse.o parse_exception.o syntax_exception.o

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
	rm -f $(BINDIR) $(MANDIR)/$(NAME).1.gz

######################
# Supporting targets #
######################

# Create required folders
.build_pre:
	mkdir -p $(BUILD) $(DIST)

# Site the installation files
.site:
	gzip $(NAME).1; mv $(DIST)/$(NAME) $(BINDIR); mv $(NAME).1.gz $(MANDIR)

# Universal *.cpp file compilation rule
%.o: $(SRC)/%.cpp
	$(GXX) $(OPTS) -c -MMD -MP -MF $(BUILD)/$@.d $< -o $(BUILD)/$@
