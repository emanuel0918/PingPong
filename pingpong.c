/*****************************************************
This program was produced by the
CodeWizardAVR V2.05.0 Professional
Automatic Program Generator
© Copyright 1998-2010 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 09/07/2020
Author  : NeVaDa
Company : 
Comments: 


Chip type               : ATmega8535
Program type            : Application
AVR Core Clock frequency: 1.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 128
*****************************************************/

#include <mega8535.h>
#include <delay.h>
#define b11 PINA.2 //barra de jugador 1 para ir a la izquierda
#define b12 PINA.3 //barra de jugador 1 para ir a la derecha
#define b21 PINA.0 //barra de jugador 2 para ir a la izquierda
#define b22 PINA.1 //barra de jugador 2 para ir a la derecha
//#define TAM_MAXIMO 8
// Declare your global variables here
const char tabla7segmentos[10]={0x02,0x9e,0x24,0x0c,0x98,0x48,0x40,0x1e,0x00,0x08};
//
int TAM_MAXIMO_x;
int TAM_MAXIMO_y;
int barra_espacioMax;
int boton_antiRebote;
//
eeprom short random;
//
int direccion;
int rand;
int x;
int y;
//Para prender toda la pantalla se deben prender
// individualmente las columnas
int cols;
int print_cols;
int state;
int stay;
int rapidez;
//
int n;
int i;
int aux1;
//char hx1,hx2;
char print_matrix1,print_matrix2;
int c;
int display;
int barra1,barra2;
int puntos1,puntos2;
int win;
int antir1,antir2,antir3,antir4;
//
void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
// Func7=Out Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=0 State6=P State5=P State4=P State3=P State2=P State1=P State0=P 
PORTA=0x7F;
DDRA=0x80;

// Port B initialization
// Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out 
// State7=0 State6=0 State5=0 State4=0 State3=0 State2=0 State1=0 State0=0 
PORTB=0x00;
DDRB=0xFF;

// Port C initialization
// Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out 
// State7=0 State6=1 State5=0 State4=0 State3=0 State2=0 State1=0 State0=0 
PORTC=0x40;
DDRC=0xFF;

// Port D initialization
// Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out 
// State7=0 State6=0 State5=0 State4=0 State3=0 State2=0 State1=0 State0=0 
PORTD=0x00;
DDRD=0xFF;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=0xFF
// OC0 output: Disconnected
TCCR0=0x00;
TCNT0=0x00;
OCR0=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer1 Stopped
// Mode: Normal top=0xFFFF
// OC1A output: Discon.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=0x00;
TCCR1B=0x00;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: Timer2 Stopped
// Mode: Normal top=0xFF
// OC2 output: Disconnected
ASSR=0x00;
TCCR2=0x00;
TCNT2=0x00;
OCR2=0x00;

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// INT2: Off
MCUCR=0x00;
MCUCSR=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x00;

// USART initialization
// USART disabled
UCSRB=0x00;

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
SFIOR=0x00;

// ADC initialization
// ADC disabled
ADCSRA=0x00;

// SPI initialization
// SPI disabled
SPCR=0x00;

// TWI initialization
// TWI disabled
TWCR=0x00;
//CONSTANTS
TAM_MAXIMO_x=8;
TAM_MAXIMO_y=8;
barra_espacioMax=TAM_MAXIMO_x-2;
boton_antiRebote=100;
//Generar numero random
if(random<1){
    random=1;
}
//multiplicar por numero primo
random=(random*7)+2;
random=random%17;
//definir direccion
rand=(int)random;
rand*=7;
direccion=rand%4;
//definir x
x=TAM_MAXIMO_x/2;
//definir y
y=TAM_MAXIMO_y/2;
//
cols=0;
stay=1;
state=0;
rapidez=TAM_MAXIMO_y*30;
//
display=0;
barra1=TAM_MAXIMO_x/2;
barra1--;
barra2=TAM_MAXIMO_x/2;
barra2--;
puntos1=0;
puntos2=0;
win=0;
antir1=0;
antir2=0;
antir3=0;
antir4=0;
c=0;
i=0;
while (1)
      {
        // Place your code here
        //
        delay_ms(1);
        //
        //MOVIMIENTO DE LOS CONTROLES
        if(b11==0){
            if(win){
                //empezar juego si se ha acabado previamente
                win=0;
                puntos1=0;
                puntos2=0;
            }
            //boton de jugador 1 para ir a la izquierda
            antir1++;
            if(antir1>=boton_antiRebote){
                //resetear el lag del boton
                antir1=0;
                antir2=0;
                //resetear el lag del boton
                barra1--;
                if(barra1<0){
                    barra1=0;
                }
            }
        }
        //
        if(b12==0){
            if(win){
                //empezar juego si se ha acabado previamente
                win=0;
                puntos1=0;
                puntos2=0;
            }
            //boton de jugador 1 para ir a la derecha
            antir2++;
            if(antir2>=boton_antiRebote){
                //resetear el lag del boton
                antir1=0;
                antir2=0;
                
                barra1++;
                if(barra1>barra_espacioMax){
                    barra1=barra_espacioMax;
                }
            }
        }
        //
        if(b21==0){
            if(win){
                //empezar juego si se ha acabado previamente
                win=0;
                puntos1=0;
                puntos2=0;
            }
            //boton de jugador 2 para ir a la izquierda
            antir3++;
            if(antir3>=boton_antiRebote){
                //resetear el lag del boton
                antir3=0;
                antir4=0;
                barra2--;
                if(barra2<0){
                    barra2=0;
                }
            }
        }
        //
        if(b22==0){
            if(win){
                //empezar juego si se ha acabado previamente
                win=0;
                puntos1=0;
                puntos2=0;
            }
            //boton de jugador 2 para ir a la derecha
            antir4++;
            if(antir4>=boton_antiRebote){
                //resetear el lag del boton
                antir3=0;
                antir4=0;
                barra2++;
                if(barra2>barra_espacioMax){
                    barra2=barra_espacioMax;
                }
            }
        }
        //
        //
        if(display==0){
            // DISPLAY 7 Segmentos del jugador 1
            display=1;
            PORTC=0xfe;
            PORTC&=tabla7segmentos[puntos1];
            PORTC&=0xfe;
            PORTA|=0x80;
        }else{
            // DISPLAY 7 Segmentos del jugador 2
            display=0;
            PORTC=0xfe;
            PORTC&=tabla7segmentos[puntos2]; 
            PORTA&=0x7f;
            PORTC|=0x01;
        }        
        //--------------------
        //
        //
        //
        //          x
        //
        //
        //
        //--------------------
        //
        if(!win){
        state++;
        if(state>rapidez){
        state=0;
        //CONTROLAR LA DIRECCION 
        switch(direccion){
            case 0: //noroeste
            if((x-1)<0){
                if(y==1){
                    if(barra2==0 || barra2==1){
                        direccion=2;

                    }else{
                        direccion=1;
                    }
                }else if(y>=2){
                        direccion=1;
                }
            }else{
                if(y==1){
                    if((x-1)==barra2){
                        direccion=3;
                    }else if((x-2)==barra2){
                        direccion=2;
                    }
                }else if(y<=2){
                    //direccion=0;
                }
            }
            break;
            case 1: //noreste
            if((x+1)>TAM_MAXIMO_x-1){
                if(y==1){
                    if(barra2==TAM_MAXIMO_x-3 || barra2==TAM_MAXIMO_x-2){
                        direccion=3;

                    }else{
                        direccion=0;
                    }
                }else if(y>=2){
                    direccion=0;
                }
            }else{
                if(y==1){
                    if(x==barra2){
                        direccion=2;
                    }else if((x+1)==barra2){
                        direccion=3;
                    }

                }else if(y>=2){
                    //direccion=1;
                }
            }
            break;
            case 2: //sureste
            if((x+1)>TAM_MAXIMO_x-1){
                if(y==TAM_MAXIMO_y-2){
                    if(barra1==TAM_MAXIMO_x-3 || barra1==TAM_MAXIMO_x-2){
                        direccion=0;

                    }else{
                        direccion=3;
                    }
                }else if(y<=TAM_MAXIMO_y-3){
                    direccion=3;
                }
            }else{
                if(y==TAM_MAXIMO_y-2){
                    if(x==barra1){
                        direccion=1;
                    }else if((x+1)==barra1){
                        direccion=0;
                    }
                }else if(y<=TAM_MAXIMO_y-3){
                    //direccion=2;
                }
            }
            break;
            case 3: //suroeste
            if((x-1)<0){
                if(y==TAM_MAXIMO_y-2){
                    if(barra1==0 || barra1==1){
                        direccion=1;

                    }else{
                        direccion=2;
                    }
                }else if(y<=TAM_MAXIMO_y-3){
                    direccion=2;
                }
            }else{
                if(y==TAM_MAXIMO_y-2){
                    if((x-1)==barra1){
                        direccion=0;
                    }else if((x-2)==barra1){
                        direccion=1;
                    }
                }else if(y<=TAM_MAXIMO_y-3){
                    //direccion=3;
                }
            }
            break;
            default:
            break;
        }
        //
        //CAMBIAR EL VALOR DE LA POSICION
        switch(direccion){
            case 0: //noroeste
                x--;
                y--;
                break;
            case 1: // noreste
                x++;
                y--;
                break;
            case 2: // sureste
                x++;
                y++;
                break;
            case 3: //suroeste
                x--;
                y++;
                break;
            default:
                break;
        }
        
        }
        
        cols=state%8;
        print_cols=state%9;
        
        //LIMPIAR MATRIX
        PORTB=0xff;
        PORTD=0x00;
        
        //
        //PONER y
        
        print_matrix1=0x80;
        for(aux1=0;aux1<y;aux1++){
            print_matrix1=print_matrix1>>1;
        }
        print_matrix1=~print_matrix1;
        //
        //
        if(cols==x){
            PORTB&=print_matrix1;
        }
        
        if(cols==barra1){
            PORTB&=0xfe;
        }
        
        if(cols==barra1+1){
            PORTB&=0xfe;
        }
        
        if(cols==barra2){
            PORTB&=0x7f;
        }
        
        if(cols==barra2+1){
            PORTB&=0x7f;
        }
        
        // PRINT X
        print_matrix2=0x80;
        for(aux1=0;aux1<cols;aux1++){
            print_matrix2=print_matrix2>>1;
        }
        PORTD|=print_matrix2;
        
        if(y<0 || y>TAM_MAXIMO_y-1){
            PORTD=0x00;
            PORTB=0xff;
            if(y>TAM_MAXIMO_y-1){
                puntos2++;
                if(puntos2>=9){
                    win=1;
                }
                rand*=7;
                rand=rand%11;
                direccion=rand%2;
                
                //RESETEO DE Y
                y=3;
            }
            if(y<0){ 
                puntos1++;
                if(puntos1>=9){ 
                    win=1;
                }
                rand*=7;
                rand=rand%11;
                direccion=(rand%2)+2;
                
                //RESETEO DE Y
                y=4;
            }
            //RESETEO DE X
            x=TAM_MAXIMO_x/2;
            x--;
            rand*=7;
            rand=rand%11;
            x=x+rand%2;
            //
            
        }
        }
        
        /*
        hx1=0x80;
        for(aux1=0;aux1<i;aux1++){
            hx1=hx1>>1;
            //if(aux1==i-2)
            //hx2=hx1;
        }
        //hx1=hx1^hx2;
        hx1=~hx1;
        PORTB=hx1;
        if(c>=0 && c<500){
        n=0;
        PORTD=0x01;
        n++;
        c++;
        }
        if(c>=500 && c<1000){
        PORTD=0x02;
        n++;
        c++;
        }
        if(c>=1000 && c<1500){
        PORTD=0x04;
        n++;
        c++;
        }
        if(c>=1500 && c<2000){
        PORTD=0x08;
        n++;
        c++;
        }
        if(c>=2000 && c<2500){
        PORTD=0x10;
        n++;
        c++;
        }
        if(c>=2500 && c<3000){
        PORTD=0x20;
        n++;
        c++;
        }
        if(c>=3000 && c<3500){
        PORTD=0x40;
        n++;
        c++;
        }
        if(c>=3500 && c<4000){
        PORTD=0x80;
        n++;
        c++;
        }
        if(c>=4000){
            c=0;
            i++;
            if(i>7){
                i=0;
        
            }
        }
        */
        
        
        

      }
}
