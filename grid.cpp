#include "grid.h"

Grid::Grid()
{

    N_x=10;
    N_y=10;
    Step_x=width/N_x;
    Step_y=height/N_y;
}
void Grid::SetStepX(int step)
{
    Step_x=step;
}
void Grid::SetStepY(int step)
{
    Step_y=step;
}
void Grid::setcoord(QRect* rect)
{
    x1=rect->x();
    y1=rect->y();
    x2=rect->x()+rect->width();
    y2=rect->y()+rect->height();
}
void Grid::SetMaxValue_X (float value)
{
    max_value_x=value;
}
void Grid::SetMaxValue_Y (float value)
{
    max_value_y=value;
}
void Grid::SetMinValue_X (int value)
{
    min_value_x=value;
}
void Grid::SetMinValue_Y (int value)
{
    min_value_y=value;
}
void Grid::SetNx(int n_x)
{
    N_x=n_x;
}

void Grid::SetNy(int n_y)
{
    N_y=n_y;
}

void Grid::SetX1(int _x1)
{
    x1=_x1;
}

void Grid::SetX2(int _x2)
{
    x2=_x2;
}

void Grid::SetY1(int _y1)
{
    y1=_y1;
}
void Grid::SetY2(int _y2)
{
    y2=_y2;
}
void Grid::SetWidth(int w)
{
    width=w;
}

void Grid::SetNLength(int l)
{
    N_length=l;
}

int Grid::GetNx(void)
{
    return N_x;
}
int Grid::GetNy(void)
{
    return N_y;
}

int Grid::GetX1(void)
{
    return x1;
}

int Grid::GetX2(void)
{
    return x2;
}

int Grid::GetY1(void)
{
    return y1;
}

int Grid::GetY2(void)
{
    return y2;
}

int Grid::GetWidth(void)
{
    return width;
}

int Grid::GetHeight(void)
{
    return (x2-x1);
}
int Grid::GetNLength()
{
    return N_length;
}

void Grid::DrawGrid(QPainter* parent)
{

    parent->setPen(QPen(Qt::gray,1,Qt::DotLine));
    for (int i=1;i<=10;i++)
    {
        parent->drawLine(QLine(i*(x2-x1)/N_x+x1,y1,i*(x2-x1)/N_x+x1,y2-N_length));
    }
    for (int i=1;i<10;i++)
    {
        parent->drawLine(QLine(x1+N_length,i*(y2-y1)/10+y1,x2,i*(y2-y1)/10+y1));
    }
    parent->setPen(QPen(Qt::black,1,Qt::SolidLine));
    for (int i=0;i<=10;i++)
    {
        parent->drawLine(QLine(i*(x2-x1)/10+x1,y2+N_length,i*(x2-x1)/10+x1,y2-N_length));
    }
    for (int i=0;i<=10;i++)
    {
        parent->drawLine(QLine(x1-N_length,i*(y2-y1)/10+y1,x1+N_length,i*(y2-y1)/10+y1));
    }
}
void Grid::DrawBin(QPainter* parent,int count, float value)
{
    int y;
    //x=((x2-x1)/((float)(max_value_x-min_value_x))*count + x1);
    y=y2-(((y2-y1)/((float)(max_value_y-min_value_y))))*value;
    if (y<y1) y=y1;
     parent->drawLine(count+x1,y,count+x1,y2);
}
//void Grid::DrawBins(QVector* )
int Grid::GetMaxValue_X (void)
{
    return max_value_x;
}
double Grid::GetMaxValue_Y(void)
{
    return max_value_y;
}
int Grid::GetMinValue_X (void)
{
    return min_value_x;
}
int Grid::GetMinValue_Y (void)
{
   return min_value_y;
}
int Grid::GetStepX(void)
{
    return Step_x;
}
int Grid::GetStepY(void)
{
    return Step_y;
}
