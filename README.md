# mnode

The mnode is a JavaScript runtime for microcontrollers. 

## Hardware

I just use [realboard-lpc4088](https://github.com/RT-Thread/realboard-lpc4088) for mnode development. You can buy this board from [taobao](http://item.taobao.com/item.htm?spm=a1z10.1-c.w4004-5210898174.5.i62kwV&id=37483208096).

The realboard-lpc4088 has:

* 120MHz LPC4088 ARM Cortex-M4;
* 32MB SDRAM @ 120MHz
* 128MB NandFlash
* 8MB QSPI NorFlash
* 10/100M ETH
* SD card slot

## Software

The mnode uses [MuJS](http://www.mujs.com) as JavaScript engine on RT-Thread operating system and will make a IoT network framework. 

## Build

The mnode is running on RT-Thread operating system, therefore, please download RT-Thread code firstly: 

    git clone https://github.com/RT-Thread/rt-thread.git

Moreover, we need [scons](http://www.scons.org) to build firmware and js engine. Please install Python 2.7.x and scons.

Then, build them with following command:

  cd firmware
  export BSP_ROOT=`pwd`
  export RTT_ROOT=your_rt_thread_path
  export RTT_CC=gcc
  export RTT_EXEC_PATH=your_arm_gcc_toolchain_path
  
  # build firmware
  scons
  scons --target=ua -s
  
  # build js engine
  cd ..
  cd mnode
  scons --app=mnode
