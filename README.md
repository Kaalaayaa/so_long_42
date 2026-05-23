# 🎮 so_long

A small 2D game built in C using MiniLibX — a 42 Berlin project.

---

## What it is

so_long is a top-down 2D game where the player navigates a map, collects all items, and reaches the exit. The map is loaded from a `.ber` file and validated at startup.

Built entirely in C with no game engine — window management, rendering and input handling all done manually via MiniLibX.

---

## Features

- 2D tile-based rendering with custom sprites
- Map parsing and validation from `.ber` files
- Player movement (W/A/S/D or arrow keys)
- Collectible items and exit logic
- Move counter displayed in the terminal
- Error handling for invalid maps

---

## Controls

| Key | Action |
|-----|--------|
| `W` `A` `S` `D` | Move player |
| `Esc` | Exit game |

---

## Installation & Usage

```bash
git clone https://github.com/Kaalaayaa/so_long_42.git
cd so_long_42
make
./so_long maps/map.ber
```

---

## Technical Stack

- **Language:** C
- **Graphics:** MiniLibX
- **Key concepts:** 2D rendering, sprite handling, map parsing, file I/O, memory management
