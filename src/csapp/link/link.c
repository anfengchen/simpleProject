#include "link.h"

void reloction(unsigned long sectionAddrBeg, Elf64_Rela rela)
{
    unsigned long *refptr = sectionAddrBeg + rela.offset;
    unsigned long refaddr = 0;

    // Relocate a PC-relative reference
    if (rela.type == R_X86_64_PC32)
    {
        // ref's runtime address
        refaddr = ADDR(sectionAddrBeg) + rela.offset;
        *refptr = ADDR(rela.symbol)+rela.addend-refaddr;
    }

    // Relocate an absolute reference
    if(rela.type == R_X86_64_32){
        *refptr = ADDR(rela.symbol)+rela.addend;
    }
}