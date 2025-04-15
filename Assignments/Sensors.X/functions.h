#include <stdbool.h>
bool confirm;
int count;

void sevenDisp(void)
{
    switch(count)
    {
        case 0:
            PORTD=0x3F;
            break;
        case 1:
            PORTD=0x06;
            break;
        case 2:
            PORTD=0x5B;
            break;
        case 3:
            PORTD=0x4F;
            break;
        case 4:
            PORTD=0x66;
            break;
        case 5:
            PORTD=0x6D;
            break;
        case 6:
            PORTD=0x7D;
            break;
        case 7:
            PORTD=0x07;
            break;
        case 8:
            PORTD=0x7F;
            break;
        case 9:
            PORTD=0x6F;
            break;
    }
    return;
}

void input(void)
{
    while(confirm==false)
    {
        if(PORTAbits.RA0==1)
        {
            count++;
            sevenDisp();
            __delay_ms(750);
        }
        if(PORTBbits.RB1==1)
        {
            confirm=true;
        }
    }
    return;
}

void checkPassword(void)
{
    count=7;
    sevenDisp();
    if(password==code)
    {
        PORTAbits.RA5 = 1;                  
        __delay_ms(5000);
        PORTAbits.RA5 = 0;  
    }
    else
    {
        PORTBbits.RB2 = 1;
        __delay_ms(2000);
        PORTBbits.RB2 = 0;
    }
    return;
    
}

void __interrupt(irq(IRQ_INT0),base(0x3008)) INT0_ISR(void)
{
    if(PIR1bits.INT0IF == 1) 
    {          
        PORTBbits.RB2 = 1;
        __delay_ms(2000);
        PORTBbits.RB2 = 0;
    }
    PIR1bits.INT0IF = 0;                
    return;
}