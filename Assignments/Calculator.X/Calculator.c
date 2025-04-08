//-----------------------------
// Title: Calculator
//-----------------------------
// Purpose: to function as a basic calculator
// Dependencies: NONE
// Compiler: XC8 (v3.0)
// Author: Logan Cacy
// OUTPUTS: PORTD, RB0-3
// INPUTS: RB4-7
// Versions:
//  	V6.2: 4/7/2025 - First version 
//-----------------------------

// PIC18F46K42 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1L
#pragma config FEXTOSC = LP     // External Oscillator Selection (LP (crystal oscillator) optimized for 32.768 kHz; PFM set to low power)
#pragma config RSTOSC = EXTOSC  // Reset Oscillator Selection (EXTOSC operating per FEXTOSC bits (device manufacturing default))

// CONFIG1H
#pragma config CLKOUTEN = OFF   // Clock out Enable bit (CLKOUT function is disabled)
#pragma config PR1WAY = ON      // PRLOCKED One-Way Set Enable bit (PRLOCK bit can be cleared and set only once)
#pragma config CSWEN = ON       // Clock Switch Enable bit (Writing to NOSC and NDIV is allowed)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor enabled)

// CONFIG2L
#pragma config MCLRE = EXTMCLR  // MCLR Enable bit (If LVP = 0, MCLR pin is MCLR; If LVP = 1, RE3 pin function is MCLR )
#pragma config PWRTS = PWRT_OFF // Power-up timer selection bits (PWRT is disabled)
#pragma config MVECEN = ON      // Multi-vector enable bit (Multi-vector enabled, Vector table used for interrupts)
#pragma config IVT1WAY = ON     // IVTLOCK bit One-way set enable bit (IVTLOCK bit can be cleared and set only once)
#pragma config LPBOREN = OFF    // Low Power BOR Enable bit (ULPBOR disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled , SBOREN bit is ignored)

// CONFIG2H
#pragma config BORV = VBOR_2P45 // Brown-out Reset Voltage Selection bits (Brown-out Reset Voltage (VBOR) set to 2.45V)
#pragma config ZCD = OFF        // ZCD Disable bit (ZCD disabled. ZCD can be enabled by setting the ZCDSEN bit of ZCDCON)
#pragma config PPS1WAY = ON     // PPSLOCK bit One-Way Set Enable bit (PPSLOCK bit can be cleared and set only once; PPS registers remain locked after one clear/set cycle)
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config DEBUG = OFF      // Debugger Enable bit (Background debugger disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Extended Instruction Set and Indexed Addressing Mode disabled)

// CONFIG3L
#pragma config WDTCPS = WDTCPS_31// WDT Period selection bits (Divider ratio 1:65536; software control of WDTPS)
#pragma config WDTE = OFF       // WDT operating mode (WDT Disabled; SWDTEN is ignored)

// CONFIG3H
#pragma config WDTCWS = WDTCWS_7// WDT Window Select bits (window always open (100%); software control; keyed access not required)
#pragma config WDTCCS = SC      // WDT input clock selector (Software Control)

// CONFIG4L
#pragma config BBSIZE = BBSIZE_512// Boot Block Size selection bits (Boot Block size is 512 words)
#pragma config BBEN = OFF       // Boot Block enable bit (Boot block disabled)
#pragma config SAFEN = OFF      // Storage Area Flash enable bit (SAF disabled)
#pragma config WRTAPP = OFF     // Application Block write protection bit (Application Block not write protected)

// CONFIG4H
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block not write-protected)
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)
#pragma config WRTSAF = OFF     // SAF Write protection bit (SAF not Write Protected)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (Low voltage programming enabled. MCLR/VPP pin function is MCLR. MCLRE configuration bit is ignored)

// CONFIG5L
#pragma config CP = OFF         // PFM and Data EEPROM Code Protection bit (PFM and Data EEPROM code protection disabled)

#include <xc.h> // must have this
#include <stdbool.h>
//#include "../../../../../Program Files/Microchip/xc8/v2.40/pic/include/proc/pic18f46k42.h"
//#include "C:/Program Files/Microchip/xc8/v3.00/pic/include/proc/pic18f47k42.h"
//#include "C:\Program Files\Microchip\xc8\v3.00\pic\include\proc\pic18f47k42"

#define _XTAL_FREQ 4000000                 // Fosc  frequency for _delay()  library
#define FCY    _XTAL_FREQ/4

const int digits=2; //how many digits for inputs

int x_in;
int y_in;
int x;

int opperation;
int display;
int x_count=0;
int y_count=0;
int output;
bool opp=false;

int Input_num();
int Input_opp();
int Input_disp();
void wait(int x);
void equals();
void clear();
void MSDelay (unsigned int itimel, unsigned int itime2);

void MSDelay (unsigned int itimel, unsigned int itime2)
{
unsigned int i; unsigned int j;
for (i=0; i<itimel; i++) // should be able to see itime as a variable
for (j=0; j<itime2; j++);
}

void clear() //clears values
{
    opp=false; 
    opperation=0;
    x_count=0;
    y_count=0;
    x_in=0;
    y_in=0;
    PORTD=0;
    //MSDelay(5,5);
}

void equals()
{
    switch(opperation)
        {
            case 1:
                output=x_in+y_in;
                break;
            case 2:
                output=x_in-y_in;
                break;
            case 3:
                output=x_in*y_in;
                break;
            case 4:
                output=x_in/y_in;
                break;
        }    
        PORTD=output;
        return;
}

void wait(int x) //waits until the pressed number in no longer pressed
{
    switch(x)
    {
        case 1:
        {
            while(1)
            {
            PORTB=8;
            if(PORTBbits.RB7==0)
                return;
            }
        }
        case 2:
        {
            while(1)
            {
            PORTB=4;
            if(PORTBbits.RB7==0)
                return;
            }
        }
        case 3:
        {
            while(1)
            {
            PORTB=2;
            if(PORTBbits.RB7==0)
                return;
            }
        }
        case 4:
        {
            PORTB=8;
            if(PORTBbits.RB6==0)
                return;
        }
        case 5:
        {
            while(1)
            {
            PORTB=4;
            if(PORTBbits.RB6==0)
                return;
            }
        }
        case 6:
        {
            while(1)
            {
            PORTB=2;
            if(PORTBbits.RB6==0)
                return;
            }
        }
        case 7:
        {
            while(1)
            {
            PORTB=8;
            if(PORTBbits.RB5==0)
                return;
            }
        }
        case 8:
        {
            while(1)
            {
            PORTB=4;
            if(PORTBbits.RB5==0)
                return;
            }
        }
        case 9:
        {
            while(1)
            {
            PORTB=2;
            if(PORTBbits.RB5==0)
                return;
            }
        }
        case 0:
        {
            while(1)
            {
            PORTB=4;
            if(PORTBbits.RB4==0)
                return;
            }
        }
    }
}


int Input_disp() //gets equals or clear
{
    int d=0;
    PORTB=2;
    if (PORTBbits.RB4==1) // =
        d=1;
    PORTB=8;
    if (PORTBbits.RB4==1) // clear
        d=2;
    return d;
}

int Input_opp() //gets operation
{
    int o=0;
    PORTB=1;
    if (PORTBbits.RB4==1) //divide
        o=4;
    else if(PORTBbits.RB5==1) //multiply
        o=3;
    else if(PORTBbits.RB6==1) //subtract
        o=2;
    else if(PORTBbits.RB7==1) //add
        o=1;
    return o;
}

int Input_num() //gets number
{
    int x=-1; //default to show no user input
    PORTB=2;
    if (PORTBbits.RB5==1)
        x=9;
    else if(PORTBbits.RB6==1)
        x=6;
    else if(PORTBbits.RB7==1)
        x=3;
    PORTB=4;
    if (PORTBbits.RB4==1)
        x=0;
    else if(PORTBbits.RB5==1)
        x=8;
    else if(PORTBbits.RB6==1)
        x=5;
    else if(PORTBbits.RB7==1)
        x=2;
     PORTB=8;
    if (PORTBbits.RB5==1)
        x=7;
    else if(PORTBbits.RB6==1)
        x=4;
    else if(PORTBbits.RB7==1)
        x=1;
    return x;
}


int main(void)
{
    
    PORTB=0; //sets up ports
    LATB=0;
    ANSELB=0;
    TRISB=240;
    PORTD=0;
    LATD=0;
    ANSELD=0;
    TRISD=0;
    
    while(1) //runs forever
    {
    if(opp==false && x_count<digits) //gets x input
    {
        x=Input_num();
        if (x!=-1)
        {
            x_in= x_in*10+x;
            x_count++;
            MSDelay(1000, 50);
            wait(x);
        }
        if (x_count>=digits)
            PORTD=1;
    }
    if (opperation == 0) //gets operation input
        opperation=Input_opp();
    if(opperation!=0)
        opp=true;
    if(opp==true && y_count<digits) //gets y input
    {
        x=Input_num();
        if (x!=-1)
        {
            y_in= y_in*10+x;
            y_count++;
            MSDelay(1000, 50);
            wait(x);
        }
        if(y_count>=digits)
            PORTD=2;
    }
    display=Input_disp(); //gets display input
    if(display==1)
    {
        equals();
        //clear();
    }
    if(display==2) //clears values if clear is pressed
    {
        clear();
    }
    }
    
}