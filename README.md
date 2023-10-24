# dynalar_v0

## Assimp
For generating the build for 32bit application.

```
cmake ./ -A Win32
```

Then open the `Assimp.sln` and run rebuild. `dll` and `lib` files will be generated in their respective folders. 
Make sure to select the correct configuration between `Release` and `Debug`.