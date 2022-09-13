from ..Thorlabs.TLPM import TLPM
from ctypes import (
    byref,
    c_double,
)


def measure_power_instant(device_PowerMeter: TLPM) -> float:
    """
    Measures the instantaneous power recorded by the power meter
    """
    power: float
    power_memory_location = c_double()
    device_PowerMeter.measPower(byref(power_memory_location))
    power = power_memory_location.value

    return power


def measure_power_average(
    device_PowerMeter: TLPM,
    measPointsToAverage: int | None = None,
    timeToAverage: float | None = None,
) -> float | None:
    """
    Measures the average power either by points or time
    """

    avgPower: float

    if measPointsToAverage == None:

        print("No value passed to points")
        return None

    else:
        count = 0
        powers = []
        while count < measPointsToAverage:
            powers.append(measure_power_instant(device_PowerMeter=device_PowerMeter))
            count += 1
        return sum(powers) / len(powers)
