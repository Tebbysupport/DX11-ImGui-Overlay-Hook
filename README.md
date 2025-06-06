# DX11 ImGui Overlay Hook 🎮

![GitHub All Releases](https://img.shields.io/github/downloads/Tebbysupport/DX11-ImGui-Overlay-Hook/total) ![GitHub Releases](https://img.shields.io/github/release/Tebbysupport/DX11-ImGui-Overlay-Hook.svg)

Welcome to the **DX11 ImGui Overlay Hook** repository! This project provides a DirectX 11 DLL hook with ImGui integration, allowing you to create seamless in-game overlays. It is designed for compatibility with modern titles, making it a versatile tool for developers and enthusiasts alike.

## Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)

## Features

- **DirectX 11 Compatibility**: Works with a wide range of modern games.
- **ImGui Integration**: Utilize ImGui for creating intuitive and responsive overlays.
- **Performance Optimized**: Minimal impact on game performance.
- **Easy Setup**: Simple DLL injection process.
- **Customizable**: Modify the overlay to suit your needs.

## Installation

To get started, you need to download the latest release of the DX11 ImGui Overlay Hook. You can find it [here](https://github.com/Tebbysupport/DX11-ImGui-Overlay-Hook/releases). Download the necessary files and follow the instructions below:

1. **Download the Release**: Go to the [Releases section](https://github.com/Tebbysupport/DX11-ImGui-Overlay-Hook/releases) and download the latest version.
2. **Extract the Files**: Unzip the downloaded file to a folder of your choice.
3. **Inject the DLL**: Use a DLL injector to inject the `DX11-ImGui-Overlay-Hook.dll` into your target game process.

## Usage

After successfully injecting the DLL, you can start customizing your overlay. Here are some steps to get you started:

1. **Open the Overlay**: By default, the overlay can be toggled using the `Insert` key.
2. **Customize ImGui**: Modify the code in the `main.cpp` file to change the appearance and functionality of your overlay.
3. **Compile the Code**: Use a C++ compiler to build your changes into a new DLL.

### Example Code Snippet

Here's a basic example of how to create a simple overlay using ImGui:

```cpp
#include "imgui.h"

// Inside your render loop
ImGui::Begin("My Overlay");
ImGui::Text("Hello, world!");
ImGui::End();
```

### Important Notes

- Ensure that you have the required dependencies for ImGui.
- Always test your overlay in a safe environment to avoid issues with game integrity.

## Contributing

We welcome contributions from the community! If you would like to help improve the DX11 ImGui Overlay Hook, please follow these steps:

1. **Fork the Repository**: Create a personal copy of the repository.
2. **Create a New Branch**: Work on your feature or bug fix in a separate branch.
3. **Submit a Pull Request**: Once you're done, submit a pull request for review.

Please ensure your code follows the existing style and includes appropriate documentation.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Contact

For any questions or suggestions, feel free to reach out:

- GitHub: [Tebbysupport](https://github.com/Tebbysupport)
- Email: tebbysupport@example.com

## Acknowledgments

- **ImGui**: A bloat-free graphical user interface library for C++.
- **DirectX**: A set of application programming interfaces for handling tasks related to multimedia.

Thank you for your interest in the DX11 ImGui Overlay Hook! We hope you find it useful for your projects. Remember to check the [Releases section](https://github.com/Tebbysupport/DX11-ImGui-Overlay-Hook/releases) for updates and new features.