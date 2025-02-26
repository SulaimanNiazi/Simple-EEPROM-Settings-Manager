# Simple EEPROM Settings Manager

## Project Overview
This project is a firmware embedded systems task's objective is to implement a simple non-volatile settings manager using EEPROM emulation in RAM. The project involves storing and retrieving configuration settings (e.g., brightness level), simulating power-off by clearing RAM, and ensuring settings persist after reset.

## Table of Contents
1. [Project Overview](#project-overview)
2. [Skills Tested](#skills-tested)
3. [Task Details](#task-details)
4. [Files Description](#files-description)
5. [How to Use](#how-to-use)
6. [Prerequisites](#prerequisites)
7. [Building the Project](#building-the-project)
8. [Apparatus](#apparatus)
9. [Uploading to the Microcontroller](#uploading-to-the-microcontroller)
10. [Usage](#usage)
11. [Troubleshooting](#troubleshooting)
12. [Error Handling](#error-handling)
13. [Conclusion](#conclusion)

## Skills Tested
- ✅ EEPROM-like data storage in RAM
- ✅ Memory read/write operations
- ✅ Use of MPLAB X Watch Window for testing
- ✅ Basic error handling (corrupt data detection)

## Task Details
1. **Create a configuration struct** to store user settings (brightness, mode).
2. **Store settings** in EEPROM.
3. **Allow modification of settings** and simulate power reset.
4. **Verify settings** are restored correctly after simulated power-off.

## Files Description
- **main.c**: Contains the main logic for the settings manager.
- **eeprom.c**: Implements EEPROM emulation functions.
- **eeprom.h**: Header file for EEPROM emulation functions.
- **settings.c**: Implements functions to manage settings.
- **settings.h**: Header file for settings management functions.
- **Makefile**: Build script for the project.
- **README.md**: Project documentation.

## How to Use
1. **Build the project** using the provided Makefile.
2. **Run the project** in MPLAB X IDE.
3. **Use the MPLAB X Watch Window** to test and verify the settings manager functionality.
4. **Simulate power-off** by clearing RAM and ensure settings persist after reset.

## Prerequisites

- MPLAB X IDE
- XC8 Compiler
- PIC16F877A Microcontroller

## Building the Project

1. Open the project in MPLAB X IDE.
2. Ensure the XC8 compiler is selected.
3. Build the project to generate the `.hex` or `.cof` file.
4. Alternatively, you can build the project using Visual Studio Code with the MPLAB extension. Set the project output file path, name, and extension using `Ctrl+Shift+P` and selecting "Edit Project Properties".

## Apparatus

Necessary components that can't be changed:

1. PIC16F877A microcontroller: To run the program.
2. Quartz Crystal and 2 1nF non-polarized capacitors.

Optional components depending on your circuit:

1. 3 Buttons
2. 3 BCD 7-segment displays.
3. 3 Resistors.

## Uploading to the Microcontroller

After building the project, upload the generated `.hex` or `.cof` file to the PIC16F877A microcontroller using a suitable programmer. The file can be found in either of the following paths:

1. In case of using MPLAB X IDE: [dist\default\debug\Simple_EEPROM_settings_manager.X.debug.cof](./dist/default/debug/Simple_EEPROM_settings_manager.X.debug.cof)
2. In case of using Visual Studio Code (if the file name was set as default): **out\PIC_Clock\default.hex**

## Usage

1. Connect the microcontroller and the necessary components as per the [circuit diagram](./Proteus%20Simulation/).
2. Power on the system.

## Troubleshooting

- Ensure all connections are secure and correct.
- Verify the microcontroller is programmed with the correct `.hex` or `.cof` file.
- Check the power supply to the microcontroller and other components.

## Error Handling
The project includes basic error handling to detect and manage corrupt data in the EEPROM.

## Conclusion
This project demonstrates the implementation of a simple non-volatile settings manager using EEPROM emulation in RAM, with a focus on memory management, data persistence, and error handling.