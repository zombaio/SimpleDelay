#include "simpledelay.hpp"

#include <cstring>
#include <iostream>
#include <numeric>

#include <boost/range.hpp>
#include <boost/range/combine.hpp>
#include <boost/iterator/function_input_iterator.hpp>

SimpleDelay::SimpleDelay(audioMasterCallback audioMaster) :
	AudioEffectX(audioMaster, kNumPrograms, kNumParameters)
{
	setNumInputs(kNumInputs);
	setNumOutputs(kNumOutputs);
	canProcessReplacing();
}

SimpleDelay::~SimpleDelay() {}

struct SimpleDelayMonoInputGenerator {
	typedef float result_type;

	float** inputs;
	std::size_t sampleIndex;

	SimpleDelayMonoInputGenerator(float** inputs) :
		inputs(inputs), sampleIndex(0)
	{}

	result_type operator()() {
		auto result(std::accumulate(inputs, inputs + SimpleDelay::kNumInputs, 0.0f, [this](float accum, float* input) {
			return accum + input[sampleIndex];
		}) / SimpleDelay::kNumInputs);
		++sampleIndex;
		return result;
	}
};

void SimpleDelay::processReplacing(float** inputs, float** outputs, VstInt32 sampleFrames) {
	SimpleDelayMonoInputGenerator svmig(inputs);

	auto monoSampleRange(boost::make_iterator_range(
		boost::make_function_input_iterator(svmig, 0),
		boost::make_function_input_iterator(svmig, sampleFrames)));

	monoSampleFrameBuffer.emplace_back(monoSampleRange.begin(), monoSampleRange.end());

	if(monoSampleFrameBuffer.size() >= SD_NUM_BUFFERS_BEFORE_PLAYBACK) {
		auto& first(monoSampleFrameBuffer.front());
		auto sampleIndex(0);
		for(float height : first) {
			for(auto channel(0); channel != SimpleDelay::kNumOutputs; ++channel) {
				outputs[channel][sampleIndex] = height;
			}
			++sampleIndex;
		}
		monoSampleFrameBuffer.pop_front();
	}
	else {
		for(auto channel(0); channel != SimpleDelay::kNumOutputs; ++channel) {
			std::fill(outputs[channel], outputs[channel]+sampleFrames, 0.0f);
		}
	}
}
