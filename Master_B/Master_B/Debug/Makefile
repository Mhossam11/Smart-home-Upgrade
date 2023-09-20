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

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../DIO_driver.c \
../EEPROM_driver.c \
../EXT._Interrupt.c \
../LCD_driver.c \
../LED_driver.c \
../Master_B.c \
../Show_Menu.c \
../SPI_driver.c \
../Timer_driver.c \
../UART_driver.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
DIO_driver.o \
EEPROM_driver.o \
EXT._Interrupt.o \
LCD_driver.o \
LED_driver.o \
Master_B.o \
Show_Menu.o \
SPI_driver.o \
Timer_driver.o \
UART_driver.o


OBJS_AS_ARGS +=  \
DIO_driver.o \
EEPROM_driver.o \
EXT._Interrupt.o \
LCD_driver.o \
LED_driver.o \
Master_B.o \
Show_Menu.o \
SPI_driver.o \
Timer_driver.o \
UART_driver.o


C_DEPS +=  \
DIO_driver.d \
EEPROM_driver.d \
EXT._Interrupt.d \
LCD_driver.d \
LED_driver.d \
Master_B.d \
Show_Menu.d \
SPI_driver.d \
Timer_driver.d \
UART_driver.d


C_DEPS_AS_ARGS +=  \
DIO_driver.d \
EEPROM_driver.d \
EXT._Interrupt.d \
LCD_driver.d \
LED_driver.d \
Master_B.d \
Show_Menu.d \
SPI_driver.d \
Timer_driver.d \
UART_driver.d


OUTPUT_FILE_PATH +=Master_B.elf

OUTPUT_FILE_PATH_AS_ARGS +=Master_B.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

# AVR32/GNU C Compiler





















./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : (AVR_8_bit_GNU_Toolchain_3.4.1_830) 4.6.2
	$(QUOTE)C:\Users\20100\Downloads\atmel setup_mtgesh gmbo\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-gcc.exe$(QUOTE) -funsigned-char -funsigned-bitfields -O1 -fpack-struct -fshort-enums -g2 -Wall -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"  -mmcu=atmega32   -o"$@" "$<" 
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

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : (AVR_8_bit_GNU_Toolchain_3.4.1_830) 4.6.2
	$(QUOTE)C:\Users\20100\Downloads\atmel setup_mtgesh gmbo\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="Master_B.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group  -mmcu=atmega32  
	@echo Finished building target: $@
	"C:\Users\20100\Downloads\atmel setup_mtgesh gmbo\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature  "Master_B.elf" "Master_B.hex"
	"C:\Users\20100\Downloads\atmel setup_mtgesh gmbo\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "Master_B.elf" "Master_B.eep" || exit 0
	"C:\Users\20100\Downloads\atmel setup_mtgesh gmbo\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-objdump.exe" -h -S "Master_B.elf" > "Master_B.lss"
	"C:\Users\20100\Downloads\atmel setup_mtgesh gmbo\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature  "Master_B.elf" "Master_B.srec"
	"C:\Users\20100\Downloads\atmel setup_mtgesh gmbo\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-size.exe" "Master_B.elf"
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS)$(C_DEPS_AS_ARGS) $(EXECUTABLES) 
	rm -rf "Master_B.elf" "Master_B.a" "Master_B.hex" "Master_B.lss" "Master_B.eep" "Master_B.map" "Master_B.srec"
	