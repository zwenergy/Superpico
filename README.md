# Superpico
A Raspberry Pi Pico-based Supervision Flash Cart

This is an RP2040-based flash cartridge for the Watara Supervision handheld.
The RP2040 acts as the ROM chip of the cart.
The cartridge can hold one game at a time.

## Software Side
In order to load a game onto the cartridge, you first have a "convert" a ROM to a UF2 file.

**Requirements:**
1. Python
2. CMake
3. RP2040 C SDK installed and paths set up

### Single ROM
Steps:

1. Use the bin2c.py script to convert a ROM file to a C-array. Usage: `bin2c.py ROMFILE rom.h`. Place the genereated `rom.h` file in the root of code directory, beside main.c.
2. Run `make` in the code directory.
3. Connect the Raspberry Pi Pico to the computer while holding down the BOOTSEL button.
4. Drag and drop the newly generated .uf2 file onto the Pico.

### Batch Conversion
You can convert several ROMs at once by using the `batch.py` script.
Steps:

1. Place the (extracted) ROMs into the batch/ROM folder.
2. Run the `batch.py` script.
3. After a short time, the generated .uf2 files should be in the uf2 folder.

## Hardware Side
### BOM
| Component | Amount | 
|-----------|--------|
|Raspberry Pi Pico | 1 |
|74LVC245AT20 | 3 |

### PCB
The PCB can be ordered using the Gerber files. A width of **1.0 mm or 1.2 mm** should be chosen with ENIG surface.
