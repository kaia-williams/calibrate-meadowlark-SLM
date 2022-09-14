from Thorlabs.TLPM import TLPM
from tlpm_interface import *
from meadowlark_tools.MeadowlarkInterface import SLM_Interface
import numpy
from typing import List
from time import sleep
import pandas as pd

def run_calibration() -> None:

    points_to_average: int = 100

    print("Start.")

    # find and create a power meter instance
    power_meter: TLPM = find_power_meter(logging=True)
       
    # The number of data points we will use in the calibration is 256 (8 bits)
    numDataPoints: int = 256

    # If you are generating a global calibration (recommended) the number of regions is 1,
    # if you are generating a regional calibration (typically not necessary) the number of regions is 64
    numRegions: int = 1

    slmInstance = SLM_Interface()

    # this should all get functionalized, but for now
    # is a bastard combination of my stuff and Meadowlark stuff

    SLMwidth = slmInstance.SLMwidth.value
    SLMheight = slmInstance.SLMheight.value
    SLMdepth = slmInstance.bytesPerPixel

    try:
        imVolume = SLMwidth * SLMheight * SLMdepth
    except NameError:
        print("WARNING: slmInstance not defined")
        imVolume = 50

    # Create an array to hold the image data
    imageData = numpy.empty([imVolume], dtype=numpy.unit8, order="C")

    # Create a blank vector to hold the wavefront correction
    WFC = numpy.empty([imVolume], dtype=numpy.uint8, order="C")

    # create an array to hold the intensities recorded by the power meter
    dataIntensities: List[float] = []

    # start the SLM blank, we are using RGB images
    isEightBit = False
    RGB: bool = True
    vert: bool = True

    SLM_Interface.libImage.Generate_Solid(
        imageData, WFC, slmInstance.SLMwidth.value, SLMheight, SLMdepth, 0, RGB
    )
    SLM_Interface.libImage.Write_image(imageData, isEightBit)

    # load diffraction patterns, and record the 1st order intensity

    PixelValueOne, PixelValueTwo: int = 0 

    # use a reference graylevel of 0 for the 1920x1152 and 255 for the 1920x1200
    if (SLMheight == 1152):
        PixelValueOne = 0; 
    else:
        PixelValueOne = 255;

    PixelPerStripe: int = 8
    avg_pwr: int = 0

    for region in range(numRegions): 
        print(f"Region: {region}")

        for gray in range(numDataPoints):
            print(f"Gray Value: {gray}")#, end ="\r")

            # the variable graylevel increments from 0 - 255 for the 1920x1152, and decrements from 255 to 0 for the 1920x1200
            if (SLMheight == 1152):
                PixelValueTwo = gray;
            else:
                PixelValueTwo = 255 - gray;

            SLM_Interface.libimage.Generate_Stripe(imageData, WFC, SLMwidth, SLMheight, SLMdepth, PixelValueOne, PixelValueTwo, PixelPerStripe, vert, RGB)

            SLM_Interface.libimage.Mask_Image(imageData, SLMwidth, SLMheight, SLMdepth, region, numRegions, RGB)

            SLM_Interface.libimage.Write_image(imageData, isEightBit)

            # sleep for 100 ms to let the SLM settle into the pattern
            sleep(0.1)

            #measure power meter values
            avg_pwr = measure_power_average(power_meter, measPointsToAverage=points_to_average)
            print(f"Average power: {avg_pwr}")
            dataIntensities.append(avg_pwr)

    print("Completed calibration. Writing data...")

    #need to create a dataframe to hold the data and print to CSV

    power_meter.close()

    return
