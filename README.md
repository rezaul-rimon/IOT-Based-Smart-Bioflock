# IoT-Based Smart Bioflock Monitoring System

Monitor and manage your bioflock environment in real-time with this ESP-32-based IoT system. Continuously track temperature, pH, TDS, oxygen, and nutrient levels. Easily visualize data through Thingspeak IoT for effective bioflock management.

## Table of Contents
- [Features](#features)
- [Hardware Components](#hardware-components)
- [Installation](#installation)
- [Usage](#usage)
- [Configuration](#configuration)
- [Contributing](#contributing)
- [License](#license)

## Features

- **Real-time Monitoring:** The ESP-32 microcontroller collects data in real-time from various sensors deployed in the bioflock, providing up-to-the-minute information on the environmental conditions.

- **Multi-sensor Integration:** This system integrates four 50K POTs as substitutes for individual sensors, measuring pH, dissolved oxygen, nutrient levels, and TDS. The DS18B20 serves as the temperature sensor, offering accurate temperature readings.

- **Automated Water Management:** A water pump and water treatment plant are employed to adjust water quality based on TDS values. This ensures optimal conditions for the bioflock.

- **Oxygen Enrichment:** An air pump is utilized to add oxygen to the bioflock environment based on real-time oxygen level readings.

## Hardware Components

- ESP-32 Microcontroller
- DS18B20 Temperature Sensor
- Four 50K POTs (pH, Dissolved Oxygen, Nutrient, TDS)
- Water Pump
- Water Treatment Plant
- Air Pump

## Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/rezaul-rimon/IOT-Based-Smart-Bioflock.git
2. Navigate to the project directory:
    ```bash
    cd iot-bioflock-monitoring
3. Install required dependencies:
    ```bash
    pip install -r requirements.txt

## Usage

1. Connect the hardware components according to the provided schematic.

2. Upload the Arduino sketch (`ThingSpeak.ino`) to the ESP-32 using the Arduino IDE or your preferred method.

3. Power on the system and monitor the bioflock conditions in real-time through the Thingspeak IoT platform.

## Configuration

- Update the Thingspeak API key in the Arduino sketch to link your sensor data with your Thingspeak channel.

- Adjust threshold values for water quality and oxygen enrichment based on your bioflock requirements.

## Contributing

Contributions are welcome! Feel free to open an issue or submit a pull request.

## License

This project is licensed under the [MIT License](LICENSE).

