#define m1Port RB0_bit
#define m2Port RB1_bit
#define toggleDirection RB4_bit
#define togglePWMPeriod RB5_bit
#define togglePWMDutyCycle RB6_bit

int currentMode = 0;
int duty_cycle = 0;
int period = 0;

void main () {

	TRISB.F0 = 0;
	TRISB.F1 = 0;
	TRISB.F4 = 1;
	TRISB.F5 = 1;
	TRISB.F6 = 1;

	m1Port = 1;
	m2Port = 0;

	// Enable RB_4567 External interrupts
	INTCON.GIE = 1;
	INTCON.RBIE = 1;
	INTCON.RBIF = 0;
	
        // Initially --> 3KHz, %25 Duty Cycle
 	//1. Set the PWM period by writing to the PR2 register.
        PR2 = 103;  // 3KHz
	//2. Set the PWM duty cycle by writing to the CCPR1L register and CCP1CON<5:4> bits.
        CCPR1L = 0b00011010; // 3KHz %25 Duty cycle
        CCP1CON.F5 = 0;  // 3KHz %25 Duty cycle
        CCP1CON.F4 = 0;
	//3. Make the CCP1 pin an output by clearing the TRISB<3> bit.
        TRISB.F3 = 0;
	//4. Set the TMR2 prescale value and enable Timer2 by writing to T2CON.
        T2CON.TMR2ON = 1;   //timer2 on
        T2CON.T2CKPS1 = 1;  //prescale value = 16, 3KHz
        T2CON.T2CKPS0 = 0; //don't care
	//5. Configure the CCP1 module for PWM operation. PWM mode on
        CCP1CON.CCP1M3 = 1;
        CCP1CON.CCP1M2 = 1;

        

}


void interrupt() {
        /*
        TODO Determine which button is pressed and change the configuration accordingly.
		TIP: You can use a variable to keep track of the current configuration.
        */
        if (toggleDirection){
           m1Port = ~m1Port;
           m2Port = ~m2Port;
        }
        if (togglePWMPeriod){
           period = !period;
        }
        if (togglePWMDutyCycle) {
           if(duty_cycle <2){
              duty_cycle++;
           }
           else {
              duty_cycle = 0;
           }
        }
        if ( duty_cycle==0 && period==0){  // 3KHz, %25 Duty Cycle
 	//1. Set the PWM period by writing to the PR2 register.
        PR2 = 103;  // 3KHz
	//2. Set the PWM duty cycle by writing to the CCPR1L register and CCP1CON<5:4> bits.
        CCPR1L = 0b00011010; // 3KHz %25 Duty cycle
        CCP1CON.F5 = 0;  // 3KHz %25 Duty cycle
        CCP1CON.F4 = 0;
        }
        
        if ( duty_cycle==1 && period==0){  // 3KHz, %50 Duty Cycle
 	//1. Set the PWM period by writing to the PR2 register.
        PR2 = 103;  // 3KHz
	//2. Set the PWM duty cycle by writing to the CCPR1L register and CCP1CON<5:4> bits.
        CCPR1L = 0b00110100; // 3KHz %50 Duty cycle
        CCP1CON.F5 = 0;  // 3KHz %50 Duty cycle
        CCP1CON.F4 = 0;
        }

        if ( duty_cycle==2 && period==0){  // 3KHz, %75 Duty Cycle
 	//1. Set the PWM period by writing to the PR2 register.
        PR2 = 103;  // 3KHz
	//2. Set the PWM duty cycle by writing to the CCPR1L register and CCP1CON<5:4> bits.
        CCPR1L = 0b01001110; // 3KHz %75 Duty cycle
        CCP1CON.F5 = 0;  // 3KHz %75 Duty cycle
        CCP1CON.F4 = 1;
        }

        if ( duty_cycle==2 && period==1){  // 15KHz, %75 Duty Cycle
 	//1. Set the PWM period by writing to the PR2 register.
        PR2 = 20;  // 15KHz
	//2. Set the PWM duty cycle by writing to the CCPR1L register and CCP1CON<5:4> bits.
        CCPR1L = 0b00001111; // 15KHz %75 Duty cycle
        CCP1CON.F5 = 1;  // 15KHz %75 Duty cycle
        CCP1CON.F4 = 1;
        }

        if ( duty_cycle==1 && period==1){  // 15KHz, %50 Duty Cycle
 	//1. Set the PWM period by writing to the PR2 register.
        PR2 = 20;  // 15KHz
	//2. Set the PWM duty cycle by writing to the CCPR1L register and CCP1CON<5:4> bits.
        CCPR1L = 0b00001010; // 15KHz %50 Duty cycle
        CCP1CON.F5 = 1;  // 15KHz %50 Duty cycle
        CCP1CON.F4 = 0;
        }

        if ( duty_cycle==0 && period==1){  // 15KHz, %25 Duty Cycle
 	//1. Set the PWM period by writing to the PR2 register.
        PR2 = 20;  // 15KHz
	//2. Set the PWM duty cycle by writing to the CCPR1L register and CCP1CON<5:4> bits.
        CCPR1L = 0b00000101; // 15KHz %25 Duty cycle
        CCP1CON.F5 = 0;  // 15KHz %25 Duty cycle
        CCP1CON.F4 = 1;
        }
        
        
	INTCON.RBIF = 0;

}