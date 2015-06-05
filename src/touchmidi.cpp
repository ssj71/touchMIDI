#include "touchmidi.h"
#include "ui_touchmidi.h"
#include "processthread.h"

TouchMIDI::TouchMIDI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TouchMIDI)
{
    process = new processThread;
    ui->setupUi(this);
    about = new AboutWindow;
    about->setWindowTitle("About TouchMIDI");

    connect(this,SIGNAL(destroyed()),process,SLOT(quit()));
    connect(ui->AboutButton,SIGNAL(clicked()),this,SLOT(showAbout()));
    connect(ui->Mode,SIGNAL(currentIndexChanged(QString)),this,SLOT(changeMode(QString)));
    connect(ui->Mode,SIGNAL(currentIndexChanged(int)),process,SLOT(setMode(int)));

    connect(ui->CTL1_Type,SIGNAL(valueChanged(int)),process,SLOT(setCtl1(int)));
    connect(ui->CTL2_Type,SIGNAL(valueChanged(int)),process,SLOT(setCtl2(int)));
    connect(ui->RelativeCheck,SIGNAL(toggled(bool)),process,SLOT(setRel(bool)));
    connect(ui->Pitch_Spring,SIGNAL(toggled(bool)),process,SLOT(setSpringPitch(bool)));
    connect(ui->MOD_Spring,SIGNAL(toggled(bool)),process,SLOT(setSpringMod(bool)));
    connect(ui->CTL1_Spring,SIGNAL(toggled(bool)),process,SLOT(setSpring1(bool)));
    connect(ui->CTL2_Spring,SIGNAL(toggled(bool)),process,SLOT(setSpring2(bool)));

    connect(ui->XType,SIGNAL(currentIndexChanged(int)),process,SLOT(setXtype(int)));
    connect(ui->YType,SIGNAL(currentIndexChanged(int)),process,SLOT(setYtype(int)));
    connect(ui->ZType,SIGNAL(currentIndexChanged(int)),process,SLOT(setZtype(int)));
    connect(ui->CTLX_Type,SIGNAL(valueChanged(int)),process,SLOT(setXctl(int)));
    connect(ui->CTLY_Type,SIGNAL(valueChanged(int)),process,SLOT(setYctl(int)));
    connect(ui->CTLZ_Type,SIGNAL(valueChanged(int)),process,SLOT(setZctl(int)));
    connect(ui->note_low,SIGNAL(valueChanged(int)),process,SLOT(setNoteLow(int)));
    connect(ui->note_high,SIGNAL(valueChanged(int)),process,SLOT(setNoteHigh(int)));

    connect(process,SIGNAL(pitchChanged(int)),ui->Pitch,SLOT(setValue(int)));
    connect(process,SIGNAL(modChanged(int)),ui->MOD,SLOT(setValue(int)));
    connect(process,SIGNAL(ctl1Changed(int)),ui->CTL1,SLOT(setValue(int)));
    connect(process,SIGNAL(ctl2Changed(int)),ui->CTL2,SLOT(setValue(int)));
    connect(process,SIGNAL(Xchanged(int)),ui->XVal,SLOT(setNum(int)));
    connect(process,SIGNAL(Ychanged(int)),ui->YVal,SLOT(setNum(int)));
    connect(process,SIGNAL(Zchanged(int)),ui->ZVal,SLOT(setNum(int)));

    process->start();
}

TouchMIDI::~TouchMIDI()
{
    delete ui;
}

void TouchMIDI::changeMode(const QString &modeSelected)
{
    if(modeSelected == "Control Wheel")
    {
        ui->CTLWheelWidget->move(0,30);
        ui->CTLWheelWidget->setVisible(true);
        ui->XYWidget->move(0,240);
        ui->XYWidget->setVisible(false);
        mode = 1;
    }
    else
    {
        ui->CTLWheelWidget->move(0,240);
        ui->CTLWheelWidget->setVisible(false);
        ui->XYWidget->move(0,30);
        ui->XYWidget->setVisible(true);
        mode = 2;
    }
}

void TouchMIDI::showAbout()
{
    if (about->isHidden())
        about->show();
    else
        about->hide();
}
