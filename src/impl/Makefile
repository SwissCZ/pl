### Variables definitions

PREFIX	= /usr/local
BINDIR	= $(PREFIX)/bin
MANDIR	= $(PREFIX)/man/man1

GXX		= g++
OPTS	= -Wall -pedantic -std=c++11

BUILD	= build
DOC		= doc
OUT		= out
SRC		= src

NAME	= pl
FILES	:= $(patsubst $(SRC)/%.cpp, $(BUILD)/%.o, $(wildcard $(SRC)/*.cpp))

### Primary targets

# Compile the source files
build: .folders $(FILES)
	$(GXX) $(OPTS) $(FILES) -o $(OUT)/$(NAME)

# Remove all outputs
clean:
	rm -rf $(BUILD) $(OUT) $(DOC)

# Create the documentation
doc:
	doxygen
	
# Build and test the program
test: $(BUILD) .test

# Build and install the program
install: $(BUILD) .install

# Uninstall the program
uninstall:
	sudo rm -f $(BINDIR)/$(NAME) $(MANDIR)/$(NAME).1.gz

### Auxiliary targets

# Create output directories
.folders:
	mkdir -p $(BUILD) $(OUT)

# Install the binary and manual page
.install:
	sudo install -g 0 -o 0 -m 0755 $(OUT)/$(NAME) $(BINDIR)
	sudo install -g 0 -o 0 -m 0644 $(NAME).1 $(MANDIR) && sudo gzip -f $(MANDIR)/$(NAME).1

# Run the test script
.test:
	sh test.sh

# Universal *.cpp file compilation rule
$(BUILD)/%.o: $(SRC)/%.cpp
	$(GXX) $(OPTS) -c -MD -MP $< -o $@

# PHONY targets
.PHONY: build clean doc test install uninstall .folders .install .test
