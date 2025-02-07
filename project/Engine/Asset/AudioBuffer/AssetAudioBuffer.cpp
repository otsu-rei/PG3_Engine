#include "AssetAudioBuffer.h"

////////////////////////////////////////////////////////////////////////////////////////////
// Asset AudioBuffer class methods
////////////////////////////////////////////////////////////////////////////////////////////

void AssetAudioBuffer::Load(_MAYBE_UNUSED const DirectXThreadContext* context) {
	if (CheckAndBeginLoad()) {
		AudioBuffer::Load(filepath_);
		EndLoad();
	}
}
