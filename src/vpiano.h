/*
    MIDI Virtual Piano Keyboard
    Copyright (C) 2008-2010, Pedro Lopez-Cabanillas <plcl@users.sf.net>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef VPIANO_H
#define VPIANO_H


//#include "ui_vpiano.h"
//#include "pianoscene.h"
//#include <QtGui/QMainWindow>
#include <stdio.h>
#include <vector>
//class QComboBox;
//class QSpinBox;
//class QSlider;
//class QStyle;
//class Knob;
//class Instrument;
class RtMidiIn;
class RtMidiOut;
//class About;
//class Preferences;
//class MidiSetup;
//class KMapDialog;
//class DialogExtraControls;
//class RiffImportDlg;

class VPiano //: public QMainWindow, public PianoHandler
{
//    OBJECT
//
public:
//    m_midiout(0),
//    m_midiin(0),
//    m_currentOut(-1),
//    m_currentIn(-1),
//    m_inputActive(false),
//    m_midiThru(false),
//    m_initialized(false),
//    m_dlgAbout(NULL),
//    m_dlgPreferences(NULL),
//    m_dlgMidiSetup(NULL),
//    m_dlgKeyMap(NULL),
//    m_dlgExtra(NULL),
//    m_dlgRiffImport(NULL)
    VPiano(); //QWidget * parent = 0, Qt::WindowFlags flags = 0 );
    virtual ~VPiano();
    int getInputChannel();
//    void midiThru(std::vector<unsigned char> *message) const;
    bool isInitialized() const { return m_initialized; }
    void sendController(const int controller, const int value);
    void sendBender(const int value);
    void sendNoteOn(const int midiNote, const int velocity);
    void sendNoteOff(const int midiNote);
    bool initMidi();
//
//    // PianoHandler methods
//    void noteOn(const int midiNote);
//    void noteOff(const int midiNote);
//
//    // static methods
//    static QString dataDirectory();
//
//#if ENABLE_DBUS
//
//public Q_SLOTS:
//    void quit();
//    void panic();
//    void reset_controllers();
//    void channel(int value);
//    void octave(int value);
//    void transpose(int value);
//    void velocity(int value);
//    void connect_in(const QString &value);
//    void connect_out(const QString &value);
//    void connect_thru(bool value);
//
//    void noteoff(int note);
//    void noteon(int note);
//    void polykeypress(int note, int value);
//    void controlchange(int control, int value);
//    void programchange(int value);
//    void programnamechange(const QString &value);
//    void chankeypress(int value);
//    void pitchwheel(int value);
//
//Q_SIGNALS:
//    void event_noteoff(int note);
//    void event_noteon(int note);
//    void event_polykeypress(int note, int value);
//    void event_controlchange(int control, int value);
//    void event_programchange(int value);
//    void event_chankeypress(int value);
//    void event_pitchwheel(int value);
//
//#endif /*ENABLE_DBUS*/
//
//protected Q_SLOTS:
//    void slotAbout();
//    void slotAboutQt();
//    void slotConnections();
//    void slotPreferences();
//    void slotEditKeyboardMap();
//    void slotPanic();
//    void slotResetAllControllers();
//    void slotResetBender();
//    void slotHelpContents();
//    void slotOpenWebSite();
//    void slotImportSF();
//    void slotEditExtraControls();
//    void slotShowNoteNames();
//    void slotControlSliderMoved(const int value);
//    void slotExtraController(const int value);
//    void slotControlClicked(const bool value);
//    void slotBenderSliderMoved(const int pos);
//    void slotBenderSliderReleased();
//    void slotComboBankActivated(const int index = -1);
//    void slotComboProgActivated(const int index = -1);
//    void slotBaseOctaveValueChanged(const int octave);
//    void slotTransposeValueChanged(const int transpose);
//    void slotVelocityValueChanged(int value);
//    void slotChannelValueChanged(const int channel);
//    void slotComboControlCurrentIndexChanged(const int index);
//    //void slotEditPrograms();
//    //void slotDebugDestroyed(QObject *obj);
//
//protected:
//    void closeEvent ( QCloseEvent *event );
//    void customEvent ( QEvent *event );
//    void showEvent ( QShowEvent *event );
//    void hideEvent( QHideEvent *event );

private:
    void initialization();
//    bool initMidi();
    void readSettings();
    void writeSettings();
    void applyPreferences();
    void applyConnections();
    void applyInitialSettings();
    void populateControllers();
    void populateInstruments();
    void populatePrograms(int bank = -1);
    void refreshConnections();
    void initToolBars();
    void clearExtraControllers();
    void initExtraControllers();
    void initControllers(int channel);
    void resetAllControllers();
    void allNotesOff();
//    void sendController(const int controller, const int value);
    void sendBankChange(const int bank);
    void sendNoteOn(const int midiNote);
//    void sendNoteOff(const int midiNote);
    void sendProgramChange(const int program);
//    void sendBender(const int value);
    void sendPolyKeyPress(const int note, const int value);
    void sendChanKeyPress(const int value);
//    void sendSysex(const QByteArray& data);
    void sendMessageWrapper(std::vector<unsigned char> *message) const;
    void updateController(int ctl, int val);
    void updateExtraController(int ctl, int val);
    void updateBankChange(int bank = -1);
    void updateProgramChange(int program = -1);
    void grabKb();
    void releaseKb();
    void updateStyles();
    void updateNoteNames(bool drums);

//    void setWidgetTip(QWidget* w, int val);
//    QByteArray readSysexDataFile(const QString& fileName);
//
//    About *dlgAbout();
//    Preferences *dlgPreferences();
//    MidiSetup *dlgMidiSetup();
//    KMapDialog *dlgKeyMap();
//    DialogExtraControls *dlgExtra();
//    RiffImportDlg *dlgRiffImport();

    RtMidiOut* m_midiout;
    //RtMidiIn* m_midiin;
    int m_currentOut;
    int m_currentIn;
    bool m_inputActive;
    bool m_midiThru;
    bool m_initialized;
//
//    About *m_dlgAbout;
//    Preferences *m_dlgPreferences;
//    MidiSetup *m_dlgMidiSetup;
//    KMapDialog *m_dlgKeyMap;
//    DialogExtraControls *m_dlgExtra;
//    RiffImportDlg *m_dlgRiffImport;
//
//    Ui::VPiano ui;
//
//    QSpinBox* m_sboxChannel;
//    QSpinBox* m_sboxOctave;
//    QSpinBox* m_sboxTranspose;
//    Knob* m_Velocity;
//    QComboBox* m_comboControl;
//    Knob* m_Control;
//    QSlider* m_bender;
//    QComboBox* m_comboBank;
//    QComboBox* m_comboProg;
//    QStyle* m_dialStyle;
//    Instrument* m_ins;
//    QStringList m_extraControls;
//    QMap<int,QMap<int,int> > m_ctlState, m_ctlSettings;
//    QMap<int,int> m_lastBank;
//    QMap<int,int> m_lastProg;
//    QMap<int,int> m_lastCtl;
    int m_channel;
    int m_velocity;
    int m_baseOctave;
//#if ENABLE_DBUS
//    new VmpkAdaptor(this);
//    QDBusConnection dbus = QDBusConnection::sessionBus();
//    dbus.registerObject("/", this);
//    dbus.registerService("net.sourceforge.vmpk");
//#endif
    int m_transpose;
};

#endif // VPIANO_H
