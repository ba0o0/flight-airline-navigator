# Flight Airline Navigator
A text-based application that allows user to manage airport routes and navigation.

## Overview

A C++ application for building and managing airline routes using a custom linked-list implementation. Users can create routes from a list of airports, display them with total distance, remove airports, and reverse routes.

## Features

- **Route Creation** — Build custom flight routes by selecting from 40 preloaded airports. Add as many stops as you want (minimum 2), and the route is automatically named after the first and last airport (e.g. "Amsterdam to Bangkok").

- **Route Display** — View any saved route as a numbered list of airports with their code, full name, city, country, and coordinates. Total route distance in miles is calculated and shown at the bottom.

- **Airport Removal** — Remove any airport from an existing route by index. Only available when a route has more than 2 airports. The route name updates automatically to reflect the new endpoints.

- **Route Reversal** — Reverse the order of airports in any route. Can be applied multiple times. The route name updates to match (e.g. "Bangkok to Amsterdam"). Nodes are physically rotated — not just data-swapped.

- **Distance Calculation** — Total mileage is computed for any route using geographic coordinates (degrees north/west) via the provided `CalcDistance` function, summing leg-by-leg distances across the full route.

## How use my makefile
```bash
# To compile the code
make proj3
```
```bash
# To run the code 
make run
```
```bash
# To clean
make clean
```

---

## File Structure

| File | Description |
|------|-------------|
| `proj3.cpp` | Program entry point |
| `Airport.h` |`Airport` node class declaration |
| `Airport.cpp` |`Airport` class definitions |
| `Route.h` | `Route` linked-list class declaration |
| `Route.cpp` | `Route` class definitions |
| `Navigator.h` |`Navigator` manager class declaration |
| `Navigator.cpp` |`Navigator` class definitions |
| `proj3_data.txt` | Input file with 40 airports with location data |

---
