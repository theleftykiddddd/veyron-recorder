# Window analysis design

## What is a window?

A click's hold duration is not its frame window. A true window is the set or count
of timing offsets around a reference input that still produce a valid outcome for
the same intended route. A macro file by itself usually does not contain that
information. Veyron therefore separates:

1. **Observed input spacing**: facts directly present in the macro.
2. **Measured window**: a value supplied by a validated test/simulation backend.
3. **Unknown**: no valid measurement is available.

The starter only implements grouping/statistics and a pitch mapping for already
measured values. It must not label an observed hold length as a real window.

## Default visual bands

The bands mirror the user's reference chart: 0-1, 2, 3, 4, 5-6, 7-8, 9-12,
13-16, 17-24 frames. Counts from the screenshot are stored separately as an
illustrative reference, not as live level data.

## Audio

Map lower frame windows to lower frequencies. Proposed defaults: sine wave,
95-880 Hz, 90 ms, 65% master volume. Add a short cooldown and coalesce same-frame
inputs to prevent a wall of sound. Include mute, per-band enable, waveform, duration,
volume, and custom frequency controls. Audio playback belongs in a Geode audio
adapter; the core only computes target frequencies.

## HUD

- Current measured window, large and color-coded.
- Total measured clicks and unknown count.
- Counts per band, with optional percentages.
- Current macro frame and playback/recording state.
- Compact mode, movable position, scale, opacity, hide/show hotkey.
- Pause analysis, reset session, export CSV/JSON report.

## Measurement backend

The backend is intentionally an interface/milestone, not a fabricated algorithm.
A robust implementation needs controlled replay variants or a validated physics
simulation, a definition of “same outcome”, checkpoint/route segmentation, and
repeatability checks. It must not infer a true window from a single successful run.
