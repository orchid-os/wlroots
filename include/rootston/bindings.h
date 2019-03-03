#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef ROOTSTON_BINDINGS_H
#define ROOTSTON_BINDINGS_H

#include "rootston/seat.h"
#include "rootston/input.h"

void execute_binding_command(struct roots_seat *seat, struct roots_input *input, const char *command);

#endif //ROOTSTON_BINDINGS_H
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
}
#endif
