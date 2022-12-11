/** @file EXTI_config.h
 *
 * @brief A header file including Sense Control options and init state for the EXTI peripheral.
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Dec 11, 2022
 *
 */

/* Include guard */
#ifndef EXTI_CONFIG_H
#define EXTI_CONFIG_H

/**
 * Macros for setting the initialized state for each external interrupt
 * for pins (D0->INT0 , D1->INT1 , D2->INT2)
 * Ranges: EXTI_ENABLE
 *         EXTI_DISABLE
 */
#define EXTI0_INIT_STATE EXTI_DISABLE
#define EXTI1_INIT_STATE EXTI_DISABLE
#define EXTI2_INIT_STATE EXTI_DISABLE

/**
 * Macros for setting the initialized sense level for each external interrupt
 * for pins (D0->INT0 , D1->INT1 , D2->INT2)
 * Ranges: EXTI_LOW_LEVEL_SC
 *         EXTI_FALLING_EDGE_SC
 *         EXTI_RISING_EDGE_SC
 *         EXTI_ONCHANGE_SC
 *
 * NOTE: EXTI2 Only supports FALLING_EDGE and RISING_EDGE SC
 */
#define EXTI0_SENSE_CONTROL EXTI_RISING_EDGE_SC
#define EXTI1_SENSE_CONTROL EXTI_LOW_LEVEL_SC
#define EXTI2_SENSE_CONTROL EXTI_FALLING_EDGE_SC

#endif /* EXTI_CONFIG_H */

/*** end of file ***/
