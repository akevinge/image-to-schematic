# Image to Minecraft... Image

A (currently partial-functional) C++ Learning Project

### Before
![Before](/assets/images/before.png)

### After (click for zoom)
![After](/assets/images/after.png)

## How to run

**You must have Minecraft installed**

Load textures and extract colors

```sh
cd colorizer && ./run.sh
```

Create the image made of MC textures

```sh
cd mapper && make clean && make build
bin/main /path/to/textures-version /path/to/colors-version.json /path/to/image.png /out-dir # ex: bin/main ../textures-1.18.2 ../colors-1.18.2.json ./test-img.png .
```
