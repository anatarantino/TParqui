#ifndef IDTFILE_H
#define IDTFILE_H

static void setup_IDT_entry (int index, uint64_t offset);
void load_idt();

#endif