#include "Timer.h"

void initTimer()
{
	//init Timer0 for low-accuracy scheduling (1/10th sec tick)
	TIMSK |= (1 << TOIE0);	//enable interrupt
	TCCR0 |= (1 << CS00) | (1 << CS02);	//prescaler
}