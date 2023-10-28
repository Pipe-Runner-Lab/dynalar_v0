# dynalar_v0

## Assimp
For generating the build for 32bit application.

```
cmake ./ -A Win32
```

Then open the `Assimp.sln` and run rebuild. `dll` and `lib` files will be generated in their respective folders. 
Make sure to select the correct configuration between `Release` and `Debug`.

## Using DLL
For now, just copy the `dll` file in the same directory as the generated binary. 
Automation can be done via: https://learn.microsoft.com/en-us/cpp/build/walkthrough-creating-and-using-a-dynamic-link-library-cpp?view=msvc-170