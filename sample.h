<<<<<<< HEAD
#ifndef SAMPLE_H
#define SAMPLE_H
#include <math.h>

class Sample
{
private:
    float step;
    static long rate;
    static int N;
    int freq;

public:
    void set_freq(float);
    void set_sample_rate(int);
    long get_sample_rate(void);
    void set_N(int);
    int get_N(void);
    unsigned char get_sample (int );
    unsigned int get_time_ms(int);
    int get_freq(void);
    ~Sample();
};

#endif // SAMPLE_H
=======
#ifndef SAMPLE_H
#define SAMPLE_H
#include <math.h>

class Sample
{
private:
    float step;
    static long rate;
    static int N;
    int freq;

public:
    void set_freq(float);
    void set_sample_rate(int);
    long get_sample_rate(void);
    void set_N(int);
    int get_N(void);
    unsigned char get_sample (int );
    unsigned int get_time_ms(int);
    int get_freq(void);
    ~Sample();
};

#endif // SAMPLE_H
>>>>>>> 79935ad053a35863bad5aeae212192014e3aef8f
