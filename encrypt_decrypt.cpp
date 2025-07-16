#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <vector>
#include <random>
#include <limits>

bool processFile(const std::string& filepath, bool encrypt) {
    // 1. Read the file content
    std::ifstream readFile(filepath, std::ios::binary);
    if (!readFile) {
        std::cerr << "Error opening file: " << filepath << "\n";
        return false;
    }

    std::vector<char> content((std::istreambuf_iterator<char>(readFile)),
        std::istreambuf_iterator<char>());
    readFile.close();

    // 2. Get the encryption/decryption key
    std::string key;
    if (encrypt) {
        while (true) {
            std::cout << "\nKey options:\n" << "1. Generate strong random key\n" << "2. Enter my own key\n" << "Choose (1 or 2): ";

            int keyOption;
            if (!(std::cin >> keyOption)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cerr << "Invalid input! Please enter 1 or 2.\n";
                continue;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (keyOption == 1) {
                // Generate random key
                const std::string charsets = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "abcdefghijklmnopqrstuvwxyz"
                    "0123456789!@#$%^&*()-_=+";
                const int keyLength = 16;

                std::random_device rd;
                std::mt19937 generator(rd());
                std::uniform_int_distribution<> dist(0, charsets.size() - 1);

                for (int i = 0; i < keyLength; ++i) {
                    key += charsets[dist(generator)];
                }

                std::cout << "\nGENERATED KEY: " << key << "\n"
                    << "WARNING: You MUST save this key to decrypt the file later!\n"
                    << "Store it in a password manager or secure location.\n\n";
                break;
            }
            else if (keyOption == 2) {
                // Get user key
                std::cout << "Enter encryption key (min 8 chars): ";
                std::getline(std::cin, key);

                if (key.empty()) {
                    std::cerr << "Error: Key cannot be empty!\n";
                    continue;
                }
                if (key.length() < 8) {
                    std::cerr << "Error: Key must be at least 8 characters!\n";
                    continue;
                }
                break;
            }
            else {
                std::cerr << "Invalid choice! Please enter 1 or 2.\n";
                continue;
            }
        }
    }
    else {
        // For decryption
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Enter decryption key: ";
        std::getline(std::cin, key);

        if (key.empty()) {
            std::cerr << "Error: Key cannot be empty!\n";
            return false;
        }
    }

    // 3. Perform XOR operation
    for (size_t i = 0; i < content.size(); ++i) {
        content[i] ^= key[i % key.length()];
    }

    // 4. Write back to the same file
    std::ofstream outFile(filepath, std::ios::binary | std::ios::trunc);
    if (!outFile) {
        std::cerr << "Error writing file: " << filepath << "\n";
        return false;
    }
    outFile.write(content.data(), content.size());
    outFile.close();

    return true;
}

int main()
{
    std::cout << "File Encryptor/Decryptor\n";
    std::cout << "------------------------\n";

    std::cout << "Enter file path: ";
    std::string filepath;
    std::getline(std::cin >> std:: ws, filepath); // Get file path
    std::cout << "Encrypt or Decrypt? (e/d): "; //  To define the process
    char process;
    std::cin >> process;

    // For encryption process
    if (tolower(process) == 'e') {
        if (processFile(filepath, true)) {
            std::cout << "File encrypted successfully!\n";
            return 0;
        }

        // Error handling
        else {
            std::cerr << "Encryption failed!\n";
            return 1;
        }
    }

    // For decryption process
    else if (tolower(process) == 'd') {
        if (processFile(filepath, false)) {
            std::cout << "File decrypted successfully!\n";
            return 0;
        }

        // Error handling
        else {
            std::cerr << "Decryption failed!\n";
            return 1;
        }
    }

    // Error handling
    else {
        std::cerr << "Invalid choice! Please enter 'e' or 'd'.\n";
        return 1;
    }
}

