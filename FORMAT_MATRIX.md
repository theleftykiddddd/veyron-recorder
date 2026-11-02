# Macro format interoperability

Veyron uses a normalized internal event model: frame, button, player, press/release.
A format adapter must map timing units, button IDs, player IDs, and event ordering
without silently discarding metadata.

| Format / tool | Import | Export | Status in this starter |
|---|---:|---:|---|
| VPR (Veyron native) | Yes | Yes | Implemented, line-oriented v1 |
| GDR / GDR2 (xdBot ecosystem) | Planned | Planned | Not implemented; requires spec + fixture tests |
| SLC (Silicate) | Planned | Planned | Not implemented; version-specific adapter required |
| CML | Planned | Planned | Not implemented; format/version must be confirmed |
| tcBot | Planned | Planned | Not implemented; version-specific adapter required |
| Eclipse | Planned | Planned | No single universal interchange format assumed |

**Important:** “Compatible with a tool” is not the same as supporting every format
that tool can read. Veyron will advertise each exact extension and version only after
round-trip tests against real sample files. Unknown fields should be preserved where
possible; unsupported features must produce a warning, never silent corruption.

## Adapter acceptance checklist

- Public specification or permissioned sample files available.
- Header/version validation and file-size/event-count limits.
- Correct frame/tick-rate conversion and stable same-frame event ordering.
- Player 1 / Player 2 and button mapping tests.
- Import -> normalized model -> export -> re-import round-trip tests.
- Explicit warnings for unsupported metadata, offsets, FPS assumptions, or triggers.
