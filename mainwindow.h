#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sample.h"
#include "goerzel.h"
#include "QValidator"
#include "QString"
#include "QLineEdit"
#include "spectrumwindow.h"
#include "qcustomplot.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    SpectrumWindow* spectrumwindow;
    Sample *sample1, *sample2;
    Goertzel* goertzel;
    QVector<double> *x, *y;
    int dtmf_enc_data[4][4];
    QVector<QVector<QLineEdit*>*>* dtmf_freq_lineedit;
    QVector<QLineEdit*>* dtmf_data_lineedit;
    explicit MainWindow(QWidget *parent = 0);
    void refresh_graph(Sample*, QLineEdit *);
    QPalette p;
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    void resizeEvent(QResizeEvent *);
    void clear_table_background();

public slots:
    void change_rate();
    void change_freq1();
    void change_freq2();
    void change_freqs(void);


    void change_N();
    void initialize_controls(void);
    void initialize_plot(void);
    void initialize_signals(void);
    void change_dtmf_data(const QString &data);
    void dtmf_button_pressed(void);
    void showspectr(void);

};

#endif // MAINWINDOW_H
