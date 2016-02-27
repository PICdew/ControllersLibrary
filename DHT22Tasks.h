/** DHT22Tasks.h
 * v.1.1
 */

#ifndef DHT22TASKS_H
#define	DHT22TASKS_H

#include "Delay.h"
#include "DHT22.h"
#include "TaskManager.h"

/** Задержка до первого выполнения задачи DHT22ReadTask (в единицах T_INT, параметр - в секундах).
 */
#define DHT22ReadTaskDelay           GetTaskManagerTimerTime(0.0)

/** Задержка до повторного выполнения задачи DHT22ReadTask в случае успешного чтения данных из датчика (в единицах T_INT, параметр - в секундах).
 * Это значение равно периоду обновления влажности и температуры датчика при штатной работе и при отсутствии ошибок на шине.
 */
#define DHT22RepeatOKReadTaskDelay   GetTaskManagerTimerTime(5.0)

/** Задержка до повторного выполнения задачи DHT22ReadTask в случае ошибки при чтении данных из датчика (в единицах T_INT, параметр - в секундах).
 * Это значение равно периоду обновления влажности и температуры датчика при отсутствии датчика или при ошибке на шине.
 * При попытке обновления чаще, чем раз в одну секунду, датчик не возвращает сигнал присутствия при первом опросе после ошибки на шине (например при замыкании VDD и SDA).
 */
#define DHT22RepeatFailReadTaskDelay GetTaskManagerTimerTime(1.5)

void DHT22InitializeSensorTask();
void DHT22InitializeSensorAction();

void DHT22ReadTask();
void DHT22ReadAction();

/** Удаляет все задачи, связанные с библиотекой, из очереди диспетчера задач.
 * Хотя в один момент времени в очереди находится только одна связанная задача, для гарантированного удаления из очереди любой связанной задачи следует использовать эту функцию.
 */
void DHT22RemoveAllTasks();

#endif	/* DHT22TASKS_H */
