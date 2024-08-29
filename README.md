# YomeX

**Y**unus' **O**rder **M**atching **E**ngine e**X**tra (...better features in development)

This project is a simulation of an order book and matching engine, implemented in C++. The system currently fetches static historical crypto market data using a Python script that interacts with the Alpha Vantage and Coinbase APIs.

## Current Features

- **Order Book Simulation:** Simulates an order book and matching engine.
- **Data Fetching:** Market data is retrieved using API calls to Alpha Vantage (for Level 1 market data) and Coinbase (for Level 2 market data).
- **Customization:** The script can be easily modified to fetch Level 2 data for different assets—however, planned WebSocket integration for non-crypto assets will not be compatible with the current system.

## Planned Features

- **WebSocket Integration:** Enabling live, real-time order matching with improved performance.
- **Automated Polling:** Refreshing the static market data (currently often ends with very few matched orders!).
- **Simple GUI:** A basic GUI to visualize order book data, performance, and switch between static and live data.
- **Strategy Testing:** Static daily data is currently underutilized—currently working on this.

## Directory Structure

- `data/`: Contains static market data in JSON format.
- `include/`: Contains header files for YomeX.
- `src/`: Contains source files for YomeX.
- `scripts/`: Contains Python scripts to fetch market data.

## Fetching Market Data

To fetch historical and order book data:

1. Run Python setup

   ```sh
   ./setup.sh
   ```

2. Activate venv:

   ```sh
   source venv/bin/activate
   ```

3. Run the Python script to retrieve the data:

   ```sh
   python fetchdata.py
   ```

## Compiling the Project

To compile the project, use the `make` command:

```sh
make
```

## Running the Matching Engine

To run the matching engine, execute:

```sh
./yomex
```

## Notes

- **Level 2 Market Data:** Crypto data is used by default due to its better availability. However, the `fetchdata.py` script can be modified to retrieve Level 2 data for other assets.

---
