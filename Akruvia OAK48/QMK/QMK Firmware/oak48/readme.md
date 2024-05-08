# Akruvia OAK48

![OAK48](https://i.imgur.com/SYku3eEh.png)

*12x4 Ortholinear keyboard | Gateron Low Profile*

* Keyboard Maintainer: [akruvia](https://github.com/akruvia)
* Hardware Supported: Akruvia OAK48 - An RP2040-based 12x4 ortholinear keyboard
* [Product Guide](https://ikejr.com/2024/05/08/akruvia-oak48-documentation-product-guide-12x4-ortholinear-keyboard-gateron-low-profile-vial/)

Make example for this keyboard (after setting up your build environment):

    make akruvia/oak48:default

Flashing example for this keyboard:

    make akruvia/oak48:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical boot button**: Hold the boot button then plug in the keyboard
