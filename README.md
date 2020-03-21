# nx-TAS
> Rewrite of [TAS-nx](https://github.com/hamhub7/TAS-nx)

nx-TAS is fundamentally different than its predecessor, TAS-nx, in that it uses a virtual controller to send inputs instead of changing the inputs of the currently used controller.

## Support the Creators
Join our [Discord server](http://discord.gg/qeamCcV)  
Support me on [Patreon](https://www.patreon.com/aaronhh)  
Make a pull request!  

## Usage
nx-TAS requires an [Atmosphere-injected Switch](https://switch.homebrew.guide/).

### Installation
1. Acquire `nx-TAS.nsp` via building yourself via the instructions below (preferred) or downloading the [latest release](https://github.com/hamhub7/nx-TAS/releases/latest)
2. Create the relevant title directory on your Switch's SD card at `sdmc:/atmosphere/contents/0100000000000cab/`
3. Place the NSP as `sdmc:/atmosphere/contents/0100000000000cab/exefs.nsp`
4. Create an empty file at `sdmc:/atmosphere/contents/0100000000000cab/flags/boot2.flag`
5. Reboot into CFW

### Scripts
To run scripts, you need to have a USB keyboard attached to your Switch, either via the dock or a USB-A to USB-C adapter in the charging port. Place scripts in the `sdmc:/scripts/` directory. Different function keys will run different scripts; pressing `F1` runs `sdmc:/scripts/script1.txt`, and so on up to `script12.txt`.

To make scripts, see [the web documentation](https://hamhub7.github.io/nx-TAS). General programming knowledge may be required.

## Building from Source
1. [Set up the Switch Development Environment](https://switchbrew.org/wiki/Setting_up_Development_Environment).
2. In the MSYS2 shell, navigate to a suitable parent folder for the project. If unsure, `cd /c/Users/[username]/Documents` (replacing `[username]` with your Windows username).
3. `git clone https://github.com/hamhub7/nx-TAS.git`. This downloads nx-TAS to your local machine.
4. `cd nx-TAS`. This puts you in the project folder.
5. `make`. This compiles the sources and generates the output NSP file.
6. `ls` or open the folder in Windows Explorer and should see a resultant file named `nx-TAS.nsp`.

Running `make` may produce an error, which is commonly one of these four:
- You `git clone`d at a time when the project doesn't compile properly: wait for an update on GitHub and then `git pull --rebase`
- Your folder you are `make`ing in is named something other than `nx-TAS`: if you are in the correct folder, `ln -s nx-TAS.json config.json`
- Your directory's full path has spaces in it (usually your account name): check with `pwd`
- You do not have BNFC installed: [download the latest exe](https://github.com/BNFC/bnfc/releases) and put it somewhere on your [`$PATH`](https://linuxconfig.org/linux-path-environment-variable)
