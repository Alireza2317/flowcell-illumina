# Flow Cell Illumina Simulation

This project simulates the process of DNA sequencing on an Illumina flow cell. It can generate synthetic data representing clusters of DNA on a flow cell and then processes this data to detect and analyze these clusters.

## Features

*   **Data Generation:** Create synthetic flow cell data with customizable parameters.
*   **Frame Processing:** Load and process individual frames (images) from the simulated data.
*   **Blob Detection:** Identify and analyze DNA clusters within the processed frames.

## Getting Started

To get a local copy up and running, follow these simple steps.

### Prerequisites

*   CMake (version 3.10 or higher)
*   OpenCV (version 4.x)
*   A C++23 compatible compiler (e.g., GCC, Clang)

### Installation and Build

1.  **Clone the repository:**

    ```bash
    git clone https://github.com/Alireza2317/flowcell-illumina.git
    cd flowcell-illumina
    ```

2.  **Create a build directory and configure CMake:**

    ```bash
    mkdir build
    cd build
    cmake ..
    ```

3.  **Build the project:**

    ```bash
    cmake --build . --config Release
    ```

    This will build all targets, including `datagen` and `analyze`.

## Data Preparation

Before running the main analysis, you need to generate a dataset using the `datagen` executable.

```bash
./datagen
```

This will create a new directory `test_data` inside the `data` folder with simulated frames and a `.txt` file, holding the blob positions and actual sequences.

### Examples of the generated frames/images:

Frame 1:
<img width="800" height="800" alt="frame_1" src="https://github.com/user-attachments/assets/d0b539f4-fa81-4f4c-b529-b26aacab161c" />

Frame 2:
<img width="800" height="800" alt="frame_2" src="https://github.com/user-attachments/assets/b862f28a-0beb-461b-8892-944cfbb67d3a" />

And so on...

## Usage

After building and preparing your data, you can run the analysis tools.

### Analysis Tool

The `analyze` executable processes an existing dataset.

```bash
./analyze
```

## Contributing

Contributions are what make the open-source community such an amazing place to learn, inspire, and create. Any contribution you make is **greatly appreciated**.
