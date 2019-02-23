## Building

Insure you have all the tools installed listed below

Recussivly clone the repo to get submodules
```sh
$ git clone --recurse-submodules https://github.com/supermileage/mbedSteering.git
```

Navigate into the repo and run the following command to install the mbed libraries
```sh
$ mbed deploy
```

* NOTE: If you make any changes to the mbedCanLib then make sure to commit and push those before you commit and push mbedSteeting.


If this is your first time using mbed, navigate to mbed-os folder, and run
```sh
$ pip install -r requirements.txt
```

Navigate back to project root, and run
```sh
$ mbed new .
```

Then export the project for your board and compiler, in this case for the lpc1768 with vscode use the following
```sh
$ mbed export -i vscode_gcc_arm -m lpc1768 --profile mbed-os/tools/profiles/debug.json
```

Now open the project in VSCode, and go the launch.json. Change the 2 lines with the comment 'CHANGE', to the location of your 'arm-none-eabi-gdb' and 'pyocd-gdbserver'.
The pyocd-server will be located inside the virtualenv (if you followed instructions from tools section below), so for you '.../mbedEnv/bin/pyocd-gdbserver' (fill in the ... with the actual path)

You should be able to plug in the LPC1768 and debug. Please read the comments about breakpoints and wait() at the top of main.cpp


## Tools (for mac)

First, insure you have the arm toolchain arm-none-eabi-gdb installed, you can check this with
```sh
$ arm-none-eabi-gdb
```

Install it if you don't have it already
```sh
$ brew tap ArmMbed/homebrew-formulae
$ brew install arm-none-eabi-gcc
```

Then, install `virtualenv`, which allows you to isolate python environments:
```sh
$ pip install virtualenv
```

Next, create a virtual environment, anything you install with pip will go in here
```sh
$ virtualenv mbedCanEnv
```

Enter that virtualenv
```sh
$ source mbedCanEnv/bin/activate
```

You can leave this environment at any point with
```sh
$ deactivate
```

Now install the mbed command line interface (mbed-cli)
```sh
$ pip install mbed-cli
```

