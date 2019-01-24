// ProjectY.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define DR_WAV_IMPLEMENTATION
#include "wavfile.h"
//#include "my_splitting_filter_c.h"
#include "splitting_filter.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
	// 读取音频文件
	wav wavfile;
	wavread("WAV48K24B-倩女幽魂.wav", &wavfile);
	size_t sample_rate = wavfile.sampleRate;
	size_t len = wavfile.totalPCMFrameCount;
	mSplittingFilter* sf = (mSplittingFilter*)SplittingFilter_Create(sample_rate);
	printf("sample rate is %d", sample_rate);

	int16_t bands_data[3][160]{};
	int16_t *pBands[3] = { bands_data[0],bands_data[1],bands_data[2] };
	int16_t *pOut = (int16_t*)malloc(len*sizeof(int16_t));
	int16_t *pCurIn = wavfile.pDataS16[0];
	int16_t *pCurOut = pOut;
	unsigned int nFrames = sample_rate / 100;

	for (size_t n = 0; n < len / nFrames; n++)
	{
		SplittingFilter_Analysis_s16(sf, pCurIn, pBands);
		// your band processing here

		SplittingFilter_Synthesis_s16(sf, pBands, pCurOut);

		pCurIn += nFrames;
		pCurOut += nFrames;
	}
	wavwrite_s16("After synthesis - 48k - 2.wav", &pOut, len, 1, sample_rate);

	SplittingFilter_Destory(sf);
	wav_destory(&wavfile);
	free(pOut);
	return 0;
}