
#ifndef ADC_FUNCTION_MAZIDI_H
#define	ADC_FUNCTION_MAZIDI_H

#include "../MEM_MAP_AT32/MACROS.h"
#include "../MEM_MAP_AT32/Mem_map32.h"
#include "../HELPERS/STD_TYPES.h"
//#include "../MEM_MAP_AT32/Mem_map32.h"

/********ADCSRA_BITS*********/

#define ADEN  7
#define ADSC  6
#define ADATE 5
#define ADIF  4
#define ADIE  3
#define ADPS2 2
#define ADPS1 1
#define ADPS0 0

/********ADMUX_BITS*********/
#define REFS1  7
#define REFS0  6
#define ADLAR  5
#define MUX4   4
#define MUX3   3
#define MUX2   2
#define MUX1   1
#define MUX0   0

/*************************/

typedef enum {
    DIV_2,
    DIV_2_2,
    DIV_4,
    DIV_8,
    DIV_16,
    DIV_32,
    DIV_64,
    DIV_128
} PRESCALER_t;

typedef enum {
    AREF,
    AVCC,
    AREF2v56
} VOLTAGE_REFERENCE_t;

typedef enum {
    ADC0,
    ADC1,
    ADC2,
    ADC3,
    ADC4,
    ADC5,
    ADC6,
    ADC7
} CHANNEL_t;


void init_ADC(PRESCALER_t div, VOLTAGE_REFERENCE_t vref, CHANNEL_t channel);
u16 read_ADC();
//u16 read_INT_ADC();
u16 TEMP_read_ADC();


#endif	/* ADC_FUNCTION_MAZIDI_H */

