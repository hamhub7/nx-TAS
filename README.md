# nx-TAS
Rewrite of [TAS-nx](https://github.com/hamhub7/TAS-nx)

It works fundamentally differently than TAS-nx in that it uses a virtual controller to send inputs instead for changing the inputs of the currently used controller. The program now supports multiple scripts, which can be run with the F1-F12 keys. The scrips should be placed in sdmc:/scripts/script1.txt - sdmc:/scripts/script12.txt. Keybindings have also changed to allow more controller types to be added. Q presses L+R on the controller and W presses A, useful for initially pairing the controller (not yet implemented). The minus key to the right of the 0 key subtracts the highest controller in the list (you have to press this twice to get rid of two joycons, they count as seprate controllers). The number keys all add different types of controllers to the console: 

1-Procon  
2-Pair of Joycons (this is technically two controllers, but its used commonly enough we decided to add a "macro" for it)  
3-Left Joycon  
4-Right Joycon  
5-Famicom Controller  
6-Famicom Controller with mic  
7-NES Controller  
8-Unused Controller that is still usable. Try it if you want!

This project is still in early development, but it is usable if built from source. How to build it: follow the directions [here](https://switchbrew.org/wiki/Setting_up_Development_Environment) to install MSYS2. Open MSYS2, navigate to the folder you downloaded to with `cd`, then simply type `make` and press enter. Once the .nsp is built, create `sdmc:/atmosphere/titles/0100000000000cab`. Rename `nx-TAS.nsp` to `exefs.nsp`, then move it to the empty folder you just created. In that same folder, also make another folder simply named `flags`. Inside it, create a blank file called `boot2.flag`. Make sure it is just named that, with no `.txt` at the end. Then you are good to go for use.

IMPORTANT: It will not build the .nsp if the folder is not named 'nx-TAS'. It is case sensitive.

# Features
New features are already planned, such as changing the tye of controller (pro, joycons, sideways joycons, and possibly other controllers), multiple player TAS support, motion controls, some way to combat variable load times and rng (for most games), and color customizaition of the controllers.
