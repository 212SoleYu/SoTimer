/*
 * File name： nv.h
 * Date： 2024-03-21
 * Description： 声明了非易失性内存的宏定义，可以在任何地方调用
 */
#ifndef DRIVER_NV_H_
#define DRIVER_NV_H_

#define __nv __attribute__((section(".TI.persistent")))

#define __no_init __attribute__((section(".TI.noinit")))

#define __ro_nv __attribute__((section(".ro_nv_vars")))

#endif /* DRIVER_NV_H_ */
