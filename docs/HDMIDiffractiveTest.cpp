// HDMIDiffractiveTest.cpp : Defines the entry point for the console application to calibrate the SLM
//

#include "Blink_C_wrapper.h"
#include "ImageGen.h"
#include <afx.h>
#include <iostream>

// -------------------------- HDMI Diffractive Test --------------------------------
// Simple example using the Blink_C_wrapper DLL to load diffraction patterns to the SLM
// and measure the 1st order intensity by reading from an analog input board, then
// saving the measurements to raw files for post processing to generate either 
// a regional or global LUT.
// ----------------------------------------------------------------------------
int main()
{
	CStdioFile sFile;
	CString FileName, str;

	//The number of data points we will use in the calibration is 256 (8 bit's)
	int NumDataPoints = 256;

	//If you are generating a global calibration (recommended) the number of regions is 1, 
	//if you are generating a regional calibration (typically not necessary) the number of regions is 64
	int NumRegions = 1;

	// Initialize the SDK. 
	Create_SDK();

	//Read the height and width of the SLM found. The default is 1920x1152 if no SLM is found. The default location
	//is immediately right of the primary monitor. If you monitor is smaller than 1920x1152 you can still run, you will
	//just see a sub-section of the image on the monitor. 
	int height = Get_Height();
	int width = Get_Width();
	int depth = Get_Depth(); //will return 8 for 8-bit, or 10 for 10-bit
	int BytesPerImage = 4; //RGBA
  
	// To measure the raw response we want to disable the LUT by loading a linear LUT. If you are testing the linearity of 
	// your calibration, load the custom LUT that you generated (or we generated).
	if(height == 1152)
		Load_lut("C:\\Program Files\\Meadowlark Optics\\Blink 1920 HDMI\\LUT Files\\1920x1152_linearVoltage.lut");
	else
	{
	  if(depth == 8)
		  Load_lut("C:\\Program Files\\Meadowlark Optics\\Blink 1920 HDMI\\LUT Files\\19x12_8bit_linearVoltage.lut");
	  if(depth == 10)
		  Load_lut("C:\\Program Files\\Meadowlark Optics\\Blink 1920 HDMI\\LUT Files\\19x12_10bit_linearVoltage.lut");
	}
  
	//Create an array to hold the image data
	unsigned char* Image = new unsigned char[width*height*BytesPerImage];

	//use a blank wavefront correction during the LUT calibration process
	unsigned char* WFC = new unsigned char[width*height*BytesPerImage];
	memset(WFC, 0, width*height*BytesPerImage);

	//Create an array to hold measurements from the analog input (AI) board. We ususally use a NI USB 6008 or equivalent
	//for an analog input board.
	float* AI_Intensities = new float[NumDataPoints];
	memset(AI_Intensities, 0, NumDataPoints);
	

	//start the SLM blank, we are using RGB images
	bool isEightBit = false;
	bool RGB = true;
  bool Vertical = true;
	Generate_Solid(Image, WFC, width, height, depth, 0, RGB);
	Write_image(Image, isEightBit);

	//load diffraction patterns, and record the 1st order intensity
	int PixelValueOne, PixelValueTwo;


	float inputVal;
	float rawInput;
	//use a reference graylevel of 0 for the 1920x1152 and 255 for the 1920x1200
	if (height == 1152)
		PixelValueOne = 0;
	else
		PixelValueOne = 255;
	
	int PixelsPerStripe = 8; //use a fairly high frequency pattern (a short period) to separate the 0th from the 1st order
	for (int region = 0; region < NumRegions; region++)
	{
		printf("Region: %d\n\r", region);

		for (int Gray = 0; Gray < NumDataPoints; Gray++)
		{
			printf("Gray: %d\n\r", Gray);

			//the variable graylevel increments from 0 - 255 for the 1920x1152, and decrements from 255 to 0 for the 1920x1200
			if (height == 1152)
				PixelValueTwo = Gray;
			else
				PixelValueTwo = 255 - Gray;

			//generate a stripe
			Generate_Stripe(Image, WFC, width, height, depth, PixelValueOne, PixelValueTwo, PixelsPerStripe, Vertical, RGB);
      
			//if generating a regional LUT mask out all but the current region of interest
			Mask_Image(Image, width, height, depth, region, NumRegions, RGB);

			//load the image to the SLM
			Write_image(Image, isEightBit);

			//give the LC time to settle into the image
			Sleep(100);

			std::cout << "Input power:\n\r";
			std::cin >> rawInput;
			AI_Intensities[Gray] = rawInput;

			//printf("Input: %d\n\r", rawInput);
			//std::cout << inputVal;
			//YOU FILL IN HERE...FIRST: read from your specific AI board, note it might help to clean up noise to average several readings
			//SECOND: store the measurement in your AI_Intensities array
			//AI_Intensities[Gray] = measured value
		
		}
		printf("\n");

		//dump the AI Intensities to a csv file - THIS WILL PROPERLY FORMAT THE FILE
		//this first column should be an integer, and the second column a float
		FileName.Format(_T("Raw%d.csv"), region);
		sFile.Open(FileName, CFile::modeCreate | CFile::modeWrite | CFile::typeText);
		for (int i = 0; i < NumDataPoints; i++)
		{
			str.Format(_T("%d, %f\n"), i, AI_Intensities[i]);
			sFile.WriteString(str);
		}
		sFile.Close();
	}

	//clean up allocations
	delete[]Image;
	delete[]AI_Intensities;

	// Destruct
	Delete_SDK();

	return 0;
}

