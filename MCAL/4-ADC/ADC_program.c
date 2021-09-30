#include "../Lib/Std_Types.h"
#include "../Lib/Bit_Math.h"
#include "DIO_interface.h"
#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"

void ADC_VidInit(void)
{
//Select refernce
#if ADC_REFRENCE_SELECTION == ADC_AREF_INTERNAL_OFF

    CLR_BIT(ADMUX, ADMUX_REFS0);
    CLR_BIT(ADMUX, ADMUX_REFS1);

#elif ADC_REFRENCE_SELECTION == ADC_AVCC_EXTCAP_AREF

    SET_BIT(ADMUX, ADMUX_REFS0);
    CLR_BIT(ADMUX, ADMUX_REFS1);

#elif ADC_REFRENCE_SELECTION == ADC_INTERNAL_EXTCAP_AREF

    SET_BIT(ADMUX, ADMUX_REFS0);
    SET_BIT(ADMUX, ADMUX_REFS1);

#else

#error No Refernce selected, kindly take a look at Config File.

#endif

    //Resolution selection

#if ADC_READING_RESOLUTION == ADC_10_BIT

    CLR_BIT(ADMUX, ADMUX_ADLAR);

#elif ADC_READING_RESOLUTION == ADC_8_BIT

    SET_BIT(ADMUX, ADMUX_ADLAR);

#else

#error No Resolution selected, kindly take a look at Config File.

#endif

//Select 128 prescalar
#if ADC_PRESCALER == ADC_PRESCALER_2

    CLR_BIT(ADCSRA, ADCSRA_ADPS0);
    CLR_BIT(ADCSRA, ADCSRA_ADPS1);
    CLR_BIT(ADCSRA, ADCSRA_ADPS2);

#elif ADC_PRESCALER == ADC_PRESCALER_4

    CLR_BIT(ADCSRA, ADCSRA_ADPS0);
    SET_BIT(ADCSRA, ADCSRA_ADPS1);
    CLR_BIT(ADCSRA, ADCSRA_ADPS2);

#elif ADC_PRESCALER == ADC_PRESCALER_8

    SET_BIT(ADCSRA, ADCSRA_ADPS0);
    SET_BIT(ADCSRA, ADCSRA_ADPS1);
    CLR_BIT(ADCSRA, ADCSRA_ADPS2);

#elif ADC_PRESCALER == ADC_PRESCALER_16

    CLR_BIT(ADCSRA, ADCSRA_ADPS0);
    CLR_BIT(ADCSRA, ADCSRA_ADPS1);
    SET_BIT(ADCSRA, ADCSRA_ADPS2);

#elif ADC_PRESCALER == ADC_PRESCALER_32

    SET_BIT(ADCSRA, ADCSRA_ADPS0);
    CLR_BIT(ADCSRA, ADCSRA_ADPS1);
    SET_BIT(ADCSRA, ADCSRA_ADPS2);

#elif ADC_PRESCALER == ADC_PRESCALER_64

    CLR_BIT(ADCSRA, ADCSRA_ADPS0);
    SET_BIT(ADCSRA, ADCSRA_ADPS1);
    SET_BIT(ADCSRA, ADCSRA_ADPS2);

#elif ADC_PRESCALER == ADC_PRESCALER_128

    SET_BIT(ADCSRA, ADCSRA_ADPS0);
    SET_BIT(ADCSRA, ADCSRA_ADPS1);
    SET_BIT(ADCSRA, ADCSRA_ADPS2);

#else

#error No prescalar selected, kindly take a look at Config File.

#endif

    //Enable ADC
    SET_BIT(ADCSRA, ADCSRA_ADEN);

    //Clear Interrupt Flag
    SET_BIT(ADCSRA, ADCSRA_ADIF);
}

u16 ADC_u16Read(u8 Copy_u8Channel)
{
    ADMUX &= 0b11110000;
    ADMUX = ADMUX | Copy_u8Channel;
    //Start conversion
    SET_BIT(ADCSRA, ADCSRA_ADSC);

    //Poll the ADC until the value is ready
    while (GET_BIT(ADCSRA, ADCSRA_ADIF) == low)
        ;

    //Clear interrupt flag
    SET_BIT(ADCSRA, ADCSRA_ADIF);

#if ADC_READING_RESOLUTION == ADC_10_BIT

    u16 lowerbyte, result;

    lowerbyte = ADCL;
    result = ADCH * 256;
    result += lowerbyte;
    return (result);

#elif ADC_READING_RESOLUTION == ADC_8_BIT

    return (ADCH);

#else

#error No Resolution selected, kindly take a look at Config File.

#endif
}