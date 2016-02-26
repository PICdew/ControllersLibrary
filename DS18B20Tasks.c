/** DS18B20Tasks.c
 * v.1.3
 */

#include "DS18B20Tasks.h"

void DS18B20WriteScratchpadTask() {
    DS18B20WriteScratchpad();
    if (DS18B20LastError == DS18B20OperationOK) {
        AddTask(DS18B20ConvertTemperatureTask, 0);
    }
    else {
        AddTask(DS18B20WriteScratchpadTask, DS18B20PresencePulseNotDetectedDelay);
    }
}

void DS18B20ConvertTemperatureTask() {
    DS18B20ConvertT();
    if (DS18B20LastError == DS18B20OperationOK) {
        AddTask(DS18B20ReadScratchpadTask, DS18B20ConvertTemperatureDelay);
    }
    else {
        AddTask(DS18B20WriteScratchpadTask, DS18B20PresencePulseNotDetectedDelay);
    }
}

void DS18B20ReadScratchpadTask() {
    DS18B20ReadScratchpad();
    switch (DS18B20LastError) {
        case DS18B20OperationOK: {
            AddTask(DS18B20ConvertTemperatureTask, DS18B20ReadScratchpadSuccessfullyDelay - DS18B20ConvertTemperatureDelay);
            break;
        }
        case DS18B20ScratchpadReadError: {
            AddTask(DS18B20WriteScratchpadTask, DS18B20ReadScratchpadErrorDelay);
            break;
        }
        default: {
            AddTask(DS18B20WriteScratchpadTask, DS18B20PresencePulseNotDetectedDelay);
            break;
        }
    }
}

void DS18B20RemoveAllTasks() {
    RemoveTask(DS18B20WriteScratchpadTask);
    RemoveTask(DS18B20ConvertTemperatureTask);
    RemoveTask(DS18B20ReadScratchpadTask);
}
