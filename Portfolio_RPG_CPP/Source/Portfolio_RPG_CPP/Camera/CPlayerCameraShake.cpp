#include "CPlayerCameraShake.h"

UCPlayerCameraShake::UCPlayerCameraShake()
{
    // ����: ��鸲 ���� ����
    OscillationDuration = 0.2f;

    //RotOscillation.Pitch.Amplitude = 5.0f;
    //RotOscillation.Pitch.Frequency = 25.0f;

    RotOscillation.Yaw.Amplitude = 10.0f;
    RotOscillation.Yaw.Frequency = 50.0f;

}