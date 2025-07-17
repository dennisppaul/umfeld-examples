# Known Issues


- `point()` doesn't draw any point.
- `fill()`, when value exceeds `1.f`, `lights()` doesn't work, ie. shadow disappear and whites out. Seems to need clipping internally.
- `fill()` and `fill_color()` is confusing regarding input types, ie. uint32 or float or 8bit int(0-255) -> seems to need more thoughts and decision for a better consistent API?