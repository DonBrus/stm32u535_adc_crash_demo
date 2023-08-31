toolchain_prefix:=arm-none-eabi

CC := $(toolchain_prefix)-gcc
GPP := $(toolchain_prefix)-g++
AS := $(toolchain_prefix)-as
BIN2ELF := $(toolchain_prefix)-objdump
OBJCPY := $(toolchain_prefix)-objcopy
SIZE :=  $(toolchain_prefix)-size

processor := cortex-m33

build_dir := build

include sources.mk
include includes.mk
include options.mk

OBJS := $(sources:%=$(build_dir)/%.o)
DEP := $(sources:%=$(build_dir)/%.d)
-include $(DEP)

.PHONY: clean

all: $(build_dir)/main.elf

clean:
	rm -rf $(build_dir)


$(build_dir)/main.elf: $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM Cross C Linker'
	@$(GPP) $(OBJS) $(linker_flags) -o "$(build_dir)/main.elf"
	@echo 'Finished building target: $@'
	@$(SIZE) $(build_dir)/main.elf


#####################################################
# Objects
#####################################################

$(build_dir)/%.cpp.o: %.cpp
	@mkdir -p $(@D)
	@echo 'Building file: $<'
	@$(GPP) $(compile_flags_cpp) -MMD -MP -c -o "$@" "$<"
	@echo 'Created file: $@'
	$(printSeparator)
	
$(build_dir)/%.c.o: %.c
	@mkdir -p $(@D)
	@echo 'Building file: $<'
	@$(CC) $(compile_flags_c) -MMD -MP -c -o "$@" "$<"
	@echo 'Created file: $@'
	$(printSeparator)

$(build_dir)/%.sx.o: %.sx
	@mkdir -p $(@D)
	@echo 'Building file: $<'
	@$(CC) $(compile_flags_asm) -MMD -MP -c -o "$@" "$<"
	@echo 'Created file: $@'
	$(printSeparator)
	
$(build_dir)/%.S.o: %.S
	@mkdir -p $(@D)
	@echo 'Building file: $<'
	@echo '.S With preprocessor'
	@$(CC) $(compile_flags_asm) -MMD -MP -c -o "$@" "$<"
	@echo 'Created file: $@'
	$(printSeparator)
	
$(build_dir)/%.s.o: %.s
	@mkdir -p $(@D)
	@echo 'Building file: $<'
	@echo '.s Pure assembly'
	@$(CC) $(compile_flags_asm) -MMD -MP -c -o "$@" "$<"
	@echo 'Created file: $@'
	$(printSeparator)
	
