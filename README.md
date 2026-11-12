<div align="center">
  <h1>🎮 LTEG (Lightweight Engine)</h1>
  <p>A custom, from-scratch C++ game engine built on modern OpenGL.</p>
  
  <p>
    <img src="https://img.shields.io/badge/C%2B%2B-17%2F20-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="C++">
    <img src="https://img.shields.io/badge/OpenGL-3.3%20Core-5586A4?style=for-the-badge&logo=opengl&logoColor=white" alt="OpenGL">
    <img src="https://img.shields.io/badge/License-MIT-green?style=for-the-badge" alt="License">
    <img src="https://img.shields.io/badge/Status-In%20Development-orange?style=for-the-badge" alt="Status">
  </p>

  <img width="1919" height="1049" alt="LTEG Preview" src="https://github.com/user-attachments/assets/4703a64b-a934-4fbc-96a4-351f1baeb60b">
</div>

---

## 📖 Overview

**LTEG** is a custom game engine written in C++ designed to explore low-level graphics programming, rendering pipelines, and real-time game loop architecture. Built directly on top of **OpenGL 3.3 Core**, **GLFW**, and **GLAD**, it provides a lightweight, dependency-minimal foundation for building games from the ground up.

## ✨ Current Features

* **Window & Context Management:** Hardware-accelerated window initialization and OpenGL 3.3 Core Profile context creation via GLFW.
* **Modern OpenGL Loader:** Dynamic OpenGL function loading powered by GLAD.
* **Custom Engine Loop (`engineCycle`):** Dedicated tick and frame rendering architecture separated from platform initialization.
* **Modular Codebase:** Clean separation between core engine logic (`LTEG.h`) and graphics backend wrappers (`opengl.h`).

## 🛠️ Tech Stack & Dependencies

* **Language:** C++
* **Graphics API:** OpenGL 3.3 Core Profile
* **Windowing & Input:** [GLFW](https://www.glfw.org/)
* **OpenGL Loader:** [GLAD](https://glad.dav1d.de/)

## 🚀 Getting Started

### Prerequisites

Make sure you have a C++ compiler (MSVC, GCC, or Clang) and CMake or Visual Studio configured with GLFW and GLAD include/library paths.

### Building & Running

1. **Clone the repository:**
   ```bash
   git clone [https://github.com/karimdos14-maker/LTEG.git](https://github.com/karimdos14-maker/LTEG.git)
   cd LTEG
