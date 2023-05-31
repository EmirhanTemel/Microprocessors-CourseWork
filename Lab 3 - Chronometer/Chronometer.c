int state = 0;
int milisecs = 0;
int secs = 0;
int tens = 0;
void display(int,int,int);
void main() {
        PCON.OSCF = 1;
        TRISB = 0x00;
        TRISA = 0x60;
        PORTB = 0x00;
        while(1) {
                display(milisecs, secs, tens);
                if(RA5_bit) {
                        state = !state;
                        delay_ms(100);
                }
                if(state) {
                        milisecs++;
                        delay_ms(10);
                }
                if(milisecs == 10) {
                        milisecs = 0;
                        secs++;
                }
                if(secs == 10){
                        secs = 0;
                        tens++;
                }

                if(tens == 10){
                        milisecs = 0;
                        secs = 0;
                        tens = 0;
                }
                if(RA6_bit){
                        milisecs = 0;
                        secs = 0;
                        tens = 0;
                        delay_ms(100);
                }
        }
} void display(int c,int a,int b) {
                PORTB = a+(b<<4);
                PORTA = c;
}