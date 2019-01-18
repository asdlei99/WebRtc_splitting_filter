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
//#include "my_sparse_fir_fliter.h"
using namespace std;

//const size_t kNumBands = 3;
//const size_t kSparsity = 4;
//const size_t kNumCoeffs = 4;
//const float kLowpassCoeffs[kNumBands * kSparsity][kNumCoeffs] // 竖着排 

int main()
{
	wav wav01;
	wavread("audioCut_2.wav", &wav01);

	ThreeBandFilter *p = ThreeBandFilter_Init(480);




	size_t len = wav01.totalPCMFrameCount;
	vector<float> out(wav01.totalPCMFrameCount, 0);

	//SparseFIRFilter_Filter(p, wav01.pDataFloat[0], len, &out[0]);

	//for (size_t i = 0; i < len; i++)
	//{
	//	cout << out.at(i) << endl;
	//}

	ThreeBandFilter_Destory(p);
	return 0;
}