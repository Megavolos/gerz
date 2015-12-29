#ifndef SPECTRUMWINDOW_H
#define SPECTRUMWINDOW_H

#include <QWidget>
#include <QPainter>
#include "grid.h"
#include "sample.h"
#include "goerzel.h"
namespace Ui {
class SpectrumWindow;
}

class SpectrumWindow : public QWidget
{
    Q_OBJECT

public:
    struct Bins
    {
        QVector<int>* freq;
        QVector<float>* value;
    } *bins;
    struct Geometry
    {
       int offset_left_x;
       int offset_right_x;
       int offset_bottom_y;
       int offset_top_y;
       int widget_x1;
       int widget_y1;
       int widget_x2;
       int widget_y2;
    } *geometry;

    int max_freq;
    int min_freq;
    int bins_step;
    QVector<int>* x;
    QVector<float>* y;
    QRect* bkgrd;
    Sample *sample1, *sample2;
    Goertzel* goertzel;
    Grid* grid;

    int mouse_x,mouse_y;
    int offset_left_x,offset_right_x,offset_bottom_y,offset_top_y,widget_x1,widget_y1,widget_x2,widget_y2;
    float mouse_dev,dev;
    explicit SpectrumWindow(QWidget *parent = 0);
    void drawbin(int , int );
    void drawspectr(QPainter* p, Bins* b);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void resizeEvent(QResizeEvent *);
    void showEvent(QShowEvent *);

    ~SpectrumWindow();


private:
    Ui::SpectrumWindow *ui;
public slots:
    void setmaxfreq();
    void setminfreq();
    void setleftcut();
    void setbinsstep();
    void binsrecalc();
protected:
   void paintEvent(QPaintEvent *);
};

#endif // SPECTRUMWINDOW_H
