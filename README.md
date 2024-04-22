#THE RISCY-BUSINESS IDE

# To download use this command
```bash
git clone https://github.com/RISCY-BUSINESS/RISC-y-Business.git
```
You will need the sfml library to use the IDE. Install from www.sfml.com for windows
Or on linux, you can use your terminal, say for example-
```bash
sudo apt-get install libsfml-dev
```

# To compile use this command

```bash
cd RISC-y-Business
cmake -DBUILD_RISCY_IDE=ON -DBUILD_SIMULATOR_CLI=OFF
make
```

# To run the IDE use this command

```bash
cd build
./RISCY-IDE
```

