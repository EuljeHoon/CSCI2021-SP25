#!/usr/bin/env python3

# SPDX-License-Identifier: GPL-3.0-or-later

## -----------------------------------------------------------------------------
## Script to verify if assembly code follows register rules/conventions
## Authors: Matt Dorow <dorow016@umn.edu>, John Kolb <jhkolb@umn.edu>
## -----------------------------------------------------------------------------

import json
import os
import sys

# Callee saved registers to verify
CALLEE_SAVED_REGS = ["%rbx", "%rbp", "%r12", "%r13", "%r14", "%r15"]

register_width_map = {
    "%ebx": "%rbx",
    "%ebp": "%rbp",
    "%r12d": "%r12",
    "%r13d": "%r13",
    "%r14d": "%r14",
    "%r15d": "%r15",
}

# Registers that should not be used directly
DISALLOWED_REGS = [
    "%eip",
    "%rip",
]

# Characters to be removed from the assembly file
SANITIZE_CHARS = ["(", ")", ","]


# Prints the error_message and exits with failure status
def print_error_and_exit(error_message, error_number):
    print("ERROR: " + error_message)
    sys.exit(error_number)


# Validate input argument count
if len(sys.argv) < 3:
    print_error_and_exit(
        f"Usage: {sys.argv[0]} <puzzle_json_filename> <assembly_filename>", 1
    )

# JSON file with puzzle names
puzzle_list_filename = sys.argv[1]

# File to be checked
assembly_filename = sys.argv[2]

# Check if assembly file exists
if not os.path.isfile(assembly_filename):
    print_error_and_exit(assembly_filename + " does not exist", 2)

if not os.path.isfile(puzzle_list_filename):
    print_error_and_exit(puzzle_list_filename + " does not exist", 2)

# Obtain puzzle names from JSON file
with open(puzzle_list_filename) as f:
    function_names = json.load(f)

# Init callee register map
# False = Register not on stack
# True = Register pushed on stack
callee_regs = {}
for reg in CALLEE_SAVED_REGS:
    callee_regs[reg] = False

# Check the assembly file for any register rules violations
with open(assembly_filename, "r") as assembly_file:
    # Check assembly file line by line
    lines = assembly_file.readlines()

for line_number, line in enumerate(lines):
    # line_number zero indexed so offset by one
    line_number = line_number + 1

    # Strip off any inline comments
    line = line.split("#")[0]

    # Skip over any full line comments
    if len(line.lstrip()) > 0 and line.lstrip()[0] == "/":
        continue

    # Sanitize the input file so that basically only labels, instructions, and
    # registers are left
    for sanitize_char in SANITIZE_CHARS:
        line = line.replace(sanitize_char, " ")

    # Interpret each line as tokens of larger instruction
    tokens = line.split()
    push_instruction = False
    for token in tokens:
        # Mark down if this is a push instruction
        if token == "push" or token == "pushq":
            push_instruction = True

        # Check if this is the start of a new function
        if (token == ".global") and (tokens[-1] in function_names):
            # Reset all callee registers to not yet pushed
            for reg in callee_regs.keys():
                callee_regs[reg] = False

        # Callee-saved register checks
        if token in callee_regs:
            if push_instruction:
                # Callee register has been pushed
                callee_regs[token] = True
            else:
                # For regular uses, exit if hasn't been previously pushed
                if callee_regs[token] == False:
                    print_error_and_exit(
                        f"Register {token} used without being pushed on line {line_number}",
                        4,
                    )
        elif token in register_width_map:
            # No push instructions to worry about here, just check if register was previously pushed
            full_reg_name = register_width_map[token]
            if callee_regs[full_reg_name] == False:
                print_error_and_exit(
                    "Register "
                    + token
                    + " used without being pushed on line "
                    + str(line_number),
                    4,
                )

        # Exit if a disallowed register is being used directly
        if token in DISALLOWED_REGS:
            print_error_and_exit(
                f"Register {token} should not be used directly on line {line_number}", 5
            )

# All good, no output and exit with code 0
sys.exit(0)
