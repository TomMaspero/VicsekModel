# VicsekModel

> **Archived.** This is my original C/GLUT version. It has been rewritten in C# as
> [VicsekSharp](https://github.com/TomMaspero/VicsekSharp), which fixes the bugs listed below and adds live parameter controls.

Simulation of the [Vicsek model](https://en.wikipedia.org/wiki/Vicsek_model) of collective motion: 1000 particles in a periodic 1000x1000 box align with their neighbours within a radius, with added angular noise. Rendered with freeglut. Code::Blocks project (`Vicsek.cbp`).

## Known issues

- The neighbour search only looks in the particle's own cell, so particles near a cell edge miss neighbours in the adjacent cells.
- Headings are averaged as raw angles instead of unit vectors (359° and 1° average to 180°), which biases the motion.
- A particle does not include itself in the average.
- Distances ignore the periodic boundary, so particles on opposite edges never interact.
- `calcH` wraps to cell 10 instead of 9, and the cell index can go out of range at the box edge.
- Parameters are hard-coded in `main.c`.
- `bin/Debug/run.bat` belongs to a different project.
