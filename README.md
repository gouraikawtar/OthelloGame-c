# OthelloGame-c
## Overview
**Othello** is a strategy board game for two players, played on an 8×8 uncheckered board.
We tried to implement its algorithm in our way using C langage. <br/>
**This project was given as an assignment in the school where we study.**
## Contributors
[Kawtar Gourai](https://github.com/gouraikawtar)<br/>
[Zineb Thoum](https://github.com/ZinebThoum)
## Get started (Windows OS setup)
This project was developped using Code::Blocks IDE and **ncurses** library to manipulate output. <br/>
The following steps will guide you through the  installation and setup process so you can make it correctly. 
### Install your IDE
Download **Code::Blocks** [here](http://www.codeblocks.org/downloads/binaries). Download the *mingw-setup.exe* version which includes additionally the GCC/G++/GFortran compiler and GDB debugger from MinGW-W64 project. <br/> Install it after download proccess ended.
### Download ncurses library
Download **ncurses** [here](https://invisible-island.net/ncurses/#downloads).<br/> Go to *MinGw Port* and download the *32-bit* or *64-bit* version depending on your compiler's version.<br/>
Now open your downloaded folder, extract the 3 folders into a new folder and place it somewhere on your hard drive.  

### Clone the project
Clone your project locally on your hard drive
```
git clone url
```
### Setup ncurses with the project
Open your cloned project folder and do the following:
1. Open your **ncurses downloaded folder**, then navigate to **bin** folder, copy the file named **libncursesw6.dll** to your project's folder.<br/>
<p>Now open the <strong>.cbp</strong> file on <strong>Code::Blocks</strong>. You have to setup the project's build path.</p><br/>

2. On your *Code:Blocks* taskbar, go to **Project -> Build options -> Linker settings -> Other linker options** and type the following commands:
```
-lmingw32 -lncursesw
```
3. On the same window, navigate to **Search directories -> Compiler** and add the following **(replace *my_path* with the appropriate path to the ncurses include folder)**
```
my_path\include
my_path\include\ncursesw
```
4. On the same window, navigate to **Search directories -> Linker** and add the following **(replace *my_path* with the appropriate path to the ncurses lib folder)**
```
my_path\lib
```
5. Click on **ok** to save changes.
6. **Rebuild** the project.
7. Click **Build and run** to build and run project.
>And here is it, your project is ready. HAVE FUN!
