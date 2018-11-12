COMPONENT_SUBMODULES := .
COMPONENT_SRCDIRS := . ./src/nmea ./src/parsers
COMPONENT_ADD_INCLUDEDIRS := include ./src/nmea ./src/parsers
PARSER_OBJS := $(addprefix ./src/parsers/,\
		gpgga.o \
		gpgll.o \
		gprmc.o \
		gpgsv.o \
		strptime.o \
	)

COMPONENT_OBJS := $(addprefix ./src/,\
		nmea/nmea.o \
		nmea/parser_static.o \
		parsers/parse.o \
		parsers/strptime.o \
	) \
	$(PARSER_OBJS)

define RENAME_SYMBOLS
	$(OBJCOPY) \
		--redefine-sym init=nmea_$(1)_init \
		--redefine-sym parse=nmea_$(1)_parse \
		--redefine-sym set_default=nmea_$(1)_set_default \
		--redefine-sym allocate_data=nmea_$(1)_allocate_data \
		--redefine-sym free_data=nmea_$(1)_free_data \
		./src/parsers/$(1).o
endef

$(COMPONENT_LIBRARY): | rename_symbols

.PHONY: rename_symbols

rename_symbols: | $(PARSER_OBJS)
	$(call RENAME_SYMBOLS,gpgga)
	$(call RENAME_SYMBOLS,gpgll)
	$(call RENAME_SYMBOLS,gprmc)
	$(call RENAME_SYMBOLS,gpgsv)

CPPFLAGS += -DENABLE_GPGLL=1 -DENABLE_GPGGA=1 -DENABLE_GPRMC=1 -DENABLE_GPGSV=1 -DPARSER_COUNT=4
