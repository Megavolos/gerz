#include "freqlevels.h"
#include "ui_freqlevels.h"

FreqLevels::FreqLevels(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FreqLevels)
{
    ui->setupUi(this);
    this->setMouseTracking(true);
    ui->frame->setMouseTracking(true);


}

void FreqLevels::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::black,1,Qt::DashLine));
    if ((mouse_x>ui->frame->x())&&(mouse_x<(ui->frame->width()+ui->frame->x()))&&(mouse_y>ui->frame->y())&&(mouse_y<(ui->frame->y()+ui->frame->height())))
    level1.setLine(ui->frame->x(),mouse_y,ui->frame->width()+ui->frame->x(),mouse_y);
    painter.drawLine(level1);

}
void FreqLevels::mouseMoveEvent(QMouseEvent *event)
{
    mouse_x=event->pos().x();
    mouse_y=event->pos().y();
    this->update();
}

void FreqLevels::wheelEvent(QWheelEvent *event)
{

}

FreqLevels::~FreqLevels()
{
    delete ui;
}
