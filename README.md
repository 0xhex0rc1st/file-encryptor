# File Encryptor/Decryptor 🔒

A secure C++ application that encrypts and decrypts files using XOR operation with customizable keys. Works on Windows systems.

## Features ✨

- **Strong Encryption**: XOR operation with key stretching
- **Multiple Key Options**:
  - Generate cryptographically-strong random keys (16 chars)
  - Use your own custom key (min 8 chars)
- **In-Place Processing**: Securely overwrites original file
- **Binary Safe**: Works with any file type (text, images, executables, etc.)
- **Simple Interface**: Easy-to-follow console interface

## Installation 💻

### Requirements
- Windows OS
- For compilation: C++17 compatible compiler

### Option 1: Download Pre-built Binary
1. Download the latest `.exe` from [Releases](#)
2. Run directly from command prompt

### Option 2: Build from Source
```bash
git clone https://github.com/yourusername/file-encryptor.git
cd file-encryptor
g++ encrypt_decrypt.cpp -o filecryptor -static -O2