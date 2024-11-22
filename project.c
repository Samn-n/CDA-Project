#include "spimcore.h"


/* ALU */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{

}

/* instruction fetch */
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{

}


/* instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{

}



/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{

}

/* Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{
    //it basically "reads" the register (which is the number thats in r1/r2's
    //position in the reg array), and copies it into data 1 and 2. "reading" it.)
    *data1 = Reg[r1]; 
    *data2 = Reg[r2];
}


/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{

}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{

}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{
    //Halt condition: Memory is out of range
    if (ALUresult > 0xFFFF)
        return 1;
    //Halt condition: Address not word-aligned
    if (ALUresult % 4 != 0)
        return 1;

    if (MemWrite == 1) 
        Mem[ALUresult >> 2] = data2;    //This writes data2 to memory

    if (MemRead == 1)
        *memdata = Mem[ALUresult >> 2];  //Reads data from memory

    return 0;
}


/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{
    //We bring data from memory since RegWrite and MemtoReg are both 1 and assign this to r2
    if (RegWrite == 1 && MemtoReg == 1) 
        Reg[r2] = memdata;

    //We bring data from ALUresult since MemtoReg is not 1 and we assign this to r3
    if (RegWrite == 1 && MemtoReg == 0)
        Reg[r3] = ALUresult;
    
}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{
    *PC = *PC + 4; //we always add four regardless of instruction

    if (Jump == 1){//check if we need to jump
        *PC = (jsec << 2) | (*PC & 0xf0000000); //combines both jsec (address to jump to, shifted 2 bits to the left) with the upper four bits of PC
    }

    if (Branch == 1){ //if branch is true
        if (Zero == 1){ //if zero is true
            *PC = *PC + (extended_value << 2); //add pc to extended value and shift 2 so it goes from words to bits
        }
        
    }

}

