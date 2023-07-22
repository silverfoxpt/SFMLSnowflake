# SFMLSnowflake

SFMLSnowflake is a 2D Snowflake Generator that uses the Cellular Automata (CA) principle and is implemented using the C++ SFML library, along with the ImGui library for the User Interface (UI).

Wiki: [https://en.wikipedia.org/wiki/Cellular_automaton](https://en.wikipedia.org/wiki/Cellular_automaton)

Reference research: [https://www.sciencedirect.com/science/article/abs/pii/S0167278907003387](https://www.sciencedirect.com/science/article/abs/pii/S0167278907003387)

## Installation

To run the simulator, download and execute the `main.exe` file.

## Features

Modify starting conditions for generating a snowflake on a 2D hexagonal grid.

## Usage
* Settings
	* Size settings
		* Hexagon cell diameter
		* Number of columns/rows
		* Offset (compared to center)
	* Crystal settings:
		* `rho`: Initial value of the density of water vapor in each cell.
		* `beta`, `alpha`, `theta`: Control the likelihood of *non-crystal* cells attaching to *crystal-ed* cell, based on their *vapor*, *quasi-liquid* and *ice* mass.
		* `kappa` : Control boundary diffusive mass (*quasi-liquid*) proportions of turning to ice.
		* `mu`, `gamma`: Control boundary diffusive mass (*quasi-liquid*) proportions of turning **back** into vapor.
		* `sigma`: Random noise
