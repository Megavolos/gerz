#include "spectrogram.h"

Spectrogram::Spectrogram()
{
    x_axe_x1=0;
    x_axe_x2=0;
    y_axe_y1=0;
    y_axe_y2=0;
    scale_factor=1;
}

void Spectrogram::setx_axe_x1(int x)
{
    x_axe_x1 = x;
}

void Spectrogram::setx_axe_x2(int x)
{
    x_axe_x2 = x;
}

void Spectrogram::sety_axe_y1(int y)
{
     y_axe_y1 = y;
}

void Spectrogram::sety_axe_y2(int y)
{
     y_axe_y2 = y;
}

int Spectrogram::getx_axe_x1(void)
{
    return x_axe_x1;
}

int Spectrogram::getx_axe_x2(void)
{
    return x_axe_x2;
}

int Spectrogram:: gety_axe_y1(void)
{
    return y_axe_y1;
}

int Spectrogram::gety_axe_y2(void)
{
    return y_axe_y2;
}

int Spectrogram::globalx_to_localx (int freq)
{
    int local_x;
    local_x =  (x_axe_x2-x_axe_x1);
}
