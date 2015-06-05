#ifndef PROCESSTHREAD_H
#define PROCESSTHREAD_H

#include <QThread>
#include <synclient.h>
#include <vpiano.h>
#include <RtMidi.h>

class processThread : public QThread
{
    Q_OBJECT
public:
    explicit processThread(QObject *parent = 0);
    void run();
    int mode;
    int ctl1, ctl2;
    bool springPitch, springMod, spring1, spring2;
    bool rel;
    int xtype, ytype, ztype;
    int xctl, yctl, zctl;
    int notelow, notehigh;
    bool stop;
    int xmin, xmax, ymin, ymax, zmin, zmax;
    SynapticsSHM *touchpad;
    VPiano midicontrol;

signals:
    void pitchChanged(int);
    void modChanged(int);
    void ctl1Changed(int);
    void ctl2Changed(int);
    void Xchanged(int);
    void Ychanged(int);
    void Zchanged(int);

public slots:
    void setMode(int i) {mode = i;}
    void setCtl1(int i) { ctl1 = i;}
    void setCtl2(int i) {ctl2 = i;}
    void setSpringPitch(bool i) {springPitch = i;}
    void setSpringMod(bool i) {springMod = i;}
    void setSpring1(bool i) {spring1 = i;}
    void setSpring2(bool i) {spring2 = i;}
    void setRel(bool i) {rel = i;}
    void setXtype(int i) {xtype = i;}
    void setYtype(int i) {ytype = i;}
    void setZtype(int i) {ztype = i;}
    void setXctl(int i) {xctl = i;}
    void setYctl(int i) {yctl = i;}
    void setZctl(int i) {zctl = i;}
    void setNoteLow(int i) {notelow = i;}
    void setNoteHigh(int i) {notehigh = i;}
    void quit() {stop = true;}
};

#endif // PROCESSTHREAD_H
