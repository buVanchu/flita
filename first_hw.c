#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#define bit_in_byte 8
int main(){
    int numb = 0;
    char simb;
    int max = 0;;
    bool sign = false;
    while(((simb = getchar()) != EOF) && (max <= sizeof(int)*bit_in_byte))
    {
        max++;
        if(simb == '-'){
            sign = true;
        }
        else
        {   
            if((simb == '0')||(simb == '1')){
                numb <<= 1;
                if(simb !='0')
                {
                    numb++;
                }
            }
            else {
                exit(-1);
            }
        }
    }
    if (sign == true)
    {
        numb = -numb;
    }
 	printf("%d\n",numb);
 }