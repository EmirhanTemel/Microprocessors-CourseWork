unsigned char number1 = 0;
unsigned char number2 = 0;
unsigned char state = 0;
unsigned char buttonP = 0;

void display(unsigned char,unsigned char,unsigned char);
void increment();

void main() {
	PCON.OSCF = 1;
	TRISA = 0x60; //  0110 0000
	TRISB = 0x00;
	PORTA = 0x00;
	PORTB = 0x00;

	// TIMER1 Settings
	T1CON.T1CKPS1 = 0; // Set PRESCALERS
	T1CON.T1CKPS0 = 0; // Set PRESCALERS
        T1CON.TMR1CS = 0; // TODO TIMER use internal clock
	TMR1H = 0xE8;  // TODO TIMER1 Counter TMR1H:TMR1L
	TMR1L = 0x48; // TODO TIMER1 Counter TMR1H:TMR1L
	T1CON.TMR1ON = 1; // TODO set TIMER1 on

	// intterupts
	INTCON.GIE = 1; // TURN on global interruts enable
	PIE1.TMR1IE = 1; // TURN on timer 1 interrupt
	INTCON.PEIE = 1; // TURN on peripheral interrupt enable

	while(1) {
		if(buttonP == 0 && RA5_bit == 1){
			state = state == 9 ? 0 : state + 1;
		}
		if(RA6_bit == 1)
			state = 0;
		buttonP = RA5_bit;
		display(number2,number1,state);
	}
}

void increment() {
	number1 = number1 + 1;
	if(number1 == 10) {
		number1 = 0;
		number2++;
		if( number2 == 10) {
			number2 = 0;
		}
	}
}

void display(unsigned char num1, unsigned char num2,unsigned char num3){
	PORTB = (num3<<4) + num2;
    PORTA = num1;
}

void interrupt() {
	increment();
        TMR1H = 0xE8;  // TODO reset timer1 counter according to your need
	TMR1L = 0x48;
	PIR1.TMR1IF = 0; // TODO TIMER1 interrupt flag
}