/**
 *  The MIT License (MIT)
 *
 *  Copyright (c) 2013 Paulo B. de Oliveira Filho <pauloborgesfilho@gmail.com>
 *  Copyright (c) 2013 Claudio Takahasi <claudio.takahasi@gmail.com>
 *  Copyright (c) 2013 João Paulo Rechi Vita <jprvita@gmail.com>
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

#include <stdint.h>
#include <string.h>

#include <blessed/timer.h>
#include <blessed/log.h>

#define TIMER1_MS			1000
#define TIMER2_MS			250
#define TIMER3_MS			10000

uint16_t counter = 0;
uint16_t timer_data = 0;

int16_t timer1;
int16_t timer2;
int16_t timer3;

void timeout1(void *user_data)
{
	DBG("%u second(s)", ++counter);

	if (counter == 5) {
		DBG("timer1 stopped");
		timer_stop(timer1);
	}
}

void timeout2(void *user_data)
{
	uint16_t *data = user_data;
	(*data)++;

	DBG("Data: %u", *data);
}

void timeout3(void *user_data)
{
	DBG("singleshot timer after %d seconds", TIMER3_MS / 1000);
}

int main(void)
{
	log_init();
	timer_init();

	timer1 = timer_create(TIMER_REPEATED, timeout1);
	timer2 = timer_create(TIMER_REPEATED, timeout2);
	timer3 = timer_create(TIMER_SINGLESHOT, timeout3);

	timer_start(timer1, TIMER1_MS, NULL);
	timer_start(timer2, TIMER2_MS, &timer_data);
	timer_start(timer3, TIMER3_MS, NULL);

	while (1);

	return 0;
}
