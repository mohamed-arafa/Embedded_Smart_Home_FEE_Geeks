
#ifndef _MACROS_H
#define _MACROS_H

#define SET_BIT(REG,BIT)        (REG)|=(0X01<<(BIT))
#define CLR_BIT(REG,BIT)        (REG)&=~(0X01<<(BIT))
#define TGL_BIT(REG,BIT)        (REG)^=(0X01<<(BIT))
#define GET_BIT(REG,BIT)        ((REG)>>(BIT))&(0X01)

#define SET_HIGH_NIPPLE(REG) 	(REG)|=(0XF0)
#define CLR_HIGH_NIPPLE(REG) 	(REG)&=~(0XF0)

#define WRT_HIGH_NIPPLE(REG,VALUE) 	REG=((REG)&0X0F)|(VALUE&0xf0) 	
#define WRT_LOW_NIPPLE(REG,VALUE) 	REG=((REG)&0XF0)|(VALUE)

#define SET_LOW_NIPPLE(REG) 	(REG)|=(0X0F)
#define CLR_LOW_NIPPLE(REG) 	(REG)&=~(0X0F)

#define SET_BITS_MASK(REG,VALUE)(REG)|=(VALUE)
#define CLR_BITS_MASK(REG,MASK) (REG)&=~(MASK)
#define WRT_REG(REG,VALUE)		(REG)=(VALUE)



#endif
