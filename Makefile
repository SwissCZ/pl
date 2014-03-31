#############
# Variables #
#############

PREFIX	= /usr/local
BINDIR	= $(PREFIX)/bin
MANDIR	= $(PREFIX)/man/man1

GXX		= g++
OPTS	= -Wall -pedantic -std=c++11

NAME	= pl
FILES	= configuration.o target.o formula.o hilbert.o main.o parseException.o parse.o provability.o syntaxException.o

BUILD	= build
DIST	= output
DOC		= documentation
SRC		= source

###################
# Primary targets #
###################

# Compile the source files
build: .folders $(FILES)
	cd $(BUILD); $(GXX) $(FILES) -o ../$(DIST)/$(NAME) $(OPTS)

# Remove all outputs
clean:
	rm -fr $(BUILD) $(DIST) $(DOC)

# Create the documentation
doc:
	doxygen

# Install the program
install: build .binary .manpage

# Uninstall the program
uninstall:
	rm -f $(BINDIR)/$(NAME) $(MANDIR)/$(NAME).1.gz

#####################
# Auxiliary targets #
#####################

# Install the binary
.binary:
	install -g 0 -o 0 -m 0755 $(DIST)/$(NAME) $(BINDIR);

# Create output directories
.folders:
	mkdir -p $(BUILD) $(DIST)

# Install the manual page
.manpage:
	install -g 0 -o 0 -m 0644 $(NAME).1 $(MANDIR) && gzip -f $(MANDIR)/$(NAME).1

# Universal *.cpp file compilation rule
%.o: $(SRC)/%.cpp
	$(GXX) $(OPTS) -c -MMD -MP -MF $(BUILD)/$@.d $< -o $(BUILD)/$@

.PHONY: build all clean doc install uninstall .binary .folders .manpage
