from Thorlabs.TLPM import TLPM
import tlpm_interface
from ctypes import POINTER, c_ubyte
from meadowlark_tools.MeadowlarkInterface import SLM_Interface
import numpy
from time import sleep
import pandas as pd
from os import path


def run_calibration() -> None:

    points_to_average: int = 100

    print("Start.")

    # find and create a power meter instance
    power_meter: TLPM = tlpm_interface.find_power_meter(logging=True)

    # The number of data points we will use in the calibration is 256 (8 bits)
    numDataPoints: int = 256

    # If you are generating a global calibration (recommended) the number of regions is 1,
    # if you are generating a regional calibration (typically not necessary) the number of regions is 64
    numRegions: int = 1

    slmInstance = SLM_Interface()

    # libSLM, libImage, SLMsuccess = SLM_Interface.load_libs()

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
    blankData = numpy.empty([imVolume], dtype=numpy.uint8, order="C")
    gratingData = numpy.empty([imVolume], dtype=numpy.uint8, order="C")

    # The meadowlark methods anticipate getting pointers to the location of the
    # empty arrays used to hold the image and grating data
    blankDataLoc = blankData.ctypes.data_as(POINTER(c_ubyte))
    gratingDataLoc = gratingData.ctypes.data_as(POINTER(c_ubyte))

    # Create a blank vector to hold the wavefront correction
    WFCData = numpy.empty([imVolume], dtype=numpy.uint8, order="C")
    # same as image data; slm methods expect a memory pointer
    WFCDataLoc = WFCData.ctypes.data_as(POINTER(c_ubyte))

    # start the SLM blank, we are using RGB images
    isEightBit = False
    RGBbool: bool = True
    vert: bool = True

    slmInstance.libImage.Generate_Solid(
        blankDataLoc,
        WFCDataLoc,
        SLMwidth,
        SLMheight,
        SLMdepth,
        0,
        RGBbool,
    )

    # note that this method is a member of libSLM, not libImage
    slmInstance.libSLM.Write_image(blankDataLoc, isEightBit)

    PixelValueOne: int = 0
    PixelValueTwo: int = 0

    # use a reference graylevel of 0 for the 1920x1152 and 255 for the 1920x1200
    if SLMheight == 1152:
        PixelValueOne = 0
    else:
        PixelValueOne = 255

    PixelPerStripe: int = 8
    avg_pwr: int = 0

    regional_fn = ""

    for region in range(numRegions):
        print(f"Region: {region}")

        # create an array to hold the intensities recorded by the power meter
        localDataToWrite = pd.DataFrame(columns=["Intensity"])
        localGray = []
        localIntensity = []

        for gray in range(numDataPoints):
            print(f"Gray Value: {gray}")  # , end ="\r")

            # the variable graylevel increments from 0 - 255 for the 1920x1152, and decrements from 255 to 0 for the 1920x1200
            if SLMheight == 1152:
                PixelValueTwo = gray
            else:
                PixelValueTwo = 255 - gray

            slmInstance.libImage.Generate_Stripe(
                gratingDataLoc,
                WFCDataLoc,
                SLMwidth,
                SLMheight,
                SLMdepth,
                PixelValueOne,
                PixelValueTwo,
                PixelPerStripe,
                vert,
                RGBbool,
            )

            slmInstance.libImage.Mask_Image(
                gratingDataLoc,
                SLMwidth,
                SLMheight,
                SLMdepth,
                region,
                numRegions,
                RGBbool,
            )

            # note that this method is a member of libSLM, not libImage
            slmInstance.libSLM.Write_image(gratingDataLoc, isEightBit)

            # sleep for 100 ms to let the SLM settle into the pattern
            sleep(0.1)

            # measure power meter values
            # for this example, we will be interfacing with the thorlabs
            # interface to measure the average power
            # from the first power meter connected to the computer

            avg_pwr: float = tlpm_interface.measure_power_average(
                power_meter, measPointsToAverage=points_to_average
            )

            if avg_pwr == None:
                print("No data returned from power meter.")
            else:
                print(f"Average power: {avg_pwr}")

            localGray.append(gray)
            localIntensity.append(avg_pwr)

        regional_fn = path.join("output_files", f"Raw {region}.csv")

        print(f"Writing region {region} data to: {regional_fn}... ", end="")
        # localDataToWrite["Gray"] = localGray
        localDataToWrite["Intensity"] = localIntensity
        localDataToWrite.to_csv(regional_fn, header=False)
        print(" written.")

    print("Completed calibration.")

    power_meter.close()

    return
