### Variables definitions

PREFIX	= /usr/local
BINDIR	= $(PREFIX)/bin
MANDIR	= $(PREFIX)/man/man1

GXX		= g++
OPTS	= -Wall -pedantic -std=c++11

NAME	= pl
FILES	= configuration.o formula.o hilbert.o main.o parse.o parseException.o proof.o syntaxException.o target.o

BUILD	= build
DOC		= doc
OUT		= out
SRC		= src
TEST	= test

### Primary targets

# Compile the source files
build: .folders $(FILES)
	cd $(BUILD) && $(GXX) $(FILES) -o ../$(OUT)/$(NAME) $(OPTS)

# Remove all outputs
clean:
	rm -rf $(BUILD) $(OUT) $(DOC)

# Create the documentation
doc:
	doxygen
	
# Test the program
test: $(BUILD) .test

# Install the binary and manual page
install: $(BUILD) .binary .manpage

# Uninstall the program
uninstall:
	sudo rm -f $(BINDIR)/$(NAME) $(MANDIR)/$(NAME).1.gz

### Auxiliary targets

# Create output directories
.folders:
	mkdir -p $(BUILD) $(OUT)

# Install the binary file
.binary:
	sudo install -g 0 -o 0 -m 0755 $(OUT)/$(NAME) $(BINDIR)

# Install the manual page
.manpage:
	sudo install -g 0 -o 0 -m 0644 $(NAME).1 $(MANDIR) && sudo gzip -f $(MANDIR)/$(NAME).1

# Perform tests
.test:
	sh test.sh

# Universal *.cpp file compilation rule
%.o: $(SRC)/%.cpp
	$(GXX) $(OPTS) -c -MD -MP $< -o $(BUILD)/$@

# PHONY targets
.PHONY: build clean doc test install uninstall .folders .binary .manpage .test
