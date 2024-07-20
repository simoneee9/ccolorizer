# CColorizer - VERY WIP

Image colorization using the Colorization using Optimization method *[DOI:10.1145/1015706.1015780](https://doi.org/10.1145/1015706.1015780)*

this project is mainly a cli tool rn, but i am planning to publish the underlying colorization library too.
i have implemented this algorithm in python already inside of a GIMP plugin that i made. and although the speed of the colorization has dramatically improved after rewriting a critical section of the algorithm in C, it can still reach more than 120 seconds for large images. im hoping a complete rewrite in c++ could be way more performant. this is NOT a GIMP plugin ...yet

## planned features

- [ ] handling and evaluating cli arguments
- [ ] colorizing a grayscale image based on colored marks/tags/hints drawn onto it
- [ ] option to select a different affinity (weights calculation) function (a set predefined functions, not custom (unless you modify the source code))
- [ ] verbose option
- [ ] multithreading
- [ ] option to draw the marks when running the command using a gui (qt?) instead of specifying a path to the tagged image
- [ ] option to immediately show the colored image after the colorization is done in an image viewer (feh, loupe, ...) 

## Dependencies

- SAIL - [github](https://github.com/HappySeaFox/sail), [aur](https://aur.archlinux.org/packages/sail-img)
