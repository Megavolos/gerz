#ifndef FREQLEVELS_H
#define FREQLEVELS_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
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
    void wheelEvent(QWheelEvent*);
private:
    QLine level1;
    Ui::FreqLevels *ui;
    int mouse_x,mouse_y;

protected:
   void paintEvent(QPaintEvent *);
};

#endif // FREQLEVELS_H
