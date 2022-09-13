from Thorlabs.TLPM import TLPM
from tlpm_interface import *


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

    return
