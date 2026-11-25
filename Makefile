PROGRAM  := d_led_test
PORT     := /dev/ttyACM0

BUILD_DIR := Build
CC        := avr-gcc
CPP       := avr-g++
OBJCOPY   := avr-objcopy
MMCU      := -mmcu=atmega328p

# Sources des drivers uniquement
DRIVER_C_SRCS   := $(shell find drivers -type f -name '*.c' 2>/dev/null)
DRIVER_CPP_SRCS := $(shell find drivers -type f -name '*.cpp' 2>/dev/null)

DRIVER_C_OBJS   := $(patsubst %.c,$(BUILD_DIR)/%.c.o,$(DRIVER_C_SRCS))
DRIVER_CPP_OBJS := $(patsubst %.cpp,$(BUILD_DIR)/%.cpp.o,$(DRIVER_CPP_SRCS))
DRIVER_OBJS     := $(DRIVER_C_OBJS) $(DRIVER_CPP_OBJS)

# Détection automatique des dossiers contenant des en-têtes (.h)
INC_DIRS := . $(sort $(dir $(shell find drivers test -type f -name '*.h' 2>/dev/null)))
INCLUDES := $(addprefix -I,$(INC_DIRS))

CFLAGS   := -Os -g -Wall -Wextra -std=gnu11 -ffunction-sections -fdata-sections -MMD -MP -flto ${MMCU} -DF_CPU=16000000L
CPPFLAGS := -Os -g -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -MP -flto ${MMCU} -DF_CPU=16000000L
LDFLAGS  := -Os -g -flto -fuse-linker-plugin -Wl,--gc-sections ${MMCU}

# Liste des cibles de test disponibles (ex: test/testx.c -> testx)
TEST_NAMES := $(basename $(notdir $(shell find test -maxdepth 1 -type f \( -name '*.c' -o -name '*.cpp' \) 2>/dev/null)))

.PHONY: all drivers upload clean $(TEST_NAMES)

# Compile uniquement tous les objets des drivers
drivers: ${DRIVER_OBJS}

# Cible générique pour compiler un seul test : ex. `make testx` ou `make d_led_test`
$(TEST_NAMES): %: ${BUILD_DIR}/test/%.hex

# Résolution automatique du fichier source de test (.c ou .cpp)
define TEST_RULE
ifneq (,$(wildcard test/$(1).c))
${BUILD_DIR}/test/$(1).elf: ${DRIVER_OBJS} ${BUILD_DIR}/test/$(1).c.o
	@mkdir -p $$(dir $$@)
	${CPP} ${LDFLAGS} $$^ -o $$@
else ifneq (,$(wildcard test/$(1).cpp))
${BUILD_DIR}/test/$(1).elf: ${DRIVER_OBJS} ${BUILD_DIR}/test/$(1).cpp.o
	@mkdir -p $$(dir $$@)
	${CPP} ${LDFLAGS} $$^ -o $$@
endif
endef

$(foreach t,$(TEST_NAMES),$(eval $(call TEST_RULE,$(t))))

${BUILD_DIR}/%.c.o: %.c
	@mkdir -p $(dir $@)
	${CC} -c ${CFLAGS} ${INCLUDES} $< -o $@

${BUILD_DIR}/%.cpp.o: %.cpp
	@mkdir -p $(dir $@)
	${CPP} -c ${CPPFLAGS} ${INCLUDES} $< -o $@

${BUILD_DIR}/%.hex: ${BUILD_DIR}/%.elf
	${OBJCOPY} -O ihex -R .eeprom $< $@

all: ${BUILD_DIR}/test/${PROGRAM}.hex

# Téléverse le test demandé (`make upload PROG=testx`) ou ${PROGRAM} par défaut
PROG ?= ${PROGRAM}
upload: ${BUILD_DIR}/test/${PROG}.hex
	avrdude -F -V -c arduino -p ATMEGA328P -P ${PORT} -b 115200 -U flash:w:$<

clean:
	rm -rf ${BUILD_DIR}

ALL_DEPS := $(DRIVER_OBJS:.o=.d) $(patsubst %,${BUILD_DIR}/test/%.c.d,$(TEST_NAMES)) $(patsubst %,${BUILD_DIR}/test/%.cpp.d,$(TEST_NAMES))
-include $(wildcard $(ALL_DEPS))