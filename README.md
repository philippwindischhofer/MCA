# MCA
Firmware of the DSP of a multichannel analyzer for gamma spectroscopy. Schematics and detailled informations can be found at <https://am241.wordpress.com/2014/11/01/gamma-spectroscopy-for-the-practical-man/>.

./dspic ... source files for the DSPIC digital signal processor contained in the MCA. To be built with the MPLAB IDE.

./mega32 ... example project for an ATMega32 controlling the MCA via I2C, listening for high-level commands via UART. MCA functionality is implemented by MCA.c / MCA.h.
