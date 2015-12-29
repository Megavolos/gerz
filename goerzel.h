<<<<<<< HEAD
#ifndef GOERZEL_H
#define GOERZEL_H
#include "sample.h"
#include <math.h>
#include "QVector"
class Goertzel
{
private:
    float omega;
    float coeff;
    float sine;
    float cosine;
    float Q1,Q2;
    int k;
    int target_frequency;
public:
    void initialize (int, Sample*);

    void reset(void);
    void process_sample(int);
    float get_real(void);
    float get_imag(void);
    float get_magnitude_squared(void);
    int get_target_freq(void);
};

#endif // GOERZEL_H
=======
#ifndef GOERZEL_H
#define GOERZEL_H
#include "sample.h"
#include <math.h>
#include "QVector"
class Goertzel
{
private:
    float omega;
    float coeff;
    float sine;
    float cosine;
    float Q1,Q2;
    int k;
    int target_frequency;
public:
    void initialize (int, Sample*);

    void reset(void);
    void process_sample(int);
    float get_real(void);
    float get_imag(void);
    float get_magnitude_squared(void);
    int get_target_freq(void);
};

#endif // GOERZEL_H
>>>>>>> 79935ad053a35863bad5aeae212192014e3aef8f
