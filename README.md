# Huffman Coding
## About
Lightweight implementation of **Huffman Coding Algorithm** in **C**.

## Installation
Run the following commands in the terminal:
```
git clone https://github.com/TheAcebyte/huffman-coding.git
cd huffman-coding
make
```

## Usage
```
./main <encode|decode> <filename> [-d]
```
- `-d`: optional flag to delete the input file after compression/decompression.

> To encode a file, say `test/foo.txt`, you would run:
> ```
> ./main encode test/foo.txt -d
> ```
>
> The above command deletes `test/foo.txt` after producing `test/foo.bin`.
>
> To decode `test/foo.bin`, you would run:
> ```
> ./main encode test/foo.bin -d
> ```
>
> The above command deletes `test/foo.bin` after producing `test/foo.txt`.

## License
You may redistribute or modify this project under the [**MIT** license](LICENSE).