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
    fill1_r = new QRect();
    fill1_g = new QRect();
    fill2_r = new QRect();
    fill2_g = new QRect();
    fill3_r = new QRect();
    fill3_g = new QRect();
    fill4_r = new QRect();
    fill4_g = new QRect();
    fill5_r = new QRect();
    fill5_g = new QRect();
    fill6_r = new QRect();
    fill6_g = new QRect();
    fill7_r = new QRect();
    fill7_g = new QRect();
    fill8_r = new QRect();
    fill8_g = new QRect();
    goertzel = new Goertzel();

    onceShowed=false;
    connect (ui->Edit_f1,SIGNAL(valueChanged(int)),this,SLOT(goerzelrecalc()));
    connect (ui->Edit_f2,SIGNAL(valueChanged(int)),this,SLOT(goerzelrecalc()));
    connect (ui->Edit_f3,SIGNAL(valueChanged(int)),this,SLOT(goerzelrecalc()));
    connect (ui->Edit_f4,SIGNAL(valueChanged(int)),this,SLOT(goerzelrecalc()));
    connect (ui->Edit_f5,SIGNAL(valueChanged(int)),this,SLOT(goerzelrecalc()));
    connect (ui->Edit_f6,SIGNAL(valueChanged(int)),this,SLOT(goerzelrecalc()));
    connect (ui->Edit_f7,SIGNAL(valueChanged(int)),this,SLOT(goerzelrecalc()));
    connect (ui->Edit_f8,SIGNAL(valueChanged(int)),this,SLOT(goerzelrecalc()));

    this->setWindowTitle("Goertzel test for 8 freq");


}
void FreqLevels::showEvent(QShowEvent*)
{
    if (!onceShowed)
    {
        level1->line->setLine(ui->frame_1->x(),ui->frame_1->height()/2+ui->frame_1->y(),ui->frame_1->width()+ui->frame_1->x()-1,ui->frame_1->height()/2+ui->frame_1->y());
        level1->level=ui->frame_1->height()/2+ui->frame_1->y();
        level2->line->setLine(ui->frame_2->x(),ui->frame_2->height()/2+ui->frame_2->y(),ui->frame_2->width()+ui->frame_2->x()-1,ui->frame_2->height()/2+ui->frame_2->y());
        level2->level=ui->frame_2->height()/2+ui->frame_2->y();
        level3->line->setLine(ui->frame_3->x(),ui->frame_3->height()/2+ui->frame_3->y(),ui->frame_3->width()+ui->frame_3->x()-1,ui->frame_3->height()/2+ui->frame_3->y());
        level3->level=ui->frame_3->height()/2+ui->frame_3->y();
        level4->line->setLine(ui->frame_4->x(),ui->frame_4->height()/2+ui->frame_4->y(),ui->frame_4->width()+ui->frame_4->x()-1,ui->frame_4->height()/2+ui->frame_4->y());
        level4->level=ui->frame_4->height()/2+ui->frame_4->y();
        level5->line->setLine(ui->frame_5->x(),ui->frame_5->height()/2+ui->frame_5->y(),ui->frame_5->width()+ui->frame_5->x()-1,ui->frame_5->height()/2+ui->frame_5->y());
        level5->level=ui->frame_5->height()/2+ui->frame_5->y();
        level6->line->setLine(ui->frame_6->x(),ui->frame_6->height()/2+ui->frame_6->y(),ui->frame_6->width()+ui->frame_6->x()-1,ui->frame_6->height()/2+ui->frame_6->y());
        level6->level=ui->frame_6->height()/2+ui->frame_6->y();
        level7->line->setLine(ui->frame_7->x(),ui->frame_7->height()/2+ui->frame_7->y(),ui->frame_7->width()+ui->frame_7->x()-1,ui->frame_7->height()/2+ui->frame_7->y());
        level7->level=ui->frame_7->height()/2+ui->frame_7->y();
        level8->line->setLine(ui->frame_8->x(),ui->frame_8->height()/2+ui->frame_8->y(),ui->frame_8->width()+ui->frame_8->x()-1,ui->frame_8->height()/2+ui->frame_8->y());
        level8->level=ui->frame_8->height()/2+ui->frame_8->y();
    }
    onceShowed=true;
}

void FreqLevels::resizeEvent(QResizeEvent* )
{
    float resize;
    resize = ui->frame_1->height();
    level1->line->setLine(ui->frame_1->x(),level1->line->y1(),ui->frame_1->width()+ui->frame_1->x()-1,level1->line->y1());
    level2->line->setLine(ui->frame_2->x(),level2->line->y1(),ui->frame_2->width()+ui->frame_2->x()-1,level2->line->y1());
    level3->line->setLine(ui->frame_3->x(),level3->line->y1(),ui->frame_3->width()+ui->frame_3->x()-1,level3->line->y1());
    level4->line->setLine(ui->frame_4->x(),level4->line->y1(),ui->frame_4->width()+ui->frame_4->x()-1,level4->line->y1());
    level5->line->setLine(ui->frame_5->x(),level5->line->y1(),ui->frame_5->width()+ui->frame_5->x()-1,level5->line->y1());
    level6->line->setLine(ui->frame_6->x(),level6->line->y1(),ui->frame_6->width()+ui->frame_6->x()-1,level6->line->y1());
    level7->line->setLine(ui->frame_7->x(),level7->line->y1(),ui->frame_7->width()+ui->frame_7->x()-1,level7->line->y1());
    level8->line->setLine(ui->frame_8->x(),level8->line->y1(),ui->frame_8->width()+ui->frame_8->x()-1,level8->line->y1());

    goerzelrecalc();
}

float FreqLevels::getMaxGoertzel()
{
    float max1,max2;
    goertzel->initialize(sample1->get_freq(),sample1);
    goertzel->reset();
    for (int i=0; i<sample1->get_N(); i++)
    {
        goertzel->process_sample(sample1->get_sample(i)+sample2->get_sample(i));
    }
    max1 = goertzel->get_magnitude_squared()/10000;

    goertzel->initialize(sample2->get_freq(),sample1);
    goertzel->reset();
    for (int i=0; i<sample1->get_N(); i++)
    {
        goertzel->process_sample(sample1->get_sample(i)+sample2->get_sample(i));
    }
    max2 = goertzel->get_magnitude_squared()/10000;
    if (max2>=max1)
    {
        return max2;
    }
    else
    {
        return max1;
    }
}
void FreqLevels::frame_fill(QRect* fill_g, QRect* fill_r, QFrame* frame, Level* lev, QLineEdit* lineedit )
{
    bool ok;
    int recalc;
    recalc =(frame->height()/(float)getMaxGoertzel())*10000;
    goertzel->initialize(lineedit->text().toInt(&ok),sample2);
    goertzel->reset();
    for (int i=0; i<sample1->get_N(); i++)
    {
        goertzel->process_sample(sample1->get_sample(i)+sample2->get_sample(i));
    }
    recalc*=goertzel->get_magnitude_squared()/100000000;

    if (recalc<=lev->level)
    {
        fill_g->setRect(lev->line->x1(),frame->height()+frame->y()-recalc,lev->line->x2()-lev->line->x1(),recalc);
        fill_r->setRect(lev->line->x1(),frame->height()+frame->y()-recalc,0,0);
    }
    if (recalc>lev->level)
    {
        fill_g->setRect(lev->line->x1(),lev->line->y1(),lev->line->x2()-lev->line->x1(),frame->height()+frame->y()-lev->line->y1());
        fill_r->setRect(lev->line->x1(),frame->height()+frame->y()-recalc,lev->line->x2()-lev->line->x1(),recalc-frame->height()+lev->line->y1()-frame->y());
    }

}
void FreqLevels::frame_fill(QRect* fill_g, QRect* fill_r, QFrame* frame, Level* lev, QSpinBox* spinbox )
{
    bool ok;
    int recalc;
    recalc =(frame->height()/(float)getMaxGoertzel())*10000;
    goertzel->initialize(spinbox->text().toInt(&ok),sample1);
    goertzel->reset();
    for (int i=0; i<sample1->get_N(); i++)
    {
        goertzel->process_sample(sample1->get_sample(i)+sample2->get_sample(i));
    }
    recalc*=goertzel->get_magnitude_squared()/100000000;

    if (recalc<=lev->level)
    {
        fill_g->setRect(lev->line->x1(),frame->height()+frame->y()-recalc,lev->line->x2()-lev->line->x1(),recalc);
        fill_r->setRect(lev->line->x1(),frame->height()+frame->y()-recalc,0,0);
    }
    if (recalc>lev->level)
    {
        fill_g->setRect(lev->line->x1(),lev->line->y1(),lev->line->x2()-lev->line->x1(),frame->height()+frame->y()-lev->line->y1());
        fill_r->setRect(lev->line->x1(),frame->height()+frame->y()-recalc,lev->line->x2()-lev->line->x1(),recalc-frame->height()+lev->line->y1()-frame->y());
    }

}
void FreqLevels::goerzelrecalc()
{

    frame_fill(fill1_g,fill1_r,ui->frame_1,level1,ui->Edit_f1);
    frame_fill(fill2_g,fill2_r,ui->frame_2,level2,ui->Edit_f2);
    frame_fill(fill3_g,fill3_r,ui->frame_3,level3,ui->Edit_f3);
    frame_fill(fill4_g,fill4_r,ui->frame_4,level4,ui->Edit_f4);
    frame_fill(fill5_g,fill5_r,ui->frame_5,level5,ui->Edit_f5);
    frame_fill(fill6_g,fill6_r,ui->frame_6,level6,ui->Edit_f6);
    frame_fill(fill7_g,fill7_r,ui->frame_7,level7,ui->Edit_f7);
    frame_fill(fill8_g,fill8_r,ui->frame_8,level8,ui->Edit_f8);

    this->update();

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


void FreqLevels::fillFrame(QPainter *painter)
{
    painter->fillRect(*fill1_g,Qt::green);
    painter->fillRect(*fill1_r,Qt::red);
    painter->fillRect(*fill2_g,Qt::green);
    painter->fillRect(*fill2_r,Qt::red);
    painter->fillRect(*fill3_g,Qt::green);
    painter->fillRect(*fill3_r,Qt::red);
    painter->fillRect(*fill4_g,Qt::green);
    painter->fillRect(*fill4_r,Qt::red);
    painter->fillRect(*fill5_g,Qt::green);
    painter->fillRect(*fill5_r,Qt::red);
    painter->fillRect(*fill6_g,Qt::green);
    painter->fillRect(*fill6_r,Qt::red);
    painter->fillRect(*fill7_g,Qt::green);
    painter->fillRect(*fill7_r,Qt::red);
    painter->fillRect(*fill8_g,Qt::green);
    painter->fillRect(*fill8_r,Qt::red);

}

void FreqLevels::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter_p = &painter;

    fillFrame(&painter);

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
           emit ui->Edit_f1->valueChanged(1);
        }
        if ((mouse_x>ui->frame_2->x())&&(mouse_x<(ui->frame_2->width()+ui->frame_2->x()))&&(mouse_y>ui->frame_2->y())&&(mouse_y<(ui->frame_2->y()+ui->frame_2->height())))
        {
           level2->line->setLine(ui->frame_2->x(),mouse_y,ui->frame_2->width()+ui->frame_2->x()-1,mouse_y);
           level2->level=ui->frame_2->height()-mouse_y+ui->frame_2->y();
           emit ui->Edit_f2->valueChanged(1);
        }
        if ((mouse_x>ui->frame_3->x())&&(mouse_x<(ui->frame_3->width()+ui->frame_3->x()))&&(mouse_y>ui->frame_3->y())&&(mouse_y<(ui->frame_3->y()+ui->frame_3->height())))
        {
           level3->line->setLine(ui->frame_3->x(),mouse_y,ui->frame_3->width()+ui->frame_3->x()-1,mouse_y);
           level3->level=ui->frame_3->height()-mouse_y+ui->frame_3->y();
           emit ui->Edit_f3->valueChanged(1);
        }
        if ((mouse_x>ui->frame_4->x())&&(mouse_x<(ui->frame_4->width()+ui->frame_4->x()))&&(mouse_y>ui->frame_4->y())&&(mouse_y<(ui->frame_4->y()+ui->frame_4->height())))
        {
           level4->line->setLine(ui->frame_4->x(),mouse_y,ui->frame_4->width()+ui->frame_4->x()-1,mouse_y);
           level4->level=ui->frame_4->height()-mouse_y+ui->frame_4->y();
           emit ui->Edit_f4->valueChanged(1);
        }
        if ((mouse_x>ui->frame_5->x())&&(mouse_x<(ui->frame_5->width()+ui->frame_5->x()))&&(mouse_y>ui->frame_5->y())&&(mouse_y<(ui->frame_5->y()+ui->frame_5->height())))
        {
           level5->line->setLine(ui->frame_5->x(),mouse_y,ui->frame_5->width()+ui->frame_5->x()-1,mouse_y);
           level5->level=ui->frame_5->height()-mouse_y+ui->frame_5->y();
           emit ui->Edit_f5->valueChanged(1);
        }
        if ((mouse_x>ui->frame_6->x())&&(mouse_x<(ui->frame_6->width()+ui->frame_6->x()))&&(mouse_y>ui->frame_6->y())&&(mouse_y<(ui->frame_6->y()+ui->frame_6->height())))
        {
           level6->line->setLine(ui->frame_6->x(),mouse_y,ui->frame_6->width()+ui->frame_6->x()-1,mouse_y);
           level6->level=ui->frame_6->height()-mouse_y+ui->frame_6->y();
           emit ui->Edit_f6->valueChanged(1);
        }
        if ((mouse_x>ui->frame_7->x())&&(mouse_x<(ui->frame_7->width()+ui->frame_7->x()))&&(mouse_y>ui->frame_7->y())&&(mouse_y<(ui->frame_7->y()+ui->frame_7->height())))
        {
           level7->line->setLine(ui->frame_7->x(),mouse_y,ui->frame_7->width()+ui->frame_7->x()-1,mouse_y);
           level7->level=ui->frame_7->height()-mouse_y+ui->frame_7->y();
           emit ui->Edit_f7->valueChanged(1);
        }
        if ((mouse_x>ui->frame_8->x())&&(mouse_x<(ui->frame_8->width()+ui->frame_8->x()))&&(mouse_y>ui->frame_8->y())&&(mouse_y<(ui->frame_8->y()+ui->frame_8->height())))
        {
           level8->line->setLine(ui->frame_8->x(),mouse_y,ui->frame_8->width()+ui->frame_8->x()-1,mouse_y);
           level8->level=ui->frame_8->height()-mouse_y+ui->frame_8->y();
           emit ui->Edit_f8->valueChanged(1);
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
    delete fill1_g;
    delete fill1_r;
    delete fill2_g;
    delete fill2_r;
    delete fill3_g;
    delete fill3_r;
    delete fill4_g;
    delete fill4_r;
    delete fill5_g;
    delete fill5_r;
    delete fill6_g;
    delete fill6_r;
    delete fill7_g;
    delete fill7_r;
    delete fill8_g;
    delete fill8_r;
    delete goertzel;
    delete ui;
}
