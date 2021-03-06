//
//#define DR_WAV_IMPLEMENTATION	// for the dr_wav.h
#include "unittest_helper.h"
//#include "wavfile.h"
#include "splitting_filter.h"	
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int splitting_filter_demo(const char* inFile) {
	uint16_t channels;
	uint16_t sampleRate;
	uint64_t totalPCMFrameCount;
	drwav* pWavIn = open_wavfile(inFile, &channels, &sampleRate, &totalPCMFrameCount);

	if (pWavIn == NULL) {
		printf("Error in opening wav file\n");
		return -1;
	}
	if (channels != 1)
	{
		printf("Only support mono wav file\n");
		drwav_uninit(pWavIn);
		return -1;
	}

	// Test for two bands splitting filter
	if (sampleRate == 32000 )
	{
		printf("Splitting filter Test for 32000 Hz\n");
		mSplittingFilter* sf = (mSplittingFilter*)SplittingFilter_Create(sampleRate);
		uint16_t nFrames = sampleRate / 100;// 320
		size_t len = totalPCMFrameCount;

		int16_t bandLower[160];
		int16_t bandUpper[160];
		int16_t* bandData[] = { bandLower, bandUpper };

		int16_t frameIn[320];
		int16_t frameOut[320];
		drwav* pWav_low = init_wavfile("32k_low_band.wav", 1, 32000, 16);
		drwav* pWav_high = init_wavfile("32k_high_band.wav", 1, 32000, 16);
		drwav* pWav_synthesis = init_wavfile("32k_synthesis.wav", 1, 32000, 16);

		for (size_t n = 0; n < len / nFrames; n++)
		{
			get_frame_s16(pWavIn, frameIn, 320);
			SplittingFilter_Analysis_s16(sf, frameIn, bandData);

			write_frames_s16(pWav_low, 160, bandData[0]);
			write_frames_s16(pWav_high, 160, bandData[1]);

			SplittingFilter_Synthesis_s16(sf, bandData, frameOut);
			write_frames_s16(pWav_synthesis, 320, frameOut);
		}

		printf("Two bands splitting test finish...\n");

		drwav_uninit(pWavIn);
		drwav_uninit(pWav_low);
		drwav_uninit(pWav_high);
		drwav_uninit(pWav_synthesis);
		SplittingFilter_Destory(sf);

	}


	if (sampleRate == 48000) {
		//TODO
	}

	return 0;
}

int main(int argc, char const* argv[]) {
	
	const char* testFile = "sweep_32k.wav";

	splitting_filter_demo(testFile);

}
