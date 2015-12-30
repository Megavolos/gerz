#ifndef FREQLEVELS_H
#define FREQLEVELS_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include "goerzel.h"
#include "sample.h"
namespace Ui {
class FreqLevels;
}

class FreqLevels : public QWidget
{
    Q_OBJECT

public:
    explicit FreqLevels(QWidget *parent = 0);
    ~FreqLevels();
    void mouseMoveEvent(QMouseEvent*);
    void mousePressEvent(QMouseEvent*);
    void wheelEvent(QWheelEvent*);
    Sample* sample1;
    Sample* sample2;
private:
    struct Level
    {
      QLine line;
      bool setup_level;
      int level;
    } level1,level2,level3,level4,level5,level6,level7,level8;

    QRect fill1;
    Ui::FreqLevels *ui;
    int mouse_x,mouse_y;

protected:
   void paintEvent(QPaintEvent *);
};

#endif // FREQLEVELS_H
