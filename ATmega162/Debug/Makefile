################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../src \
../src/drivers \
../src/communication_drivers


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../../communication_drivers/can.c \
../../communication_drivers/MCP2515.c \
../../communication_drivers/spi.c \
../../communication_drivers/uart.c \
../src/drivers/adc.c \
../src/drivers/send2can.c \
../src/drivers/joystick.c \
../src/drivers/oled.c \
../src/drivers/sram.c \
../src/drivers/timer.c \
../src/drivers/touch_panel.c \
../src/highscore.c \
../src/main.c \
../src/menu.c \
../src/state_option.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
src/communication_drivers/can.o \
src/communication_drivers/MCP2515.o \
src/communication_drivers/spi.o \
src/communication_drivers/uart.o \
src/drivers/adc.o \
src/drivers/send2can.o \
src/drivers/joystick.o \
src/drivers/oled.o \
src/drivers/sram.o \
src/drivers/timer.o \
src/drivers/touch_panel.o \
src/highscore.o \
src/main.o \
src/menu.o \
src/state_option.o

OBJS_AS_ARGS +=  \
src/communication_drivers/can.o \
src/communication_drivers/MCP2515.o \
src/communication_drivers/spi.o \
src/communication_drivers/uart.o \
src/drivers/adc.o \
src/drivers/send2can.o \
src/drivers/joystick.o \
src/drivers/oled.o \
src/drivers/sram.o \
src/drivers/timer.o \
src/drivers/touch_panel.o \
src/highscore.o \
src/main.o \
src/menu.o \
src/state_option.o

C_DEPS +=  \
src/communication_drivers/can.d \
src/communication_drivers/MCP2515.d \
src/communication_drivers/spi.d \
src/communication_drivers/uart.d \
src/drivers/adc.d \
src/drivers/send2can.d \
src/drivers/joystick.d \
src/drivers/oled.d \
src/drivers/sram.d \
src/drivers/timer.d \
src/drivers/touch_panel.d \
src/highscore.d \
src/main.d \
src/menu.d \
src/state_option.d

C_DEPS_AS_ARGS +=  \
src/communication_drivers/can.d \
src/communication_drivers/MCP2515.d \
src/communication_drivers/spi.d \
src/communication_drivers/uart.d \
src/drivers/adc.d \
src/drivers/send2can.d \
src/drivers/joystick.d \
src/drivers/oled.d \
src/drivers/sram.d \
src/drivers/timer.d \
src/drivers/touch_panel.d \
src/highscore.d \
src/main.d \
src/menu.d \
src/state_option.d

OUTPUT_FILE_PATH +=ATmega162.elf

OUTPUT_FILE_PATH_AS_ARGS +=ATmega162.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler































src/communication_drivers/%.o: ../../communication_drivers/%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.8.1
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega162 -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

src/drivers/%.o: ../src/drivers/%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.8.1
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega162 -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

src/%.o: ../src/%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.8.1
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega162 -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 4.8.1
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="ATmega162.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mmcu=atmega162  
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "ATmega162.elf" "ATmega162.hex"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "ATmega162.elf" "ATmega162.eep" || exit 0
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "ATmega162.elf" > "ATmega162.lss"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "ATmega162.elf" "ATmega162.srec"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-size.exe" "ATmega162.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "ATmega162.elf" "ATmega162.a" "ATmega162.hex" "ATmega162.lss" "ATmega162.eep" "ATmega162.map" "ATmega162.srec" "ATmega162.usersignatures"
	