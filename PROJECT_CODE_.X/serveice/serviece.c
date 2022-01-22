/*
 * surviece.c
 *
 * Created: 1/26/2021 2:24:41 PM
 *  Author: Mohamed_Arafa
 */ 
#include "serviece.h"

void int_to_str(u16 temp ,u8 *str,u8 str_size){
	u8 i;
	for (i=0;i<str_size;i++)
	{
		int num;
		num=temp%10;
		str[str_size-i-1]=num+48;
		temp/=10;
	}
    str[i]=0;
}