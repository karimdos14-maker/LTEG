<div align="center">
  <h1>🎮 LTEG (Lightweight Engine)</h1>
  <p>A custom, from-scratch C++ game engine built on modern OpenGL and Vulkan.</p>
  
  <p>
    <img src="https://img.shields.io/badge/C%2B%2B-17%2F20-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="C++">
    <img src="https://img.shields.io/badge/Vulkan-API-333333?style=for-the-badge&logo=vulkan&logoColor=AC142D" alt="Vulkan">
    <img src="https://img.shields.io/badge/License-GPL-green?style=for-the-badge" alt="License">
    <img src="https://img.shields.io/badge/Status-In%20Development-orange?style=for-the-badge" alt="Status">
  </p>

  <img width="1919" height="1049" alt="LTEG Preview" src="https://github.com/user-attachments/assets/4703a64b-a934-4fbc-96a4-351f1baeb60b">
</div>

---

## 📖 Overview

**LTEG** is a custom game engine written in C++ designed to explore low-level graphics programming, rendering pipelines, and real-time game loop architecture. Built to support multiple backends including **Vulkan**, it provides a lightweight, highly customizable foundation for building games from the ground up.

## ✨ Current Features

* **Window & Context Management:** Hardware-accelerated window initialization and context creation via GLFW.
* **Custom Engine Loop (`engineCycle`):** Dedicated tick and frame rendering architecture separated from platform initialization.
* **Modular Codebase:** Clean separation between core engine logic (`LTEG.h`) and graphics wrappers (`vulkann.h`).

## 🛠️ Tech Stack & Dependencies

* **Language:** C++
* **Graphics APIs:** Vulkan API
* **Windowing & Input:** [GLFW](https://www.glfw.org/)

## 🚀 Getting Started

### Prerequisites

Make sure you have a C++ compiler (MSVC, GCC, or Clang), CMake, and the appropriate SDKs (like the Vulkan SDK) configured on your system.

### Building & Running

1. **Clone the repository:**
   ```bash
   git clone [https://github.com/karimdos14-maker/LTEG.git]
   cd LTEG
