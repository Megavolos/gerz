#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <QWidget>
#include <QIODevice>
#include <QAudioDeviceInfo>
#include <QAudioOutput>
#include "qmath.h"
#include <qendian.h>
#include <QByteArray>
#include "audiooutput.h"
#include <QTimer>
#include <QDebug>
namespace Ui {
class Sequence;
}

class Sequence : public QWidget
{
    Q_OBJECT

public:
    explicit Sequence(QWidget *parent = 0);
    ~Sequence();




private:
    Ui::Sequence *ui;
    QTimer *m_pushTimer;
    QAudioDeviceInfo m_device;
    Generator *m_generator;
    QAudioOutput *m_audioOutput;
    QIODevice *m_output; // not owned
    QAudioFormat m_format;

    bool m_pullMode;
    QByteArray m_buffer;

    void initializeAudio();
    void createAudioOutput();
};

#endif // SEQUENCE_H
