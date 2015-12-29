#include "goerzel.h"


void Goertzel::initialize(int target_freq, Sample* S)
{
    float temp;
    target_frequency=target_freq;
    temp=(float)S->get_N() * target_freq;
    temp/=S->get_sample_rate();
    temp+=0.5;
    k=(int)temp;
    k = (int) (0.5 + (((float)S->get_N() * target_freq) / S->get_sample_rate()));
    omega = (2.0 * M_PI * k) / (float)S->get_N();
    sine = sin(omega);
    cosine = cos(omega);
    coeff = 2.0 * cosine;
}
int Goertzel::get_target_freq(void)
{
    return target_frequency ;
}

void Goertzel::reset(void)
{
    Q2 = 0;
    Q1 = 0;
}
void Goertzel::process_sample(int sample)
{
    float Q0;
    Q0 = coeff * Q1 - Q2 + (float) sample;
    Q2 = Q1;
    Q1 = Q0;
}
float Goertzel::get_real(void)
{
    return (Q1 - Q2 * cosine);
}
float Goertzel::get_imag(void)
{
    return (Q2 * sine);
}

float Goertzel::get_magnitude_squared(void)
{
    return (Q1 * Q1 + Q2 * Q2 - Q1 * Q2 * coeff);
}
