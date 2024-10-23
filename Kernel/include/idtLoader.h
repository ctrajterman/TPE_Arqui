//******************************************************************************
// Archivo: idtLoader.h
//******************************************************************************

#ifndef _IDTLOADER_H_
#define _IDTLOADER_H_
#include <stdint.h>
//******************************************************************************
// DECLARACIÓN DE PROTOTIPOS
//******************************************************************************

static void setup_IDT_entry(int index, uint64_t offset);
void load_idt();


#endif // _IDTLOADER_H_
