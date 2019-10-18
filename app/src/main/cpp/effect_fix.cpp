//
// Created by tang.wangqiang on 2019/10/16.
//
#include "include/fmod.hpp"
#include "org_fmod_example_EffectUtils.h"
#include <android/log.h>
#include <unistd.h>

#define LOGI(FORMATE, ...)  __android_log_print(ANDROID_LOG_ERROR, "TAG", FORMATE, __VA_ARGS__);

#define  MODE_NORMAL 0
#define MODE_LUOLI  1
#define MODE_DASHU  2
#define MODE_JINGSONG  3
#define MODE_GAOGUAI  4
#define MODE_KONGLING  5

using namespace FMOD;
extern "C" JNIEXPORT void JNICALL Java_org_fmod_example_EffectUtils_fix
        (JNIEnv *env, jclass jcls, jstring jstr_path, jint type) {
    bool playing = true;
    System *system;
    Sound *sound;
    DSP *dsp;
    float frequency = 0;
    Channel *channel = NULL;
    const char *path = env->GetStringUTFChars(jstr_path, NULL);
    try {
        System_Create(&system);
        system->init(32, FMOD_INIT_NORMAL, 0);//初始化
        //创建声音
        system->createSound(path, FMOD_DEFAULT, NULL, &sound);
        switch (type) {
            case MODE_NORMAL:
                system->playSound(sound, 0, false, &channel);
                break;
            case MODE_LUOLI:
                //dsp 提升或者降低音调用的一种音效
                system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
                //设置音调的参数
                dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 2.5);
                //添加进去
                system->playSound(sound, 0, false, &channel);
                channel->addDSP(0, dsp);
                LOGI("%s", "luoli");
                break;
            case MODE_DASHU:
                //dsp 提升或者降低音调用的一种音效
                system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
                //设置音调的参数
                dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 0.8);
                //添加进去
                system->playSound(sound, 0, false, &channel);
                channel->addDSP(0, dsp);
                break;
            case MODE_GAOGUAI://搞怪
                system->playSound(sound, 0, false, &channel);
                channel->getFrequency(&frequency);
                frequency = static_cast<float>(frequency * 1.6);
                channel->setFrequency(frequency);
                break;
            case MODE_KONGLING://空灵
                system->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp);
                dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY, 300);
                dsp->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK, 20);
                //添加进去
                system->playSound(sound, 0, false, &channel);
                channel->addDSP(0, dsp);
                break;
            case MODE_JINGSONG://惊悚
                system->createDSPByType(FMOD_DSP_TYPE_TREMOLO, &dsp);
                dsp->setParameterFloat(FMOD_DSP_TREMOLO_SKEW, 0.5);
                system->playSound(sound, 0, false, &channel);
                channel->addDSP(0, dsp);
                break;
            default:
                break;
        }
    }catch (...){
        goto end;
    }
    //释放资源
    //单位是微秒
    system->update();
    usleep(5 * 1000 * 1000);
    while (playing) {
        channel->isPlaying(&playing);
        usleep(1000 * 1000);//每隔一秒判断一下
    }
    goto  end;
    end:
    env->ReleaseStringUTFChars(jstr_path, path);
    sound->release();
    system->close();
    system->release();
}
