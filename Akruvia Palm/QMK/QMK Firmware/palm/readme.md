# Akruvia Palm

![Palm](https://i.imgur.com/yOTFp9Th.png)

*This is a wired handheld 12x4 keyboard for your DIY Cyderdecks, UMPCs, handheld PC builds. (104mm x 45.15mm)*

* Keyboard Maintainer: [akruvia](https://github.com/akruvia)
* Hardware Supported: Akruvia Palm - An RP2040-based wired handheld keyboard
* [Product Guide](https://ikejr.com/2024/04/20/akruvia-palm-documentation-product-guide-handheld-cyberdeck-small-usb-keyboard/)

Make example for this keyboard (after setting up your build environment):

    make palm:default

Flashing example for this keyboard:

    make palm:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the Escape key and plug in the keyboard
* **Physical boot and reset button**: Hold the boot button then press the reset button