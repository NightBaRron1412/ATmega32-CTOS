/** @file ADC_program.c
 *
 * @brief A program file including functions implementations to init and read ADC
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Dec 21, 2022
 *
 */

/*========================== Libraries Includes ==========================*/
#include "../Lib/Std_Types.h"
#include "../Lib/Bit_Math.h"
#include "DIO_interface.h"
#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"

/* pointer to the callback function which  which will run as ISR on ADC conversion complete */
static void (*PVCallBack)(void) = NULL;

/* static variable to hold the ADC value pointer */
static u16 *ADCValue = 0;

/*
 * Description: Function to initialize the ADC peripheral
 * Inputs: void
 * Output: void
 */
void ADC_VidInit(void)
{
#if (ADC_u8_INIT_STATE == ADC_u8_ENABLE)
    {
        /* Prescaler Selection */
        switch (ADC_PRESCALER)
        {
        case ADC_PRESCALER_2:
            CLR_BIT(ADCSRA, ADCSRA_ADPS0);
            CLR_BIT(ADCSRA, ADCSRA_ADPS1);
            CLR_BIT(ADCSRA, ADCSRA_ADPS2);
            break;

        case ADC_PRESCALER_4:
            CLR_BIT(ADCSRA, ADCSRA_ADPS0);
            SET_BIT(ADCSRA, ADCSRA_ADPS1);
            CLR_BIT(ADCSRA, ADCSRA_ADPS2);
            break;

        case ADC_PRESCALER_8:
            SET_BIT(ADCSRA, ADCSRA_ADPS0);
            SET_BIT(ADCSRA, ADCSRA_ADPS1);
            CLR_BIT(ADCSRA, ADCSRA_ADPS2);
            break;

        case ADC_PRESCALER_16:
            CLR_BIT(ADCSRA, ADCSRA_ADPS0);
            CLR_BIT(ADCSRA, ADCSRA_ADPS1);
            SET_BIT(ADCSRA, ADCSRA_ADPS2);
            break;

        case ADC_PRESCALER_32:
            SET_BIT(ADCSRA, ADCSRA_ADPS0);
            CLR_BIT(ADCSRA, ADCSRA_ADPS1);
            SET_BIT(ADCSRA, ADCSRA_ADPS2);
            break;

        case ADC_PRESCALER_64:
            SET_BIT(ADCSRA, ADCSRA_ADPS0);
            SET_BIT(ADCSRA, ADCSRA_ADPS1);
            CLR_BIT(ADCSRA, ADCSRA_ADPS2);
            break;

        case ADC_PRESCALER_128:
            CLR_BIT(ADCSRA, ADCSRA_ADPS0);
            SET_BIT(ADCSRA, ADCSRA_ADPS1);
            SET_BIT(ADCSRA, ADCSRA_ADPS2);
            break;
        }

        /* Voltage Reference Selection */
        switch (ADC_REFRENCE_SELECTION)
        {
        case ADC_AVCC:
            SET_BIT(ADMUX, ADMUX_REFS0);
            CLR_BIT(ADMUX, ADMUX_REFS1);
            break;

        case ADC_INTERNAL_VREF:
            SET_BIT(ADMUX, ADMUX_REFS0);
            SET_BIT(ADMUX, ADMUX_REFS1);
            break;

        case ADC_AREF:
            CLR_BIT(ADMUX, ADMUX_REFS0);
            CLR_BIT(ADMUX, ADMUX_REFS1);
            break;
        }

        /* ADC Adjustment */
        switch (ADC_ADJUSTMENT)
        {
        case ADC_RIGHT_ADJ:
            CLR_BIT(ADMUX, ADMUX_ADLAR);
            break;

        case ADC_LEFT_ADJ:
            SET_BIT(ADMUX, ADMUX_ADLAR);
            break;
        }

        /* Interrupt state */
        switch (ADC_INT_STATE)
        {
        case ADC_ENABLE:
            SET_BIT(ADCSRA, ADCSRA_ADIE);
            break;

        case ADC_DISABLE:
            CLR_BIT(ADCSRA, ADCSRA_ADIE);
            break;
        }

        /* Auto Trigger state */
        if (ADC_AUTO_TRIGGER_STATE == ADC_ENABLE)
        {
            SET_BIT(ADCSRA, ADCSRA_ADATE);

            /* Auto Trigger Source Selection */
            switch (ADC_AUTO_TRIGGER_SOURCE)
            {
            case ADC_ANALOG_COMPARATOR:
                SET_BIT(SFIOR, SFIOR_ADTS0);
                CLR_BIT(SFIOR, SFIOR_ADTS1);
                CLR_BIT(SFIOR, SFIOR_ADTS2);
                break;

            case ADC_EXTI0:
                SET_BIT(SFIOR, SFIOR_ADTS1);
                break;

            case ADC_TIMER0_COMPARE_MATCH:
                SET_BIT(SFIOR, SFIOR_ADTS0);
                SET_BIT(SFIOR, SFIOR_ADTS1);
                CLR_BIT(SFIOR, SFIOR_ADTS2);
                break;

            case ADC_TIMER0_OVERFLOW:
                CLR_BIT(SFIOR, SFIOR_ADTS0);
                CLR_BIT(SFIOR, SFIOR_ADTS1);
                SET_BIT(SFIOR, SFIOR_ADTS2);
                break;

            case ADC_TIMER_COMPARE_MATCH_B:
                SET_BIT(SFIOR, SFIOR_ADTS0);
                CLR_BIT(SFIOR, SFIOR_ADTS1);
                SET_BIT(SFIOR, SFIOR_ADTS2);
                break;

            case ADC_TIMER1_OVERFLOW:
                CLR_BIT(SFIOR, SFIOR_ADTS0);
                SET_BIT(SFIOR, SFIOR_ADTS1);
                SET_BIT(SFIOR, SFIOR_ADTS2);
                break;

            case ADC_TIMER1_CAPTURE_EVENT:
                SET_BIT(SFIOR, SFIOR_ADTS0);
                SET_BIT(SFIOR, SFIOR_ADTS1);
                SET_BIT(SFIOR, SFIOR_ADTS2);
                break;
            }
        }

        SET_BIT(ADCSRA, ADCSRA_ADEN);
    }

#endif
}

/*
 * Description: Function to get the ADC value from the required ADC channel using ISR method
 * Inputs: ADC channel number and the Pointer to the variable supposed to hold the ADC variable
 * Output: the Error state of the function
 */
u8 ADC_u8ReadBlocking(u8 Copy_u8Channel, u16 *Copy_Pu16ADCValue)
{
    /* Local Variable to hold the Error State */
    u8 Local_u8ErrorState = STATUS_OK;

    if (Copy_u8Channel <= A7 && Copy_Pu16ADCValue != NULL)
    {
        /* Select the required channel by setting the four bits in ADMUX */
        ADMUX = (ADMUX & 0xF0) | (Copy_u8Channel);

        /* Start Conversion by setting ADSC bit */
        SET_BIT(ADCSRA, ADCSRA_ADSC);

        /* turn off ADC interrupt */
        CLR_BIT(ADCSRA, ADCSRA_ADIE);

        /* Wait until the conversion is complete ADIF becomes 1 */
        while (GET_BIT(ADCSRA, ADCSRA_ADIF) == LOW)
            ;

        /* Clear ADIF by writing one to it */
        SET_BIT(ADCSRA, ADCSRA_ADIF);

        if (ADC_INT_STATE == ADC_ENABLE)
        {
            /* Re-enable ADC interrupt */
            SET_BIT(ADCSRA, ADCSRA_ADIE);
        }

        /* Read the ADC value from the ADC Data Register */
        if (ADC_READING_RESOLUTION == ADC_8BITS)
        {
            *Copy_Pu16ADCValue = ADCH;
        }
        else if (ADC_READING_RESOLUTION == ADC_10BITS)
        {
            *Copy_Pu16ADCValue = ADCVAL_10BITS;
        }
    }
    else
    {
        Local_u8ErrorState = STATUS_ERROR;
    }

    /* Return the Error State */
    return Local_u8ErrorState;
}

/*
 * Description: Function to get the ADC value from the required ADC channel using ISR method
 * Inputs: ADC channel number and the Pointer to the variable supposed to hold the ADC variable
 * Output: the Error state of the function
 */
u8 ADC_u8ReadNonBlocking(u8 Copy_u8Channel, u16 *Copy_Pu16ADCValue)
{
    /* Local Variable to hold the Error State */
    u8 Local_u8ErrorState = STATUS_OK;

    if (Copy_u8Channel <= A7 && Copy_Pu16ADCValue != NULL)
    {
        /* Copy pointer to global variable for use in ISR */
        ADCValue = Copy_Pu16ADCValue;

        /* Select the required channel by setting the four bits in ADMUX */
        ADMUX = (ADMUX & 0xF0) | (Copy_u8Channel);

        /* Start Conversion by setting ADSC bit */
        SET_BIT(ADCSRA, ADCSRA_ADSC);
    }
    else
    {
        Local_u8ErrorState = STATUS_ERROR;
    }

    /* Return the Error State */
    return Local_u8ErrorState;
}

/*
 * Description: Function to set the callback function which will run as ISR on ADC conversion complete
 * Inputs: a pointer to the callback function
 * Output: the Error state of the function
 */
u8 ADC_u8SetCallBack(void (*Copy_PVCallBack)(void))
{
    /* Local Variable to hold the Error State */
    u8 Local_u8ErrorState = STATUS_OK;

    if (Copy_PVCallBack != NULL)
    {
        /* Save the address of the Call Back function in a global variable */
        PVCallBack = Copy_PVCallBack;
    }
    else
    {
        Local_u8ErrorState = STATUS_ERROR;
    }

    /* Return the Error State */
    return Local_u8ErrorState;
}

/*========================== ADC ISR ==========================*/
void __vector_16(void)
{
    /* Read the ADC value from the ADC Data Register */
    if (ADC_READING_RESOLUTION == ADC_8BITS)
    {
        ADCValue = ADCH;
    }
    else if (ADC_READING_RESOLUTION == ADC_10BITS)
    {
        ADCValue = ADCVAL_10BITS;
    }

    /* Call the Call Back function in the application after completion of the ADC conversion */
    if (PVCallBack != NULL)
    {
        PVCallBack();
    }
}
