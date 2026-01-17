# Made of Waves — KeebDeck Basic (QMK + VIA)

This repository contains the **Made of Waves** configuration for the **KeebDeck Basic**, including:
- Updated **QMK firmware** sources
- A matching **VIA layout definition** (JSON) for easy remapping

## Credit (Important 🧡)

The **KeebDeck Basic** hardware and the original QMK keyboard definition are by **Solder Party**.

This repo is a **derivative configuration** (custom layout + VIA definition + firmware tweaks) built on top of Solder Party’s work and the broader QMK ecosystem.

- Original creator / maintainer: **Solder Party**  
- Solder Party GitHub: https://github.com/solderparty  
- QMK Firmware: https://github.com/qmk/qmk_firmware  

If you're looking for the original upstream keyboard project and documentation, please start with Solder Party.

---

## What’s in this repo?

- `keebdeck_basic/`  
  QMK keyboard definition + keymaps used by Made of Waves.
- `keebdeck_basic/keymaps/default/`  
  Standard “non-VIA” build target.
- `keebdeck_basic/keymaps/via/`  
  VIA-enabled build target (keymap is identical to `default`, the difference is build flags).
- `via/keebdeck_basic_via.json`  
  VIA definition JSON (layout sizing + matrix positions) for loading into the VIA app.

---

## Building the firmware

After setting up your QMK build environment:

- Build the default (non-VIA) keymap:

qmk compile -kb solderparty/keebdeck_basic -km default

- Build the VIA-enabled keymap:

qmk compile -kb solderparty/keebdeck_basic -km via

If you prefer the classic make syntax:

make solderparty/keebdeck_basic:default
make solderparty/keebdeck_basic:via

See:
- QMK build tools setup: https://docs.qmk.fm/#/getting_started_build_tools
- QMK make guide: https://docs.qmk.fm/#/getting_started_make_guide
- New to QMK? https://https://doc.qmk.fm/#/newbs

---

## Flashing
Example flashing commands:

qmk flash -kb solderparty/keebdeck_basic -km default
qmk flash -kb solderparty/keebdeck_basic -km via

Or using make:

make solderparty/keebdeck_basic:default:flash
make solderparty/keebdeck_basic:via:flash

## Via Setup
This keyboard uses a custom VIA definition file.

Open VIA

Go to Settings and enable Show Design tab

Go to Design → Load and select:

via/keebdeck_basic_via.json

After loading, you should see the Made of Waves layout and be able to remap keys.

Bootloader

Enter the bootloader in any of these ways:

Bootmagic reset: Hold the key at (0,0) (usually Esc / top-left) while plugging in USB

Physical reset: Press the reset button on the PCB (or short the reset pads if your board uses pads)

Keycode reset: Use a key mapped to QK_BOOT (if present)

## License

This project includes QMK-derived firmware sources and follows the licensing expectations of that ecosystem.
See the LICENSE file for details.

If you want, I can also rewrite it with a slightly more “product page” feel (photos, features, matrix size, spacebar dome note, build badges) while keeping the credit section front-and-center.

