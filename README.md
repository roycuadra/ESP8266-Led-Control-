# ESP8266 LED Control Access Point Mode
 
## Description

This project uses the ESP8266 microcontroller to create a Wi-Fi access point (AP) that hosts a simple web server for controlling an LED. Users can turn the LED on or off using buttons on the web page. The HTML content is stored in flash memory to save space.

## Features

- **Wi-Fi Access Point**: Sets up the ESP8266 as a Wi-Fi hotspot.
- **Web Server**: Hosts a web page to control the LED.
- **HTML Stored in Flash**: Uses `PROGMEM` to store the HTML page in flash memory.
- **LED Control**: Allows toggling an LED on and off via the web interface.

## Hardware Requirements

- **ESP8266 Module**: NodeMCU or similar.
- **LED**: Connected to pin D4 (GPIO2).

## Libraries Used

- `ESP8266WiFi.h` - For Wi-Fi connectivity.

## Configuration

1. **Wi-Fi Credentials**:
   - **SSID**: `ESP8266-AP`
   - **Password**: `12345678`
   
2. **LED Pin**:
   - Connected to pin D4 (GPIO2).

## Setup

1. **Include Libraries**:
   Ensure the `ESP8266WiFi` library is installed in your Arduino IDE.

2. **Upload Code**:
   Flash the code to your ESP8266 module using the Arduino IDE.

3. **Connect to Wi-Fi**:
   Connect to the ESP8266 Wi-Fi network with SSID `ESP8266-AP` and password `12345678`.

4. **Access Web Page**:
   Open a web browser and navigate to the IP address of the ESP8266, which will be displayed in the Serial Monitor.

## Code Overview

1. **Setup Function**:
   - Initializes serial communication.
   - Configures the LED pin and sets its initial state.
   - Sets up the ESP8266 as a Wi-Fi access point.
   - Starts the web server.

2. **Loop Function**:
   - Listens for incoming client connections.
   - Reads HTTP requests and processes commands to turn the LED on or off.
   - Updates the LED state and sends the appropriate HTML response.

3. **sendResponse Function**:
   - Formats and sends the HTML page to the client.
   - Displays the current LED state and provides buttons to toggle the LED.

## HTML Content

The HTML content is stored in flash memory using the `PROGMEM` keyword. This helps to minimize SRAM usage. The web page includes:
- A heading.
- A status indicator for the LED.
- Buttons to turn the LED on or off.

## Troubleshooting

- **No IP Address**: Ensure the ESP8266 is correctly powered and connected.
- **Web Page Not Loading**: Check if the ESP8266 is correctly connected to your Wi-Fi network and if the IP address is correct.
- **LED Not Responding**: Verify the LED connection and the pin configuration.

## License

This project is open-source and available under the MIT License. See the [LICENSE](LICENSE) file for more details.
