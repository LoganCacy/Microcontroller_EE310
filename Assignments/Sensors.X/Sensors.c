void initialize(void);
void checkPassword(void);
void sevenDisp(void);
void input(void);

int password;
int count;
int code;

#include <stdbool.h>
#include <xc.h>
#include "myConfigFile.h"
#include "initialize.h"
#include "functions.h"

bool confirm;

void main(void) 
{
    while(1)
    {
    initialize();               
    sevenDisp();
    while (confirm == false)      
        input();            
    __delay_ms(500);
    password = count * 10;       
    confirm = false;              
    count = 0;
    sevenDisp();                    
    while (confirm == false)      
        input();            
    __delay_ms(500);
    password = password+count;
    checkPassword();               
    }
}