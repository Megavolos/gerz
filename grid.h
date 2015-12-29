#ifndef GRID_H
#define GRID_H
#include <QPainter>
#include <QVector>
class Grid
{

    int N_x;                        //кол-во рисок по х
    int N_y;                        //кол-во рисок по у
    int Step_x;                     //шаг по х
    int Step_y;                     //шаг по у
    int x1,x2,y1,y2,width,height;   //координаты
    int N_length;                   //длина рисок
    float max_value_x;                //максимальное значение по оси x
    double max_value_y;                //максимальное значение по оси y
    int min_value_x;                //минимальное значение по оси x
    int min_value_y;                //минимальное значение по оси y
public:
    Grid();
    void SetStepY(int step);
    void SetStepX(int step);
    void SetMaxValue_X(float);
    void SetMaxValue_Y(float);
    void SetMinValue_X(int);
    void SetMinValue_Y(int);
    void setcoord(QRect*);
    void DrawGrid(QPainter* parent);
    void SetNx(int);
    void SetNy(int);
    void SetX1(int);
    void SetX2(int);
    void SetY1(int);
    void SetY2(int);
    void SetWidth(int);
    void SetHeight(int);
    void SetNLength(int);
    int GetNy(void);
    int GetNx(void);
    int GetX1(void);
    int GetX2(void);
    int GetY1(void);
    int GetY2(void);
    void DrawBin(QPainter* parent, int count, float value);
    int GetWidth(void);
    int GetHeight(void);
    int GetNLength(void);
    int GetMaxValue_X(void);
    double GetMaxValue_Y(void);
    int GetMinValue_X(void);
    int GetMinValue_Y(void);
    int GetStepX(void);
    int GetStepY(void);

};

#endif // GRID_H
