/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.c to edit this template
 */
#include <stdlib.h> /* added */
#include <stdio.h>

void *__real_malloc (size_t size) {
    return malloc(size);
}

void __real_free(void *ptr) {
    free(ptr);
}