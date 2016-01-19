#include "sequence.h"
#include "ui_sequence.h"

Sequence::Sequence(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sequence),
     m_pushTimer(new QTimer(this))
   ,   m_device(QAudioDeviceInfo::defaultOutputDevice())
   ,   m_generator(0)
   ,   m_audioOutput(0)
   ,   m_output(0)
   ,   m_buffer(32768, 0)
{
    ui->setupUi(this);

    initializeAudio();

}

Sequence::~Sequence()
{
    delete ui;
}

void Sequence::initializeAudio()
{
    m_format.setSampleRate(44100);
    m_format.setChannelCount(1);
    m_format.setSampleSize(16);
    m_format.setCodec("audio/pcm");
    m_format.setByteOrder(QAudioFormat::LittleEndian);
    m_format.setSampleType(QAudioFormat::SignedInt);

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    if (!info.isFormatSupported(m_format)) {
        qWarning() << "Default format not supported - trying to use nearest";
        m_format = info.nearestFormat(m_format);
    }

    m_generator = new Generator(m_format, 1000000, 600, this);

    createAudioOutput();
}

void Sequence::createAudioOutput()
{
    delete m_audioOutput;
    m_audioOutput = 0;
    m_audioOutput = new QAudioOutput(m_device, m_format, this);
    m_generator->start();
    m_audioOutput->start(m_generator);

}
