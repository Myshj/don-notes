# Notes
Reference implementation of the simplest notebook.

No-exception program flow handling.

Uses `std::variant` and return codes to achieve runtime safety.

Storage is append-only.

No dynamic memory is used directly.

Single `save.data` file is used as a storage.

# Possible improvements
1. QFile reading throws if `save.data` is not hexadecimal
2. Slightly awkward error-handling in `MainWindow`
3. Unhappy paths in general
4. Add internationalization
5. Limit storage
6. Add tests
