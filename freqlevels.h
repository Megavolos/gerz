#ifndef FREQLEVELS_H
#define FREQLEVELS_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include "goerzel.h"
#include "sample.h"
#include <QFrame>
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
    class Level
    {
    public:
        Level();
        QLine* line;
        int level;
        ~Level();
    };
    Level *level1,*level2,*level3,*level4,*level5,*level6,*level7,*level8;
    QRect fill1;
    Ui::FreqLevels *ui;
    int mouse_x,mouse_y;
    void fillFrame(QPainter *painter, QFrame *frame, Level* lev, float vol, float max);

protected:
   void paintEvent(QPaintEvent *);
};

#endif // FREQLEVELS_H
