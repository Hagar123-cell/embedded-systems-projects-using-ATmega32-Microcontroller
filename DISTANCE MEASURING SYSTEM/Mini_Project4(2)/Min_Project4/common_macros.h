/*----------------------------------------------------------------------------
 [file name]: commom_macros.h
 [AUTHOR]: Hagar Ahmed
 [DATE CREATED]: 9/10/2022
 [DESCRIPTION]:header file for common macros in the AVR drivers
 -----------------------------------------------------------------------------*/
#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

/* Set a certain bit in any register */
#define SET_BIT(REG, BIT)           (REG|=(1<<BIT))

/* Clear a certain bit in any register */
#define CLEAR_BIT(REG, BIT)         (REG&=(~(1<<BIT)))

/* Toggle a certain bit in any register */
#define TOGGLE_BIT(REG, BIT)        (REG^=(1<<BIT))

/* Check if a specific bit is set in any register and return true if yes */
#define BIT_IS_SET(REG, BIT)        (REG&(1<<BIT))

/* Check if a specific bit is cleared in any register and return true if yes */
#define BIT_IS_CLEAR(REG, BIT)      (!(REG&(1<<BIT)))

/* Rotate right the register value with specific number of rotates */
#define ROR(REG, BIT)               ( REG= (REG>>BIT) | (REG<<(8-BIT)) )

/* Rotate left the register value with specific number of rotates */
#define ROL(REG, BIT)               ( REG= (REG<<BIT) | (REG>>(8-BIT)) )

/*get the given bit*/
#define GET_BIT(REG, BIT)           ((REG &(1<<BIT)) >> BIT)

#endif /* COMMON_MACROS_H_ */
