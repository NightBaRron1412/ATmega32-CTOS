#include "../Lib/Std_Types.h"
#include "../Lib/Bit_Math.h"
#include "TMR_private.h"
#include "TMR_interface.h"
#include "TMR_config.h"
#include "DIO_interface.h"

/*Static variables which save the value of TCCR register corresponding to each timer*/
static u8 TMR_u8Timer0CtrlRegValue;
static u8 TMR_u8Timer1CtrlRegValue;
static u8 TMR_u8Timer2CtrlRegValue;

/*Static variable needed in the ISR of each OVF timer interrupt*/
static u32 TMR_u32Timer0Counter = 0;
static u32 TMR_u32Timer1Counter = 0;
static u32 TMR_u32Timer2Counter = 0;

static u32 TMR_u32Timer0Preload = TMR_Timer0Preload;
static u32 TMR_u32Timer1Preload = TMR_Timer1Preload;
static u32 TMR_u32Timer2Preload = TMR_Timer2Preload;

static u32 TMR_u32ReqTimer0Cntr = TMR_ReqTimer0Cntr;
static u32 TMR_u32ReqTimer1Cntr = TMR_ReqTimer1Cntr;
static u32 TMR_u32ReqTimer2Cntr = TMR_ReqTimer2Cntr;

static u16 TMR_u16ONTime;
static u16 TMR_u16TotalTime;
static u16 TMR_u16DutyCycle;

static void (*PVCallBack[TMR_NO_OF_TIMERS])(void) = {NULL, NULL, NULL};

void TMR_VidInit()
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

        /* Checking the compare output mode applied on OC1A/OC1B pins in (CTC/FAST PWM/PHASE CORRECT) modes*/
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

void TMR_VidDisableTimer(u8 Copy_u8TimerNb)
{
    switch (Copy_u8TimerNb)
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

void TMR_VidEnableTimer(u8 Copy_u8TimerNb)
{
    switch (Copy_u8TimerNb)
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

void TMR_VidSetDutyCycle(u8 Copy_u8TimerNb, u8 Copy_u8DutyCycle)
{

    u16 Local_u16CompareValue;
    
    switch (Copy_u8TimerNb)
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

void TMR_VidSetCallBack(u8 Copy_u8TimerNb, void (*Copy_PVCallBack)(void))
{
    TCNT0 = TMR_u32Timer0Preload;
    TCNT1 = TMR_u32Timer1Preload;
    TCNT2 = TMR_u32Timer2Preload;

    PVCallBack[Copy_u8TimerNb] = Copy_PVCallBack;
    DIO_VidSetPinValue(Port_C, Pin_7, high);
}

/*-----------------------------Functions related to Input Capture Mode----------------------------------*/

void TMR_VidEnableIcuInterrupt()
{
    SET_BIT(TIMSK, TIMSK_TICIE1);
}

void TMR_VidDisbleIcuInterrupt()
{
    CLR_BIT(TIMSK, TIMSK_TICIE1);
}

u16 TMR_u16GetPeriod()
{
    return TMR_u16TotalTime * TMR_TIMER1_TICKTIME;
}

u16 TMR_u16GetDutyCycle()
{

    return TMR_u16DutyCycle;
}

u16 TMR_u16OnTime()
{

    return TMR_u16ONTime * TMR_TIMER1_TICKTIME;
}

u16 TMR_u16OffTime()
{

    return (TMR_u16TotalTime - TMR_u16ONTime) * TMR_TIMER1_TICKTIME;
}

/*ISR of Input Capture interrupts */
void __vector_6()
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
        CLR_BIT(TCCR1B, TCCR1B_ICES1); /*Sense Falling Edge */
    }
    else
    {
        Local_u8Flag = 0;
        Local_u16StopTime = ICR1;
        SET_BIT(TCCR1B, TCCR1B_ICES1); /* Sense Raising Edge */
    }
}

/*-----------------------------ISRs of Overflow timer interrupts----------------------------------*/

/*The ISR of Timer/Counter0 Overflow interrupt*/
void __vector_11()
{
    if (PVCallBack[TMR_TIMER0] != NULL)
    {
        TMR_u32Timer0Counter++;
        if (TMR_u32Timer0Counter == TMR_u32ReqTimer0Cntr)
        {
            TMR_u32Timer0Counter = 0;
            TCNT0 = TMR_u32Timer0Preload;
            PVCallBack[TMR_TIMER0](); /*The ISR action*/
        }
    }
}

/*The ISR of Timer/Counter1 Overflow interrupt*/
void __vector_9()
{
    if (PVCallBack[TMR_TIMER1] != NULL)
    {
        TMR_u32Timer1Counter++;
        if (TMR_u32Timer1Counter == TMR_u32ReqTimer1Cntr)
        {
            TMR_u32Timer1Counter = 0;
            TCNT1H = TMR_u32Timer1Preload >> 8;
            TCNT1L = TMR_u32Timer1Preload;
            PVCallBack[TMR_TIMER1](); /*The ISR action*/
        }
    }
    return;
}

/*The ISR of Timer/Counter2 Overflow interrupt*/
void __vector_5()
{
    if (PVCallBack[TMR_TIMER2] != NULL)
    {
        TMR_u32Timer2Counter++;
        if (TMR_u32Timer2Counter == TMR_u32ReqTimer2Cntr)
        {
            TMR_u32Timer2Counter = 0;
            TCNT2 = TMR_u32Timer2Preload;
            PVCallBack[TMR_TIMER2](); /*The ISR action*/
        }
    }
    return;
}

/*-----------------------------ISRs of Compare Match timer interrupts----------------------------------*/

/*The ISR of Timer/Counter0 Compare Match interrupt*/
void __vector_10()
{
    if (PVCallBack[TMR_TIMER0] != NULL)
    {
        TMR_u32Timer0Counter++;
        if (TMR_u32Timer0Counter == TMR_u32ReqTimer0Cntr)
        {
            TMR_u32Timer0Counter = 0;
            PVCallBack[TMR_TIMER0](); /*The ISR action*/
        }
    }
}

/*The ISR of Timer/Counter1 Compare Match A interrupt*/
void __vector_7()
{
    if (PVCallBack[TMR_TIMER1] != NULL)
    {
        TMR_u32Timer1Counter++;
        if (TMR_u32Timer1Counter == TMR_u32ReqTimer1Cntr)
        {
            TMR_u32Timer1Counter = 0;
            PVCallBack[TMR_TIMER1](); /*The ISR action*/
        }
    }
}

/*The ISR of Timer/Counter1 Compare Match B interrupt*/
void __vector_8()
{
    if (PVCallBack[TMR_TIMER1] != NULL)
    {
        TMR_u32Timer1Counter++;
        if (TMR_u32Timer1Counter == TMR_u32ReqTimer1Cntr)
        {
            TMR_u32Timer1Counter = 0;
            PVCallBack[TMR_TIMER1](); /*The ISR action*/
        }
    }
}

/*The ISR of Timer/Counter2 Compare Match interrupt*/
void __vector_4()
{
    if (PVCallBack[TMR_TIMER2] != NULL)
    {
        TMR_u32Timer2Counter++;
        if (TMR_u32Timer2Counter == TMR_u32ReqTimer2Cntr)
        {
            TMR_u32Timer2Counter = 0;
            PVCallBack[TMR_TIMER2](); /*The ISR action*/
        }
    }
}
