/*
 * File name�� nv.h
 * Date�� 2024-03-21
 * Description�� �����˷���ʧ���ڴ�ĺ궨�壬�������κεط�����
 */
#ifndef DRIVER_NV_H_
#define DRIVER_NV_H_

#define __nv __attribute__((section(".TI.persistent")))

#define __no_init __attribute__((section(".TI.noinit")))

#define __ro_nv __attribute__((section(".ro_nv_vars")))

#endif /* DRIVER_NV_H_ */
