# Mini Version Control System

## Introduction

This project is a mini version control system (VCS) that mimics the basic functionalities of Git. It allows users to add files, commit changes, and checkout specific commits. The goal is to understand the core concepts of version control systems and how they manage file changes over time.

## Features Implemented

- Initialize a new repository
- Hash object files
- Display content or metadata of object files
- Write the current directory tree to an object
- List the contents of a tree object
- Add files to the staging area
- Commit changes
- Display commit history
- Checkout specific commits

## Compilation Instructions

To compile the program, ensure you have a C/C++ compiler installed. Navigate to the project directory and run:

```bash
make
```

This will compile all the necessary source files and generate the executable `mygit`.

## Execution Instructions

After compiling, you can execute the program using the following commands:

### 1. Initialize Repository

```bash
./mygit init
```

**Purpose**: Initializes a new repository by creating a directory called `.mygit` and sets up the necessary structure to store objects, metadata, and references to track changes.

### 2. Hash-Object

```bash
./mygit hash-object [-w] <file>
```

**Example**:

```bash
echo -n "hello world" > test.txt
./mygit hash-object -w test.txt
```

**Purpose**: Calculates the SHA-1 hash of a file, compresses it, and optionally stores it as a blob object in the repository when the `-w` option is used. If `-w` is not included, it simply prints the file's SHA-1 hash.

### 3. Cat-File

```bash
./mygit cat-file <flag> <object_sha>
```

**Flags**:

- `-p`: Print the actual content of the object.
- `-s`: Display the size of the object in bytes.
- `-t`: Show the type of the object (e.g., blob, tree).

**Example**:

```bash
./mygit cat-file -p a3c9c2f58c4b6a2e5f0f48757c2f0e4ef9b8d6d4
```

**Purpose**: Reads and displays the content or metadata of an object stored using its SHA-1 hash.

### 4. Write Tree

```bash
./mygit write-tree
```

**Purpose**: Writes the current directory structure to a tree object, representing the hierarchy of files and directories. It creates a new tree object and stores it in the repository.

### 5. List Tree (ls-tree)

```bash
./mygit ls-tree [--name-only] <tree_sha>
```

**Example**:

```bash
./mygit ls-tree 6d5c10cb0693c0f9ea3ef477651a15e40698bad8
```

**Purpose**: Lists the contents of a tree object (directory) using its SHA-1 hash. Displays detailed information about the files and subdirectories or just their names when using `--name-only`.

### 6. Add Files

```bash
./mygit add <file1> <file2> ...
./mygit add .
```

**Purpose**: Adds files or directories to the staging area, preparing them for the next commit.

**Examples**:

- Add specific files:

  ```bash
  ./mygit add main.cpp utils.cpp
  ```
- Add all files in the current directory:

  ```bash
  ./mygit add .
  ```

### 7. Commit Changes

```bash
./mygit commit [-m "Commit message"]
```

**Purpose**: Creates a commit object, representing a snapshot of the staged changes, and updates the repository’s history.

**Examples**:

- Commit with a message:

  ```bash
  ./mygit commit -m "Initial commit"
  ```
- Commit without a message (a default message will be assigned):

  ```bash
  ./mygit commit
  ```

### 8. Log Command

```bash
./mygit log
```

**Purpose**: Displays the commit history from the latest commit to the oldest.

### 9. Checkout Command

```bash
./mygit checkout <commit_sha>
```

**Example**:

```bash
./mygit checkout 95d09f2b10159347eece71399a7e2e907ea3df4f
```

**Purpose**: Checks out a specific commit, restoring the state of the project as it was at that commit.

## Working Procedure

1. **Initialization**: Start by initializing a new repository using `./mygit init`. This creates a `.mygit` directory to store all version control data.
2. **Adding Files**: Use `./mygit add <files>` to add files to the staging area.
3. **Committing Changes**: Commit the staged changes using `./mygit commit -m "Your commit message"`.
4. **Viewing History**: Use `./mygit log` to view the commit history.
5. **Checking Out Commits**: Restore the project to a previous state using `./mygit checkout <commit_sha>`.
6. **Hashing Objects**: Use `./mygit hash-object [-w] <file>` to compute the SHA-1 hash of a file and optionally store it.
7. **Inspecting Objects**: Use `./mygit cat-file` to display the content or metadata of an object.
8. **Writing Trees**: Capture the current directory structure with `./mygit write-tree`.
9. **Listing Trees**: List the contents of a tree object using `./mygit ls-tree`.

## Assumptions:

- The SHA-1 hashes are assumed to be unique identifiers for objects in the repository.
- our file size will be small enough that it can be read at ones if larger then just change hash_command function in hash_command.cpp file
- The `.mygit` directory is not manually altered by the user.
- The system is designed to work in a Unix-like environment.
- All files are text files unless specified otherwise.
- The user has the necessary permissions to read and write files in the working directory.
- The program is executed from the root directory of the project (where `.mygit` is located).

## Short Description of Each Feature

- **Initialize Repository**: Sets up the version control environment by creating necessary directories and files.
- **Hash-Object**: Computes the SHA-1 hash of a file and stores it as a blob object for tracking content.
- **Cat-File**: Retrieves and displays the content or metadata of stored objects using their SHA-1 hashes.
- **Write Tree**: Captures the current directory structure and stores it as a tree object representing the state of the project.
- **List Tree (ls-tree)**: Lists the contents of a tree object, showing files and directories tracked in a specific tree.
- **Add Files**: Stages files for the next commit, recording changes to be included in the snapshot.
- **Commit Changes**: Creates a commit object that encapsulates the current state of the project, linking to the tree and parent commits.
- **Log Command**: Provides a history of commits, allowing users to see changes over time.
- **Checkout Command**: Switches the working directory to reflect the state of a specific commit, enabling version control navigation.

## Additional Information

- The `make` command compiles the source code and produces an executable named `mygit`.
- Error handling is implemented to ensure graceful failures when invalid inputs are provided.
- The program uses standard C/C++ libraries and permissible external libraries as per the assignment guidelines.
- Compression techniques and the SHA-1 algorithm are used for storing and verifying object data.
