#ifndef HEADER_GET_LAYOUT_H
#define HEADER_GET_LAYOUT_H

struct layout_var;

struct layout_var *get_layout_var();
void print_layout_var(struct layout_var *var);
struct layout_var *layout_var_to_phy(struct layout_var *var);

#endif