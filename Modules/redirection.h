/*
 * File name��redirection.h
 * Date�� 2024-03-21
 * Description: ����������printf�������ض��򷽷����������κεط����е���printf������������е��Ժ�ͨ�š�
 */

#ifndef REDIRECTION_H
#define REDIRECTION_H

#include<Modules/driver_include.h>
#include<stdio.h>
#include<string.h>

int fputc(int _c, register FILE *_fp);
int fputs(const char *_ptr, register FILE *_fp);


#endif
