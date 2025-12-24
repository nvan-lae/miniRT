# miniRT

miniRT is a 42 school project that implements a basic raytracer in C. It renders 3D scenes by simulating the physical behavior of light rays interacting with various geometric objects.
## 🚀 Features

* **Geometric Objects**: Supports rendering of Spheres, Planes, Cylinders, and Paraboloids.

* **Lighting System**: Includes ambient lighting and direct light sources with brightness ratios.

* **Materials**:

    * **Diffuse**: Standard matte surfaces.

    * **Mirror**: Reflective surfaces.

    * **Glass**: Transparent surfaces with refraction (Index of Refraction support).

* Advanced Effects:

    * **Shadows**: Objects cast shadows based on light source positions.

    * **UV Mapping**: Supports procedural checkerboard textures.

* **Multi-Camera**: Support for multiple cameras within a single scene file.

## 🧠 Raytracing Logic

The engine follows a recursive raytracing algorithm implemented in `src/math/trace_ray.c`:

1. **Ray Generation**: For every pixel on the screen (1080x720), a primary ray is cast from the camera's position through the viewport into the 3D scene.

2. **Intersection Testing**: The engine checks for the closest intersection point between the ray and all objects in the scene (spheres, planes, cylinders, or paraboloids).

3. **Shading & Lighting**:

    * **Direct Lighting**: If an object is hit, the engine calculates the color based on light sources and the surface normal.

    * **Shadow Rays**: A ray is cast from the hit point toward the light source; if an object blocks this ray, the point is in shadow.

4. **Recursion (Reflections & Refractions)**: For mirror or glass materials, new rays are spawned from the hit point. This process is recursive, with a maximum depth of 5 to ensure performance and prevent infinite loops.

## 🛠️ Requirements & Installation

This project is designed for Linux and utilizes the MiniLibX graphical library.
#### Prerequisites

Ensure you have the following X11 development libraries installed:

* `libxext-dev`

* `libx11-dev`

#### Compilation

The project uses a `Makefile` to handle compilation for both the main executable and its dependencies (`libft` and `minilibx`).

```
make
```
## 💻 Usage

To run the raytracer, provide a scene description file with the `.rt` extension:

```
./miniRT scenes/test.rt
```
#### Controls

* **ESC**: Close the application.

* **Window Close Button**: Exit the program safely.
* **C-key**: Change camera if multiple available
* **↑/↓**: Change FOV (Zoom in/out)

## 📄 Scene File Format

Scene files (`.rt`) define the environment and objects. Each line starts with a unique identifier:

* `A`: Ambient lighting

* `C`: Camera

* `L`: Light source

* `sp`: Sphere

* `pl`: Plane

* `cy`: Cylinder

* `pa`: Paraboloid

Example:
```
A 0.2 255,255,255
C 0,0,-10 0,0,1 70
C -10,0,0 1,0,0 70
L 0,9,0 1.0 255,255,255

# Floor
pl 0,-10,0 0,1,0 150,200,150 def checker 255,255,255

# Ceiling
pl 0,10,0 0,-1,0 255,60,60 def checker 255,255,255

# Walls
pl -15,0,0 1,0,0 220,220,220 mirror   # Left
pl 15,0,0 -1,0,0 220,220,220 mirror   # Right
pl 0,0,15 0,0,-1 220,220,220 mirror   # Back
pl 0,0,-15 0,0,1 220,220,220 mirror   # Front

# Corner cylinders
cy -15,-10,15 0,1,0 2 40 200,0,200 def
cy 15,-10,15 0,1,0 2 40 0,200,200 def
cy -15,-10,-15 0,1,0 2 40 200,200,0 def
cy 15,-10,-15 0,1,0 2 40 0,200,255 def

# Spheres at bottom of cylinders
sp -15,-10,15 4 50,200,200 def
sp 15,-10,15 4 200,50,200 def
sp -15,-10,-15 4 200,200,50 def
sp 15,-10,-15 4 100,100,100 def

# Spheres at top of cylinders
sp -15,10,15 4 50,200,200 def
sp 15,10,15 4 200,50,200 def
sp -15,10,-15 4 200,200,50 def
sp 15,10,-15 4 100,100,100 def

# Center red sphere
sp 0,0,0 6 255,0,255 mirror
```
<img width="1216" height="856" alt="Screenshot from 2025-12-23 18-02-56" src="https://github.com/user-attachments/assets/7d672426-b728-49e8-b994-60689755c68d" />

#### Authors

* **jvan-der**

* **nvan-lae**
