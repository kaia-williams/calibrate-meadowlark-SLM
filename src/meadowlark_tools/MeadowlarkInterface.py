import ctypes
import os
from ctypes import CDLL, POINTER, c_ubyte, c_uint, cdll
from dataclasses import dataclass
from time import sleep
from typing import List

import numpy

# flake8: noqa


@dataclass
class Gratings_Config:

    start_pitch: int  # in pixels
    end_pitch: int  # in pixels
    num_patterns: int  # unitless
    pattern_count_spacing: int  # spacing in between patern counts
    increase: bool
    horizontal: bool

    def __init__(
        self,
        start_pitch: int,
        end_pitch: int,
        pattern_count_spacing: int = 1,
        horizontal: bool = False,
        increase: bool = False,
    ):
        self.start_pitch = start_pitch
        self.end_pitch = end_pitch
        self.pattern_count_spacing = pattern_count_spacing
        self.horizontal = horizontal
        self.increase = increase
        self.num_patterns = abs(
            (self.end_pitch - self.start_pitch) / self.pattern_count_spacing
        )


@dataclass
class Grating_Object:

    pitch: int
    increase: bool
    horizontal: bool
    pattern_data: numpy.object_


class SLM_Interface:

    pxpitch = 9.2  # microns

    def __init__(self):

        self.libSLM, self.libImage, SLMsuccess = SLM_Interface.load_libs()
        self.create_SDK()

        self.RGB = c_uint(1)
        self.SLMheight = c_uint(self.libSLM.Get_Height())
        self.SLMwidth = c_uint(self.libSLM.Get_Width())
        self.SLMdepth = c_uint(self.libSLM.Get_Depth())
        self.bytesPerPixel = 4
        # RGBA

        self.SLMcenterX = c_uint(self.SLMwidth.value // 2)
        self.SLMcenterY = c_uint(self.SLMheight.value // 2)

        self.load_LUT(SLMsuccess)

    def __del__(self):
        # Always call Delete_SDK before exiting
        self.libSLM.Delete_SDK()
        print("SDK deleted.")

    @staticmethod
    def load_libs():
        """
        Load the SLM and Image libraries from the DLLs
        """

        workingdir = os.getcwd()
        dllDir = os.path.join("src", "ext")

        awareness = ctypes.c_int()
        """
        errorCode = ctypes.windll.shcore.GetProcessDpiAwareness(
            0, ctypes.byref(awareness)
        )
        """
        print(awareness.value)

        # Set DPI Awareness  (Windows 10 and 8)
        # errorCode = ctypes.windll.shcore.SetProcessDpiAwareness(2)
        # the argument is the awareness level, which can be 0, 1 or 2:
        # for 1-to-1 pixel control I seem to need it to be non-zero (I'm using level 2)

        # Set DPI Awareness  (Windows 7 and Vista)
        success = ctypes.windll.user32.SetProcessDPIAware()
        # behaviour on later OSes is undefined,
        # although when I run it on my Windows 10 machine,
        # it seems to work with effects identical to SetProcessDpiAwareness(1)
        ######################################################################

        # Load the DLL
        # Blink_C_wrapper.dll, HdmiDisplay.dll, ImageGen.dll, freeglut.dll and glew64.dll
        # should all be located in the same directory as the program referencing the
        # library
        try:
            cdll.LoadLibrary(os.path.join(dllDir, "Blink_C_wrapper"))
            slm_lib = CDLL("Blink_C_wrapper")
        except OSError:
            print(
                f"WARNING: could not load Blink_C_wrapper.dll from root directory: {dllDir}."
                + "Please validate .dll integrity. Trying to load from Meadowlark Install dir."
            )
            try:
                cdll.LoadLibrary(
                    "C:\\Program Files\\Meadowlark Optics\\Blink 1920 HDMI\\SDK\\Blink_C_wrapper"
                )
                slm_lib = CDLL("Blink_C_wrapper")
            except:
                raise Exception(
                    f"Could not load Blink_C_wrapper.dll in either {dllDir} or \
                    C:\\Program Files\\Meadowlark Optics\\Blink 1920 HDMI\\SDK"
                )
        except:
            raise Exception(
                "Could not load Blink_C_wrapper.dll due to some unknown error."
            )

        try:
            # Open the image generation library
            cdll.LoadLibrary(os.path.join(dllDir, "ImageGen"))
            image_lib = CDLL("ImageGen")
        except OSError:
            print(
                f"WARNING: could not load ImageGen.dll from root directory: {dllDir}"
                + "Please validate .dll integrity. Trying to load from Meadowlark Install dir."
            )
            try:
                cdll.LoadLibrary(
                    "C:\\Program Files\\Meadowlark Optics\\Blink 1920 HDMI\\SDK\\ImageGen"
                )
                image_lib = CDLL("ImageGen")
            except:
                raise Exception(
                    f"Could not load ImageGen.dll in either {dllDir} or \
                        C:\\Program Files\\Meadowlark Optics\\Blink 1920 HDMI\\SDK"
                )
        except:
            raise Exception("Could not load ImageGen.dll due to some unknown error.")

        return slm_lib, image_lib, success

    def create_SDK(self) -> None:
        """
        Create the SDK using the loaded SLM library
        """
        # Call the constructor
        self.libSLM.Create_SDK()
        print("Blink SDK was successfully constructed")

    def load_LUT(self, sucVal: int) -> None:
        # ***you should replace linear.LUT with your custom LUT file***
        # but for now open a generic LUT that linearly maps input graylevels to output voltages
        # ***Using linear.LUT does NOT give a linear phase response***
        sucVal = 0
        if self.SLMheight.value == 1152:
            sucVal = self.libSLM.Load_lut(
                "C:\\Program Files\\Meadowlark Optics\\Blink 1920 HDMI\\LUT Files\\1920x1152_linearVoltage.lut"
            )
        if (self.SLMheight.value == 1200) and (self.SLMdepth.value == 8):
            sucVal = self.libSLM.Load_lut(
                "C:\\Program Files\\Meadowlark Optics\\Blink 1920 HDMI\\LUT Files\\19x12_8bit_linearVoltage.lut"
            )
        if (self.SLMheight.value == 1200) and (self.SLMdepth.value == 10):
            sucVal = self.libSLM.Load_lut(
                "C:\\Program Files\\Meadowlark Optics\\Blink 1920 HDMI\\LUT Files\\19x12_10bit_linearVoltage.lut"
            )

        if sucVal > 0:
            print("LoadLUT Successful")
        else:
            print("LoadLUT Failed")

    def generate_grating_patterns(
        self, gratings: Gratings_Config
    ) -> List[Grating_Object]:
        """
        Generate a number of grating patterns with defined inputs.

        Parameters
        ----------
        start_Prd : int
            The spatial frequency to start with .
        end_Prd  : int
            The spatial frequency to end with.
        numPats (optional): int
            Number of patterns to generate
        increase (optional) : bool
            Does the pattern increase or decrease across period?
        horizontal (optional): bool
            Does the pattern go up-down or left-right?
        Returns
        -------
        numpy Array
            An array contianing the list of gratings.
        """
        # check if the periods spacing is an integer number. if not, error
        if (gratings.end_pitch - gratings.start_pitch) % gratings.num_patterns != 0:
            raise TypeError("The period interval must be an integer!")

        try:
            imVolume = self.SLMwidth.value * self.SLMheight.value * self.bytesPerPixel
        except NameError:
            print("WARNING: self not defined")
            imVolume = 50

        # Create a blank vector to hold the wavefront correction
        WFC = numpy.empty([imVolume], numpy.uint8, "C")

        # Create a blank list to hold the image arrays
        listOfGratings: List[Grating_Object] = []

        for prd in range(
            gratings.start_pitch, gratings.end_pitch, gratings.pattern_count_spacing
        ):
            listOfGratings.append(
                Grating_Object(
                    pitch=prd,
                    increase=gratings.increase,
                    horizontal=gratings.horizontal,
                    pattern_data=numpy.empty([imVolume], numpy.uint8, "C"),
                )
            )
            # append a list of objects with a new Grating_Object containing prd and data from gratings
            # append list of periods by inverting frequency
            # periods.append(1 / prd)

        for patrn in listOfGratings:
            # img.pattern_data =
            self.libImage.Generate_Grating(
                patrn.pattern_data.ctypes.data_as(POINTER(c_ubyte)),
                WFC.ctypes.data_as(POINTER(c_ubyte)),
                self.SLMwidth.value,
                self.SLMheight.value,
                self.SLMdepth.value,
                patrn.pitch,
                patrn.increase,
                patrn.horizontal,
                self.RGB,
            )

        return listOfGratings

    def write_images_to_SLM(
        self, listOfGratings: List[Grating_Object], delay: int = 0
    ) -> None:
        """
        Write images passed to funciton to SLM
        """
        is_eight_bit_image = c_uint(0)

        # Loop between our images
        for img in listOfGratings:
            self.libSLM.Write_image(
                img.pattern_data.ctypes.data_as(POINTER(c_ubyte)),
                is_eight_bit_image,
            )
            sleep(delay)
            # This is in seconds

    def BlinkExampleOOP(self) -> None:

        is_eight_bit_image = c_uint(0)

        imVolume = self.SLMwidth.value * self.SLMheight.value * self.bytesPerPixel
        # Create two vectors to hold values for two SLM images
        ImageOne = numpy.empty([imVolume], numpy.uint8, "C")
        ImageTwo = numpy.empty([imVolume], numpy.uint8, "C")

        # Create a blank vector to hold the wavefront correction
        WFC = numpy.empty([imVolume], numpy.uint8, "C")

        # Generate phase gradients
        VortexCharge = 5
        self.libImage.Generate_LG(
            ImageOne.ctypes.data_as(POINTER(c_ubyte)),
            WFC.ctypes.data_as(POINTER(c_ubyte)),
            self.SLMwidth.value,
            self.SLMheight.value,
            self.SLMdepth.value,
            VortexCharge,
            self.SLMcenterX.value,
            self.SLMcenterY.value,
            0,
            self.RGB,
        )
        VortexCharge = 3
        self.libImage.Generate_LG(
            ImageTwo.ctypes.data_as(POINTER(c_ubyte)),
            WFC.ctypes.data_as(POINTER(c_ubyte)),
            self.SLMwidth.value,
            self.SLMheight.value,
            self.SLMdepth.value,
            VortexCharge,
            self.SLMcenterX.value,
            self.SLMcenterY.value,
            0,
            self.RGB,
        )

        # Loop between our images
        for x in range(6):
            self.libSLM.Write_image(
                ImageOne.ctypes.data_as(POINTER(c_ubyte)), is_eight_bit_image
            )
            sleep(1.0)
            # This is in seconds
            self.libSLM.Write_image(
                ImageTwo.ctypes.data_as(POINTER(c_ubyte)), is_eight_bit_image
            )
            sleep(1.0)
            # This is in seconds

    @staticmethod
    def BlinkExample():
        # this function probably doesn't work. is only included within this method for posterity anyway

        slm_lib, image_lib, success = SLM_Interface.load_libs()

        # indicate that our images are RGB
        RGB = c_uint(1)
        is_eight_bit_image = c_uint(0)

        height = c_uint(slm_lib.Get_Height())
        width = c_uint(slm_lib.Get_Width())
        depth = c_uint(slm_lib.Get_Depth())
        bytpesPerPixel = 4
        # RGBA

        center_x = c_uint(width.value // 2)
        center_y = c_uint(height.value // 2)

        # ***you should replace linear.LUT with your custom LUT file***
        # but for now open a generic LUT that linearly maps input graylevels to output voltages
        # ***Using linear.LUT does NOT give a linear phase response***
        success = 0
        if height.value == 1152:
            success = slm_lib.Load_lut(
                "C:\\Program Files\\Meadowlark Optics\\Blink 1920 HDMI\\LUT Files\\1920x1152_linearVoltage.lut"
            )
        if (height.value == 1200) and (depth.value == 8):
            success = slm_lib.Load_lut(
                "C:\\Program Files\\Meadowlark Optics\\Blink 1920 HDMI\\LUT Files\\19x12_8bit_linearVoltage.lut"
            )
        if (height.value == 1200) and (depth.value == 10):
            success = slm_lib.Load_lut(
                "C:\\Program Files\\Meadowlark Optics\\Blink 1920 HDMI\\LUT Files\\19x12_10bit_linearVoltage.lut"
            )

        if success > 0:
            print("LoadLUT Successful")
        else:
            print("LoadLUT Failed")

        # Create two vectors to hold values for two SLM images
        ImageOne = numpy.empty(
            [width.value * height.value * bytpesPerPixel], numpy.uint8, "C"
        )
        ImageTwo = numpy.empty(
            [width.value * height.value * bytpesPerPixel], numpy.uint8, "C"
        )

        # Create a blank vector to hold the wavefront correction
        WFC = numpy.empty(
            [width.value * height.value * bytpesPerPixel], numpy.uint8, "C"
        )

        # Generate phase gradients
        VortexCharge = 5
        image_lib.Generate_LG(
            ImageOne.ctypes.data_as(POINTER(c_ubyte)),
            WFC.ctypes.data_as(POINTER(c_ubyte)),
            width.value,
            height.value,
            depth.value,
            VortexCharge,
            center_x.value,
            center_y.value,
            0,
            RGB,
        )
        VortexCharge = 3
        image_lib.Generate_LG(
            ImageTwo.ctypes.data_as(POINTER(c_ubyte)),
            WFC.ctypes.data_as(POINTER(c_ubyte)),
            width.value,
            height.value,
            depth.value,
            VortexCharge,
            center_x.value,
            center_y.value,
            0,
            RGB,
        )

        # Loop between our images
        for x in range(6):
            slm_lib.Write_image(
                ImageOne.ctypes.data_as(POINTER(c_ubyte)), is_eight_bit_image
            )
            sleep(1.0)
            # This is in seconds
            slm_lib.Write_image(
                ImageTwo.ctypes.data_as(POINTER(c_ubyte)), is_eight_bit_image
            )
            sleep(1.0)
            # This is in seconds

        # Always call Delete_SDK before exiting
        slm_lib.Delete_SDK()
