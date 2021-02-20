CC = gcc
LD = ld

CFLAGS  := -fPIC

TARGETS := sig.so int3

# The Directories, Source, Includes, Objects, Binary and Resources
SRCDIR      := src
INCDIR      := inc
BUILDDIR    := obj
#TARGETDIR   := bin
SRCEXT      := c
DEPEXT      := d
OBJEXT      := o

# Flags, Libraries and Includes
CFLAGS      := -Wall -O3 -g
LIB         := -lpthread
INC         := -I$(INCDIR)# -I/usr/local/include

ifneq ($(VERBOSE),y)
HUSH_CC         = @echo ' [CC]\t\t'$@;
HUSH_CC_LD      = @echo ' [CC+LD]\t'$@;
HUSH_LD         = @echo ' [LD]\t\t'$@;
HUSH_AR         = @echo ' [AR]\t\t'$@;
endif

#-----------------------------------------------------------------------------
# Recipes
#-----------------------------------------------------------------------------
SOURCES     := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS     := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))

all: clean $(TARGETS)

$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(HUSH_CC) $(CC) -fPIC $(INC) -c -o $@ $<

sig.so: $(BUILDDIR)/sig.o
	$(HUSH_LD) $(LD) -shared $< -o $@
	@echo $@ ready.

int3: test/int3.c
	$(HUSH_CC_LD) $(CC) -o $@ $<
	@echo $@ ready.

run_int3: sig.so int3
	LD_PRELOAD=./sig.so ./int3 && echo "Exit zero!" || echo "Exit non zero!"

# Clean only Objecst
clean:
	@$(RM) -rf $(BUILDDIR) $(TARGETS)

# Full Clean, Objects and Binaries
#distclean: clean
#	@$(RM) -rf $(TARGETS)

