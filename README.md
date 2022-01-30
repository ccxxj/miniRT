# miniRT
Project goal:
The goal of this program is to generate images using the Raytracing protocol. 
Those computer generated images will each represent a scene, as seen from a specific angle 
and position, defined by simple geometric objects, and each with its own lighting system.

MiniRT uses MinilibX, a small graphics library that allows for simple window management and putting pixels to the screen. The program can render the following shapes and scene elements using their respective identifiers:
  R - Window resolution
  A - Ambient lighting
  l - Point light
  c - Camera
  pl - Plane
  sp - Sphere
  cy - Cylinder (non-capped)
  sq - Square
  tr - Triangle

Compilation:
running make will compile the program. make clean or make fclean can be used to wipe binaries



