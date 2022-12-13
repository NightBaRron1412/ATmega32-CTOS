/** @file TMR_program.c
 *
 * @brief A c file including Timers functions implementations
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Dec 10, 2022
 *
 */

#include "../Lib/Std_Types.h"
#include "../Lib/Bit_Math.h"
#include "TMR_private.h"
#include "TMR_interface.h"
#include "TMR_config.h"

/*Static variables which save the value of TCCR register corresponding to each timer*/
static u8 TMR_u8Timer0CtrlRegValue;
static u8 TMR_u8Timer1CtrlRegValue;
static u8 TMR_u8Timer2CtrlRegValue;

/*Static variable needed in the ISR of each OVF timer interrupt*/
static u32 TMR_u32Timer0Cntr = 0;
static u32 TMR_u32Timer1Cntr = 0;
static u32 TMR_u32Timer2Cntr = 0;

static u32 TMR_u32Timer0Preload = TMR_Timer0Preload;
static u32 TMR_u32Timer1Preload = TMR_Timer1Preload;
static u32 TMR_u32Timer2Preload = TMR_Timer2Preload;

static u32 TMR_u32ReqTimer0Cntr = TMR_ReqTimer0Cntr;
static u32 TMR_u32ReqTimer1Cntr = TMR_ReqTimer1Cntr;
static u32 TMR_u32ReqTimer2Cntr = TMR_ReqTimer2Cntr;

static u16 TMR_u16ONTime;
static u16 TMR_u16TotalTime;
static u16 TMR_u16DutyCycle;

/* Static array where each element is a pointer to function of each one of overflow interrupt for timer 0,1,2 */
static void (*PVCallBack[TMR_NO_OF_TIMERS])(void) = {NULL, NULL, NULL};

/*
 * Description: Function to set the initialized state and prescaler for each timer (0,1,2)
 * Inputs: none
 * Output: void
 */
void TMR_VidInit(void)
{

    /* Setting the initialization for Timer0 */
    if (TMR_TIMER0_INIT_STATE == TMR_DISABLE)
    {
        CLR_BIT(TCCR0, TCCR0_CS00);
        CLR_BIT(TCCR0, TCCR0_CS01);
        CLR_BIT(TCCR0, TCCR0_CS02);
    }
    else
    {
        if (TMR_TIMER0_MODE == TMR_NORMAL)
        {
            CLR_BIT(TCCR0, TCCR0_WGM00);
            CLR_BIT(TCCR0, TCCR0_WGM01);

            /* Checking Timer/Counter0 Overflow Interrupt Enable bit */
            if (TMR_TIMER0_OVF_INT == TMR_EN_INT)
            {
                SET_BIT(TIMSK, TIMSK_TOIE0);
            }
            else
            {
                CLR_BIT(TIMSK, TIMSK_TOIE0);
            }
        }

        else if (TMR_TIMER0_MODE == TMR_CTC)
        {
            CLR_BIT(TCCR0, TCCR0_WGM00);
            SET_BIT(TCCR0, TCCR0_WGM01);

            /* Checking Timer/Counter0 CTC Interrupt Enable bit */
            if (TMR_TIMER0_CTC_INT == TMR_EN_INT)
            {
                SET_BIT(TIMSK, TIMSK_OCIE0);
            }

            else
            {
                CLR_BIT(TIMSK, TIMSK_OCIE0);
            }
        }

        else if (TMR_TIMER0_MODE == TMR_FASTPWM_8BIT)
        {
            SET_BIT(TCCR0, TCCR0_WGM01);
            SET_BIT(TCCR0, TCCR0_WGM00);
        }

        else if (TMR_TIMER0_MODE == TMR_PWM_PHASE_CORRECT)
        {
            SET_BIT(TCCR0, TCCR0_WGM00);
            CLR_BIT(TCCR0, TCCR0_WGM01);
        }

        /* Checking the compare output mode applied on OC0 pin in (CTC/FAST PWM/PHASE CORRECT) modes*/
        switch (TMR_TIMER0_COPT_MODE)
        {

        case TMR_NORMAL:

            CLR_BIT(TCCR0, TCCR0_COM00);
            CLR_BIT(TCCR0, TCCR0_COM01);
            break;

        case TMR_TOGGLE_OCX:

            SET_BIT(TCCR0, TCCR0_COM00);
            CLR_BIT(TCCR0, TCCR0_COM01);
            break;

        case TMR_CLEAR_OCX:

            SET_BIT(TCCR0, TCCR0_COM01);
            CLR_BIT(TCCR0, TCCR0_COM00);
            break;

        case TMR_SET_OCX:

            SET_BIT(TCCR0, TCCR0_COM00);
            SET_BIT(TCCR0, TCCR0_COM01);
            break;
        }

        /* Checking assigned Prescaler for Timer/Counter0 */
        switch (TMR_TIMER0_PRESCALER)
        {
        case TMR_NO_PRESCALER:

            SET_BIT(TCCR0, TCCR0_CS00);
            CLR_BIT(TCCR0, TCCR0_CS01);
            CLR_BIT(TCCR0, TCCR0_CS02);
            break;

        case TMR_PRESCALER_8:

            CLR_BIT(TCCR0, TCCR0_CS00);
            SET_BIT(TCCR0, TCCR0_CS01);
            CLR_BIT(TCCR0, TCCR0_CS02);
            break;

        case TMR_PRESCALER_64:

            SET_BIT(TCCR0, TCCR0_CS00);
            SET_BIT(TCCR0, TCCR0_CS01);
            CLR_BIT(TCCR0, TCCR0_CS02);
            break;

        case TMR_PRESCALER_256:

            CLR_BIT(TCCR0, TCCR0_CS00);
            CLR_BIT(TCCR0, TCCR0_CS01);
            SET_BIT(TCCR0, TCCR0_CS02);
            break;

        case TMR_PRESCALER_1024:

            SET_BIT(TCCR0, TCCR0_CS00);
            CLR_BIT(TCCR0, TCCR0_CS01);
            SET_BIT(TCCR0, TCCR0_CS02);
            break;

        default:

            SET_BIT(TCCR0, TCCR0_CS00);
            CLR_BIT(TCCR0, TCCR0_CS01);
            CLR_BIT(TCCR0, TCCR0_CS02);
        }

        TMR_u8Timer0CtrlRegValue = TCCR0;
    }

    /* Setting the initialization for Timer1 */
    if (TMR_TIMER1_INIT_STATE == TMR_DISABLE)
    {
        CLR_BIT(TCCR1B, TCCR1B_CS10);
        CLR_BIT(TCCR1B, TCCR1B_CS11);
        CLR_BIT(TCCR1B, TCCR1B_CS12);
    }
    else
    {
        if (TMR_TIMER1_MODE == TMR_NORMAL)
        {
            /* Checking Timer/Counter1 Overflow Interrupt Enable bit */
            if (TMR_TIMER1_OVF_INT == TMR_EN_INT)
            {
                SET_BIT(TIMSK, TIMSK_TOIE1);
            }
            else
            {
                CLR_BIT(TIMSK, TIMSK_TOIE1);
            }

            if (TMR_ICP_INT == TMR_EN_INT)
            {
                if (TMR_ICES == TMR_RISING_EDGE)
                {
                    SET_BIT(TCCR1B, TCCR1B_ICES1);
                }
                else
                {
                    CLR_BIT(TCCR1B, TCCR1B_ICES1);
                }

                SET_BIT(TIMSK, TIMSK_TICIE1);
            }
        }
        else if (TMR_TIMER1_MODE == TMR_CTC)
        {
            SET_BIT(TCCR1B, TCCR1B_WGM12);

            /* Checking Timer/Counter1A CTC Interrupt Enable bit */
            if (TMR_TIMER1A_COMP_STATE == TMR_ENABLE)
            {
                SET_BIT(TIMSK, TIMSK_OCIE1A);
            }
            else
            {
                CLR_BIT(TIMSK, TIMSK_OCIE1A);
            }
            /* Checking Timer/Counter1B CTC Interrupt Enable bit */
            if (TMR_TIMER1B_COMP_STATE == TMR_ENABLE)
            {
                SET_BIT(TIMSK, TIMSK_OCIE1B);
            }
            else
            {
                CLR_BIT(TIMSK, TIMSK_OCIE1B);
            }
            /* Checking Timer/Counter1 CTC Interrupt Enable bit */
            if (TMR_TIMER1_CTC_INT == TMR_EN_INT)
            {
                SET_BIT(TIMSK, TIMSK_OCIE1B);
                SET_BIT(TIMSK, TIMSK_OCIE1A);
            }
            else
            {
                CLR_BIT(TIMSK, TIMSK_OCIE1B);
                CLR_BIT(TIMSK, TIMSK_OCIE1A);
            }
        }
        else if (TMR_TIMER1_MODE == TMR_FASTPWM_8BIT)
        {
            SET_BIT(TCCR1A, TCCR1A_WGM10);
            CLR_BIT(TCCR1A, TCCR1A_WGM11);
            SET_BIT(TCCR1B, TCCR1B_WGM12);
            CLR_BIT(TCCR1B, TCCR1B_WGM13);
        }
        else if (TMR_TIMER1_MODE == TMR_FASTPWM_9BIT)
        {
            CLR_BIT(TCCR1A, TCCR1A_WGM10);
            SET_BIT(TCCR1A, TCCR1A_WGM11);
            SET_BIT(TCCR1B, TCCR1B_WGM12);
            CLR_BIT(TCCR1B, TCCR1B_WGM13);
        }
        else if (TMR_TIMER1_MODE == TMR_FASTPWM_10BIT)
        {
            SET_BIT(TCCR1A, TCCR1A_WGM10);
            SET_BIT(TCCR1A, TCCR1A_WGM11);
            SET_BIT(TCCR1B, TCCR1B_WGM12);
            CLR_BIT(TCCR1B, TCCR1B_WGM13);
        }
        else if (TMR_TIMER1_MODE == TMR_FASTPWM_ICR1)
        {
            CLR_BIT(TCCR1A, TCCR1A_WGM10);
            SET_BIT(TCCR1A, TCCR1A_WGM11);
            SET_BIT(TCCR1B, TCCR1B_WGM12);
            SET_BIT(TCCR1B, TCCR1B_WGM13);

            ICR1 = TMR_ICR1_VAL;
        }
        else if (TMR_TIMER1_MODE == TMR_PWM_PHASE_CORRECT)
        {
            SET_BIT(TCCR1A, TCCR1A_WGM10);
            SET_BIT(TCCR1A, TCCR1A_WGM11);
            CLR_BIT(TCCR1B, TCCR1B_WGM12);
            SET_BIT(TCCR1B, TCCR1B_WGM13);
        }

        /* Checking the compare output mode applied on OC1A/OC1B pins in (CTC/FAST PWM/PHASE CORRECT) modes */
        switch (TMR_TIMER1_COPT_MODE)
        {
        case TMR_NORMAL:

            if (TMR_TIMER1A_COPT_STATE == TMR_ENABLE)
            {
                CLR_BIT(TCCR1A, TCCR1A_COM1A0);
                CLR_BIT(TCCR1A, TCCR1A_COM1A1);
            }

            if (TMR_TIMER1B_COPT_STATE == TMR_ENABLE)
            {
                CLR_BIT(TCCR1A, TCCR1A_COM1B0);
                CLR_BIT(TCCR1A, TCCR1A_COM1B1);
            }

            break;

        case TMR_TOGGLE_OCX:

            if (TMR_TIMER1A_COPT_STATE == TMR_ENABLE)
            {
                SET_BIT(TCCR1A, TCCR1A_COM1A0);
                CLR_BIT(TCCR1A, TCCR1A_COM1A1);
            }

            if (TMR_TIMER1B_COPT_STATE == TMR_ENABLE)
            {
                SET_BIT(TCCR1A, TCCR1A_COM1B0);
                CLR_BIT(TCCR1A, TCCR1A_COM1B1);
            }

            break;

        case TMR_CLEAR_OCX:

            if (TMR_TIMER1A_COPT_STATE == TMR_ENABLE)
            {
                CLR_BIT(TCCR1A, TCCR1A_COM1A0);
                SET_BIT(TCCR1A, TCCR1A_COM1A1);
            }

            if (TMR_TIMER1B_COPT_STATE == TMR_ENABLE)
            {
                CLR_BIT(TCCR1A, TCCR1A_COM1B0);
                SET_BIT(TCCR1A, TCCR1A_COM1B1);
            }

            break;

        case TMR_SET_OCX:

            if (TMR_TIMER1A_COPT_STATE == TMR_ENABLE)
            {
                SET_BIT(TCCR1A, TCCR1A_COM1A0);
                SET_BIT(TCCR1A, TCCR1A_COM1A1);
            }
            if (TMR_TIMER1B_COPT_STATE == TMR_ENABLE)
            {
                SET_BIT(TCCR1A, TCCR1A_COM1B0);
                SET_BIT(TCCR1A, TCCR1A_COM1B1);
            }
            break;
        }

        /* Checking assigned Prescaler for Timer/Counter1 */
        switch (TMR_TIMER1_PRESCALER)
        {
        case TMR_NO_PRESCALER:
        {
            SET_BIT(TCCR1B, TCCR1B_CS10);
            CLR_BIT(TCCR1B, TCCR1B_CS11);
            CLR_BIT(TCCR1B, TCCR1B_CS12);
            break;
        }
        case TMR_PRESCALER_8:
        {
            SET_BIT(TCCR1B, TCCR1B_CS11);
            CLR_BIT(TCCR1B, TCCR1B_CS10);
            CLR_BIT(TCCR1B, TCCR1B_CS12);

            break;
        }
        case TMR_PRESCALER_64:
        {
            SET_BIT(TCCR1B, TCCR1B_CS10);
            SET_BIT(TCCR1B, TCCR1B_CS11);
            CLR_BIT(TCCR1B, TCCR1B_CS12);
            break;
        }
        case TMR_PRESCALER_256:
        {
            SET_BIT(TCCR1B, TCCR1B_CS12);
            CLR_BIT(TCCR1B, TCCR1B_CS11);
            CLR_BIT(TCCR1B, TCCR1B_CS10);
            break;
        }
        case TMR_PRESCALER_1024:
        {
            SET_BIT(TCCR1B, TCCR1B_CS10);
            SET_BIT(TCCR1B, TCCR1B_CS12);
            CLR_BIT(TCCR1B, TCCR1B_CS11);
            break;
        }
        default:
        {
            SET_BIT(TCCR1B, TCCR1B_CS10);
            CLR_BIT(TCCR1B, TCCR1B_CS11);
            CLR_BIT(TCCR1B, TCCR1B_CS12);
        }
        }
        TMR_u8Timer1CtrlRegValue = TCCR1B;
    }

    /* Setting the initialization for Timer2 */
    if (TMR_TIMER2_INIT_STATE == TMR_DISABLE)
    {
        CLR_BIT(TCCR2, TCCR2_CS20);
        CLR_BIT(TCCR2, TCCR2_CS21);
        CLR_BIT(TCCR2, TCCR2_CS22);
    }
    else
    {
        if (TMR_TIMER2_MODE == TMR_NORMAL)
        {
            /* Checking Timer/Counter0 Overflow Interrupt Enable bit */
            if (TMR_TIMER2_OVF_INT == TMR_EN_INT)
            {
                SET_BIT(TIMSK, TIMSK_TOIE2);
            }
            else
            {
                CLR_BIT(TIMSK, TIMSK_TOIE2);
            }
        }
        else if (TMR_TIMER2_MODE == TMR_CTC)
        {
            SET_BIT(TCCR2, TCCR2_WGM21);
            /* Checking Timer/Counter2 CTC Interrupt Enable bit */
            if (TMR_TIMER2_CTC_INT == TMR_EN_INT)
            {
                SET_BIT(TIMSK, TIMSK_OCIE2);
            }
            else
            {
                CLR_BIT(TIMSK, TIMSK_OCIE2);
            }
        }
        else if (TMR_TIMER2_MODE == TMR_FASTPWM_8BIT)
        {
            SET_BIT(TCCR2, TCCR2_WGM21);
            SET_BIT(TCCR2, TCCR2_WGM20);
        }
        else if (TMR_TIMER2_MODE == TMR_PWM_PHASE_CORRECT)
        {
            SET_BIT(TCCR2, TCCR2_WGM20);
        }
        /* Checking the compare output mode applied on OC2 pin in (CTC/FAST PWM/PHASE CORRECT) modes*/
        switch (TMR_TIMER2_COPT_MODE)
        {
        case TMR_NORMAL:
        {
            CLR_BIT(TCCR2, TCCR2_COM20);
            CLR_BIT(TCCR2, TCCR2_COM21);
            break;
        }
        case TMR_TOGGLE_OCX:
        {
            SET_BIT(TCCR2, TCCR2_COM20);
            break;
        }
        case TMR_CLEAR_OCX:
        {
            SET_BIT(TCCR2, TCCR2_COM21);
            break;
        }
        case TMR_SET_OCX:
        {
            SET_BIT(TCCR2, TCCR2_COM20);
            SET_BIT(TCCR2, TCCR2_COM21);
            break;
        }
        }
        /* Checking assigned Prescaler for Timer/Counter2 */
        switch (TMR_TIMER2_PRESCALER)
        {
        case TMR_NO_PRESCALER:
        {
            SET_BIT(TCCR2, TCCR2_CS20);
            break;
        }
        case TMR_PRESCALER_8:
        {
            SET_BIT(TCCR2, TCCR2_CS21);
            break;
        }
        case TMR_PRESCALER_32:
        {
            SET_BIT(TCCR2, TCCR2_CS20);
            SET_BIT(TCCR2, TCCR2_CS21);
            break;
        }
        case TMR_PRESCALER_64:
        {
            SET_BIT(TCCR2, TCCR2_CS22);
            break;
        }
        case TMR_PRESCALER_128:
        {
            SET_BIT(TCCR2, TCCR2_CS20);
            SET_BIT(TCCR2, TCCR2_CS22);
            break;
        }
        case TMR_PRESCALER_256:
        {
            SET_BIT(TCCR2, TCCR2_CS21);
            SET_BIT(TCCR2, TCCR2_CS22);
            break;
        }
        case TMR_PRESCALER_1024:
        {
            SET_BIT(TCCR2, TCCR2_CS20);
            SET_BIT(TCCR2, TCCR2_CS21);
            SET_BIT(TCCR2, TCCR2_CS22);
            break;
        }
        }
        TMR_u8Timer2CtrlRegValue = TCCR2;
    }
}

/*
 * Description: Function to enable one of the available timers in AVR ATmega32 (0,1,2)
 * Inputs: Timer Number
 * Output: the Error state of the function
 */

u8 TMR_u8EnableTimer(u8 Copy_u8TimerNumber)
{
    /* Local Variable holding the error state */
    u8 Local_u8Error = STATUS_OK;

    if (Copy_u8TimerNumber >= TMR_NO_OF_TIMERS)
    {
        Local_u8Error = STATUS_ERROR;
    }
    else
    {

        switch (Copy_u8TimerNumber)
        {
        case TMR_TIMER0:
        {
            TCCR0 = TMR_u8Timer0CtrlRegValue;
            break;
        }
        case TMR_TIMER1:
        {
            TCCR1B = TMR_u8Timer1CtrlRegValue;
            break;
        }
        case TMR_TIMER2:
        {
            TCCR2 = TMR_u8Timer2CtrlRegValue;
            break;
        }
        }
    }
    /* return the Error state of the function */
    return Local_u8Error;
}

/*
 * Description: Function to disable one of the available timers in AVR ATmega32 (0,1,2)
 * Inputs: Timer Number
 * Output: the Error state of the function
 */
u8 TMR_u8DisableTimer(u8 Copy_u8TimerNumber)
{
    /* Local Variable holding the error state */
    u8 Local_u8Error = STATUS_OK;

    if (Copy_u8TimerNumber >= TMR_NO_OF_TIMERS)
    {
        Local_u8Error = STATUS_ERROR;
    }
    else
    {
        switch (Copy_u8TimerNumber)
        {
        case TMR_TIMER0:
        {
            CLR_BIT(TCCR0, TCCR0_CS00);
            CLR_BIT(TCCR0, TCCR0_CS01);
            CLR_BIT(TCCR0, TCCR0_CS02);
            break;
        }
        case TMR_TIMER1:
        {
            CLR_BIT(TCCR1B, TCCR1B_CS10);
            CLR_BIT(TCCR1B, TCCR1B_CS11);
            CLR_BIT(TCCR1B, TCCR1B_CS12);
            break;
        }
        case TMR_TIMER2:
        {
            CLR_BIT(TCCR2, TCCR2_CS20);
            CLR_BIT(TCCR2, TCCR2_CS21);
            CLR_BIT(TCCR2, TCCR2_CS22);
            break;
        }
        }
    }
    /* return the Error state of the function */
    return Local_u8Error;
}

/*
 * Description: Function to set the duty cycle of the PWM signal generated from Timers(0,1,2)
 * Inputs: Timer Number and the desired duty cycle
 * Output: the Error state of the function
 */
u8 TMR_u8SetDutyCycle(u8 Copy_u8TimerNumber, u8 Copy_u8DutyCycle)
{
    /* Local Variable holding the error state */
    u8 Local_u8Error = STATUS_OK;

    if (Copy_u8TimerNumber >= TMR_NO_OF_TIMERS || Copy_u8DutyCycle > 100)
    {
        Local_u8Error = STATUS_ERROR;
    }
    else
    {

        u16 Local_u16CompareValue;

        switch (Copy_u8TimerNumber)
        {
        case TMR_TIMER0:
        {
            OCR0 = ((Copy_u8DutyCycle * (TMR_MAXVAL_TIMER02_REG - 1)) / 100);
            break;
        }
        case TMR_TIMER1:
        {
            Local_u16CompareValue = ((Copy_u8DutyCycle * (TMR_MAXVAL_TIMER1_REG - 1)) / 100);
            if (TMR_TIMER1A_COPT_STATE == TMR_ENABLE)
            {
                OCRA1 = Local_u16CompareValue;
            }
            if (TMR_TIMER1B_COPT_STATE == TMR_ENABLE)
            {
                OCRB1 = Local_u16CompareValue;
            }
            break;
        }
        case TMR_TIMER2:
        {
            OCR2 = ((Copy_u8DutyCycle * (TMR_MAXVAL_TIMER02_REG - 1)) / 100);
            break;
        }
        }
    }
    /* return the Error state of the function */
    return Local_u8Error;
}

/*
 * Description: Function to set the duty cycle of the PWM signal generated from Timer1,Pins OC1A or/and OC1B
 * (used mainly in servo interfacing and load which needs TMR_u8_FASTPWM_ICR1 timer mode)
 * Inputs: The desired timer compare value
 * Output: void
 */
void TMR_VidSetPWM(u16 Copy_u16ReqCompValue)
{
    if (TMR_TIMER1A_COPT_STATE == TMR_ENABLE)
    {
        if (TMR_TIMER1_COPT_MODE == TMR_CLEAR_OCX)
        {
            OCRA1 = Copy_u16ReqCompValue;
        }
        else if (TMR_TIMER1_COPT_MODE == TMR_SET_OCX)
        {
            OCRA1 = TMR_ICR1_VAL - Copy_u16ReqCompValue;
        }
    }
    if (TMR_TIMER1B_COPT_STATE == TMR_ENABLE)
    {
        if (TMR_TIMER1_COPT_MODE == TMR_CLEAR_OCX)
        {
            OCRB1 = Copy_u16ReqCompValue;
        }
        else if (TMR_TIMER1_COPT_MODE == TMR_SET_OCX)
        {
            OCRB1 = TMR_ICR1_VAL - Copy_u16ReqCompValue;
        }
    }
}

/*
 * Description: Function to set the delay time for the required timer
 * this function can be used for making delay (in case of Timer normal mode)
 * or for specifying a sampling time (in case of Timer CTC mode)
 * Inputs: the delay time in microsecond
 * Output: the Error state of the function
 */
u8 TMR_u8SetDesiredTime(u8 Copy_u8TimerNumber, u32 Copy_u32Time_us)
{
    /* Local Variable holding the error state */
    u8 Local_u8Error = STATUS_OK;

    f32 Local_f32TimerCtr;

    if (Copy_u8TimerNumber >= TMR_NO_OF_TIMERS)
    {
        Local_u8Error = STATUS_ERROR;
    }

    else
    {
        switch (Copy_u8TimerNumber)
        {
        case TMR_TIMER0:
        {
            Local_f32TimerCtr = ((Copy_u32Time_us) / TMR_TIMER0_TOVF);
            if (TMR_TIMER0_MODE == TMR_CTC)
            {
                TMR_VidSetTIMER0CTCTime(Local_f32TimerCtr);
            }
            else if (TMR_TIMER0_MODE == TMR_NORMAL)
            {
                TMR_VidSetTIMER0OVFTime(Local_f32TimerCtr);
            }
            break;
        }
        case TMR_TIMER1:
        {
            Local_f32TimerCtr = ((Copy_u32Time_us) / TMR_TIMER1_TOVF);
            if (TMR_TIMER1_MODE == TMR_CTC)
            {
                TMR_VidSetTIMER1CTCTime(Local_f32TimerCtr);
            }
            else if (TMR_TIMER1_MODE == TMR_NORMAL)
            {
                TMR_VidSetTIMER1OVFTime(Local_f32TimerCtr);
            }
            break;
        }
        case TMR_TIMER2:
        {
            Local_f32TimerCtr = ((Copy_u32Time_us) / TMR_TIMER2_TOVF);
            if (TMR_TIMER2_MODE == TMR_CTC)
            {
                TMR_VidSetTIMER2CTCTime(Local_f32TimerCtr);
            }
            else if (TMR_TIMER2_MODE == TMR_NORMAL)
            {
                TMR_VidSetTIMER2OVFTime(Local_f32TimerCtr);
            }
            break;
        }
        }
    }

    /* Function return Error state */
    return Local_u8Error;
}

/*
 * Description: Function to set the callback function for a certain timer in case of firing its interrupt
 * Inputs: the number of the available timer (0,1,2) and a pointer to its callback function
 * Output: the Error state of the function
 */
u8 TMR_u8SetCallBack(u8 Copy_u8TimerNumber, void (*Copy_PVCallBack)(void))
{
    /* Local Variable holding the error state */
    u8 Local_u8Error = STATUS_OK;

    if (Copy_u8TimerNumber >= TMR_NO_OF_TIMERS)
    {
        Local_u8Error = STATUS_ERROR;
    }
    else
    {
        TCNT0 = TMR_u32Timer0Preload;
        TCNT1 = TMR_u32Timer1Preload;
        TCNT2 = TMR_u32Timer2Preload;

        PVCallBack[Copy_u8TimerNumber] = Copy_PVCallBack;
    }
    /* Function return Error state */
    return Local_u8Error;
}

/*========================== Functions related to Input Capture Mode ==========================*/

/*
 * Description: Function to enable input capture interrupt
 * Inputs: void
 * Output: void
 */
void TMR_VidEnableIcuInterrupt(void)
{
    SET_BIT(TIMSK, TIMSK_TICIE1);
}

/*
 * Description: Function to disable input capture interrupt
 * Inputs: void
 * Output: void
 */
void TMR_VidDisableIcuInterrupt(void)
{
    CLR_BIT(TIMSK, TIMSK_TICIE1);
}

/*
 * Description: Function to get the Period of the signal received by the input capture pin ICP1 (D6)
 * Inputs: the container variable which will hold the value of the period
 * Output: the Error state of the function
 */
u8 TMR_u8GetPeriod(u16 *Copy_Pu16Period)
{
    /* Local Variable holding the error state */
    u8 Local_u8Error = STATUS_OK;
    if (Copy_Pu16Period == NULL)
    {
        Local_u8Error = STATUS_ERROR;
    }
    else
    {
        *Copy_Pu16Period = TMR_u16TotalTime * TMR_TIMER1_TICKTIME;
    }
    /* Function return Error state */
    return Local_u8Error;
}

/*
 * Description: Function to get the Duty Cycle of the signal received by the input capture pin ICP1 (D6)
 * Inputs: the container variable which will hold the value of the Duty Cycle
 * Output: the Error state of the function
 */
u8 TMR_u8GetDutyCycle(u16 *Copy_Pu16DutyCycle)
{

    /* Local Variable holding the error state */
    u8 Local_u8Error = STATUS_OK;
    if (Copy_Pu16DutyCycle == NULL)
    {
        Local_u8Error = STATUS_ERROR;
    }
    else
    {
        *Copy_Pu16DutyCycle = TMR_u16DutyCycle;
    }
    /* Function return Error state */
    return Local_u8Error;
}

/*
 * Description: Function to get the OnTime of the signal received by the input capture pin ICP1 (D6)
 * Inputs: the container variable which will hold the value of the OnTime
 * Output: the Error state of the function
 */
u8 TMR_u8OnTime(u16 *Copy_Pu16OnTime)
{
    /* Local Variable holding the error state */
    u8 Local_u8Error = STATUS_OK;
    if (Copy_Pu16OnTime == NULL)
    {
        Local_u8Error = STATUS_ERROR;
    }
    else
    {
        *Copy_Pu16OnTime = TMR_u16ONTime * TMR_TIMER1_TICKTIME;
    }
    /* Function return Error state */
    return Local_u8Error;
}

/*
 * Description: Function to get the OffTime of the signal received by the input capture pin ICP1 (D6)
 * Inputs: the container variable which will hold the value of the OffTime
 * Output: the Error state of the function
 */
u8 TMR_u8OffTime(u16 *Copy_Pu16OffTime)
{
    /* Local Variable holding the error state */
    u8 Local_u8Error = STATUS_OK;
    if (Copy_Pu16OffTime == NULL)
    {
        Local_u8Error = STATUS_ERROR;
    }
    else
    {
        *Copy_Pu16OffTime = (TMR_u16TotalTime - TMR_u16ONTime) * TMR_TIMER1_TICKTIME;
    }
    /* Function return Error state */
    return Local_u8Error;
}

/* ISR of Input Capture interrupts */
void __vector_6(void)
{
    static u8 Local_u8Flag = 0;
    static u16 Local_u16StartTime = 0;
    static u16 Local_u16StopTime = 0;

    if (Local_u8Flag == 0)
    {
        Local_u8Flag = 1;
        TMR_u16TotalTime = ICR1 - Local_u16StartTime;
        TMR_u16ONTime = Local_u16StopTime - Local_u16StartTime;
        Local_u16StartTime = ICR1;
        TMR_u16DutyCycle = ((TMR_u16ONTime * 100) / TMR_u16TotalTime);
        CLR_BIT(TCCR1B, TCCR1B_ICES1); /* Sense Falling Edge */
    }
    else
    {
        Local_u8Flag = 0;
        Local_u16StopTime = ICR1;
        SET_BIT(TCCR1B, TCCR1B_ICES1); /* Sense Raising Edge */
    }
}

/*========================== ISRs of Overflow timer interrupts ==========================*/

/* The ISR of Timer/Counter0 Overflow interrupt */
void __vector_11(void)
{
    if (PVCallBack[TMR_TIMER0] != NULL)
    {
        TMR_u32Timer0Cntr++;
        if (TMR_u32Timer0Cntr == TMR_u32ReqTimer0Cntr)
        {
            TMR_u32Timer0Cntr = 0;
            TCNT0 = TMR_u32Timer0Preload;
            PVCallBack[TMR_TIMER0](); /* The ISR action */
        }
    }
}

/* The ISR of Timer/Counter1 Overflow interrupt */
void __vector_9(void)
{
    if (PVCallBack[TMR_TIMER1] != NULL)
    {
        TMR_u32Timer1Cntr++;
        if (TMR_u32Timer1Cntr == TMR_u32ReqTimer1Cntr)
        {
            TMR_u32Timer1Cntr = 0;
            TCNT1H = TMR_u32Timer1Preload >> 8;
            TCNT1L = TMR_u32Timer1Preload;
            PVCallBack[TMR_TIMER1](); /* The ISR action */
        }
    }
}

/* The ISR of Timer/Counter2 Overflow interrupt */
void __vector_5(void)
{
    if (PVCallBack[TMR_TIMER2] != NULL)
    {
        TMR_u32Timer2Cntr++;
        if (TMR_u32Timer2Cntr == TMR_u32ReqTimer2Cntr)
        {
            TMR_u32Timer2Cntr = 0;
            TCNT2 = TMR_u32Timer2Preload;
            PVCallBack[TMR_TIMER2](); /* The ISR action */
        }
    }
}

/*========================== ISRs of Compare Match timer interrupts ==========================*/

/* The ISR of Timer/Counter0 Compare Match interrupt */
void __vector_10(void)
{
    if (PVCallBack[TMR_TIMER0] != NULL)
    {
        TMR_u32Timer0Cntr++;
        if (TMR_u32Timer0Cntr == TMR_u32ReqTimer0Cntr)
        {
            TMR_u32Timer0Cntr = 0;
            PVCallBack[TMR_TIMER0](); /* The ISR action */
        }
    }
}

/* The ISR of Timer/Counter1 Compare Match A interrupt */
void __vector_7(void)
{
    if (PVCallBack[TMR_TIMER1] != NULL)
    {
        TMR_u32Timer1Cntr++;
        if (TMR_u32Timer1Cntr == TMR_u32ReqTimer1Cntr)
        {
            TMR_u32Timer1Cntr = 0;
            PVCallBack[TMR_TIMER1](); /* The ISR action */
        }
    }
}

/* The ISR of Timer/Counter1 Compare Match B interrupt */
void __vector_8(void)
{
    if (PVCallBack[TMR_TIMER1] != NULL)
    {
        TMR_u32Timer1Cntr++;
        if (TMR_u32Timer1Cntr == TMR_u32ReqTimer1Cntr)
        {
            TMR_u32Timer1Cntr = 0;
            PVCallBack[TMR_TIMER1](); /* The ISR action */
        }
    }
}

/* The ISR of Timer/Counter2 Compare Match interrupt */
void __vector_4(void)
{
    if (PVCallBack[TMR_TIMER2] != NULL)
    {
        TMR_u32Timer2Cntr++;
        if (TMR_u32Timer2Cntr == TMR_u32ReqTimer2Cntr)
        {
            TMR_u32Timer2Cntr = 0;
            PVCallBack[TMR_TIMER2](); /* The ISR action */
        }
    }
}

/*========================== Static Functions to set the desired time needed in case of normal mode or CTC mode ==========================*/

static void TMR_VidSetTIMER0OVFTime(f32 Copy_f32TimerCtr)
{
    f32 Local_f32FractionCount;
    u32 Local_u32preload;
    if (Copy_f32TimerCtr == 1)
    {
        TMR_u32ReqTimer0Cntr = 1;
        TMR_u32Timer0Preload = 0;
        TCNT0 = 0;
    }
    else if (Copy_f32TimerCtr > 1)
    {
        if (Copy_f32TimerCtr - (u32)Copy_f32TimerCtr == 0) /* if integer */
        {
            TMR_u32ReqTimer0Cntr = Copy_f32TimerCtr;
            TMR_u32Timer0Preload = 0;
            TCNT0 = 0;
        }
        else /* if float */
        {
            Local_f32FractionCount = TMR_MAXVAL_TIMER02_REG * (Copy_f32TimerCtr - (u32)Copy_f32TimerCtr);
            Local_u32preload = TMR_MAXVAL_TIMER02_REG - Local_f32FractionCount;
            TMR_u32ReqTimer0Cntr = ((u32)Copy_f32TimerCtr) + 1;
            TMR_u32Timer0Preload = Local_u32preload;
            TCNT0 = Local_u32preload;
        }
    }
    else if (Copy_f32TimerCtr < 1)
    {
        Local_f32FractionCount = TMR_MAXVAL_TIMER02_REG * Copy_f32TimerCtr;
        Local_u32preload = TMR_MAXVAL_TIMER02_REG - Local_f32FractionCount;
        TMR_u32ReqTimer0Cntr = 1;
        TMR_u32Timer0Preload = Local_u32preload;
        TCNT0 = Local_u32preload;
    }
}

static void TMR_VidSetTIMER1OVFTime(f32 Copy_f32TimerCtr)
{
    f32 Local_f32FractionCount;
    u32 Local_u32preload;
    if (Copy_f32TimerCtr == 1)
    {
        TMR_u32ReqTimer1Cntr = 1;
        TMR_u32Timer1Preload = 0;
        TCNT1H = 0;
        TCNT1L = 0;
    }
    else if (Copy_f32TimerCtr > 1)
    {
        if (Copy_f32TimerCtr - (u32)Copy_f32TimerCtr == 0) /*if integer*/
        {
            TMR_u32ReqTimer1Cntr = (u32)Copy_f32TimerCtr;
            TMR_u32Timer1Preload = 0;
            TCNT1H = 0;
            TCNT1L = 0;
        }
        else /* if float */
        {
            Local_f32FractionCount = TMR_MAXVAL_TIMER1_REG * (Copy_f32TimerCtr - (u32)Copy_f32TimerCtr);
            Local_u32preload = TMR_MAXVAL_TIMER1_REG - Local_f32FractionCount;
            TMR_u32ReqTimer1Cntr = ((u32)Copy_f32TimerCtr) + 1;
            TMR_u32Timer1Preload = Local_u32preload;
            TCNT1H = Local_u32preload >> 8;
            TCNT1L = Local_u32preload;
        }
    }
    else if (Copy_f32TimerCtr < 1)
    {
        Local_f32FractionCount = TMR_MAXVAL_TIMER1_REG * Copy_f32TimerCtr;
        Local_u32preload = TMR_MAXVAL_TIMER1_REG - Local_f32FractionCount;
        TMR_u32ReqTimer1Cntr = 1;
        TMR_u32Timer1Preload = Local_u32preload;
        TCNT1H = Local_u32preload >> 8;
        TCNT1L = Local_u32preload;
    }
}

static void TMR_VidSetTIMER2OVFTime(f32 Copy_f32TimerCtr)
{
    f32 Local_f32FractionCount;
    u32 Local_u8preload;
    if (Copy_f32TimerCtr == 1)
    {
        TMR_u32ReqTimer2Cntr = 1;
        TMR_u32Timer2Preload = 0;
        TCNT2 = 0;
    }
    else if (Copy_f32TimerCtr > 1)
    {
        if ((Copy_f32TimerCtr - (u32)Copy_f32TimerCtr == 0)) /* if integer */
        {
            TMR_u32ReqTimer2Cntr = (u32)Copy_f32TimerCtr;
            TMR_u32Timer2Preload = 0;
            TCNT2 = 0;
        }
        else /* if float */
        {
            Local_f32FractionCount = TMR_MAXVAL_TIMER02_REG * (Copy_f32TimerCtr - (u32)Copy_f32TimerCtr);
            Local_u8preload = TMR_MAXVAL_TIMER02_REG - Local_f32FractionCount;
            TMR_u32ReqTimer2Cntr = ((u32)Copy_f32TimerCtr) + 1;
            TMR_u32Timer2Preload = Local_u8preload;
            TCNT2 = Local_u8preload;
        }
    }
    else if (Copy_f32TimerCtr < 1)
    {
        Local_f32FractionCount = TMR_MAXVAL_TIMER02_REG * Copy_f32TimerCtr;
        Local_u8preload = TMR_MAXVAL_TIMER02_REG - Local_f32FractionCount;
        TMR_u32ReqTimer2Cntr = 1;
        TMR_u32Timer2Preload = Local_u8preload;
        TCNT2 = Local_u8preload;
    }
}

static void TMR_VidSetTIMER0CTCTime(f32 Copy_f32TimerCtr)
{
    f32 Local_f32FractionCount;
    if (Copy_f32TimerCtr == 1)
    {
        TMR_u32ReqTimer0Cntr = 1;
        OCR0 = 0xff;
    }
    else if (Copy_f32TimerCtr > 1)
    {
        if (Copy_f32TimerCtr - (u32)Copy_f32TimerCtr == 0) /* if integer */
        {
            TMR_u32ReqTimer0Cntr = (u32)Copy_f32TimerCtr;
            OCR0 = 0xff;
        }
        else /* if float */
        {
            Local_f32FractionCount = TMR_MAXVAL_TIMER02_REG * (Copy_f32TimerCtr - (u32)Copy_f32TimerCtr);
            TMR_u32ReqTimer0Cntr = (u32)Copy_f32TimerCtr + 1;
            OCR0 = Local_f32FractionCount;
        }
    }
    else if (Copy_f32TimerCtr < 1)
    {
        Local_f32FractionCount = TMR_MAXVAL_TIMER02_REG * Copy_f32TimerCtr;
        TMR_u32ReqTimer0Cntr = 1;
        OCR0 = Local_f32FractionCount;
    }
}

static void TMR_VidSetTIMER1CTCTime(f32 Copy_f32TimerCtr)
{
    f32 Local_f32FractionCount;
    if (Copy_f32TimerCtr == 1)
    {
        TMR_u32ReqTimer1Cntr = 1;
        if (TMR_TIMER1A_COMP_STATE == TMR_ENABLE)
        {
            OCR1AL = 0xff;
            OCR1AH = 0xff;
        }
        if (TMR_TIMER1B_COMP_STATE == TMR_ENABLE)
        {
            OCR1BL = 0xff;
            OCR1BH = 0xff;
        }
    }
    else if (Copy_f32TimerCtr > 1)
    {
        if (Copy_f32TimerCtr - (u32)Copy_f32TimerCtr == 0) /* if integer */
        {
            TMR_u32ReqTimer1Cntr = (u32)Copy_f32TimerCtr;
            if (TMR_TIMER1A_COMP_STATE == TMR_ENABLE)
            {
                OCR1AL = 0xff;
                OCR1AH = 0xff;
            }
            if (TMR_TIMER1B_COMP_STATE == TMR_ENABLE)
            {
                OCR1BL = 0xff;
                OCR1BH = 0xff;
            }
        }
        else /* if float */
        {
            Local_f32FractionCount = TMR_MAXVAL_TIMER1_REG * (Copy_f32TimerCtr - Copy_f32TimerCtr);
            TMR_u32ReqTimer1Cntr = (u32)Copy_f32TimerCtr + 1;

            if (TMR_TIMER1A_COMP_STATE == TMR_ENABLE)
            {
                OCR1AL = Local_f32FractionCount;
                OCR1AH = (u32)Local_f32FractionCount >> 8;
            }
            if (TMR_TIMER1B_COMP_STATE == TMR_ENABLE)
            {
                OCR1BL = Local_f32FractionCount;
                OCR1BH = (u32)Local_f32FractionCount >> 8;
            }
        }
    }
    else if (Copy_f32TimerCtr < 1)
    {
        Local_f32FractionCount = TMR_MAXVAL_TIMER02_REG * Copy_f32TimerCtr;
        TMR_u32ReqTimer1Cntr = 1;
        if (TMR_TIMER1A_COMP_STATE == TMR_ENABLE)
        {
            OCR1AH = (u32)Local_f32FractionCount >> 8;
            OCR1AL = Local_f32FractionCount;
        }
        if (TMR_TIMER1B_COMP_STATE == TMR_ENABLE)
        {
            OCR1BH = (u32)Local_f32FractionCount >> 8;
            OCR1BL = Local_f32FractionCount;
        }
    }
}

static void TMR_VidSetTIMER2CTCTime(f32 Copy_f32TimerCtr)
{
    f32 Local_f32FractionCount;
    if (Copy_f32TimerCtr == 1)
    {
        TMR_u32ReqTimer2Cntr = 1;
        OCR2 = 0xff;
    }
    else if (Copy_f32TimerCtr > 1)
    {
        if (Copy_f32TimerCtr - (u32)Copy_f32TimerCtr == 0) /* if integer */
        {
            TMR_u32ReqTimer2Cntr = (u32)Copy_f32TimerCtr;
            OCR2 = 0xff;
        }
        else /* if float */
        {
            Local_f32FractionCount = TMR_MAXVAL_TIMER02_REG * (Copy_f32TimerCtr - (u32)Copy_f32TimerCtr);
            TMR_u32ReqTimer2Cntr = (u32)Copy_f32TimerCtr + 1;
            OCR2 = Local_f32FractionCount;
        }
    }
    else if (Copy_f32TimerCtr < 1)
    {
        Local_f32FractionCount = TMR_MAXVAL_TIMER02_REG * Copy_f32TimerCtr;
        TMR_u32ReqTimer2Cntr = 1;
        OCR2 = Local_f32FractionCount;
    }
}
