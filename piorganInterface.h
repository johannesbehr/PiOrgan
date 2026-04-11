#ifndef MYCLASS_H
#define MYCLASS_H

#include <QDebug>
#include <QObject>
#include <QtWidgets>

#include <string>
#include <piorgan.h>

class PiOrganInterface : public QObject
{
    Q_OBJECT

public:
    explicit PiOrganInterface(QObject *parent = 0);
    void onPresetsChanged(int instrument);
    void onSettingChanged(int setting);
    void onOffsetChanged(int offset, int instrument);
    void setPresetsChanged(void (*fnk)(int));
    void setResetScreenSaver(void (*fnk)());
    void setSaveMode(bool save);
    QStringList getPresets(const int instrument);
    QStringList getSoundFonts();
    QStringList getMidiFiles();
    QStringList getSequencerStyles();
    int getOffset(const int instrument);
    double getVolume(const int instrument);
    int getSelectedPreset(const int instrument);
    double getReverbParameter(int index);
    double getChorusParameter(int index);
    void setEventsEnabled(const bool enabled);
    void setRootObject(QObject *rootObject);
    void onSoundFontLoaded(std::string soundFont);
    void onTick(int ticks, int bpm);

public slots:
   void buttonClicked(const int instrument, const QString& in);
   void sliderValueChanged(const double value, const int instrument);
   void currentIndexChanged(const int instrument, int index);
   void soundFontChanged(const QString &itemText);
   void loadSoundFont();
   void loadMidiFile(const QString &midiFile);
   void playMidiFile();
   void stopMidiFile();
   void midiSpeedValueChanged(const double value);
   void setProperty(QObject*, const char*, const QVariant& );

   void sequencerCmdLoadStyle(const QString &styleName);
   void sequencerCmdLoadStyle(int styleIndex);   
   void sequencerCmdLoadStyles();
   void sequencerCmdStart();
   void sequencerCmdStop();
   void sequencerCmdDrumsOnOff();
   void sequencerCmdBassOnOff();
   void sequencerCmdBackingOnOff();
   
   void sequencerCmdSetTempo(const double value);

signals :
   void signalSetProperty(QObject*, const char*, const QVariant& );


private :
    void loadSoundFontThread();
    void doSettings(const int setting);
    bool eventsEnabled_ = false;
    PiOrgan myPiOrgan; 
    bool saveSettings = false;
    std::string selectedSoundFont = ""; 
    int currentSetting = -1;
    int last_min = -1;
    int last_sec = -1;

    QObject *rootObject;

    QObject *txtOffsetInstrument0;
    QObject *txtOffsetInstrument1;
    QObject *txtOffsetInstrument2;

    QObject *tmbInstrument0;
    QObject *tmbInstrument1;
    QObject *tmbInstrument2;

    QObject *sldVolumeInstrument0;
    QObject *sldVolumeInstrument1;
    QObject *sldVolumeInstrument2;

    QObject *sldReverbLevel;
    QObject *sldReverbRoomsize;
    QObject *sldReverbDamp;
    QObject *sldReverbWidth;

    QObject *sldChorusLevel;
    QObject *sldChorusDepth;
    QObject *sldChorusSpeed;

    QObject *lvSoundFonts;
    QObject *lvMidiFiles;

    QObject *btnSetting[7];
    QObject *btnSaveSetting;

    QObject *pltBtnHighlight;
    QObject *pltBtnRegular;
    QObject *pltBtnDisabled;

    QObject *txtCurrentSoundFont;
    QObject *btnLoadSoundFont;

    QObject *btnStopMidiFile;
    QObject *btnPlayMidiFile;

    QObject *txtMidiTime;


    QObject *busyIndicator;


    // PageSequencer
    QObject *lvSequencerStyles;
    QObject *btnSequencerStart;
    QObject *btnSequencerStop;
    QObject *sldSequencerTempo;
    QObject *txtSequencerTempo;
    QObject *btnSequencerLoadStyle;
    


};

#endif // MYCLASS_H
