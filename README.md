# To compile use this command

```bash
gcc -o build/assembler_executable \
    src/main.c \
    src/memory/memory.c \
    src/instructions/instructions.c \
    src/registers/registers.c \
    src/utils/utils.c
```

# To run the assembler use this command

```bash
./build/assembler_executable <input_file> <output_file>
```

