// ProjectY.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define DR_WAV_IMPLEMENTATION

#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <string>
#include <map>
#include<typeinfo>

#include "wavfile.h"
#include "mThreeBandFilter.h"

#include"three_band_filter_bank.h"	// C++ version 
using namespace std;

//const size_t kNumBands = 3;
//const size_t kSparsity = 4;
//const size_t kNumCoeffs = 4;
//const float kLowpassCoeffs[kNumBands * kSparsity][kNumCoeffs] // 竖着排 

int main()
{
	// 读取音频文件
	wav wav01;
	wavread("audioCut_2.wav", &wav01);


	size_t len = wav01.totalPCMFrameCount;

	float in[480] = {};
	float out[3][160] = {};

	float *out_band[3];		// 指针数组
	for (size_t i = 0; i < 3; i++)
	{
		out_band[i] = (float*)malloc(sizeof(float) * 160);
	}

	float *out_band2[3];		// 指针数组
	for (size_t i = 0; i < 3; i++)
	{
		out_band2[i] = (float*)malloc(sizeof(float) * 160);
	}

	// 开始测试
	cout << "========TEST START=========" << endl;

	ThreeBandFilter *p = ThreeBandFilter_Create(480);		// C 版本


	ThreeBandFilterBank T1(480);				// C++ 版本

	memcpy(in, wav01.pDataFloat[0], sizeof(float) * 480);



	// Analysis test
	T1.Analysis(in, len, out_band);
	ThreeBandFilter_Analysis(p, in, len, out_band2);

	for (size_t kBand = 0; kBand < 3; kBand++)
	{
		cout << "||======== " << kBand << " Band ==========||" << endl;
		for (size_t kSamples = 0; kSamples < 160; kSamples++)
		{
			cout << out_band[kBand][kSamples] << "	||	"<<out_band2[kBand][kSamples]<< endl;
		}
	}
	// Synthesis test
	float synthesis_out1[480]{};
	float synthesis_out2[480]{};
	T1.Synthesis(out_band, 160, synthesis_out1);
	ThreeBandFilter_Synthesis(p,out_band2, 160, synthesis_out2);

	for (size_t kSamples = 0; kSamples < 480; kSamples++)
	{
		cout << synthesis_out1[kSamples] << "		||		" << synthesis_out2[kSamples] << endl;
	}



	// free
	for (size_t i = 0; i < 3; i++)
	{
		free(out_band2[i]);
		free(out_band[i]);
	}
	ThreeBandFilter_Destory(p);
	return 0;
}