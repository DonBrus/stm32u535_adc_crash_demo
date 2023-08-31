defines?=
defines+= \
-DSTM32U535xx \
$(include_dirs) \

arch_options := \
-mcpu=cortex-m33 \
-mthumb \
-mfpu=fpv5-sp-d16 -mfloat-abi=hard


warnings :=	\
-Wall \

f_flags := \
-fsigned-char \
-ffunction-sections \
-fdata-sections \

f_flags_cpp := \
-fno-rtti \
-fno-exceptions \

compile_options_c := \
-std=c11 \

compile_options_asm := \
-x assembler-with-cpp \

compile_options_cpp := \
-std=c++14 \

linker_options := \
-T "linker.ld" \
-Xlinker --gc-sections \
-Wl,-Map,"$(build_dir)/main.map"

compile_flags_common:= \
$(arch_options) \
$(fpu_options) \
$(warnings) \
$(f_flags) \
$(defines) \
-Os -g

compile_flags_cpp := \
$(compile_flags_common) \
$(compile_options_cpp) \
$(f_flags_cpp)

compile_flags_c := \
$(compile_flags_common) \
$(compile_options_c) \

compile_flags_asm := \
$(compile_flags_common) \
$(compile_options_asm) \

linker_flags :=	\
$(arch_options) \
$(linker_options) \
--specs=nano.specs
