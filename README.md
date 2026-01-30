# Introduction
For _some_ reason, many colleges and universities still use TurboC for their Computer Graphics labs. But TurboC is bad, and horrible, and ugly, and worse of all, it hurts the eyes.

In this repository, I'll show you how to run TurboC-style graphics.h program in VS Code.

> [!WARNING]
> The setup is intended for academic use, keeping behavior close to what is expected in labs and exams.

> [!IMPORTANT]  
> This guide is intended for **Windows 10/11** systems only. The setup uses **MinGW (GCC)** as the compiler.

# Steps
### 1. Install VS Code
Install [Visual Studio Code](https://code.visualstudio.com/download).

--- 

### 2. Install MinGW
> [!NOTE]  
> If you already have MinGW installed and `gcc` works in the terminal, you can skip reinstalling it.  
> Both **32-bit** and **64-bit** MinGW are supported, as long as the correct `libbgi.a` is used later.

1. Download the [MinGW](https://winlibs.com/#:~:text=it%20here.-,Release%20versions,-UCRT%20runtime) 64-bit .zip file.
2. Extract the .zip file to an easy-to-access location such as `C:\MinGW`. From now on, this guide will assume that you extracted the files to `C:\MinGW`
3. Navigate to `C:\MinGW\bin` and ensure you can find `gcc.exe` and `g++.exe` in that folder.

---

### 3. Setting up Environment Variables
1. Click Win+S and search for "Edit the system environment variables". Click on it and then click "Environment Variables..." on the bottom

<img width="300" height="300" alt="image" src="https://github.com/user-attachments/assets/f3c2df66-1cb9-4f2d-9420-b2b2e00caba7" />

2. Under "System Variables", find "Path" and click on "Edit".

<img width="400" height="350" alt="image" src="https://github.com/user-attachments/assets/a6891fe9-d39b-4edf-ba1e-88270b5baa94" />

3. Click on "New" and paste the path to the bin folder, e.g. `C:\MinGW\bin`. Save everything and close.
4. Open Command Prompt and run `gcc -v`. If you get a successful output, MinGW is set up for you.

---

### 4. Downloading the necessary files
1. Download the following files from the repository:
    - [`graphics.h`](graphics.h)
    - [`winbgim.h`](winbgim.h)
2. After running `gcc -v`, check the output.
    - If you see `Target: x86_64-w64-mingw32` in the output, then you are using 64-bit MinGW. Download the [64-bit `libbgi.a`](64-bit/libbgi.a).
    - Otherwise, if you see something along the lines of `Target: i686-w64-mingw32-g++`, then you are using 32-bit MinGW. Download the [32-bit `libbgi.a`](32-bit/libbgi.a).

> [!NOTE]  
> Make sure the `libbgi.a` you download matches your compiler bitness:
> - 64-bit MinGW → [`64-bit/libbgi.a`](64-bit/libbgi.a)
> - 32-bit MinGW → [`32-bit/libbgi.a`](32-bit/libbgi.a)
> Mixing 32-bit and 64-bit will cause linker errors.

---

### 5. Add the files to MinGW
1. Open File Explorer
2. Copy/cut the `graphics.h` and `winbgim.h` files that you just downloaded and paste them in `C:/MinGW/include` folder.
3. Copy/cut the `libbgi.a` file that you just downloaded and paste it in `C:/MinGW/lib` folder.

> [!NOTE]
> Alternatively, you can have the files in your project directory as shown below and use `-Llib -Iinclude` flags during compilation.
> ```
> your-project/
> ├── lib/
> │    └── libbgi.a
> └── include/
>      ├── graphics.h
>      └── winbgim.h
> ```

---

### 6. Setting up tasks.json
Compiling a program that uses graphics.h involves using a lot of flags. Instead, we will configure a **Build Task** in VS Code.

1. Create a `.vscode` folder in your project directory if you do not have one already.
2. Add a file `tasks.json` in the `.vscode` folder if it doesn't exist already.
3. Copy the contents from the [`tasks/Normal-tasks.json`](tasks/Normal-tasks.json) file in this repository into your `tasks.json`.

> [!WARNING]
> If you already have a configured task, be sure to merge it properly.

> [!IMPORTANT]
> Make sure to update the path to `g++.exe` if you didn't extract the files to `C:\MinGW`.
> ```jsonc
>  {
>     "label": "...",
>     "command": "C:\\MinGW\\bin\\g++.exe", // <--- HERE
>     "args": [...]
>  }
> ```

> [!TIP]
> If you used the `your-project/lib/` and `your-project/include/` method as mentioned in the previous step, add the following flags to your "args" array:
> - `-Llib`
> - `-Iinclude`
> Or you can copy the contents from the [`tasks/LF-tasks.json`](tasks/LF-tasks.json) file instead.

> [!NOTE]
> This build task outputs an `a.exe` in the root directory of your project. You can change this in the "args" array.

---

### 7. Running your graphics.h code
1. Write your program and save the file. Here's an [example program](example/circle.c) that you can use.
2. Press **Ctrl + Shift + B** to run the build task. After a successful build, run the `a.exe` file. The output will be generated in another window.

> [!NOTE]  
> Differences from TurboC:
> - `initgraph(&gd, &gm, "C:\\TURBOC3\\BGI")` → `initgraph(&gd, &gm, "")`
> - `closegraph()` → `closegraph(0)`
