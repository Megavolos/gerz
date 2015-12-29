#include "spectrumwindow.h"
#include "ui_spectrumwindow.h"
#include "mainwindow.h"
#include <QPainter>
SpectrumWindow::SpectrumWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpectrumWindow)
{
    ui->setupUi(this);
    bool ok;
    bins = new Bins;
    bins->freq = new QVector<int>;
    bins->value = new QVector<float>;
    bkgrd=new QRect;
    grid = new Grid();
    offset_left_x=70;
    offset_right_x=10;
    offset_bottom_y=10;
    offset_top_y=10;

    this->setWindowTitle("Spectrogram");
    geometry = new Geometry;



    bins_step=ui->edit_BinsStep->text().toInt(&ok);
    max_freq=ui->edit_MaxFreq->text().toInt(&ok);
    min_freq=ui->edit_MinFreq->text().toInt(&ok);
    this->setMouseTracking(true);
    ui->spectrum_widget->setMouseTracking(true);

    grid->SetNx(10);
    grid->SetNy(10);
    grid->SetMaxValue_X(max_freq);
    grid->SetMaxValue_Y(300);
    grid->SetMinValue_X(min_freq);
    grid->SetMinValue_Y(0);
    grid->SetNLength(5);
    mouse_dev=1;

    connect (ui->edit_MaxFreq,SIGNAL(editingFinished()),this,SLOT(setmaxfreq()));
    connect (ui->edit_MinFreq,SIGNAL(editingFinished()),this,SLOT(setminfreq()));
    connect (ui->zero_cut,SIGNAL(stateChanged(int)),this,SLOT(setleftcut()));
    connect (ui->edit_BinsStep,SIGNAL(editingFinished()),this,SLOT(setbinsstep()));

}
void SpectrumWindow::showEvent(QShowEvent *)
{
    bool ok;
    int x1,x2;
    x1=ui->spectrum_widget->x()+offset_left_x;
    x2=ui->spectrum_widget->width();
    dev = (ui->edit_MaxFreq->text().toInt(&ok)-ui->edit_MinFreq->text().toInt(&ok))/(x2-x1);
    if (!dev) dev=1;
    bins->value->resize(x2-x1);
    binsrecalc();
    this->update();
}
void SpectrumWindow::resizeEvent(QResizeEvent *)
{
    int x1,x2;
    bool ok;
    x1=ui->spectrum_widget->x();
    x1+=offset_left_x;
    x2=ui->spectrum_widget->width();
    //x2-=offset_left_x;
    //x2-=offset_right_x;
    bins->value->resize(x2-x1);
    dev = (ui->edit_MaxFreq->text().toInt(&ok)-ui->edit_MinFreq->text().toInt(&ok));
    dev/=(float)(ui->spectrum_widget->width()-ui->spectrum_widget->x()-offset_left_x);
    if (!dev) dev=1;
    binsrecalc();
}
void SpectrumWindow::setbinsstep()
{
    bool ok;
    bins_step=ui->edit_BinsStep->text().toInt(&ok);
    binsrecalc();
    this->update();
}

void SpectrumWindow::setleftcut()
{

    binsrecalc();
    this->update();
}

void SpectrumWindow::setmaxfreq()
{
    bool ok;
    max_freq=ui->edit_MaxFreq->text().toInt(&ok);
    grid->SetMaxValue_X(max_freq);
    dev = (ui->edit_MaxFreq->text().toInt(&ok)-ui->edit_MinFreq->text().toInt(&ok));
    dev/=(float)(ui->spectrum_widget->width()-ui->spectrum_widget->x()-offset_left_x);
    if (!dev) dev=1;
    binsrecalc();
    this->update();
}
void SpectrumWindow::setminfreq()
{
    bool ok;

    min_freq=ui->edit_MinFreq->text().toInt(&ok);
    grid->SetMinValue_X(min_freq);
    dev = (ui->edit_MaxFreq->text().toInt(&ok)-ui->edit_MinFreq->text().toInt(&ok));
    dev/=(float)(ui->spectrum_widget->width()-ui->spectrum_widget->x()-offset_left_x);
    if (!dev) dev=1;
    binsrecalc();
    this->update();
}
void SpectrumWindow::mouseMoveEvent(QMouseEvent *event)
{
    int freq;
    float val;

    mouse_x=event->pos().x();
    mouse_y=event->pos().y();

    //Проверяем где курсор, чтобы значения не пересчитывались в ненужных местах
    if ((mouse_y<widget_y2+50)&&(mouse_y>widget_y1)&&(mouse_x>widget_x1-10))
    {
        freq=((mouse_x-widget_x1)*(ui->edit_MaxFreq->text().toInt() - ui->edit_MinFreq->text().toInt())/(ui->spectrum_widget->width()-widget_x1))+ui->edit_MinFreq->text().toInt();
        if (mouse_x<widget_x1) freq=ui->edit_MinFreq->text().toInt();
        if (mouse_x>ui->spectrum_widget->width()) freq=ui->edit_MaxFreq->text().toInt();
        val=(widget_y2-mouse_y);
        val*=grid->GetMaxValue_Y();
        val/=(widget_y2-widget_y1);
        if (mouse_y>widget_y2) val=0;


        ui->label_freq->setText(QString::number(freq));
        ui->label_value->setText(QString::number(val));
    }

}
void SpectrumWindow::wheelEvent(QWheelEvent *event)
{


    if ((event->delta())>0)
    {
        mouse_dev+=event->delta()/500000.0;
        if (grid->GetMaxValue_Y()/mouse_dev>0) grid->SetMaxValue_Y( grid->GetMaxValue_Y()/mouse_dev);
    }
    if ((event->delta())<0)
    {
        mouse_dev-=event->delta()/500000.0;
        if (mouse_dev<=0) mouse_dev=1;

    if ((grid->GetMaxValue_Y()*mouse_dev)<(1000000000.0))
    {
        grid->SetMaxValue_Y( grid->GetMaxValue_Y()*(mouse_dev));
    }

    }

    this->update();
}

void SpectrumWindow::binsrecalc()
{  
    for (int f=0; f<bins->value->size(); f++)   //от 0 до размера массива значений бинов, то есть до widget_x2-widget_x1
    {

        goertzel->initialize(min_freq+dev*f,sample1);    //dev-шаг частоты,dev*f-частота текущего бина
        goertzel->reset();

        for (int i=0; i<sample1->get_N(); i++)  //проход по всем семплам
        {
            goertzel->process_sample(sample1->get_sample(i)+sample2->get_sample(i));
        }
        bins->value[0][f]=goertzel->get_magnitude_squared()/10000;
        if ((ui->zero_cut->isChecked()&&((f*dev)<(sample1->get_sample_rate()/(2*sample1->get_N()))))) bins->value[0][f]=0;
    }
}

void SpectrumWindow::drawspectr(QPainter* p, Bins* b)
{
    p->setPen(QPen(Qt::red,2,Qt::SolidLine));
    for (int f=0; f<bins->value->size(); f++)
    {
        grid->DrawBin(p,f, b->value->at(f));
    }
}


void SpectrumWindow::paintEvent(QPaintEvent *)
{
    bool ok;
    QPainter painter(this);
    QLine x_axe,y_axe;

    widget_x1=ui->spectrum_widget->x()+offset_left_x;
    widget_y1=ui->spectrum_widget->y()+offset_top_y;
    widget_x2=ui->spectrum_widget->width()-offset_left_x-offset_right_x;
    widget_y2=ui->spectrum_widget->height()-offset_bottom_y;
    bkgrd->setX(widget_x1);
    bkgrd->setY(widget_y1);
    bkgrd->setWidth(widget_x2);
    bkgrd->setHeight(widget_y2);

    painter.setPen(QPen(Qt::white,1,Qt::SolidLine));
    painter.drawRect(*bkgrd);
    painter.fillRect(*bkgrd,Qt::white);

    x_axe.setLine(widget_x1,widget_y2,widget_x2,widget_y2);
    y_axe.setLine(widget_x1,widget_y1,widget_x1,widget_y2);

    painter.fillRect(x_axe.x1(),x_axe.y1(),x_axe.x2()+1,bkgrd->height(),QWidget::palette().color(QWidget::backgroundRole()));
    bkgrd->setHeight(y_axe.y2()-y_axe.y1());
    painter.setPen(QPen(Qt::black,1,Qt::SolidLine));
    painter.drawLine(x_axe);
    painter.drawLine(y_axe);

    painter.drawText(x_axe.x1()-9,ui->spectrum_widget->height()+15,QString::number(grid->GetMinValue_X()));
    painter.drawText(ui->spectrum_widget->width()-10,ui->spectrum_widget->height()+15,QString::number(grid->GetMaxValue_X()));



    grid->setcoord(bkgrd);
    grid->DrawGrid(&painter);

    //dev = (ui->edit_MaxFreq->text().toInt(&ok)-ui->edit_MinFreq->text().toInt(&ok));
    //dev/=(float)(ui->spectrum_widget->width()-x_axe.x1());
    //if (!dev) dev=1;
    drawspectr(&painter,bins);


}


SpectrumWindow::~SpectrumWindow()
{

    delete bkgrd;
    delete ui;
    delete bins->freq;
    delete bins->value;
    delete geometry;

}
