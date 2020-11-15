# MS108-2020

**Still updating...**

#### Repo Structure

```
|--docs/
|  |--YPU/				A demo-use simplified 5-stage pipelined CPU
|  |--vivadoDemo.pdf	A demo about how to create a project in Vivado
|--riscv/
|  |--ctrl/				Interface with FPGA
|  |--sim/				Testbench, add to Vivado project only in simulation
|  |--src/				Where your code should be
|  |  |--common/				Provided UART and RAM
|  |  |--Basys-3-Master.xdc		constraint file
|  |  |--cpu.v					Fill it. 
|  |  |--hci.v					A bus between UART/RAM and CPU
|  |  |--ram.v					RAM
|  |  |--riscv_top.v			Top design
|  |--sys/				Help compile
|  |--testcase/			Testcases
|  |--build_test.sh		Run it to build test.data from test.c
|  |--run_test.sh		Run test
|  |--run_test_fpga.sh	Run test on FPGA
|--serial/				A third-party library for interfacing with FPGA ports
```

#### Requirement

##### Basic Requirement

- Use Verilog to implement a CPU supporting part of RV32I Instruction set(2.1-2.6 in [RISC-V user manual](https://riscv.org//wp-content/uploads/2017/05/riscv-spec-v2.2.pdf)), with the provided code in this repository. 
- The architecture should be pipelined or Tomasulo. 

##### Grading Policy

- A 5-stage pipelined or Tomasulo CPU passing all tests in this repository with i-cache makes you get 75%. 
- Implementing your design on FPGA makes you get 5%. 
- Here are some bonus parts. Except (3), the sum of bonus will not exceed 20%: 
  1. Implement branch prediction and d-cache. Based on your performance and complexity(e.g., 1-bit global branch prediction is obviously simpler than BTB), you will get 10%~20%. 
  2. A Tomasulo architecture CPU that does not halt in every branch instruction. Send your design before code review. You will get 20% for this. 
  3. Support the rest of RV32I Instruction set (2.7-2.9 in the manual above) and privileged architecture(section 2 and section 3 in [RISC-V privileged architecture manual](https://riscv.org//wp-content/uploads/2017/05/riscv-privileged-v1.10.pdf)). Finally, you will be able to port FreeRTOS on FPGA with your design and some provided code. You will get 20% and an extra 5 pts for this. 
  4. Whatever more, but discuss with TA first. 
- A design meeting part of a requirement can get part of its corresponding points. 
- The course project assignment is not mature yet. Please give practical suggestions or bug fixes for next year's project if you feel somewhere uncomfortable with current project. You should prepare a short note or presentation for your findings. You will get extra 2% for this. If you implement your suggestion and it's meaningful in both educational purpose and project perfection purpose, the extra credit will be raised up -- up to 10%. It will be a complement for your bonus part, or extra 1 point in the final grading if you get full mark in the project.

#### Details

##### RISCV-Toolchain

The configure is: 

```./configure --prefix=/opt/riscv --with-arch=rv32i --with-abi=ilp32```

(BTW, you may use arch rv32gc for your compiler project, so keep the installation package)

##### Custom

In this project, the size of memory(ram) is 128K, so only address lower than 0x20000 is available. However, reading and writing from 0x30000 and 0x30004 have special meaning, you can see `riscv/src/cpu.v` for more details. (You can just regard the two as normal address)

##### Simulation using iverilog

```
cd ./riscv/src
iverilog *.v common/*/*.v
vvp a.out
```

##### Serial

Serial( [wjwwood/serial](https://github.com/wjwwood/serial)) is a cross-platform serial port library to help your design working on FPGA when receiving from UART. Build it by: 

```bash
cd serial
make
make install
```

##### Build test

Use the following command to build a test, it will be a `test.data` file in folder `/riscv/test/`: 

```bash
cd riscv
./build_test.sh testname
```

You can see all tests in `/riscv/testcase/` folder. 

##### FPGA

We'll provide you with Basys3 FPGA board. Use Vivado to generate bitstream and program the FPGA device. Then:

In directory 'ctrl', build the controller by

```
./build.sh
```

Modify and run the script

```
./run_test_fpga.sh testname
```

One thing need to be modified is the USB port number of the script. For example in Windows you could find it in Devices and Printers -> Digilent USB Device -> Hardware. The number X that presented in the last line of Device Functions 'USB Serial Port (COMX)' is the port you need. The port format should be like:

```
on Linux: /dev/ttyUSBX
on WSL: /dev/ttySX
on Windows: COMX
```

##### Update Note

For some strong students that start project early based on last year's assignment, here are some changes we've made this year:

1. Fixed a bug in  `riscv_top.v`  that may cause you get wrong return value when two consecutive readings are from different data sources.

2. A new `input wire io_buffer_full`  that will show the UART output buffer is full and you should stall -- otherwise some output will be missing when output requests are intensive. You can ignore the problem in the beginning stage.

   Note: you will receive `io_buffer_full` in the SECOND NEXT CYCLE from your write cycle since the FIFO module's limitation. To ensure FIFO is not full you have to stall one cycle when there are two consecutive writes to 0x30000 in two consecutive clock, especially when i-cache is on. This problem will be detected in the testcase `uartboom`. 

   You're welcome to fix this problem by modifying preset code. Elegant implementation will be counted as bonus.

##### Q&A

1. `rdy_in` and `rst_in`

   The `rst_in` has higher priority with `rdy_in`, and you CANNOT DO ANYTING when `rdy_in` is zero. `rdy_in` does not affect the result of simulation, but has effect when running on FPGA. 

You may meet various problems, especially when start testing on FPGA. Feel free to contact any TA for help.
