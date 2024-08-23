/*
 * File name：redirection.h
 * Date： 2024-03-21
 * Description: 用于声明了printf函数的重定向方法，可以在任何地方进行调用printf函数，方便进行调试和通信。
 */

#ifndef REDIRECTION_H
#define REDIRECTION_H

#include<Modules/driver_include.h>
#include<stdio.h>
#include<string.h>

int fputc(int _c, register FILE *_fp);
int fputs(const char *_ptr, register FILE *_fp);


#endif
