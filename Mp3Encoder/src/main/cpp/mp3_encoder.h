//
// Created by logan.yu on 2018/12/11.
//

#include <stdio.h>
#include <lame/lame.h>
#include "3rdparty/lame/include/lame/lame.h"

const int SUCCESS = 0;
const int INPUT_FILE_NOT_EXIST = -1;
const int OUTPUT_FILE_NOT_EXIST = -2;

#ifndef NDKDEMO_MP3_ENCODER_H
#define NDKDEMO_MP3_ENCODER_H


class mp3_encoder {

private:
    FILE *pcmFile;
    FILE *mp3File;
    lame_t lameClient;

public:
    mp3_encoder();
    ~mp3_encoder();

    int Init(const char *pcmFilePath,
             const char *mp3FilePath,
             int sampleRate,
             int channels,
             int bitRate
    );

    void Encode();

    void Destroy();

};


#endif //NDKDEMO_MP3_ENCODER_H
