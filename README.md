# To work on the projects assigments for the course
http://classweb.ece.umd.edu/enee447.S2021/

## project 0
The goal of this project is to get familiar with system timer. The BCM2837 system time is a memory-mapped peripheral. It features a 64-bit free-running counter that runs at 1 MHz and four separate compare registers that can be used to schedule interrupts. However for this project it would be enough to use counter register(s) only. 
The interface to the BCM2837 System Timer is a set of 32-bit memory-mapped registers beginning at physical address 0x20003000.
|Offset| Description                        |
|------|------------------------------------|
| 0x00 | System Timer control and status    |
| 0x04 | System Timer counter lower 32 bits |
| 0x08 | System Timer counter upper 32 bits |
| 0x0C | System Timer compare 0, IRQ line 0 |
| 0x10 | System Timer compare 1, IRQ line 1 |
| 0x14 | System Timer compare 2, IRQ line 2 |
| 0x18 | System Timer compare 3, IRQ line 3 |

CLO and CHI form a 64-bit free-running counter, which increases by itself at a rate of 1 MHz, that software can read to get the current number of timer ticks.

## project 2
The goal of the project is make timeout-queue. The idea is to schedule events which will be executed after some time period. The processing loop should update the queue periodically and trigger event with expired (or close to expiration) timeout. If no events to launch the processing loop update queue and wait some amount of time untill the nearest event will be ready to execute.

Scheduled events are described by structure which contain current value of timeout, repetition period (if event is periodical), pointer to callback function which will be executed when event is fired and some data passed to that function.

```
struct event {
    LL_PTRS;
    int timeout;
    int repeat_interval;
    int max_repeats;
    int arg;
    pfv_t go;
    namenum_t data;
};
```

Internally callout queue implemented with double-linked list. The elements are ordered - the lowest timeout value at the head of list.
The update pocedure of callout queue calculates the difference between the current time and time of the latest update. The difference is subtracted from timeout field of each element of queue. The function returns timeout value of the head item, i.e. the time to wait up to the nearest event.
When event is triggered it either dropped out or inserted in the list again at the place in accordance with it's timeout value (repeat interval becomes a timeout for the 2nd and next insertion).
