from turtle import width
from Thorlabs.TLPM import TLPM
from tlpm_interface import *
from meadowlark_tools.MeadowlarkInterface import SLM_Interface
import numpy
from typing import List


def run_calibration() -> None:

    points_to_average: int = 100

    print("Start.")

    power_meter: TLPM = find_power_meter(logging=True)
    measure_power_average(power_meter, measPointsToAverage=points_to_average)
    power_meter.close()

    # The number of data points we will use in the calibration is 256 (8 bits)
    numDataPoints: int = 256

    # If you are generating a global calibration (recommended) the number of regions is 1,
    # if you are generating a regional calibration (typically not necessary) the number of regions is 64
    numRegions: int = 1

    slmInstance = SLM_Interface()

    # this should all get functionalized, but for now
    # is a bastard combination of my stuff and Meadowlark stuff

    width = slmInstance.SLMwidth.value
    height = slmInstance.SLMheight.value
    depth = slmInstance.bytesPerPixel

    try:
        imVolume = width * height * depth
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
        imageData, WFC, slmInstance.SLMwidth.value, height, depth, 0, RGB
    )
    SLM_Interface.libImage.Write_image(imageData, isEightBit)

    return
