#include "ADC_Function.h"

//volatile u16 ADC_INT_Result = 0;
volatile u16 ADC_result ;
void init_ADC(PRESCALER_t div, VOLTAGE_REFERENCE_t vref, CHANNEL_t channel) {

    // Make PORTA INPUT
    //DDRA = 0;
    CLR_BIT(DDRA, channel);
    // Enable ADC & Setting Prescaler 
    CLR_BITS_MASK(ADCSRA, 0x07);
    SET_BITS_MASK(ADCSRA, div);
    SET_BIT(ADCSRA, ADEN);

    // Voltage Reference 
    switch (vref) {
        case AREF:
            CLR_BIT(ADMUX, REFS0);
            CLR_BIT(ADMUX, REFS1);
            break;

        case AVCC:
            SET_BIT(ADMUX, REFS0);
            CLR_BIT(ADMUX, REFS1);
            break;

        case AREF2v56:
            SET_BIT(ADMUX, REFS0);
            SET_BIT(ADMUX, REFS1);
            break;

        default:
            break;
    }
    ADMUX &= 0xF0; //Clear the older channel that was read
    // Choose ADC channel
    SET_BITS_MASK(ADMUX, channel);
    // Enable ADC interrupt 
    //SET_BIT(ADCSRA, ADIE);
}

u16 read_ADC() {
    volatile u16 ADC_Result; // ADC result
    SET_BIT(ADCSRA, ADSC); // Start ADC 
    while (!GET_BIT(ADCSRA, ADIF)); // Wait for the conversion to finish
    ADC_Result = ADCL; // Get Low Output to PORTB
    ADC_Result |= (ADCH << 8); // Get High Output to PORTD
    return ADC_Result;
}

/*u16 read_INT_ADC() {
    
    SET_BIT(ADCSRA, ADSC); // Start ADC 
    return ADC_INT_Result;
}

ISR(ADC_vect) {
    ADC_INT_Result = ADCL;
    ADC_INT_Result |= (ADCH << 8);
}*/

u16 TEMP_read_ADC() {
    ADC_result = read_ADC();
    return (int) ADC_result/2.057;
}