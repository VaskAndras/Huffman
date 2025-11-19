# Huffman Coding

A data compression implementation using Huffman encoding algorithm.

## Overview

This program implements Huffman coding, a lossless data compression technique that uses variable-length codes for different characters based on their frequency of occurrence.
The base for this program is a dynamicly generated binary tree for each text, to achieve the best result. 

## Features

The program is able to read a file and encode it to another, via Huffman encoding mechanism, and able to decode it too. 
The key mecanism is a 


## Usage

```bash
./huffman [input_file] [output_file]
```

## How It Works

1. **Frequency Analysis**: Counts character occurrences
2. **Tree Building**: Constructs a binary tree with most frequent characters closer to root
3. **Code Generation**: Assigns variable-length bit sequences to characters
4. **Encoding**: Compresses data using generated codes

## Requirements

- C/C++ compiler
- Standard library support

## Algorithm Complexity

- Time: O(n log n)
- Space: O(n)

## License

[Add appropriate license]
