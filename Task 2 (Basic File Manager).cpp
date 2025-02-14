#include <iostream>
#include <filesystem>
#include <fstream>

using namespace std;
namespace fs = std::filesystem;

void listDirectory(const string& path) {
    cout << "\nContents of " << path << "\n";
    for (const auto& entry : fs::directory_iterator(path)) {
        cout << (entry.is_directory() ? "[DIR] " : "[FILE] ") << entry.path().filename() << "\n";
    }
}

void changeDirectory(string& currentPath, const string& newPath) {
    fs::path tempPath = fs::absolute(fs::path(currentPath) / newPath);
    if (fs::exists(tempPath) && fs::is_directory(tempPath)) {
        currentPath = tempPath.string();
    } else {
        cout << "Invalid directory!\n";
    }
}

void viewFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "File not found!\n";
        return;
    }
    cout << "\n--- " << filename << " ---\n";
    string line;
    while (getline(file, line)) {
        cout << line << "\n";
    }
    file.close();
}

void createFile(const string& filename) {
    ofstream file(filename);
    if (file) {
        cout << "File created successfully.\n";
        file.close();
    } else {
        cout << "Error creating file!\n";
    }
}

void editFile(const string& filename) {
    ofstream file(filename, ios::app);
    if (!file) {
        cout << "Error opening file!\n";
        return;
    }
    cout << "Enter text to append (Ctrl+D to stop):\n";
    string input;
    while (getline(cin, input)) {
        file << input << "\n";
    }
    file.close();
}

void copyFile(const string& source, const string& destination) {
    try {
        fs::copy(source, destination, fs::copy_options::overwrite_existing);
        cout << "File copied successfully.\n";
    } catch (fs::filesystem_error& e) {
        cout << "Error copying file: " << e.what() << "\n";
    }
}

void moveFile(const string& source, const string& destination) {
    try {
        fs::rename(source, destination);
        cout << "File moved successfully.\n";
    } catch (fs::filesystem_error& e) {
        cout << "Error moving file: " << e.what() << "\n";
    }
}

void deleteFile(const string& filename) {
    if (fs::remove(filename)) {
        cout << "File deleted successfully.\n";
    } else {
        cout << "Error deleting file!\n";
    }
}

void createDirectory(const string& dirname) {
    if (fs::create_directory(dirname)) {
        cout << "Directory created successfully.\n";
    } else {
        cout << "Error creating directory!\n";
    }
}

void deleteDirectory(const string& dirname) {
    if (fs::remove_all(dirname)) {
        cout << "Directory deleted successfully.\n";
    } else {
        cout << "Error deleting directory!\n";
    }
}

int main() {
    string currentPath = fs::current_path().string();
    string command;

    while (true) {
        cout << "\nFileManager: " << currentPath << " > ";
        cin >> command;

        if (command == "ls") {
            listDirectory(currentPath);
        } else if (command == "cd") {
            string newPath;
            cin >> newPath;
            changeDirectory(currentPath, newPath);
        } else if (command == "pwd") {
            cout << currentPath << "\n";
        } else if (command == "cat") {
            string filename;
            cin >> filename;
            viewFile(filename);
        } else if (command == "touch") {
            string filename;
            cin >> filename;
            createFile(filename);
        } else if (command == "edit") {
            string filename;
            cin >> filename;
            editFile(filename);
        } else if (command == "cp") {
            string source, destination;
            cin >> source >> destination;
            copyFile(source, destination);
        } else if (command == "mv") {
            string source, destination;
            cin >> source >> destination;
            moveFile(source, destination);
        } else if (command == "rm") {
            string filename;
            cin >> filename;
            deleteFile(filename);
        } else if (command == "mkdir") {
            string dirname;
            cin >> dirname;
            createDirectory(dirname);
        } else if (command == "rmdir") {
            string dirname;
            cin >> dirname;
            deleteDirectory(dirname);
        } else if (command == "exit") {
            break;
        } else {
            cout << "Unknown command!\n";
        }
    }
    return 0;
}

