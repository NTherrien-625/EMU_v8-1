import numpy

# Extract each line of code
code = open("main.emu", 'r')
codeContents = code.read()
splitContents = codeContents.splitlines()
code.close()

# Take the newline off each line of code
for i in range(len(splitContents)):
    splitContents[i].replace('\n', '')

# Make a binary file to dump the machine code
machineCode = open("main.bin", 'w')

tempLineSplit = []
instructionLen = 0
rCount = 0
opcode = ""
addressingMode = ""
destinationRegister = ""
operand8 = ""

for i in range(len(splitContents)):
    print (splitContents[i])
    tempLineSplit = splitContents[i].split(' ')
    instructionLen = len(tempLineSplit)

    # Opcode
    if (tempLineSplit[0].find("ADD") != -1):
        opcode = "0000"
    elif (tempLineSplit[0].find("SUB") != -1):
        opcode = "0001"
    elif (tempLineSplit[0].find("AND") != -1):
        opcode = "0010"
    elif (tempLineSplit[0].find("OR") != -1):
        opcode = "0011"
    elif (tempLineSplit[0].find("NOT") != -1):
        opcode = "0100"
    elif (tempLineSplit[0].find("XOR") != -1):
        opcode = "0101"
    elif (tempLineSplit[0].find("SHL") != -1):
        opcode = "0110"
    elif (tempLineSplit[0].find("SHR") != -1):
        opcode = "0111"
    elif (tempLineSplit[0].find("JMP") != -1):
            opcode = "1000"
    elif (tempLineSplit[0].find("JG") != -1):
            opcode = "1001"
    elif (tempLineSplit[0].find("JL") != -1):
            opcode = "1010"
    elif (tempLineSplit[0].find("JE") != -1):
            opcode = "1011"
    elif (tempLineSplit[0].find("JGE") != -1):
            opcode = "1100"
    elif (tempLineSplit[0].find("JLE") != -1):
            opcode = "1101"
    elif (tempLineSplit[0].find("JNE") != -1):
            opcode = "1110"
    elif (tempLineSplit[0].find("CMP") != -1):
            opcode = "1111"
    else:
        print ("Invalid opcode at line " + str(i))
        break
    
    # Addressing mode
    rCount = splitContents[i].count('R', 3)
    if (rCount == 0):
        addressingMode = "00"
    elif (rCount == 2):
        addressingMode = "11"
    elif (rCount == 1):
        if (splitContents[i].find('[') != -1):
            addressingMode = "10"
        else:
            addressingMode = "01"
    else:
        print ("Invalid combination of tokens found at line " + str(i))
        break
    
    if (instructionLen == 2):
        # No destination register, these are jumping instructions
        destinationRegister = "00"
        addressingMode = "01"

        # Get that operand
        tempInt = numpy.int8(tempLineSplit[-1])
        operand8 = format(tempInt, "08b")
    
    if (instructionLen == 3):
        # Get that destination register
        if (tempLineSplit[1].find("PC") != -1):
            destinationRegister = "00"
        elif (tempLineSplit[1].find("R1") != -1):
            destinationRegister = "01"
        elif (tempLineSplit[1].find("R2") != -1):
            destinationRegister = "10"
        elif (tempLineSplit[1].find("R3") != -1):
            destinationRegister = "11"
        else:
            print("Invalid destination register found at line " + str(i))
            break
    
        # Get that operand8
        if (tempLineSplit[2].isdigit()):
            tempInt = numpy.int8(tempLineSplit[-1])
            operand8 = format(tempInt, "08b")
        elif (rCount == 2):
            if (tempLineSplit[2] == "R1"):
                operand8 = "00000001"
            elif (tempLineSplit[2] == "R2"):
                operand8 = "00000010"
            else:
                operand8 = "00000011"
    instruction = addressingMode + opcode + destinationRegister + operand8 + "\n"
    machineCode.write(instruction)
