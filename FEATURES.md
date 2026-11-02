# Veyron feature specification

## Recorder
- Frame-indexed press/release events; P1/P2; configurable capture filters.
- Start/stop hotkeys, pause, markers, level metadata, tick-rate metadata.
- Autosave/recovery, session naming, duplicate-event detection, event timeline.

## Playback (integration milestone)
- Play, pause, stop, seek, loop, speed control for inspection, frame stepping.
- Scheduler must use game-frame timing and must not claim deterministic accuracy
  until validated on the target GD/Geode build.
- Playback is for testing/research. Never submit macro playback as a human record.

## Analysis
- Window bands and live counter; per-click details; P1/P2 filters.
- Distribution histogram, average/median/min/max, percentiles, unknown count.
- Segment analysis by progress/checkpoint and comparison of two runs.
- Export session report as CSV/JSON and copy summary.

## Sound
- Distinct tone for each measured window; smaller window = lower pitch.
- Sine/square/triangle options, duration, volume, cooldown, mute, custom profile.
- Optional stereo distinction for P1/P2; accessibility toggle and visual-only mode.

## Quality / safety
- Never silently reinterpret unsupported macro formats.
- Validate file size, event count, tick rate, event order and metadata.
- Clear labels for measured vs inferred vs unknown values.
- Macro replay is not a legitimate human completion or proof of skill.
