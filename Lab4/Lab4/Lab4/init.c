
 void LCD_Init(void)
 {
	 //setting for the AVR//
	 CLKPR = 0x80;
	 CLKPR = 0x00;
	 //external async clock, 1/3 bias, 1/4 duty cycle, 25 segments
	 LCDCRB = (1 << LCDCS) | (1 << LCDMUX0) | (1 << LCDMUX1) | (1 << LCDPM0) | (1 << LCDPM1) | (1 << LCDPM2);
	 //clock divider N=8
	 LCDFRR = (1 << LCDCD0) | (1 << LCDCD1) | (1 << LCDCD2);
	 //LCD low power, no frame interrupt no blanking
	 LCDCRA = (1 << LCDEN) | (1 << LCDAB);
	 //Drive time 300ms, control voltage 3,35V
	 LCDCCR = (1 << LCDCC0) | (1 << LCDCC1) | (1 << LCDCC2) | (1 << LCDCC3);
	 //timer with prescaler 256
	 //TCCR1B = (1<<CS12);


	 //External input
	 EIMSK = (1 << PCIE1);
	 PCMSK1 = (1 << PCINT15);
	 //activate the button
	 PORTB = (1 << PINB7);
	 //timer with prescaler 1024
	 //TCCR1B = (1<<CS12) | (1 << CS10) | (1 << WGM12);
	 //500 ms period
	 //OCR1A = 0xF42;

	 //TIMSK1 = (1 << OCIE1A);
	 //reset timer
 }