/**
 * @file ChirpSDK.h
 *
 * @brief C++ wrapper arround the Chirp C SDK for MBED. A full documentation of
 * the C functions used by this wrapper can be found in the headers located in
 * the `include` folder or at https://docs.chirp.io/arm/.
 *
 *  ASIO CONFIDENTIAL
 *
 *  All contents are strictly proprietary, and not for copying, resale,
 *  or use outside of the agreed license.
 *
 *  Copyright © 2011-2019, Asio Ltd.
 *  All rights reserved.
 */

#ifndef CHIRPSDK_H
#define CHIRPSDK_H

#include <string>

#include "chirp_connect.h"

/**
 * Used to shorten usages of the string class.
 */
using namespace std;

namespace chirp
{
    /**
     * Typedef of some Chirp C types to make them more C++ friendly.
     * The initial types are located in the chirp_connect_*.h files
     */
    typedef chirp_connect_state_t ChirpSDKState;
    typedef chirp_connect_state_callback_t ChirpSDKStateCallback;
    typedef chirp_connect_callback_t ChirpSDKCallback;
    typedef chirp_connect_error_code_t ChirpSDKErrorCode;

    /**
     * Error code wrapping class.
     */
    class ChirpSDKError
    {
    public:
        std::ostream &operator <<(std::ostream &os);
        ChirpSDKErrorCode ErrorCode;

    private:
        friend class ChirpSDK;
        explicit ChirpSDKError(chirp_connect_error_code_t error_code);
    };

    class ChirpSDKCallbacks
    {
    public:
        ChirpSDKStateCallback on_state_changed = NULL;
        ChirpSDKCallback on_sending = NULL;
        ChirpSDKCallback on_sent = NULL;
        ChirpSDKCallback on_receiving = NULL;
        ChirpSDKCallback on_received = NULL;
    };

    class ChirpSDK
    {
    public :

        ChirpSDKError Init(string key, string secret);
        ChirpSDKError SetConfig(string config);
        ChirpSDKError SetCallbacks(ChirpSDKCallbacks callbacks, void *userData);

        ChirpSDKError Start();
        ChirpSDKError Stop();

        ChirpSDKError Send(uint8_t *payload, size_t length);
        ChirpSDKState GetState();

        ChirpSDKError Process(float *in, float *out, size_t length);
        ChirpSDKError ProcessInput(float *in, size_t length);
        ChirpSDKError ProcessOutput(float *out, size_t length);
        ChirpSDKError ProcessShorts(short *in, short *out, size_t length);
        ChirpSDKError ProcessShortsInput(short *in, size_t length);
        ChirpSDKError ProcessShortsOuput(short *out, size_t length);

        ChirpSDKState GetStateForChannel(uint8_t channel);
        ChirpSDKError SetTransimissionChannel(uint8_t channel);
        uint8_t GetTransmissionChannel();
        uint8_t GetChannelCount();

        float GetDurationForPayloadLength(size_t payloadLength);
        uint8_t *GetRandomPayload(size_t *length);
        string PayloadAsString(uint8_t *payload, size_t length);
        size_t GetMaxPayloadLength();

        float GetVolume();
        ChirpSDKError SetVolume(float volume);
        uint32_t GetInputSampleRate();
        ChirpSDKError SetInputSampleRate(uint32_t sampleRate);
        uint32_t GetOutputSampleRate();
        ChirpSDKError SetOutputSampleRate(uint32_t sampleRate);
        bool GetAutoMute();
        ChirpSDKError SetAutoMute(bool autoMute);

        ChirpSDKError SetFrequencyCorrection(float correction);
        static string GetVersion();

        string Info;

        ~ChirpSDK();

    private:
        chirp_connect_t *connect = NULL;
    };

}

#endif /* !CHIRPSDK_H */