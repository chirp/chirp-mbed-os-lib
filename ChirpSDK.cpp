//
// Created by Damien Laidin on 2019-02-26.
//

#include "ChirpSDK.h"

using namespace chirp;

ChirpSDKError ChirpSDK::Init(string key, string secret)
{
    this->connect = new_chirp_connect(key.c_str(), secret.c_str());
    if (this->connect == NULL)
    {
        return ChirpSDKError(CHIRP_CONNECT_INVALID_CREDENTIALS);
    }
    else
    {
        return ChirpSDKError(CHIRP_CONNECT_OK);
    }
}

ChirpSDKError ChirpSDK::SetConfig(string config)
{
    chirp_connect_error_code_t error_code = chirp_connect_set_config(this->connect, config.c_str());

    if (error_code == CHIRP_CONNECT_OK)
    {
        char *info = chirp_connect_get_info(this->connect);
        this->Info = string(info);
        chirp_connect_free(info);
    }

    return ChirpSDKError(error_code);
}

ChirpSDKError ChirpSDK::SetCallbacks(ChirpSDKCallbacks callbacks, void *data)
{
    chirp_connect_callback_set_t callback_set = { 0 };
    callback_set.on_state_changed = callbacks.on_state_changed;
    callback_set.on_sending = callbacks.on_sending;
    callback_set.on_sent = callbacks.on_sent;
    callback_set.on_receiving = callbacks.on_receiving;
    callback_set.on_received = callbacks.on_received;
    chirp_connect_error_code_t error_code = chirp_connect_set_callbacks(this->connect, callback_set);

    if (error_code == CHIRP_CONNECT_OK)
    {
        error_code = chirp_connect_set_callback_ptr(this->connect, data);
    }

    return ChirpSDKError(error_code);
}

ChirpSDKError ChirpSDK::Start()
{
    chirp_connect_error_code_t error_code = chirp_connect_start(this->connect);
    return ChirpSDKError(error_code);
}

ChirpSDKError ChirpSDK::Stop()
{
    chirp_connect_error_code_t error_code = chirp_connect_stop(this->connect);
    return ChirpSDKError(error_code);
}

float ChirpSDK::GetDurationForPayloadLength(size_t payloadLength)
{
    return chirp_connect_get_duration_for_payload_length(this->connect, payloadLength);
}

/**
 * Generate a random payload.
 *
 * @param length 0 to get a random payload of a random length. The value will
 *               then be updated to the length of the payload.
 *               Any other value lower or equal to MaxPayloadLength.
 * @return       A payload filled with random data.
 */
uint8_t *ChirpSDK::GetRandomPayload(size_t *length)
{
    return chirp_connect_random_payload(this->connect, length);
}

string ChirpSDK::PayloadAsString(uint8_t *payload, size_t length)
{
    char *hex_str = chirp_connect_as_string(this->connect, payload, length);
    string str = string(hex_str);
    chirp_connect_free(hex_str);
    return str;
}

ChirpSDKError ChirpSDK::Send(uint8_t *payload, size_t length)
{
    chirp_connect_error_code_t error_code = chirp_connect_send(this->connect, payload, length);
    return ChirpSDKError(error_code);
}

ChirpSDKError ChirpSDK::Process(float *in, float *out, size_t length)
{
    chirp_connect_error_code_t error_code = chirp_connect_process(this->connect, in, out, length);
    return ChirpSDKError(error_code);
}

ChirpSDKError ChirpSDK::ProcessInput(float *in, size_t length)
{
    chirp_connect_error_code_t error_code = chirp_connect_process_input(this->connect, in, length);
    return ChirpSDKError(error_code);
}

ChirpSDKError ChirpSDK::ProcessOutput(float *out, size_t length)
{
    chirp_connect_error_code_t error_code = chirp_connect_process_output(this->connect, out, length);
    return ChirpSDKError(error_code);
}

ChirpSDKError ChirpSDK::ProcessShorts(short *in, short *out, size_t length)
{
    chirp_connect_error_code_t error_code = chirp_connect_process_shorts(this->connect, in, out, length);
    return ChirpSDKError(error_code);
}

ChirpSDKError ChirpSDK::ProcessShortsInput(short *in, size_t length)
{
    chirp_connect_error_code_t error_code = chirp_connect_process_shorts_input(this->connect, in, length);
    return ChirpSDKError(error_code);
}

ChirpSDKError ChirpSDK::ProcessShortsOuput(short *out, size_t length)
{
    chirp_connect_error_code_t error_code = chirp_connect_process_shorts_output(this->connect, out, length);
    return ChirpSDKError(error_code);
}

ChirpSDKState ChirpSDK::GetStateForChannel(uint8_t channel)
{
    return chirp_connect_get_state_for_channel(this->connect, channel);
}

ChirpSDKError ChirpSDK::SetTransimissionChannel(uint8_t channel)
{
    chirp_connect_error_code_t error_code = chirp_connect_set_transmission_channel(this->connect, channel);
    return ChirpSDKError(error_code);
}

ChirpSDKState ChirpSDK::GetState()
{
    return chirp_connect_get_state(this->connect);
}

uint8_t ChirpSDK::GetTransmissionChannel()
{
    return chirp_connect_get_transmission_channel(this->connect);
}

uint8_t ChirpSDK::GetChannelCount()
{
    return chirp_connect_get_channel_count(this->connect);
}

size_t ChirpSDK::GetMaxPayloadLength()
{
    return chirp_connect_get_max_payload_length(this->connect);
}

float ChirpSDK::GetVolume()
{
    return chirp_connect_get_volume(this->connect);
}

ChirpSDKError ChirpSDK::SetVolume(float volume)
{
    chirp_connect_error_code_t error_code = chirp_connect_set_volume(this->connect, volume);
    return ChirpSDKError(error_code);
}

uint32_t ChirpSDK::GetInputSampleRate()
{
    return chirp_connect_get_input_sample_rate(this->connect);
}

ChirpSDKError ChirpSDK::SetInputSampleRate(uint32_t sampleRate)
{
    chirp_connect_error_code_t error_code = chirp_connect_set_input_sample_rate(this->connect, sampleRate);
    return ChirpSDKError(error_code);
}

uint32_t ChirpSDK::GetOutputSampleRate()
{
    return chirp_connect_get_output_sample_rate(this->connect);
}

ChirpSDKError ChirpSDK::SetOutputSampleRate(uint32_t sampleRate)
{
    chirp_connect_error_code_t error_code = chirp_connect_set_output_sample_rate(this->connect, sampleRate);
    return ChirpSDKError(error_code);
}

bool ChirpSDK::GetAutoMute()
{
    return chirp_connect_get_auto_mute(this->connect);
}

ChirpSDKError ChirpSDK::SetAutoMute(bool autoMute)
{
    chirp_connect_error_code_t error_code = chirp_connect_set_auto_mute(this->connect, autoMute);
    return ChirpSDKError(error_code);
}

string ChirpSDK::GetVersion()
{
    return string(chirp_connect_get_version());
}

ChirpSDKError ChirpSDK::SetFrequencyCorrection(float correction)
{
    chirp_connect_error_code_t error_code = chirp_connect_set_frequency_correction(this->connect, correction);
    return ChirpSDKError(error_code);
}

ChirpSDK::~ChirpSDK()
{
    del_chirp_connect(&this->connect);
}

ChirpSDKError::ChirpSDKError(chirp_connect_error_code_t error_code)
{
    this->ErrorCode = error_code;
}

std::ostream &ChirpSDKError::operator <<(std::ostream &os)
{
    return os << string(chirp_connect_error_code_to_string(this->ErrorCode));
}
