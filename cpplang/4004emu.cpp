/*
   소스코드 참고(Source Reference by)
   https://retro-static.com/4004emulator.htm
   https://github.com/lpg2709/emulator-Intel-4004/blob/master/src/4004_chip.c

   명령어 집합 참고 (Insturction Set Guide by)
   http://e4004.szyc.org/iset.html

   202412999 양현성 재작성
   전북대학교 C++ 프로그래밍 26분반 과제
*/

#include <iostream>

/* 메모리 에뮬레이션 */

class MemoryEmulator {
private:
   uint8_t* mem;
   uint8_t membank;

   uint8_t* rom;

   uint16_t stack[3];
   uint16_t stack_pointer;

   uint8_t addr;
   uint8_t romaddr;

public:
   MemoryEmulator() :
      mem(new uint8_t[2048]),
      rom(new uint8_t[4096]),
      stack_pointer(0),
      addr(0), membank(0),
      romaddr(0)
   { }

   bool setMemoryAddr(uint16_t addr);
   void writeMemory(uint8_t val);
   uint8_t readMemory();

   void setMemBank(uint8_t bank);
   uint8_t getMemBank();

   uint8_t getRomAddr();
   void setRomAddr(uint8_t addr);
   uint8_t readRomData();

   uint16_t getStackPointer();
   uint16_t getCurrentStackValue();
   bool PushtoStack(uint16_t val);
   bool PopfromStack(uint16_t* ref);
};

/* RAM 제어 */

bool MemoryEmulator::setMemoryAddr(uint16_t addr) {
   if(addr > 2047) {
      return false;
   } else {
      this->addr = addr;
      return true;
   }
}

void MemoryEmulator::writeMemory(uint8_t val) {
   this->mem[this->addr] = val;
}

uint8_t MemoryEmulator::readRomData() {
   return this->rom[this->romaddr];
}
 
uint8_t MemoryEmulator::readMemory() {
   return this->mem[this->addr];
}

void MemoryEmulator::setMemBank(uint8_t n) {
   this->membank = n;
}

uint8_t MemoryEmulator::getMemBank() {
   return this->membank;
}

/* ROM 제어 */

uint8_t MemoryEmulator::getRomAddr() {
   return this->romaddr;
}

void MemoryEmulator::setRomAddr(uint8_t addr) {
   this->romaddr = addr;
}

/* CPU 스택 제어 - stack depth = 3 */

uint16_t MemoryEmulator::getStackPointer() {
   return this->stack_pointer;
}

uint16_t MemoryEmulator::getCurrentStackValue() {
   return this->stack[this->stack_pointer];
}

bool MemoryEmulator::PushtoStack(uint16_t val) {
   if((this->stack_pointer + 1) > 2)
      return false;
   else {
      this->stack_pointer++;
      this->stack[this->stack_pointer] = val;
      return true;
   }
}

bool MemoryEmulator::PopfromStack(uint16_t* ref) {
   if(this->stack_pointer < 0) {
      this->stack_pointer = 0;
      return false;
   } else {
      ref = this->stack[this->stack_pointer];
      this->stack_pointer--;
      return true;
   }
}

/* 명령어 집합 구현 및 레지스터 등 상태 관리 */

class CPUEmulator {
private:
   MemoryEmulator mem;

   uint16_t pc;
   uint8_t accumualtor;
   uint8_t registers[16];
   uint8_t* ram_status;

   bool carry;
   bool test;

public:
   CPUEmulator() :
      pc(0),
      carry(false), test(false),
      accumualtor(0),
      mem(), ram_status(new uint8_t[4 * 4 * 16])
   { 
      for(int i = 0; i < 8; i++)
         this->registers[i] = 0;
   }

   void doReset();

protected:
   /* 일반 제어 명령어 - Basic Instructions */
   void OP_nop();
   void OP_jcn(uint16_t opa);
   void OP_fim(uint16_t op_abc);
   void OP_src(uint8_t opa);
   void OP_fin(uint16_t op_abc);
   void OP_jin(uint8_t opa);
   void OP_jms(uint16_t op_abc);
   void OP_jun(uint16_t op_abc);
   void OP_inc(uint8_t opa);
   void OP_isz(uint16_t op_abc);
   void OP_add(uint8_t opa);
   void OP_sub(uint8_t opa);
   void OP_ld(uint8_t opa);
   void OP_ldm(uint8_t opa);
   void OP_xch(uint8_t opa);
   void OP_bbl();
   
   /* 메모리 관련 명령어 - Memory Related Instructions */
   void OP_rdm();
   void OP_rd_number(int n);
   void OP_rdr();
   void OP_wrm();
   void OP_wr_number(int n);
   void OP_wrr();
   void OP_adm();
   void OP_sbm();

   void OP_clc();
   void OP_iac();
   void OP_cmc();
   void OP_cma();
   void OP_ral();
   void OP_rar();

   /*impl later*/

};

void CPUEmulator::doReset() {
   this->pc = 0;
   this->accumualtor = 0;
   this->carry = false;
   this->test = false;

   for(int i = 0; i < 8; i++)
      this->registers[i] = 0;
}

void CPUEmulator::OP_nop() {
   this->pc++;
}

void CPUEmulator::OP_ldm(uint8_t opa) {
   this->accumualtor = (opa & 0xF);
   this->pc++;
}

void CPUEmulator::OP_ld(uint8_t opa) {
   this->accumualtor = this->registers[(opa & 0xF)];
   this->pc++;
}

void CPUEmulator::OP_xch(uint8_t opa) {
   uint8_t temp = (this->accumualtor & 0xF);
   this->accumualtor = this->registers[(opa & 0xF)];
   this->registers[(opa & 0xF)] = temp;
   this->pc++;
}

void CPUEmulator::OP_add(uint8_t opa) {
   uint8_t rd = this->registers[(opa & 0xF)];
   this->accumualtor += (~(rd) + this->carry);

   this->carry = false;
   if(this->accumualtor > 15) {
      this->carry = true;
      this->accumualtor = this->accumualtor & 0xF;
   }

   this->pc++;
}

void CPUEmulator::OP_sub(uint8_t opa) {
   uint8_t rd = this->registers[(opa & 0xF)];
   this->accumualtor += (~(rd) + !this->carry);

   this->carry = true;
   if(!(this->accumualtor & 0xF0)) {
      this->carry = false;
      this->accumualtor = this->accumualtor & 0xF;
   }

   this->pc++;
}

void CPUEmulator::OP_inc(uint8_t opa) {
   this->registers[(opa & 0xF)]++;
   if(this->registers[(opa & 0xF)] > 15) {
      this->registers[(opa & 0xF)] = 0;
   }
   
   this->pc++;
}

void CPUEmulator::OP_jin(uint8_t opa) {
   uint8_t addr = (opa & 0xE);
   uint8_t regaddr = (this->registers[addr] << 4) | (this->registers[addr + 1]);

   uint16_t jumpaddr =  (this->pc & 0xF00) | regaddr;
}

void CPUEmulator::OP_src(uint8_t opa) {
   uint8_t regadrr = (opa & 0xE);
   //impl later
}

// 12bit instruction

void CPUEmulator::OP_jun(uint16_t op_abc) {
   uint16_t jumpaddr = (op_abc & 0xFFF);
   this->pc = jumpaddr;
}

void CPUEmulator::OP_jms(uint16_t op_abc) {
   this->mem.PushtoStack(this->pc);
   this->pc = (op_abc & 0xFFF);
}

void CPUEmulator::OP_jcn(uint16_t op_abc) {
   uint8_t C1 = (op_abc & 0x800) >> 11;
   uint8_t C2 = (op_abc & 0x400) >> 10;
   uint8_t C3 = (op_abc & 0x200) >> 9;
   uint8_t C4 = (op_abc & 0x100) >> 8;

   uint16_t target = (op_abc && 0xFF) | (0xFF << 8);

   /*
   JUMP = ~C1 . ((ACC = 0) . C2 + (CY = 1) . C3 +
               ~TEST . C4) + C1 . ~((ACC = 0) . C2 +
               (CY = 1) . C3 + ~TEST . C4)
   */

   if(
      !C1 && ((this->accumualtor == 0) && C2) || (this->carry)
      && C3 || (this->test && C4) || C1 && (!this->accumualtor == 0)
      && C2 || (this->carry) && C3 || (!this->test) && C4  
   ) {
      this->pc = (this->pc & target);
   } else {
      this->pc = (this->pc + 2);
   }
}

void CPUEmulator::OP_isz(uint16_t op_abc) {
   uint8_t reg = (8 >> op_abc) & 0xFF0;
   uint8_t rom = (op_abc && 0xFF);

   this->registers[reg + 1] = this->registers[reg];
   if(this->registers[reg] != 0) {
      this->pc = rom;
   } else {
      this->pc = (this->pc + 2);
   }
}

void CPUEmulator::OP_fim(uint16_t op_abc) {
   uint8_t regaddr = (8 >> op_abc) & 0x0E;
   uint8_t romaddr = (op_abc & 0xFF);

   this->registers[regaddr] = (4 >> romaddr) & 0x0F;
   this->registers[regaddr+1] = (romaddr & 0xF);

   //12bit instruction takes two clock cycle
   this->pc++;
   this->pc++;
}

void CPUEmulator::OP_rdm() {
   this->accumualtor = this->mem.readMemory();
   this->pc++;
}

void CPUEmulator::OP_rd_number(int n) {
   this->accumualtor = this->ram_status[this->mem.getMemBank() * n * 4];
   this->pc++;
}

void CPUEmulator::OP_wr_number(int n) {

}

class Excutioner : public CPUEmulator {
private:

public:
   Excutioner() :
      CPUEmulator()
   {

   }

   void Step() {
      for(;;) {
      }
   }
};

int main() {
   return 0;
}
