#ifndef NWSND_CTR_WAVE_H
#define NWSND_CTR_WAVE_H

#include "nwsnd/common.h"

enum CTR_Wave_EncodeMethod {
	PCM8 = 0,
	PCM16,
	DSP_ADPCM,
	IMA_ADPCM
};

typedef struct {
	struct PointerList pointerList;

	u32 filePosition;

	struct SoundFileHeader header;

	struct CTR_Wave_InfoPartition {
		struct {
			struct PartitionHeader partitionHeader;
		} header;

		struct {
			u8 encoding;
			u8 isLoop;
			u16 padding;
			u32 sampleRate;
			u32 loopStartFrame;
			u32 loopEndFrame;
			u32 originalLoopStartFrame;
			struct LinkTable channelInfoLinkTable;
		} body;
	} infoPartition;

	struct CTR_Wave_ChannelInfo {
		struct Link samplesLink;
		struct Link AdpcmInfoLink;
	} channelInfo;

	struct CTR_Wave_DSPAdpcmInfo {
		struct {
			u16 coef[16];
			u16 predScale;
			u16 yn1;
			u16 yn2;
		} DSPAdpcmParam;
		struct {
			u16 loopPredScale;
			u16 loopYn1;
			u16 loopYn2;
		} DSPAdpcmLoopParam;
	} DSPAdpcmInfo;

	struct CTR_Wave_DataPartition {
		struct PartitionHeader partitionHeader;
		union {
			s8 *pcm8;
			s16 *pcm16;
			u8 *byte;
		};
	} dataPartition;

} CTR_Wave;

#endif