#include "sample.h"
long Sample::rate;
int Sample::N;
void Sample::set_sample_rate(int r)
{
    rate=r;
    step = freq * ((2.0 * M_PI) / rate);
}

void Sample::set_freq(float f)
{
    freq = f;
    step = freq * ((2.0 * M_PI) / rate);
}
int Sample::get_freq(void)
{
   return freq;
}

unsigned char Sample::get_sample (int n)
{
    if (n>N) n=N;
    return (unsigned char) (100.0 * sin(n * step) + 100.0);
}

long Sample::get_sample_rate(void)
{
    return rate;
}

int Sample::get_N(void)
{
    return N;
}

unsigned int Sample::get_time_ms(int n)
{
    return 1000/(n*step);
}

void Sample::set_N(int n)
{
    N=n;
}

Sample::~Sample()
{



}
