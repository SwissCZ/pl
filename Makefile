#############
# Variables #
#############

PREFIX	= /usr/local
BINDIR	= $(PREFIX)/bin
MANDIR	= $(PREFIX)/man/man1

GXX		= g++
OPTS	= -Wall -pedantic -std=c++11

NAME	= pl
FILES	= executionTarget.o hilbertSystem.o main.o parseException.o parseFunctions.o programConfiguration.o propositionalFormula.o syntaxException.o

###################
# Primary targets #
###################

# Compile the source files
build: .folders $(FILES)
	cd build; $(GXX) $(FILES) -o ../output/$(NAME) $(OPTS)

# Remove all outputs
clean:
	rm -fr build output documentation
	rm -f test/*_test.txt

# Create the documentation
doc:
	doxygen

# Install the program
install: build .binary .manpage

# Test the program
test: build .test

# Uninstall the program
uninstall:
	rm -f $(BINDIR)/$(NAME) $(MANDIR)/$(NAME).1.gz

#####################
# Auxiliary targets #
#####################

# Install the binary
.binary:
	install -g 0 -o 0 -m 0755 output/$(NAME) $(BINDIR);

# Create output directories
.folders:
	mkdir -p build output

# Install the manual page
.manpage:
	install -g 0 -o 0 -m 0644 $(NAME).1 $(MANDIR) && gzip -f $(MANDIR)/$(NAME).1

# Perform tests
.test:
	./test.sh

# Universal *.cpp file compilation rule
%.o: source/%.cpp
	$(GXX) $(OPTS) -c -MMD -MP -MF build/$@.d $< -o build/$@

.PHONY: build all clean doc install test uninstall .binary .folders .manpage .test
