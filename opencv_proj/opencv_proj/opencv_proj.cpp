// opencv_proj.cpp : Defines the entry point for the console application.
//

#pragma once

#include "stdafx.h"
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include "wavelet.h"
#include <fstream>
#include <iostream>

#include <stdlib.h> //Для очистки экрана

#include <cstring>
using std::strerror;
#include <cerrno>
#include "WaveletPack.h"

#include <windows.h>
#include <tchar.h>
#include <stdio.h>


int _tmain(int argc, _TCHAR* argv[])
{
	//TCHAR szDir[MAX_PATH];

	//srand((unsigned)time(NULL));

	//// имя файла задаётся первым параметром

	//char* dirname = "F:\\repo\\magister\\data\\cam\\";

	//size_t dirlen = strlen(dirname);
	//
	//WIN32_FIND_DATA f;
	//HANDLE h = FindFirstFile("F:\\repo\\magister\\data\\cam\\*.mp4", &f);

	//std::ofstream outFile;
	//outFile.open("F:\\repo\\magister\\data\\cam\\result.txt");

	//if(h != INVALID_HANDLE_VALUE)
	//{
	//	do
	//	{
	//		size_t len = strlen(f.cFileName);

	//		char* out = new char[dirlen+len+8];
	//		strcpy(out, dirname);   
	//		strcat(out, f.cFileName);
	//		printf("[i] out file: %s\n", out);

	//		float result = compress(out, 5);
	//		outFile << out << std::endl;
	//		outFile << result << std::endl;

	//	} while(FindNextFile(h, &f));
	//}
	//else
	//{
	//	fprintf(stderr, "Error opening directory\n");
	//}

	//outFile.close();
	return 0;
}

