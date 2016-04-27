#include "audioeffectx.h"
#include "simpledelay.hpp"

AudioEffect* createEffectInstance(audioMasterCallback callback) {
	return new SimpleDelay(callback);
}
