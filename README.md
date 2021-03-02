# L-System Interpreter

C++ implementation of L-System. This library can output the L-System as a word,
or as a USD formated geometry reprecenting the turtle interpretation of the
resulting word

## How to build

### Dependencies

- [Imath](https://github.com/AcademySoftwareFoundation/Imath) (needed)
- [USD](https://github.com/PixarAnimationStudios/USD) (optional)

### Cmake

Minimum to build the library :

```powershell
cmake path/to/repository -G "generator_name" -D Imath_DIR="path/to/Imath/install"
```

Additional variables :

```powershell
-D LSYSTEM_OUTPUT_DIR="where/you/want/to/output/binaries"
-D pxr_DIR="path/to/usd/install"
```
