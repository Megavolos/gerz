#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    x = new QVector<double>;
    y = new QVector<double>;
    spectrumwindow = new SpectrumWindow(this);
    sample1 = new Sample;
    sample2 = new Sample;
    goertzel = new Goertzel;
    dtmf_freq_lineedit = new QVector<QVector<QLineEdit*>*>();
    dtmf_data_lineedit = new QVector<QLineEdit*>();
    initialize_plot();
    initialize_controls();
    initialize_signals();
    spectrumwindow->sample1=sample1;
    spectrumwindow->sample2=sample2;
    spectrumwindow->goertzel=goertzel;
	

}

MainWindow::~MainWindow()
{

    delete spectrumwindow;
    delete x;
    delete y;
    delete sample1;
    delete dtmf_freq_lineedit->at(0);
    delete dtmf_freq_lineedit->at(1);
    delete dtmf_freq_lineedit;

    delete dtmf_data_lineedit;

    delete sample2;
    delete goertzel;
    delete ui;

}
void MainWindow::change_freq1()
{

    refresh_graph (sample1,ui->edit_s1);
    if (spectrumwindow->isVisible())
    {
        spectrumwindow->binsrecalc();
        spectrumwindow->update();
    }
}
void MainWindow::change_freq2()
{
    refresh_graph (sample2,ui->edit_s2);
    if (spectrumwindow->isVisible())
    {
        spectrumwindow->binsrecalc();
        spectrumwindow->update();
    }
}


void MainWindow::change_N()
{
    bool ok;
    ui->label_f_res->setText("Freq.resolution: "+QString::number(ui->edit_rate->text().toInt(&ok)/ui->edit_N->text().toInt(&ok)) + " Hz");
    refresh_graph (sample1,ui->edit_N);
    if (spectrumwindow->isVisible())
    {
        spectrumwindow->binsrecalc();
        spectrumwindow->update();
    }
}
void MainWindow::change_rate()
{
    bool ok;
    ui->label_f_res->setText("Freq.resolution: "+QString::number(ui->edit_rate->text().toInt(&ok)/ui->edit_N->text().toInt(&ok)) + " Hz");
    refresh_graph (sample1,ui->edit_rate);
    if (spectrumwindow->isVisible())
    {
      spectrumwindow->binsrecalc();
      spectrumwindow->update();
    }
}

void MainWindow::refresh_graph (Sample* sample,QLineEdit* qle)
{
    QString str;
    bool ok;
    str=qle->text();
    if (qle==ui->edit_rate)
        sample->set_sample_rate(str.toUInt(&ok,10));

    if (qle==ui->edit_N)
    {
         sample->set_N(str.toUInt(&ok,10));
         x->resize(sample->get_N());
         y->resize(sample->get_N());
         ui->widget->xAxis->setRange( 0, sample->get_N() );
    }

    if ((qle==ui->edit_s1)||(qle==ui->edit_s2))
        sample->set_freq(str.toUInt(&ok,10));



    for (int i=0; i<sample->get_N(); i++)
    {
        (*x)[i]=i;
        (*y)[i]=(sample1->get_sample(i)+sample2->get_sample(i));
    }
    ui->widget->graph(0)->setData( *x, *y );
    ui->widget->graph(1)->setData( *x, *y );
    ui->widget->replot();
}

void MainWindow::resizeEvent(QResizeEvent *)
{

}
void MainWindow::initialize_plot(void)
{
    sample1->set_sample_rate(10000);
    sample1->set_freq(300);
    sample1->set_N(250);
    sample2->set_freq(0);

    x->resize(sample1->get_N());
    y->resize(sample1->get_N());
    goertzel->initialize(11000,sample1);
   goertzel->reset();
    for (int i=0; i<sample1->get_N(); i++)
    {
        goertzel->process_sample(sample1->get_sample(i));
        (*x)[i]=i;
        (*y)[i]=(sample1->get_sample(i)+sample2->get_sample(i));
    }

    // Create graph and assign data to it:
    ui->widget->addGraph();
    ui->widget->addGraph();
    ui->widget->graph(0)->setData( *x, *y );
    ui->widget->graph(1)->setData( *x, *y );

    ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone );
    ui->widget->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);
    // Give the axes some labels:
    ui->widget->xAxis->setLabel( "x" );
    ui->widget->yAxis->setLabel( "y" );

    // Set axes ranges, so we see all data:
    ui->widget->xAxis->setRange( 0, sample1->get_N() );
    ui->widget->yAxis->setRange( 0, 400 );
}

void MainWindow::initialize_controls(void)
{
    bool ok;
    dtmf_freq_lineedit->append(new QVector<QLineEdit*>());
    dtmf_freq_lineedit->append(new QVector<QLineEdit*>());
    dtmf_freq_lineedit->at(0)->append(ui->f11);
    dtmf_freq_lineedit->at(0)->append(ui->f12);
    dtmf_freq_lineedit->at(0)->append(ui->f13);
    dtmf_freq_lineedit->at(0)->append(ui->f14);
    dtmf_freq_lineedit->at(1)->append(ui->f21);
    dtmf_freq_lineedit->at(1)->append(ui->f22);
    dtmf_freq_lineedit->at(1)->append(ui->f23);
    dtmf_freq_lineedit->at(1)->append(ui->f24);


    (*dtmf_freq_lineedit)[0]->at(0)->setText("1209");
    (*dtmf_freq_lineedit)[0]->at(1)->setText("1336");
    (*dtmf_freq_lineedit)[0]->at(2)->setText("1477");
    (*dtmf_freq_lineedit)[0]->at(3)->setText("1633");
    (*dtmf_freq_lineedit)[1]->at(0)->setText("697");
    (*dtmf_freq_lineedit)[1]->at(1)->setText("770");
    (*dtmf_freq_lineedit)[1]->at(2)->setText("852");
    (*dtmf_freq_lineedit)[1]->at(3)->setText("941");

    dtmf_data_lineedit->append(ui->f11_f21);
    dtmf_data_lineedit->append(ui->f12_f21);
    dtmf_data_lineedit->append(ui->f13_f21);
    dtmf_data_lineedit->append(ui->f14_f21);
    dtmf_data_lineedit->append(ui->f11_f22);
    dtmf_data_lineedit->append(ui->f12_f22);
    dtmf_data_lineedit->append(ui->f13_f22);
    dtmf_data_lineedit->append(ui->f14_f22);
    dtmf_data_lineedit->append(ui->f11_f23);
    dtmf_data_lineedit->append(ui->f12_f23);
    dtmf_data_lineedit->append(ui->f13_f23);
    dtmf_data_lineedit->append(ui->f14_f23);
    dtmf_data_lineedit->append(ui->f11_f24);
    dtmf_data_lineedit->append(ui->f12_f24);
    dtmf_data_lineedit->append(ui->f13_f24);
    dtmf_data_lineedit->append(ui->f14_f24);


    ui->edit_rate->setValidator(new QIntValidator(0,99999999,this)  );
    ui->edit_N->setValidator(new QIntValidator(0,99999999,this)  );
    ui->edit_s1->setValidator(new QIntValidator(0,99999999,this)  );
    ui->edit_N->setText(QString::number(sample1->get_N()));
    ui->edit_s1->setText(QString::number(sample1->get_freq()));
    ui->edit_s2->setText(QString::number(sample2->get_freq()));
    ui->edit_rate->setText(QString::number(sample1->get_sample_rate()));
    ui->pushButton_1->setText(ui->f11_f21->text());
    ui->pushButton_2->setText(ui->f12_f21->text());
    ui->pushButton_3->setText(ui->f13_f21->text());
    ui->pushButton_4->setText(ui->f14_f21->text());
    ui->pushButton_5->setText(ui->f11_f22->text());
    ui->pushButton_6->setText(ui->f12_f22->text());
    ui->pushButton_7->setText(ui->f13_f22->text());
    ui->pushButton_8->setText(ui->f14_f22->text());
    ui->pushButton_9->setText(ui->f11_f23->text());
    ui->pushButton_10->setText(ui->f12_f23->text());
    ui->pushButton_11->setText(ui->f13_f23->text());
    ui->pushButton_12->setText(ui->f14_f23->text());
    ui->pushButton_13->setText(ui->f11_f24->text());
    ui->pushButton_14->setText(ui->f12_f24->text());
    ui->pushButton_15->setText(ui->f13_f24->text());
    ui->pushButton_16->setText(ui->f14_f24->text());
    ui->pushButton_17->setText("Show spectrogram");
    spectrumwindow->setWindowFlags(Qt::Window);
    this->setWindowTitle("Goertzel DTFM test");

    ui->label_f_res->setToolTip("Разрешающая способность алгоритма Гёрцеля по частоте.\nОпределяется отношением Sample Rate/Sample Buffer.\nЕсли разница между частотами в сигнале будет\nменьше,чем отношение частоты дискретизации к длине буфера\nто в сигнале будет невозможно выделить одну из частот.");
    ui->edit_rate->setToolTip("Частота дискретизации сигнала.\nУстановите частоту,с которой вы получаете \nданные из АЦП вашего микроконтроллера");
    ui->edit_N->setToolTip("Размер(длина) буфера АЦП в семплах\nВ семплах, а не в байтах/битах!");
    ui->edit_s1->setToolTip("Частота первого тона. Можно установить вручную.\nПо нажатию одной из DTMF кнопок установится\nчастота из ряда f1");
    ui->edit_s2->setToolTip("Частота второго тона. Можно установить вручную.\nПо нажатию одной из DTMF кнопок установится\nчастота из ряда f2");

    ui->label_f_res->setText("Freq.resolution: "+QString::number(ui->edit_rate->text().toInt(&ok)/ui->edit_N->text().toInt(&ok)) + " Hz");
}

void MainWindow::initialize_signals(void)
{
    connect(ui->edit_rate,SIGNAL(editingFinished()),this,SLOT(change_rate()));
    connect(ui->edit_s1,SIGNAL(textChanged(QString)),this,SLOT(change_freq1()));
    connect(ui->edit_s2,SIGNAL(textChanged(QString)),this,SLOT(change_freq2()));
    connect(ui->edit_N,SIGNAL(editingFinished()),this,SLOT(change_N()));
    connect(ui->f11_f21,SIGNAL(textEdited(const QString& )),this,SLOT(change_dtmf_data(const QString&)));
    connect(ui->f12_f21,SIGNAL(textEdited(const QString& )),this,SLOT(change_dtmf_data(const QString&)));
    connect(ui->f13_f21,SIGNAL(textEdited(const QString& )),this,SLOT(change_dtmf_data(const QString&)));
    connect(ui->f14_f21,SIGNAL(textEdited(const QString& )),this,SLOT(change_dtmf_data(const QString&)));
    connect(ui->f11_f22,SIGNAL(textEdited(const QString& )),this,SLOT(change_dtmf_data(const QString&)));
    connect(ui->f12_f22,SIGNAL(textEdited(const QString& )),this,SLOT(change_dtmf_data(const QString&)));
    connect(ui->f13_f22,SIGNAL(textEdited(const QString& )),this,SLOT(change_dtmf_data(const QString&)));
    connect(ui->f14_f22,SIGNAL(textEdited(const QString& )),this,SLOT(change_dtmf_data(const QString&)));
    connect(ui->f11_f23,SIGNAL(textEdited(const QString& )),this,SLOT(change_dtmf_data(const QString&)));
    connect(ui->f12_f23,SIGNAL(textEdited(const QString& )),this,SLOT(change_dtmf_data(const QString&)));
    connect(ui->f13_f23,SIGNAL(textEdited(const QString& )),this,SLOT(change_dtmf_data(const QString&)));
    connect(ui->f14_f23,SIGNAL(textEdited(const QString& )),this,SLOT(change_dtmf_data(const QString&)));
    connect(ui->f11_f24,SIGNAL(textEdited(const QString& )),this,SLOT(change_dtmf_data(const QString&)));
    connect(ui->f12_f24,SIGNAL(textEdited(const QString& )),this,SLOT(change_dtmf_data(const QString&)));
    connect(ui->f13_f24,SIGNAL(textEdited(const QString& )),this,SLOT(change_dtmf_data(const QString&)));
    connect(ui->f14_f24,SIGNAL(textEdited(const QString& )),this,SLOT(change_dtmf_data(const QString&)));
    connect(ui->f11,SIGNAL(editingFinished()),this,SLOT(change_freqs()));
    connect(ui->f12,SIGNAL(editingFinished()),this,SLOT(change_freqs()));
    connect(ui->f13,SIGNAL(editingFinished()),this,SLOT(change_freqs()));
    connect(ui->f14,SIGNAL(editingFinished()),this,SLOT(change_freqs()));
    connect(ui->f21,SIGNAL(editingFinished()),this,SLOT(change_freqs()));
    connect(ui->f22,SIGNAL(editingFinished()),this,SLOT(change_freqs()));
    connect(ui->f23,SIGNAL(editingFinished()),this,SLOT(change_freqs()));
    connect(ui->f24,SIGNAL(editingFinished()),this,SLOT(change_freqs()));
    connect(ui->pushButton_1,SIGNAL(pressed()),this,SLOT(dtmf_button_pressed()));
    connect(ui->pushButton_2,SIGNAL(pressed()),this,SLOT(dtmf_button_pressed()));
    connect(ui->pushButton_3,SIGNAL(pressed()),this,SLOT(dtmf_button_pressed()));
    connect(ui->pushButton_4,SIGNAL(pressed()),this,SLOT(dtmf_button_pressed()));
    connect(ui->pushButton_5,SIGNAL(pressed()),this,SLOT(dtmf_button_pressed()));
    connect(ui->pushButton_6,SIGNAL(pressed()),this,SLOT(dtmf_button_pressed()));
    connect(ui->pushButton_7,SIGNAL(pressed()),this,SLOT(dtmf_button_pressed()));
    connect(ui->pushButton_8,SIGNAL(pressed()),this,SLOT(dtmf_button_pressed()));
    connect(ui->pushButton_9,SIGNAL(pressed()),this,SLOT(dtmf_button_pressed()));
    connect(ui->pushButton_10,SIGNAL(pressed()),this,SLOT(dtmf_button_pressed()));
    connect(ui->pushButton_11,SIGNAL(pressed()),this,SLOT(dtmf_button_pressed()));
    connect(ui->pushButton_12,SIGNAL(pressed()),this,SLOT(dtmf_button_pressed()));
    connect(ui->pushButton_13,SIGNAL(pressed()),this,SLOT(dtmf_button_pressed()));
    connect(ui->pushButton_14,SIGNAL(pressed()),this,SLOT(dtmf_button_pressed()));
    connect(ui->pushButton_15,SIGNAL(pressed()),this,SLOT(dtmf_button_pressed()));
    connect(ui->pushButton_16,SIGNAL(pressed()),this,SLOT(dtmf_button_pressed()));
    connect(ui->pushButton_17,SIGNAL(pressed()),this,SLOT(showspectr()));
}
void MainWindow::change_freqs()
{
    clear_table_background();
}

void MainWindow::showspectr(void)
{

    spectrumwindow->show();
}

void MainWindow::change_dtmf_data(const QString &data )
{

    QObject* source=QObject::sender();
    if (ui->f11_f21==(QLineEdit*)source) ui->pushButton_1->setText(data);
    if (ui->f12_f21==(QLineEdit*)source) ui->pushButton_2->setText(data);
    if (ui->f13_f21==(QLineEdit*)source) ui->pushButton_3->setText(data);
    if (ui->f14_f21==(QLineEdit*)source) ui->pushButton_4->setText(data);
    if (ui->f11_f22==(QLineEdit*)source) ui->pushButton_5->setText(data);
    if (ui->f12_f22==(QLineEdit*)source) ui->pushButton_6->setText(data);
    if (ui->f13_f22==(QLineEdit*)source) ui->pushButton_7->setText(data);
    if (ui->f14_f22==(QLineEdit*)source) ui->pushButton_8->setText(data);
    if (ui->f11_f23==(QLineEdit*)source) ui->pushButton_9->setText(data);
    if (ui->f12_f23==(QLineEdit*)source) ui->pushButton_10->setText(data);
    if (ui->f13_f23==(QLineEdit*)source) ui->pushButton_11->setText(data);
    if (ui->f14_f23==(QLineEdit*)source) ui->pushButton_12->setText(data);
    if (ui->f11_f24==(QLineEdit*)source) ui->pushButton_13->setText(data);
    if (ui->f12_f24==(QLineEdit*)source) ui->pushButton_14->setText(data);
    if (ui->f13_f24==(QLineEdit*)source) ui->pushButton_15->setText(data);
    if (ui->f14_f24==(QLineEdit*)source) ui->pushButton_16->setText(data);

}
void MainWindow::clear_table_background()
{
    ui->groupBox->setStyleSheet("QLineEdit {background-color: white}");
   /* ui->f11_f21->setStyleSheet("background-color: white");
    ui->f12_f21->setStyleSheet("background-color: white");
    ui->f13_f21->setStyleSheet("background-color: white");
    ui->f14_f21->setStyleSheet("background-color: white");
    ui->f11_f22->setStyleSheet("background-color: white");
    ui->f12_f22->setStyleSheet("background-color: white");
    ui->f13_f22->setStyleSheet("background-color: white");
    ui->f14_f22->setStyleSheet("background-color: white");
    ui->f11_f23->setStyleSheet("background-color: white");
    ui->f12_f23->setStyleSheet("background-color: white");
    ui->f13_f23->setStyleSheet("background-color: white");
    ui->f14_f23->setStyleSheet("background-color: white");
    ui->f11_f24->setStyleSheet("background-color: white");
    ui->f12_f24->setStyleSheet("background-color: white");
    ui->f13_f24->setStyleSheet("background-color: white");
    ui->f14_f24->setStyleSheet("background-color: white");
    ui->f11->setStyleSheet("background-color: white");
    ui->f12->setStyleSheet("background-color: white");
    ui->f13->setStyleSheet("background-color: white");
    ui->f14->setStyleSheet("background-color: white");
    ui->f21->setStyleSheet("background-color: white");
    ui->f22->setStyleSheet("background-color: white");
    ui->f23->setStyleSheet("background-color: white");*/
}

void MainWindow::dtmf_button_pressed(void)
{

    QObject* source=QObject::sender();
    QPushButton* button = (QPushButton*)source;
    clear_table_background();

    ui->f24->setStyleSheet("background-color: white");
    if (button->objectName()=="pushButton_1")
    {
        this->setStyleSheet("QLineEdit#f11_f21 { border: 1px solid red }");
        ui->edit_s1->setText(ui->f11->text());
        ui->edit_s2->setText(ui->f21->text());
        //ui->f11_f21->setStyleSheet("background-color: red");
        ui->f11->setStyleSheet("background-color: yellow");
        ui->f21->setStyleSheet("background-color: yellow");



    }
    if (button->objectName()=="pushButton_2")
    {
        ui->edit_s1->setText(ui->f12->text());
        ui->edit_s2->setText(ui->f21->text());
        ui->f12_f21->setStyleSheet("background-color: red");
        ui->f12->setStyleSheet("background-color: yellow");
        ui->f21->setStyleSheet("background-color: yellow");


    }
    if (button->objectName()=="pushButton_3")
    {
        ui->edit_s1->setText(ui->f13->text());
        ui->edit_s2->setText(ui->f21->text());
        ui->f13_f21->setStyleSheet("background-color: red");
        ui->f13->setStyleSheet("background-color: yellow");
        ui->f21->setStyleSheet("background-color: yellow");

    }
    if (button->objectName()=="pushButton_4")
    {
        ui->edit_s1->setText(ui->f14->text());
        ui->edit_s2->setText(ui->f21->text());
        ui->f14_f21->setStyleSheet("background-color: red");
        ui->f14->setStyleSheet("background-color: yellow");
        ui->f21->setStyleSheet("background-color: yellow");

    }
    if (button->objectName()=="pushButton_5")
    {
        ui->edit_s1->setText(ui->f11->text());
        ui->edit_s2->setText(ui->f22->text());
        ui->f11_f22->setStyleSheet("background-color: red");
        ui->f11->setStyleSheet("background-color: yellow");
        ui->f22->setStyleSheet("background-color: yellow");

    }
    if (button->objectName()=="pushButton_6")
    {
        ui->edit_s1->setText(ui->f12->text());
        ui->edit_s2->setText(ui->f22->text());
        ui->f12_f22->setStyleSheet("background-color: red");
        ui->f12->setStyleSheet("background-color: yellow");
        ui->f22->setStyleSheet("background-color: yellow");

    }
    if (button->objectName()=="pushButton_7")
    {
        ui->edit_s1->setText(ui->f13->text());
        ui->edit_s2->setText(ui->f22->text());
        ui->f13_f22->setStyleSheet("background-color: red");
        ui->f13->setStyleSheet("background-color: yellow");
        ui->f22->setStyleSheet("background-color: yellow");

    }
    if (button->objectName()=="pushButton_8")
    {
        ui->edit_s1->setText(ui->f14->text());
        ui->edit_s2->setText(ui->f22->text());
        ui->f14_f22->setStyleSheet("background-color: red");
        ui->f14->setStyleSheet("background-color: yellow");
        ui->f22->setStyleSheet("background-color: yellow");

    }
    if (button->objectName()=="pushButton_9")
    {
        ui->edit_s1->setText(ui->f11->text());
        ui->edit_s2->setText(ui->f23->text());
        ui->f11_f23->setStyleSheet("background-color: red");
        ui->f11->setStyleSheet("background-color: yellow");
        ui->f23->setStyleSheet("background-color: yellow");

    }
    if (button->objectName()=="pushButton_10")
    {
        ui->edit_s1->setText(ui->f12->text());
        ui->edit_s2->setText(ui->f23->text());
        ui->f12_f23->setStyleSheet("background-color: red");
        ui->f12->setStyleSheet("background-color: yellow");
        ui->f23->setStyleSheet("background-color: yellow");

    }
    if (button->objectName()=="pushButton_11")
    {
        ui->edit_s1->setText(ui->f13->text());
        ui->edit_s2->setText(ui->f23->text());
        ui->f13_f23->setStyleSheet("background-color: red");
        ui->f13->setStyleSheet("background-color: yellow");
        ui->f23->setStyleSheet("background-color: yellow");

    }
    if (button->objectName()=="pushButton_12")
    {
        ui->edit_s1->setText(ui->f14->text());
        ui->edit_s2->setText(ui->f23->text());
        ui->f14_f23->setStyleSheet("background-color: red");
        ui->f14->setStyleSheet("background-color: yellow");
        ui->f23->setStyleSheet("background-color: yellow");

    }
    if (button->objectName()=="pushButton_13")
    {
        ui->edit_s1->setText(ui->f11->text());
        ui->edit_s2->setText(ui->f24->text());
        ui->f11_f24->setStyleSheet("background-color: red");
        ui->f11->setStyleSheet("background-color: yellow");
        ui->f24->setStyleSheet("background-color: yellow");

    }
    if (button->objectName()=="pushButton_14")
    {
        ui->edit_s1->setText(ui->f12->text());
        ui->edit_s2->setText(ui->f24->text());
        ui->f12_f24->setStyleSheet("background-color: red");
        ui->f12->setStyleSheet("background-color: yellow");
        ui->f24->setStyleSheet("background-color: yellow");

    }
    if (button->objectName()=="pushButton_15")
    {
        ui->edit_s1->setText(ui->f13->text());
        ui->edit_s2->setText(ui->f24->text());
        ui->f13_f24->setStyleSheet("background-color: red");
        ui->f13->setStyleSheet("background-color: yellow");
        ui->f24->setStyleSheet("background-color: yellow");

    }
    if (button->objectName()=="pushButton_16")
    {
        ui->edit_s1->setText(ui->f14->text());
        ui->edit_s2->setText(ui->f24->text());
        ui->f14_f24->setStyleSheet("background-color: red");
        ui->f14->setStyleSheet("background-color: yellow");
        ui->f24->setStyleSheet("background-color: yellow");

    }
}
