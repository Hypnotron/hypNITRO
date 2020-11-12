#pragma once
#include <array>
#include <memory>
#include "bank.hpp"
#include "bits.hpp"
#include "debug.hpp"
#include "types.hpp"

//ENHANCEMENT: additional cores 
//(will need to update entire Cpu class 
//and instructionSetFromCore to implement)
enum Core : u8 { 
    ARM7TDMI,
    ARM946E_S,
};
enum class BusType : u8 {
    CODE,
    DATA,
};
enum class Width : u8 {
    BYTE,
    HALFWORD,
    WORD,
};

class Coprocessor {};
class CP15 : public Coprocessor {
    protected:

    public:
        /* Registers: */
        /*            */
        u32 idCode;
        u32 cacheType;
        u32 tcmSize;
        u32 control;
        u32 dataCachability;
        u32 instructionCachability;
        u32 bufferability;
        u32 dataAccessPermission;
        u32 instructionAccessPermission;
        std::array<u32, 8> dataProtectionRegions;
        std::array<u32, 8> instructionProtectionRegions;
        u32 dataLockdown;
        u32 instructionLockdown;
        u32 dataTcmControl;
        u32 instructionTcmControl;
        u32 processId;
        //ENHANCEMENT: additional registers (will
        //need to update mcr, mrc, and registers
        //to implement)

        /* Cache + TCM: */
        /*              */
        //TODO: cache + tcm

        /* Primary interface: */
        /*                    */
        virtual u32 armRead(
                const BusType& busType,
                const Width& width, 
                const u32& address) const = 0;
        virtual void armWrite(
                const BusType& busType,
                const Width& width,
                const u32& address,
                const u32& data) const = 0;

        /* ARM operations: */
        /*                 */
        //mcr p15, opcode1, armRegister, coprocessorRegisterIndex1,
        //    coprocessorRegisterIndex2, opcode2
        void mcr(
                const u8& opcode1, 
                const u32& armRegister, 
                const u8& coprocessorRegisterIndex1,
                const u8& coprocessorRegisterIndex2,
                const u8& opcode2) {
            //TODO: finish mcr
            switch (coprocessorRegisterIndex1) {
            case 1:
                control = armRegister;
            break;
            case 2:
                switch (opcode2) {
                case 0:
                    dataCachability = armRegister;
                break;
                case 1:
                    instructionCachability = armRegister;
                break;
                default:
                    debug::write(
                            debug::message, 
                            "mcr p15, %d, ???, c%d, c%d, %d"
                            " last field (opcode 2) is invalid and"
                            " will be ignored\n", opcode1,
                            coprocessorRegisterIndex1,
                            coprocessorRegisterIndex2,
                            opcode2);
                    debug::warn();
                }
            break;
            case 3:
                bufferability = armRegister;
            break;
            case 5:
                switch (opcode2) {
                case 0:
                    for (u8_fast i {0}; i < 8; ++i) {
                        //armRegister 0b12 34 56 78 12 34 56 78 
                        //becomes access permission 
                        //0b0012 0034 0056 0078 0012 0034 0056 0078: 
                        setBits(
                                0b1111 << (i * 4),
                                dataAccessPermission,
                                (armRegister & (0b11 << (i * 2))) 
                                        << (i * 2));

                    }
                break;
                case 1:
                    for (u8_fast i {0}; i < 8; ++i) {
                        //armRegister 0b12 34 56 78 12 34 56 78 
                        //becomes access permission 
                        //0b0012 0034 0056 0078 0012 0034 0056 0078: 
                        setBits(
                                0b1111 << (i * 4),
                                instructionAccessPermission,
                                (armRegister & (0b11 << (i * 2))) 
                                        << (i * 2));

                    }
                break;
                case 2:
                    dataAccessPermission = armRegister;
                break;
                case 3:
                    instructionAccessPermission = armRegister;
                break;
                default:
                    debug::write(
                            debug::message,
                            "mcr p15, %d, ???, c%d, c%d, %d"
                            " last field (opcode 2) is invalid and"
                            " will be ignored\n", opcode1,
                            coprocessorRegisterIndex1,
                            coprocessorRegisterIndex2,
                            opcode2);
                    debug::warn();
                }
                break;
            case 6:
                if (coprocessorRegisterIndex2 >= 8) {
                    debug::write(
                            debug::message,
                            "mcr p15, %d, ???, c%d, c%d, %d"
                            " fifth field (CRm) is invalid and"
                            " will be masked to a value under 8\n", 
                            opcode1,
                            coprocessorRegisterIndex1,
                            coprocessorRegisterIndex2,
                            opcode2);
                    debug::warn();
                }
                switch (opcode2) {
                case 0:
                    dataProtectionRegions[
                            coprocessorRegisterIndex2 & 0x7] = armRegister;
                break;
                case 1:
                    instructionProtectionRegions[
                            coprocessorRegisterIndex2 & 0x7] = armRegister;
                break;
                default:
                    debug::write(
                            debug::message,
                            "mcr p15, %d, ???, c%d, c%d, %d"
                            " last field (opcode 2) is invalid and"
                            " will be ignored\n", opcode1,
                            coprocessorRegisterIndex1,
                            coprocessorRegisterIndex2,
                            opcode2);
                    debug::warn();
                }
            break;
            case 7:
                switch (coprocessorRegisterIndex2) {
                case 0:
                break;
                case 5:
                break;
                case 6:
                break;
                case 8:
                break;
                case 10:
                break;
                case 13:
                break;
                case 14:
                break;
                default:
                    debug::write(
                            debug::message,
                            "mcr p15, %d, ???, c%d, c%d, %d"
                            " fifth field (CRm) is invalid and"
                            " will be ignroed\n", opcode1,
                            coprocessorRegisterIndex1,
                            coprocessorRegisterIndex2,
                            opcode2);
                    debug::warn();
                }
            break;
            case 9:
                switch (opcode2) {
                case 0:
                    dataTcmControl = armRegister;
                break;
                case 1:
                    instructionTcmControl = armRegister;
                break;
                default:
                    debug::write(
                            debug::message,
                            "mcr p15, %d, ???, c%d, c%d, %d"
                            " last field (opcode 2) is invalid and"
                            " will be ignroed\n", opcode1,
                            coprocessorRegisterIndex1,
                            coprocessorRegisterIndex2,
                            opcode2);
                    debug::warn();
                }
            break;
            case 13:
                if (opcode2 != 1) {
                    debug::write(
                            debug::message,
                            "mcr p15, %d, ???, c%d, c%d, %d"
                            " last field (opcode 2) is invalid and"
                            " will be treated as 1\n", opcode1,
                            coprocessorRegisterIndex1,
                            coprocessorRegisterIndex2,
                            opcode2);
                    debug::warn();
                }
                processId = armRegister;
            break;
            default:
                debug::write(
                        debug::message,
                        "mcr p15, %d, ???, c%d, c%d, %d"
                        " fourth field (CRn) is invalid and"
                        " will be ignored\n", opcode1,
                        coprocessorRegisterIndex1,
                        coprocessorRegisterIndex2,
                        opcode2);
                debug::warn();
            }
        }
        //TODO: mrc

        
};
template <Core core>
class Cpu {
    public:
        /* Utilities, helpers, aliases, etc: */
        /*                                   */
        enum Interrupt : u8 {
            RESET,
            DATA_ABORT,
            FAST_INTERRUPT,
            INTERRUPT,
            PREFETCH_ABORT,
            UNDEFINED_INSTRUCTION,
            SOFTWARE_INTERRUPT,
        };
        
    protected:
        /* Utilities, helpers, aliases, etc: */
        /*                                   */
        //ENHANCEMENT: additional instruction sets 
        //(will need to update entire 
        //Cpu class to implement)
        enum InstructionSet : u8 {
            ARMv4T,
            ARMv5TE,
        };
        enum Register : u8 {
            SP = 13,
            LR,
            PC,
            CPSR,
            SPSR,
        };
        enum class Mode : u8 {
            USR,
            FIQ,
            IRQ,
            SVC,
            ABT,
            UND,
            SYS,
        };
        enum class Flag : u8 {
            MODE,
            THUMB = 5,
            DISABLE_FIQ,
            DISABLE_IRQ,
            STICKY_OVERFLOW = 27,
            OVERFLOW,
            CARRY,
            ZERO,
            NEGATIVE
        };
        static inline InstructionSet instructionSetFromCore(
                const Core& coreParam) {
            switch (coreParam) {
                case ARM7TDMI:  return ARMv4T;
                case ARM946E_S: return ARMv5TE;
            }
        }
        static inline Mode modeFromInterrupt(
                const Interrupt& interrupt) {
            switch (interrupt) {
                case RESET:                     return Mode::SVC;
                case DATA_ABORT:                return Mode::ABT;
                case FAST_INTERRUPT:            return Mode::FIQ;
                case INTERRUPT:                 return Mode::IRQ;
                case PREFETCH_ABORT:            return Mode::ABT;
                case UNDEFINED_INSTRUCTION:     return Mode::UND;
                case SOFTWARE_INTERRUPT:        return Mode::SVC;
            }
        }
        static inline u8 modeBitsFromMode(
                const Mode& mode) {
            switch (mode) {
                case Mode::USR: return 0b10000;
                case Mode::FIQ: return 0b10001;
                case Mode::IRQ: return 0b10010;
                case Mode::SVC: return 0b10011;
                case Mode::ABT: return 0b10111;
                case Mode::UND: return 0b11011;
                case Mode::SYS: return 0b11111;
            }
        }

        /* Registers, coprocessors, etc: */
        /*                               */
        //data type, size type, mode count, 
        //number of registers per mode (16 GPRs + CPSR + SPSR),
        //number of unique registers:
        Bank<u32, u8, 7, 18, 37> registers {};
        std::array<std::unique_ptr<Coprocessor>, 16> coprocessors {};

    public:
        /* Primary interface: */
        /*                    */
        void serviceInterrupt(const Interrupt& interrupt) {
            //TODO: finish serviceInterrupt
            registers.mode = static_cast<u8>(modeFromInterrupt(interrupt)); 
            registers[SPSR] = registers[CPSR];
            setBits(
                    0b11111,
                    registers[CPSR], 
                    modeBitsFromMode(registers.mode)); 
            setBit<Flag::THUMB>(registers[CPSR], false);
            setBit<Flag::DISABLE_IRQ>(registers[CPSR], true);
        }
};
