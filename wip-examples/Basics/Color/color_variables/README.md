# TODO

### note

- colors are accepted as either `uint32_t` or `float` in umfeld.
- this can cause confusion.
- also, with the Processing preconception, `fill()` and `fill_color()` may cause confusion.
- therefore, think of a better naming convention?
- also, when maintaining the `color()` and `fill()` that are overloaded with 3 or 4 `float` arguments, consider adding overloadings for `glm::vec3` and `glm::vec4`.