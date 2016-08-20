TARGET 		= test
OBJECTS 	= main.o\
			UART.o\
			MCA.o\
			I2C.o\
			utils.o\
			Timer.o\
			ADC.o
CC		= avr-gcc
GCC_CPU		= atmega32
AVRDUDE_CPU	= m32
CCFLAGS		=
PROGRAMMER_TYPE	= avr911
PROGRAMMER_PATH = /dev/tty.SLAB_USBtoUART

program: hex
	avrdude -p $(AVRDUDE_CPU) -c $(PROGRAMMER_TYPE) -P $(PROGRAMMER_PATH) -U flash:w:$(TARGET).hex:i

hex: $(TARGET)
	avr-objcopy -O ihex $(TARGET).elf $(TARGET).hex

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CCFLAGS) -mmcu=$(GCC_CPU) -o $(TARGET).elf $(OBJECTS)

%.o: %.c
	$(CC) $(CCFLAGS) -mmcu=$(GCC_CPU) -c $<

clean:
	-$(RM) $(TARGET) $(OBJECTS) $(TARGET).hex $(TARGET).elf
