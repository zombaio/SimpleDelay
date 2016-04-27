#ifndef SIMPLEDELAY_HPP_
#define SIMPLEDELAY_HPP_

#include "audioeffectx.h"

#include <deque>
#include <vector>

#define SD_NUM_BUFFERS_BEFORE_PLAYBACK 60

struct SimpleDelay : public AudioEffectX {
	enum {
		kNumPrograms = 1,
		kNumParameters = 0,
		kNumInputs = 2,
		kNumOutputs = 2
	};

	std::deque<std::vector<float>> monoSampleFrameBuffer;

	SimpleDelay(audioMasterCallback audioMaster);
	~SimpleDelay();

	void processReplacing(float** inputs, float** outputs, VstInt32 sampleFrames) override;
};


#endif /* SIMPLEDELAY_HPP_ */
