# mes_stm32f4_disco_virtual_serial_port_experiment

Based on some class discussion in the Discord, I took a stab at implementing the Virtual COM port on 
the [STM32F411E-DISCO](https://www.st.com/en/evaluation-tools/32f411ediscovery.html) board using 
[this tutorial](https://medium.com/@pasindusandima/stm32-usb-virtual-com-port-vcp-bc7cb1bd5f5).

The main changes are to add Elicia's [Command console library](https://github.com/eleciawhite/reusable)
along with a [circular buffer from Embedded Artistry](https://github.com/embeddedartistry/embedded-resources/tree/master/examples/c/circular_buffer).
