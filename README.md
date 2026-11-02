# Veyron Proyect

**A Geometry Dash / Geode macro recorder and frame-window analysis project.**

This ZIP is a complete **starter repository**, not a finished in-game mod. It contains
working platform-neutral core code (macro model, recorder state machine, replay event
scheduler, VPR import/export, window-band statistics and tone-frequency mapping), a
minimal Geode entry point, documentation, configuration defaults, tests and sample data.

The Geode integration still needs input hooks, actual in-game playback injection, HUD
rendering, Geode audio playback, and third-party format adapters. Those cannot be
honestly represented as finished without testing against the exact Geometry Dash and
Geode SDK build. In particular, a replay scheduler is not yet an input injector.

## Target / build

Target in `mod.json`: Windows Geometry Dash 2.2091 and Geode v6.0.0-alpha.1. This Geode
SDK is an alpha target; match your installed SDK version before building. You need a
C++23 toolchain, CMake 3.21+, Geode SDK and Geode CLI.

### Test the core without Geode

```bash
cmake -S . -B build -DVEYRON_STANDALONE_TESTS=ON
cmake --build build --config Release
ctest --test-dir build --output-on-failure
```

### Build the Geode mod

Set `GEODE_SDK` to your Geode SDK source directory, then from this folder run:

```bash
geode build
```

If the installed Geode CLI expects a different build workflow, follow that SDK's
current documentation. This repository deliberately does not bundle the SDK.

## What's included

- `include/veyron/Macro.hpp`: normalized frame-based input event model.
- `src/core/Recorder.cpp`: frame-indexed recorder state machine.
- `src/core/Replay.cpp`: deterministic event scheduler (does not inject game inputs).
- `src/core/FormatIO.cpp`: native VPR v1 import/export; explicit stubs for external codecs.
- `src/core/WindowAnalyzer.cpp`: band classification, statistics and pitch mapping.
- `src/geode/main.cpp`: minimal Geode mod entry point.
- `config/defaults.json`: proposed HUD/audio/recording defaults.
- `docs/`: full feature plan, format matrix and window-measurement design.
- `assets/reference-window-chart.png`: supplied visual reference.
- `examples/`: sample analysis distribution and screenshot-count transcription.

## Important: real frame windows

A click's hold duration is not the click's frame window. A real window is the range of
input timing offsets that still produce the same intended outcome. The macro itself
usually cannot reveal this. Veyron marks unmeasured windows as unknown until a validated
physics/replay measurement backend exists. The counts in `examples/reference_distribution.json`
are transcribed from the supplied reference image and are **not live measurements**.

## Compatibility status

Native `.vpr` is implemented. GDR/GDR2, SLC (Silicate), CML, tcBot and Eclipse adapters
are planned but not implemented in this starter. Each needs version-specific mapping
and round-trip fixtures. Veyron will not claim compatibility or write a misleading
file under a third-party extension.

## Roadmap

1. Build and load the minimal mod on the exact GD/Geode installation.
2. Add Geode input hooks and verify authoritative frame/tick capture.
3. Add safe autosave, session controls and VPR file picker.
4. Implement third-party codecs with fixtures and round-trip tests.
5. Add actual replay input injection and validate timing across refresh/tick rates.
6. Implement controlled timing-variation tests / validated window measurement.
7. Add movable HUD, live counter, histogram and report export.
8. Add Geode audio integration, per-band tones and sound customization.

Macro playback is for testing/research and must not be presented as a legitimate human
completion or submitted as a personal record.

## Build automatically on GitHub

This repository includes `.github/workflows/build.yml`. Upload the contents of this
folder to a GitHub repository on the `main` branch. Each push to `main` (or a manual
run from the Actions tab) asks the official `geode-sdk/build-geode-mod` action to build
the Windows `Win64` package using Geode SDK `v6.0.0-alpha.1`, then uploads the resulting
`.geode` as an Actions artifact named `Veyron-Proyect-Windows`.

To download it: open the repository's **Actions** tab, select the successful
**Build Veyron Proyect** run, and download the artifact from the run summary.
This workflow builds the current starter code; it does not implement the missing
in-game recorder hooks, playback injection, HUD, external macro codecs or live audio.
