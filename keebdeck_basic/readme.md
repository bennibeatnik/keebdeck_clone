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

**Important:** this repo is **not** the same as the stock `solderparty/keebdeck_basic`
keyboard that ships inside mainline QMK. That upstream version is Solder Party's
original, unbranded definition. This repo is the Made of Waves fork — different
branding, settings, and (in the `via` keymap) full VIA remapping support tied to
the custom layout JSON below. Building the stock `solderparty/keebdeck_basic`
target will **not** give you this configuration, even though it's the same
physical hardware.

---

## One-time setup: adding this keyboard to your QMK checkout

QMK can't build straight from this repo — it needs to live inside a full
`qmk_firmware` checkout, which has the build tooling this repo doesn't include.
Because this is a personal/derivative fork, it isn't part of the public
qmk_firmware project, so you need to add it yourself, once:

1. Set up QMK if you haven't already (see links below), which gives you a local
   clone of `qmk_firmware`.
2. Copy this repo's `keebdeck_basic/` folder into your `qmk_firmware` checkout at
   exactly this path (creating the folders if needed):

   `qmk_firmware/keyboards/madeofwaves/keebdeck_basic/`

3. That's it — QMK will now recognize `madeofwaves/keebdeck_basic` as a
   buildable keyboard.

---

## Which keymap do I want?

- **`via`** — if you want to use the [VIA app](https://www.caniusevia.com/) to remap keys without reflashing. This is what most people want, and what the custom layout JSON below is for.
- **`default`** — a fixed keymap with no runtime remapping. Only pick this if you specifically don't want VIA.

Whichever you pick, replace `via` with `default` (or vice versa) in every command below.

---

## Flashing (the short version)

You don't need to "build" and "flash" as two separate steps — `qmk flash` does
both automatically (it compiles, then flashes). This is really a 3-step process:

**1. Put the keyboard into bootloader mode.** Do one of the following:
   - **Bootmagic (easiest):** unplug the keyboard, hold down the top-left key
     (Esc), then plug the USB cable in while still holding it. Release once
     it's plugged in.
   - **Reset button:** if your board has a physical reset button, press it.

   You'll know it worked if your normal keyboard stops responding (it's no
   longer running as a keyboard — it's now in a special firmware-update mode)
   and/or your OS shows a new device appearing/disappearing briefly.

**2. Run the flash command**, from a terminal with QMK set up (see the
   one-time setup section above if you haven't done this yet):

qmk flash -kb madeofwaves/keebdeck_basic -km via

**3. Wait for it to finish.** You'll see a lot of scrolling text as it
   compiles, then a final section where it writes the firmware to the board.
   Look for a success message near the very end (no red "ERROR" text). The
   keyboard will reset itself and start working normally within a couple of
   seconds — no need to unplug/replug anything yourself.

If you'd rather compile without flashing (e.g. just to check it builds), use
`qmk compile` instead of `qmk flash` with the same arguments. If you prefer
the classic make syntax: `make madeofwaves/keebdeck_basic:via:flash`.

### If the flash command can't find your keyboard (Windows)

This is the single most common snag for first-time flashers on Windows. In
bootloader mode, the keyboard shows up as a different kind of USB device than
it does normally, and Windows sometimes doesn't have the right driver for it
installed automatically. If `qmk flash` hangs or says it can't find/open the
device:

1. Put the keyboard back into bootloader mode (step 1 above).
2. Download and run [Zadig](https://zadig.akeo.ie/) (a small, well-known tool
   for installing generic USB drivers).
3. In Zadig, find the device (it will show up only while in bootloader mode —
   look for something mentioning "DFU" or "STM"), and install the **WinUSB**
   driver for it.
4. Try `qmk flash` again.

You only need to do this once per computer — after the driver is installed,
future flashes will just work.

See also:
- QMK build tools setup: https://docs.qmk.fm/#/getting_started_build_tools
- New to QMK? https://docs.qmk.fm/#/newbs

---

## VIA setup

This keyboard uses a custom VIA layout definition, since the physical layout
differs from Solder Party's stock version. Do this once, after you've flashed
the `via` keymap:

1. Open the [VIA app](https://www.caniusevia.com/) (or usevia.app in a browser).
2. Go to **Settings** and enable **Show Design tab**.
3. Go to **Design → Load**, and select `via/keebdeck_basic_via.json` from this repo.
4. Plug in your keyboard (already flashed with the `via` keymap) — VIA should
   detect it automatically and show the Made of Waves layout, ready to remap.

If VIA doesn't detect the keyboard: confirm you flashed the `via` keymap (not
`default` — only `via` includes the remapping support VIA needs), and that
the keyboard is plugged in and working normally (not still in bootloader mode).

## License

This project includes QMK-derived firmware sources and follows the licensing expectations of that ecosystem.
See the LICENSE file for details.

