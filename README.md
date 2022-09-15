# Meadowlark SLM Calibration in Python

This repo can be used to generate a .csv file for the Meadowlark SLMs. By default, a ThorLabs power meter is used to generate the intenisites required for calibration, but other devices can be inserted as neccesary. 

## Installation
To use this software, clone the repository onto your local machine. I'm using [poetry](https://python-poetry.org/) for package management; if you choose to do so as well, simply navigate to your repository and type `poetry install` to get your packages all in order. This software only requires numpy and pandas, so it should work with most default scientific python installs anyway.

## Usage

Run the `__init__.py` file located in the `src` directory. The bulk of the script is located in the `run_calibration()` method within `calibrate.py`. If you'd like to use a power meter other than the ThorLabs models supported by the script, adjust `calibrate.py` beginning in line 141 and remove the `tlpm_interface` call in line 18.

Bundled within the repo is Thorlabs [example code](https://www.thorlabs.com/software_pages/viewsoftwarepage.cfm?code=OPM) they've provided for their power meters (`src/Thorlabs`) and the Meadowlark manual (located in the `docs` directory)

## Acknowledgements

This software relies heavily on a python template written by [Rudyard Richter](https://github.com/rudyardrichter), and the `run_calibration()` method is based heavily on the C++ code provided by Meadowlark to calibrate their SLMs. 
