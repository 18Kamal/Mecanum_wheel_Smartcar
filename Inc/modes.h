// modes.h
#ifndef MODES_H
#define MODES_H

typedef enum {
    MODE_MANUAL,
    MODE_AUTO
} OperationMode_t;

extern OperationMode_t currentMode;

#endif