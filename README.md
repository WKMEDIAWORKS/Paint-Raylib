# Paint-Raylib

A simple **paint application written in C using Raylib**, built as a learning project to explore
low-level graphics, pixel manipulation, HiDPI (Retina) handling, and render textures.

This project focuses on **understanding how things work**, not hiding complexity behind abstractions.

---

## Features

-  **Color palette** with clickable color selection  
-  **Pixel-level drawing** using mouse input  
-  **Persistent canvas** using `RenderTexture2D`  
-  **HiDPI / macOS Retina safe** (DPI-aware pixel sampling)  
-  Written in **pure C**, no frameworks  

---

##  Controls

- **Left Mouse Button** → Pick color from palette  
- **Right Mouse Button (hold)** → Draw on canvas  

---

##  Tech Stack

- **Language:** C  
- **Graphics Library:** [raylib](https://www.raylib.com/)  
- **Platform tested on:** macOS (Retina / HiDPI)

---

##  Build & Run

Make sure `raylib` is installed.

### macOS / Linux

```bash
cc paint.c $(pkg-config --libs --cflags raylib) -o paint
./paint
