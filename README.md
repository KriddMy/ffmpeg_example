# ffmpeg_info
This is just a simple project on c++ to show basic ffmpeg skills.

## Building
This is a [cmake](https://cmake.org/) project so cmake must be installed to compile this project.

Before building this project you should install ffmpeg library on your PC. If you are useing Ubuntu you can just simply type 
```bash
sudo apt-get install ffmpeg
```

If you have everything installed, run following cmake command in your your project directory 
```bash
cmake "-B./build"
```
This will create all the config files in build dictionery.

Now, simply run `--build` command to create the final program executable. The final executable `ffmpeg_info` will get created in your parent directory.
```bash
cmake --build ./build 
```

## Running
Execute the executable `ffmpeg_info` with video path specified as an argument.
```bash
./ffmpeg_info your_video.mp4
```
