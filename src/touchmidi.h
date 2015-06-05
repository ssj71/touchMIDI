#ifndef TOUCHMIDI_H
#define TOUCHMIDI_H

#include <QWidget>
#include <QString>
#include <processthread.h>
#include <aboutwindow.h>


namespace Ui {
    class TouchMIDI;
}

class TouchMIDI : public QWidget
{
    Q_OBJECT

public:
    explicit TouchMIDI(QWidget *parent = 0);
    ~TouchMIDI();

public slots:
    void changeMode(const QString &modeSelected);
    void showAbout();

private:
    Ui::TouchMIDI *ui;
    int mode;
    processThread *process;
    AboutWindow *about;

};

#endif // TOUCHMIDI_H
