#  Multi-Parameter Support with NTTs for NTRU and NTRU Prime on Cortex-M4

This repository accompanies our paper [Multi-Parameter Support with NTTs for NTRU and NTRU Prime on Cortex-M4](https://tches.iacr.org/index.php/TCHES/article/view/9823)
published at TCHES 2022.
You can find the talk [here](https://youtu.be/TSUtA5hmrtk?t=2825) and an updated version [here].

## Summary of Overall Performance

| scheme | implementation | key generation [cycles] | encapsulation [cycles] | decapsulation [cycles] |
| ------ | -------------- | ----------------------- | ---------------------- | ---------------------- |
| ntruhps2048677| m4f_1440 |  3,912k |   525k |   718k |
| ntruhrss701   | m4f_1440 |  3,822k |   361k |   778k |
| ntruhps4096821|      m4f |  5,217k |   654k |   908k |
| ntrulpr653    |      m4f |    669k | 1,131k | 1,231k |
| ntrulpr761    |      m4f |    710k | 1,266k | 1,365k |
| ntrulpr857    |      m4f |    886k | 1,465k | 1,596k |
| sntrup653     |      m4f |  6,623k |   621k |   527k |
| sntrup761     |      m4f |  7,937k |   666k |   563k |
| sntrup857     |      m4f | 10,192k |   812k |   685k |

## The Structure of the Sources

We follow pqm4 directory structure to make it easier to adopt.
- `common` contains the common functions.
- `crypto_kem` contains our implementations.
- `mk` contains the relevant makefiles stripped from [pqm4](https://github.com/mupq/pqm4) and [mupq](https://github.com/mupq/mupq).
- `ldscripts` contains the linker for our board.
We provided implementations of each parameter sets for each scheme in a separeted directory under the `crypto_kem` directory.

We focus on the NTT-based polynomial multiplications.
For each implementation,
 - The prototypes for assembly functions and precomputed tables are given in a header file `NTT.h`, and the parameters for the convolution implementation are given in a separeted header file `NTT_params.h`.
 - Dedicated butterfly operations, which are explained in Section 4.1 of the paper, are implemented in the `special_butterflies.i` and used in `Good_3x2.S` files.
 - The final map implementations are provided in the `final_map.S` files.

### Imported Code

- We used latest version of NTRU and NTRU Prime implementations from [pqm4](https://github.com/mupq/pqm4).
- We used TMVP-based polynomial multiplication from [Faster NTRU on ARM Cortex-M4 with TMVP-based multiplication](https://github.com/iremkp/NTRU-tmvp4-m4) by \'{I}rem Keskinkurt Paksoy and Murak Cenk, when any of the inputs in the polynomial multiplication of NTRU implementations doesn't have restriction that all coefficients should be in {-1, 0, 1}.
- We used NTT-based multiplication (without changing the coefficient rings) for polynomial multiplications in the key generation of Streamlined NTRU Prime implementations from [Number Theoretic Transform for Polynomial Multiplication in Lattice-based Cryptography on ARM Processors](https://github.com/dean3154/ntrup_m4) by Yun-Li Cheng.

## Running tests

### Dependencies

- arm-none-eabi-gcc 9.2.1 or later (we also tested with 10.3.1) for compiling our code.
- libopencm3 for the board, commit c78007338e13a927c71385b0d647ba5bfb526bd7.
- stlink for flashing the binaries to the board.
- python3 for running the scripts, including the following modules:
    - `pyserial`
    - `numpy`

### Compilation

For a better compilation performance we recommend compile the code with following command.

```
make -j8
```
### Binary files
After compilation, binary files are created under bin directory and can be uploaded to the board with using st-link tools as follows:
```
st-flash write XXX.bin 0x8000000
```
where `XXX.bin` is the produced binary file.

### How to Read from Board
To read the output, one needs to connect the boards PA2 and PA3 pins to an usb-ttl serial adapter and run the following command.
```
python3 ./read_serial.py
```

Setting is in the file `config.py`.

### Script for Testing
To test the correctness of the implementations in the repository, one can run the following python script.

```
python3 ./test.py
```

### Script for Benchmarking
To verify cycle counts reported in the paper, one can use following script.

```
python3 ./speed.py
```

Results will be shown in the command line output for each implementation and the formatted tables are generated in the file `speed.txt` at the end.


## Related External Code
We also have some programs for generating the tables of twiddle factors and computing the worst-case bounds based on Montgomery reductions and multiplications.

### Generating Twiddle Factors

In [gen_table](https://github.com/vincentvbh/NTTs_with_Armv7-M_Armv7E-M_Armv8-A/tree/main/gen_table/Armv7E-M/cortex-m4),
the following folders generate the tables of twiddle factors in this paper:
- `ntruhps2048677_1440`
- `ntruhps2048677_1536`
- `ntruhps4096821`
- `ntruhrss701_1440`
- `ntruhrss701_1536`
- `ntrup653`
- `ntrup761`
- `ntrup857`

### Computing Worst-Case Bounds

In [bound](https://github.com/vincentvbh/NTTs_with_Armv7-M_Armv7E-M_Armv8-A/tree/main/bound/Armv7E-M/cortex-m4),
the following folders compute the bounds (based on Montgomery reductions and multiplications) of implementations in this paper:
- `ntruhps2048677_1440`
- `ntruhps2048677_1536`
- `ntruhps4096821`
- `ntruhrss701_1440`
- `ntruhrss701_1536`
- `ntrup653`
- `ntrup761`
- `ntrup857`




