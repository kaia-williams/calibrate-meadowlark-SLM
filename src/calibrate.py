from Thorlabs.TLPM import TLPM
from tlpm_interface import *


def run_calibration() -> None:

    points_to_average: int = 100

    print("Start.")

    power_meter: TLPM = find_power_meter(logging=True)
    measure_power_average(power_meter, measPointsToAverage=points_to_average)
    power_meter.close()

    return
