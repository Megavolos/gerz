#ifndef FREQLEVELS_H
#define FREQLEVELS_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include "goerzel.h"
#include "sample.h"
#include <QFrame>
#include <QLineEdit>

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
    Goertzel* goertzel;

private:
    class Level
    {
    public:
        Level();
        QLine* line;
        int level;
        ~Level();
    };
    void setFrame(QFrame *frame, Level *lev, float vol, float max);
    Level *level1,*level2,*level3,*level4,*level5,*level6,*level7,*level8;
    QRect *fill1_r, *fill1_g, *fill2_r, *fill2_g, *fill3_r, *fill3_g, *fill4_r, *fill4_g, *fill5_r, *fill5_g, *fill6_r, *fill6_g, *fill7_r, *fill7_g, *fill8_r, *fill8_g;
    Ui::FreqLevels *ui;
    QPainter* painter_p;
    int mouse_x,mouse_y;
    float getMaxGoertzel ();
    float setRect(QRect&);
    void frame_fill(QRect* fill_g, QRect* fill_r, QFrame* frame, Level* lev , QLineEdit *lineedit);
    void fillFrame(QPainter *painter);
    void resizeEvent(QResizeEvent*);

protected:
   void paintEvent(QPaintEvent *);
public slots:
   void goerzelrecalc(void);
};

#endif // FREQLEVELS_H
