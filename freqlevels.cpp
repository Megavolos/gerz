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
    level1 = new Level();
    level2 = new Level();
    level3 = new Level();
    level4 = new Level();
    level5 = new Level();
    level6 = new Level();
    level7 = new Level();
    level8 = new Level();


}
FreqLevels::Level::Level()
{
    line = new QLine();
    level = 0;
}

FreqLevels::Level::~Level()
{

    delete line;
}

void FreqLevels::fillFrame(QPainter *painter, QFrame *frame, Level* lev,float vol,float max)
{
    int recalc;
    recalc =(frame->height()/(float)max)*vol;
    if (recalc<=lev->level)
    {
        fill1.setRect(lev->line->x1(),frame->height()+frame->y()-recalc,lev->line->x2()-lev->line->x1(),recalc);
        painter->fillRect(fill1,Qt::green);
    }
    if (recalc>lev->level)
    {

        fill1.setRect(lev->line->x1(),lev->line->y1(),lev->line->x2()-lev->line->x1(),frame->height()+frame->y()-lev->line->y1());
        painter->fillRect(fill1,Qt::green);
        fill1.setRect(lev->line->x1(),frame->height()+frame->y()-recalc,lev->line->x2()-lev->line->x1(),recalc-frame->height()+lev->line->y1()-frame->y());
        painter->fillRect(fill1,Qt::red);
    }
}

void FreqLevels::paintEvent(QPaintEvent *)
{
    QPainter painter(this);


    fillFrame(&painter,ui->frame_1,level1,5000, 6000);
    fillFrame(&painter,ui->frame_2,level2,3000, 6000);
    fillFrame(&painter,ui->frame_3,level3,1000, 6000);
    fillFrame(&painter,ui->frame_4,level4,4000, 6000);
    fillFrame(&painter,ui->frame_5,level5,4500, 6000);
    fillFrame(&painter,ui->frame_6,level6,2000, 6000);
    fillFrame(&painter,ui->frame_7,level7,2500, 6000);
    fillFrame(&painter,ui->frame_8,level8,3500, 6000);
    painter.setPen(QPen(Qt::black,1,Qt::DashLine));

    painter.drawLine(*level1->line);
    painter.drawLine(*level2->line);
    painter.drawLine(*level3->line);
    painter.drawLine(*level4->line);
    painter.drawLine(*level5->line);
    painter.drawLine(*level6->line);
    painter.drawLine(*level7->line);
    painter.drawLine(*level8->line);
}


 void FreqLevels::mousePressEvent(QMouseEvent* event)
{
    if (event->button()==Qt::LeftButton)
    {
        if ((mouse_x>ui->frame_1->x())&&(mouse_x<(ui->frame_1->width()+ui->frame_1->x()))&&(mouse_y>ui->frame_1->y())&&(mouse_y<(ui->frame_1->y()+ui->frame_1->height())))
        {
           level1->line->setLine(ui->frame_1->x(),mouse_y,ui->frame_1->width()+ui->frame_1->x()-1,mouse_y);
           level1->level=ui->frame_1->height()-mouse_y+ui->frame_1->y();
        }
        if ((mouse_x>ui->frame_2->x())&&(mouse_x<(ui->frame_2->width()+ui->frame_2->x()))&&(mouse_y>ui->frame_2->y())&&(mouse_y<(ui->frame_2->y()+ui->frame_2->height())))
        {
           level2->line->setLine(ui->frame_2->x(),mouse_y,ui->frame_2->width()+ui->frame_2->x()-1,mouse_y);
           level2->level=ui->frame_2->height()-mouse_y+ui->frame_2->y();
        }
        if ((mouse_x>ui->frame_3->x())&&(mouse_x<(ui->frame_3->width()+ui->frame_3->x()))&&(mouse_y>ui->frame_3->y())&&(mouse_y<(ui->frame_3->y()+ui->frame_3->height())))
        {
           level3->line->setLine(ui->frame_3->x(),mouse_y,ui->frame_3->width()+ui->frame_3->x()-1,mouse_y);
           level3->level=ui->frame_3->height()-mouse_y+ui->frame_3->y();
        }
        if ((mouse_x>ui->frame_4->x())&&(mouse_x<(ui->frame_4->width()+ui->frame_4->x()))&&(mouse_y>ui->frame_4->y())&&(mouse_y<(ui->frame_4->y()+ui->frame_4->height())))
        {
           level4->line->setLine(ui->frame_4->x(),mouse_y,ui->frame_4->width()+ui->frame_4->x()-1,mouse_y);
           level4->level=ui->frame_4->height()-mouse_y+ui->frame_4->y();
        }
        if ((mouse_x>ui->frame_5->x())&&(mouse_x<(ui->frame_5->width()+ui->frame_5->x()))&&(mouse_y>ui->frame_5->y())&&(mouse_y<(ui->frame_5->y()+ui->frame_5->height())))
        {
           level5->line->setLine(ui->frame_5->x(),mouse_y,ui->frame_5->width()+ui->frame_5->x()-1,mouse_y);
           level5->level=ui->frame_5->height()-mouse_y+ui->frame_5->y();
        }
        if ((mouse_x>ui->frame_6->x())&&(mouse_x<(ui->frame_6->width()+ui->frame_6->x()))&&(mouse_y>ui->frame_6->y())&&(mouse_y<(ui->frame_6->y()+ui->frame_6->height())))
        {
           level6->line->setLine(ui->frame_6->x(),mouse_y,ui->frame_6->width()+ui->frame_6->x()-1,mouse_y);
           level6->level=ui->frame_6->height()-mouse_y+ui->frame_6->y();
        }
        if ((mouse_x>ui->frame_7->x())&&(mouse_x<(ui->frame_7->width()+ui->frame_7->x()))&&(mouse_y>ui->frame_7->y())&&(mouse_y<(ui->frame_7->y()+ui->frame_7->height())))
        {
           level7->line->setLine(ui->frame_7->x(),mouse_y,ui->frame_7->width()+ui->frame_7->x()-1,mouse_y);
           level7->level=ui->frame_7->height()-mouse_y+ui->frame_7->y();
        }
        if ((mouse_x>ui->frame_8->x())&&(mouse_x<(ui->frame_8->width()+ui->frame_8->x()))&&(mouse_y>ui->frame_8->y())&&(mouse_y<(ui->frame_8->y()+ui->frame_8->height())))
        {
           level8->line->setLine(ui->frame_8->x(),mouse_y,ui->frame_8->width()+ui->frame_8->x()-1,mouse_y);
           level8->level=ui->frame_8->height()-mouse_y+ui->frame_8->y();
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
    delete level1;
    delete level2;
    delete level3;
    delete level4;
    delete level5;
    delete level6;
    delete level7;
    delete level8;
    delete ui;
}
