#include "Machine.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

Machine::Machine() : cpu(memory) {
    
    memory.attachOutputDevice(screen);
}

bool isValidInstruction(int instr) {
    int opcode = (instr >> 12) & 0xF;

    if (opcode < 1 || opcode > 0xC) {
        return false;
    }

    if (opcode == 0x4 && (((instr >> 8) & 0xF) != 0)) {
        return false;
    }

    if (opcode == 0xA && (((instr >> 4) & 0xF) != 0)) {
        return false;
    }

    if (opcode == 0xC && ((instr & 0xFFF) != 0)) {
        return false;
    }

    return true;
}

bool Machine::loadProgram(const std::string& filePath, uint8_t startAddress) {
    
    std::ifstream file(filePath);
    if (!file.is_open()) {
        return false;
    }
    
    std::vector<uint8_t> bytes;

    std::string line;
    while (std::getline(file, line)) {
        size_t firstNonSpace = line.find_first_not_of(" \t\r\n");

        if (firstNonSpace == std::string::npos || line[firstNonSpace] == ';') {
            continue;
        }

        if (line.length() - firstNonSpace < 4) {
            file.close();
            return false;
        }

        std::string hexStr = line.substr(firstNonSpace, 4);

        for (char c : hexStr) {
            if (!isxdigit(static_cast<unsigned char>(c))) {
                file.close();
                return false;
            }
        }

        int instructionVal = std::stoi(hexStr, nullptr, 16);

        if (!isValidInstruction(instructionVal)) {
            file.close();
            return false;
        }

        uint8_t highByte = static_cast<uint8_t>((instructionVal >> 8) & 0xFF);
        uint8_t lowByte  = static_cast<uint8_t>(instructionVal & 0xFF);

        bytes.push_back(highByte);
        bytes.push_back(lowByte);
    }

    file.close();

    if (bytes.empty()) {
        return false;
    }
    if (static_cast<int>(startAddress) + static_cast<int>(bytes.size()) > 0xFF) {
        return false;
    }

    return memory.loadProgram(bytes, startAddress);
}

void Machine::run() {
    while (!cpu.isHalted()) {
        step();
    }
    cout << "\nProgram execution halted successfully.\n";
}

void Machine::step() {
    cpu.step();
}

void Machine::reset() {
    cpu.reset();
    memory.reset();
    screen.clear();
}

CPU& Machine::getCPU() {
    return cpu;
}

Memory& Machine::getMemory() {
    return memory;
}

Screen& Machine::getScreen() {
    return screen;
}

void Machine::startUI() {
    int choice;
    string filename;
    int startAddr;

    do {
        cout << "\n================ Vole Machine Simulator ================\n";
        cout << "1. Load Program from File" << endl;
        cout << "2. Run Program (At Once)" << endl;
        cout << "3. Run Program (Step by Step)" << endl;
        cout << "4. Reset Machine" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter program filename: ";
                cin >> filename;
                cout << "Enter start address in hex (e.g., 00, 02): ";
                cin >> hex >> startAddr;
                cin >> dec; 
                if (loadProgram(filename, static_cast<uint8_t>(startAddr))) {
                     cout << "Program loaded successfully into memory!" << endl;
                } 
                else {
                    cout << "Failed to load program! Please check the file name or address." << endl;
                }
                break;
                
            case 2:
                run();
                break;
                
            case 3:
                if (!cpu.isHalted()) {
                    
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                    
                    step();
                    cout << "Step executed. Press Enter for next step...";
                    cin.get();
                }
                else {
                    cout << "Program is already halted. Please reset or load a new program." << endl;
                }
                break;
                
            case 4:
                reset();
                cout << "Machine has been reset successfully." << endl;
                break;
                
            case 5:
                cout << "Exiting simulator." << endl;
                break;
                
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 5);
}
