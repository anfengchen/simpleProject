#ifndef __LINK_H__
#define __LINK_H__

typedef struct
{
    int name;        // string table offset
    char type : 4,   // Function or data
        binding : 4; // Local or global
    char reserved;   // Unused
    short section;   // Section header index
    long value;      // Section offset or absolute address
    int size;        // Object size in bytes
} Elf64_Symbol;

typedef struct
{
    long offset;     // Offset of the reference to relocate
    long type : 32,  // Relocation type
        symbol : 32; // Symbol table index
    long addend;     // Constant part of relocation expression
} Elf64_Rela;

// X86_64常用寻址方式
#define R_X86_64_PC32 (0) // 32位PC相对地址寻址
#define R_X86_64_32 (0)   // 32位绝对地址寻址

#define ADDR(sym) (sym) // 未实现，获取一个symbol的实际地址

void reloction(unsigned long sectionAddrBeg, Elf64_Rela rela);
#endif
