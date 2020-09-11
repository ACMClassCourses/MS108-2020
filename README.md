# MS108-2020

**Updating...**

#### Requirement

##### Basic Requirement

- Use Verilog to implement a CPU supporting part of RV32I Instruction set(2.1-2.6 in [RISC-V user manual][https://riscv.org//wp-content/uploads/2017/05/riscv-spec-v2.2.pdf]), with the provided hci.v and io.c in this repository. 
- The architecture should be pipelined or Tomasulo. 

##### Grading Policy

- A 5-stage pipelined or Tomasulo CPU passing all tests in this repository(**Updating**) with i-cache makes you get 75%. 
- Implementing your design on FPGA makes you get 5%. 
- Choose one from the following three to get the rest: 
  1. Implement branch prediction and d-cache. Based on your performance and complexity(e.g., 1-bit global branch prediction is obviously simpler than BTB), you will get 10%~20%. 
  2. A Tomasulo architecture CPU that does not halt in every branch instruction. Send your design before code review. You will get 20% for this. 
  3. Support the rest of RV32I Instruction set (2.7-2.9 in the manual above) and privileged architecture(**todo: how much of ** [RISC-V architecture manual][https://riscv.org//wp-content/uploads/2017/05/riscv-privileged-v1.10.pdf]). Finally, you will be able to port FreeRTOS on FPGA with your design and some provided code. You will get 20% and an extra 5 pts for this. 
  4. Whatever more, but discuss with TA first. 

- A design meeting part of a requirement can get part of corresponding points. 