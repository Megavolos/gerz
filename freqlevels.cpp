#include "freqlevels.h"
#include "ui_freqlevels.h"

FreqLevels::FreqLevels(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FreqLevels)
{
    ui->setupUi(this);
    this->setMouseTracking(true);
    ui->frame_1->setMouseTracking(true);
    ui->frame_2->setMouseTracking(true);
    ui->frame_3->setMouseTracking(true);
    ui->frame_4->setMouseTracking(true);
    ui->frame_5->setMouseTracking(true);
    ui->frame_6->setMouseTracking(true);
    ui->frame_7->setMouseTracking(true);
    ui->frame_8->setMouseTracking(true);



}


void FreqLevels::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    int max = 6000;
    int vol=1000;
    int recalc;
    recalc =ui->frame_1->height()-(ui->frame_1->height()/(float)max)*vol;
    if (recalc<=level1.level)
    {
        fill1.setRect(level1.line.x1(),recalc,level1.line.x2()-level1.line.x1(),ui->frame_1->height()-recalc+ui->frame_1->y());
        painter.fillRect(fill1,Qt::green);
    }
    if (recalc>level1.level)
    {
        fill1.setRect(level1.line.x1(),level1.line.y1(),level1.line.x2()-level1.line.x1(),ui->frame_1->height()+ui->frame_1->y()-level1.line.y1());
        painter.fillRect(fill1,Qt::green);
        fill1.setRect(level1.line.x1(),ui->frame_1->y(),level1.line.x2()-level1.line.x1(),level1.line.y1()-ui->frame_1->y());
        painter.fillRect(fill1,Qt::red);
    }
    painter.setPen(QPen(Qt::black,1,Qt::DashLine));

    painter.drawLine(level1.line);
    painter.drawLine(level2.line);
    painter.drawLine(level3.line);
    painter.drawLine(level4.line);
    painter.drawLine(level5.line);
    painter.drawLine(level6.line);
    painter.drawLine(level7.line);
    painter.drawLine(level8.line);
}


 void FreqLevels::mousePressEvent(QMouseEvent* event)
{
    if (event->button()==Qt::LeftButton)
    {
        if ((mouse_x>ui->frame_1->x())&&(mouse_x<(ui->frame_1->width()+ui->frame_1->x()))&&(mouse_y>ui->frame_1->y())&&(mouse_y<(ui->frame_1->y()+ui->frame_1->height())))
        {
            int y;
            y=ui->frame_1->height();
           level1.line.setLine(ui->frame_1->x(),mouse_y,ui->frame_1->width()+ui->frame_1->x()-1,mouse_y);
           level1.level=ui->frame_1->height()-mouse_y+ui->frame_1->y();
        }
        if ((mouse_x>ui->frame_2->x())&&(mouse_x<(ui->frame_2->width()+ui->frame_2->x()))&&(mouse_y>ui->frame_2->y())&&(mouse_y<(ui->frame_2->y()+ui->frame_2->height())))
        {
           level2.line.setLine(ui->frame_2->x(),mouse_y,ui->frame_2->width()+ui->frame_2->x()-1,mouse_y);
           level2.level=ui->frame_2->height()-mouse_x+ui->frame_2->y();
        }
        if ((mouse_x>ui->frame_3->x())&&(mouse_x<(ui->frame_3->width()+ui->frame_3->x()))&&(mouse_y>ui->frame_3->y())&&(mouse_y<(ui->frame_3->y()+ui->frame_3->height())))
        {
           level3.line.setLine(ui->frame_3->x(),mouse_y,ui->frame_3->width()+ui->frame_3->x()-1,mouse_y);
           level3.level=ui->frame_3->height()-mouse_x+ui->frame_3->y();
        }
        if ((mouse_x>ui->frame_4->x())&&(mouse_x<(ui->frame_4->width()+ui->frame_4->x()))&&(mouse_y>ui->frame_4->y())&&(mouse_y<(ui->frame_4->y()+ui->frame_4->height())))
        {
           level4.line.setLine(ui->frame_4->x(),mouse_y,ui->frame_4->width()+ui->frame_4->x()-1,mouse_y);
           level4.level=ui->frame_4->height()-mouse_x+ui->frame_4->y();
        }
        if ((mouse_x>ui->frame_5->x())&&(mouse_x<(ui->frame_5->width()+ui->frame_5->x()))&&(mouse_y>ui->frame_5->y())&&(mouse_y<(ui->frame_5->y()+ui->frame_5->height())))
        {
           level5.line.setLine(ui->frame_5->x(),mouse_y,ui->frame_5->width()+ui->frame_5->x()-1,mouse_y);
           level5.level=ui->frame_5->height()-mouse_x+ui->frame_5->y();
        }
        if ((mouse_x>ui->frame_6->x())&&(mouse_x<(ui->frame_6->width()+ui->frame_6->x()))&&(mouse_y>ui->frame_6->y())&&(mouse_y<(ui->frame_6->y()+ui->frame_6->height())))
        {
           level6.line.setLine(ui->frame_6->x(),mouse_y,ui->frame_6->width()+ui->frame_6->x()-1,mouse_y);
           level6.level=ui->frame_6->height()-mouse_x+ui->frame_6->y();
        }
        if ((mouse_x>ui->frame_7->x())&&(mouse_x<(ui->frame_7->width()+ui->frame_7->x()))&&(mouse_y>ui->frame_7->y())&&(mouse_y<(ui->frame_7->y()+ui->frame_7->height())))
        {
           level7.line.setLine(ui->frame_7->x(),mouse_y,ui->frame_7->width()+ui->frame_7->x()-1,mouse_y);
           level7.level=ui->frame_7->height()-mouse_x+ui->frame_7->y();
        }
        if ((mouse_x>ui->frame_8->x())&&(mouse_x<(ui->frame_8->width()+ui->frame_8->x()))&&(mouse_y>ui->frame_8->y())&&(mouse_y<(ui->frame_8->y()+ui->frame_8->height())))
        {
           level8.line.setLine(ui->frame_8->x(),mouse_y,ui->frame_8->width()+ui->frame_8->x()-1,mouse_y);
           level8.level=ui->frame_8->height()-mouse_x+ui->frame_8->y();
        }


        this->update();
   }

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
