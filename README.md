# Made of Waves — KeebDeck Basic (Enhanced Edition)

> **Photo goes here**
>
> ![Made of Waves KeebDeck Basic — photo](./docs/photo-placeholder.jpg)

This is the **Made of Waves** edition of the **Solder Party KeebDeck Basic** — a respectful remix that keeps the soul of the original while adding a handful of quality-of-life upgrades and shipping **ready to use out of the box**.

## Massive credit where it’s due 🙌

The original **KeebDeck Basic** hardware design and the upstream QMK keyboard definition are by **Solder Party**.

This project is a **derivative hardware + firmware adaptation** built on top of Solder Party’s work and the broader QMK ecosystem.

- Original creator: **Solder Party**
- Solder Party GitHub: https://github.com/solderparty
- QMK Firmware: https://github.com/qmk/qmk_firmware
- VIA: https://www.caniusevia.com

If you want the upstream baseline and official docs, start with Solder Party’s original project.

---

## What I changed (hardware)

This edition takes the original KeebDeck Basic design and adds:

- **Backlighting**  
  Integrated backlight support (QMK-controlled), including an idle timeout behavior.

- **Boot button**  
  A dedicated hardware boot/reset button for easier flashing and recovery.

- **Qwiic connector**  
  Added a Qwiic/I²C connector for simple plug-and-play expansion (sensors, displays, etc.).

- **Black PCB**  
  Because it looks better. That’s the whole reason. 🖤

---

## What I changed (firmware + usability)

- **VIA compatibility**  
  Remap keys and adjust layers without recompiling firmware. (VIA-enabled keymap included.)

- **Pre-flashed with QMK**  
  Each keyboard is shipped with QMK already installed so it works **immediately** when plugged in — no setup required.

- **Spacebar domes behave as one key**  
  The physical spacebar uses multiple switch points for feel, but behaves like a single Space key during typing.

---

## What’s in this repo?

- `keebdeck_basic/`  
  QMK keyboard definition + keymaps (Made of Waves variant)

- `keebdeck_basic/keymaps/default/`  
  Standard keymap build (non-VIA)

- `keebdeck_basic/keymaps/via/`  
  VIA-enabled build target (same layout as default; VIA toggled via keymap-level build flags)

- `via/keebdeck_basic_via.json`  
  VIA layout definition JSON (load this into VIA’s Design tab)

---

## Out-of-the-box usage

1. Plug the keyboard in.
2. Start typing.
3. (Optional) Open VIA to customize your layout.

No compiling, no flashing, no rituals.

---

## VIA setup

This keyboard uses a custom VIA definition file:

1. Open VIA
2. Go to **Settings** → enable **Show Design tab**
3. Go to **Design** → **Load** and select:
   - `via/keebdeck_basic_via.json`

After loading, your layout should appear and you can remap keys and layers.

---

## Building the firmware (for tinkerers)

If you want to build from source, first set up QMK:

- QMK build tools: https://docs.qmk.fm/#/getting_started_build_tools

Then build:

### Default (non-VIA)
```sh
qmk compile -kb solderparty/keebdeck_basic -km default
```

### VIA-enabled
```sh
qmk compile -kb solderparty/keebdeck_basic -km via
```

Classic `make` syntax also works:
```sh
make solderparty/keebdeck_basic:default
make solderparty/keebdeck_basic:via
```

---

## Flashing

### Using QMK CLI
```sh
qmk flash -kb solderparty/keebdeck_basic -km default
qmk flash -kb solderparty/keebdeck_basic -km via
```

### Using make
```sh
make solderparty/keebdeck_basic:default:flash
make solderparty/keebdeck_basic:via:flash
```

---

## Bootloader / recovery

Use any of the following:

- **Boot button** (recommended): press the boot/reset button to enter bootloader
- **Bootmagic reset**: hold the top-left key (often Esc) while plugging in
- **QMK keycode reset**: if your layout includes `QK_BOOT`, use that

---

## Qwiic / I²C expansion notes

The Qwiic connector provides easy access to the board’s I²C bus for add-ons like:
- small displays
- sensor modules
- I/O expanders

> **Placeholder:** Add details here if you want them documented (voltage, pinout, tested modules, etc.).

---

## License

This repository includes QMK-derived firmware sources. Licensing follows the expectations of the QMK ecosystem. See `LICENSE` for details.

---

## Changelog / Versions (optional)

- v1.0 — Initial Made of Waves enhanced edition release  
  Backlight + boot button + Qwiic + black PCB + VIA + pre-flashed QMK
