#include <alsa/asoundlib.h>

#include <stdio.h>
#include <iostream>

#include "optionsdialog.h"
#include "ui_optionsdialog.h"

OptionsDialog::OptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsDialog)
{
    ui->setupUi(this);

    QString sName;
    QString sCurName;
    int iCurCard = -1;
    int iCards = 0;

    snd_ctl_t* handle;
    snd_ctl_card_info_t *info;
    snd_pcm_info_t *pcminfo;
    snd_ctl_card_info_alloca(&info);
    snd_pcm_info_alloca(&pcminfo);
    const QString sPrefix("hw:%1");
    const QString sSuffix(" (%1)");
    const QString sSubSuffix("%1,%2");
    QString sName2, sSubName2;
    bool bCapture, bPlayback;
    int iCard = -1;

    while (snd_card_next(&iCard) >= 0 && iCard >= 0) {
        sName = sPrefix.arg(iCard);
        if (snd_ctl_open(&handle, sName.toUtf8().constData(), 0) >= 0 && snd_ctl_card_info(handle, info) >= 0) {
            sName2 = sPrefix.arg(snd_ctl_card_info_get_id(info));
            std::cerr << "card" << std::endl;
            addCard(sName2, snd_ctl_card_info_get_name(info) + sSuffix.arg(sName));
            ui->inputDeviceList->addItem(sName2);
            ui->outputDeviceList->addItem(sName2);
            if (sCurName == sName || sCurName == sName2) iCurCard = iCards;
            ++iCards;
            int iDevice = -1;
            while (snd_ctl_pcm_next_device(handle, &iDevice) >= 0 && iDevice >= 0) {
                // Capture devices..
                bCapture = false;
                {
                    snd_pcm_info_set_device(pcminfo, iDevice);
                    snd_pcm_info_set_subdevice(pcminfo, 0);
                    snd_pcm_info_set_stream(pcminfo, SND_PCM_STREAM_CAPTURE);
                    bCapture = (snd_ctl_pcm_info(handle, pcminfo) >= 0);
                }
                bPlayback = false;
                {
                    snd_pcm_info_set_device(pcminfo, iDevice);
                    snd_pcm_info_set_subdevice(pcminfo, 0);
                    snd_pcm_info_set_stream(pcminfo, SND_PCM_STREAM_PLAYBACK);
                    bPlayback = (snd_ctl_pcm_info(handle, pcminfo) >= 0);
                }

                QString sSubName  = sSubSuffix.arg(sName).arg(iDevice);
                QString sSubName2 = sSubSuffix.arg(sName2).arg(iDevice);
                if (bCapture) ui->inputDeviceList->addItem(sSubName);
                if (bPlayback) ui->outputDeviceList->addItem(sSubName);
                std::cerr << "capture: " << bCapture << ", playback: " << bPlayback << std::endl;
                addCard(sSubName2, snd_pcm_info_get_name(pcminfo) + sSuffix.arg(sSubName));
                if (sCurName == sSubName || sCurName == sSubName2) iCurCard = iCards;
                ++iCards;
            }
        }
    }
    /*
    int cardNum = -1;
    int err;
    for (;;) {
        snd_ctl_t* cardHandle;
        if ((err = snd_card_next(&cardNum)) < 0) {
            fprintf(stderr, "Can't get the next card number: %s\n", snd_strerror(err));
            break;
        }
        if (cardNum < 0) break;

        {
            char str[64];
            sprintf(str, "hw:%i", cardNum);
            if ((err = snd_ctl_open(&cardHandle, str, 0)) < 0)
            {
                printf("Can't open card %i: %s\n", cardNum, snd_strerror(err));
                continue;
            }
        }

        {
            snd_ctl_card_info_t *cardInfo;
            snd_ctl_card_info_alloca(&cardInfo);

            if ((err = snd_ctl_card_info(cardHandle, cardInfo)) < 0)
            {
                printf("Can't get info for card %i: %s\n", cardNum, snd_strerror(err));
            }
            else
            {
                const char* card_name = snd_ctl_card_info_get_name(cardInfo);
                const char* card_id = snd_ctl_card_info_get_id(cardInfo);
                std::cerr << card_name << ", " << card_id << std::endl;
            }
        }
        snd_ctl_close(cardHandle);
    }

    snd_config_update_free_global();
    */
}

OptionsDialog::~OptionsDialog()
{
    delete ui;
}

void
OptionsDialog::addCard(const QString& sName, const QString& sDescription)
{
    std::cerr << sName.toStdString() << ", " << sDescription.toStdString() << std::endl;
}
