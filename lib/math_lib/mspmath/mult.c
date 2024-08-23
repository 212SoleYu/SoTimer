#include <lib/math_lib/mspmath/msp-math.h>
#include <stdint.h>

// NOTE: This is not implemented as a built-in in libmspbuiltins because Clang
// doesn't issue calls to operations where result type is different from
// argument type. But this case is more efficient and easier to implement than
// a full 32-bit multiplication.


__attribute__((naked))
uint32_t mult16(uint16_t a, uint16_t b)
{
    // NOTE: We have to hardcode addresses, because we ca neither access
    // definitions from the msp430.h header inside the assembly, nor
    // parametrize the assembly snippet since function is naked. A non-naked
    // function with parametrized snipped turned out to be horribly inefficient
    // (the result construction needs a shift: 8 instructions...).

    // NOTE: The registers are dependent on compiler calling convention.

    // Load OP1 and OP2 into the hardware multiplier and read result.

    return (uint32_t)a * (uint32_t)b;
}
