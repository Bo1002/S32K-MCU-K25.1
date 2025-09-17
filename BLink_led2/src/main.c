#include <stdint.h>

// PCC
#define PCC_BASE        (0x40065000u)
#define PCC_PORTD       (*(volatile uint32_t *)(PCC_BASE + 0x130))
#define PCC_CGC         (1u << 30)

// PORTD base (S32K1xx: 0x4004C000)
#define PORTD_BASE      (0x4004C000u)
#define PORT_PCR(n)     (*(volatile uint32_t *)(PORTD_BASE + (n)*4u))
#define PCR_MUX(v)      ((uint32_t)((v) << 8))     // bits 10:8

// GPIOD base (PTD: 0x400FF0C0)
typedef struct {
    volatile uint32_t PDOR;
    volatile uint32_t PSOR;
    volatile uint32_t PCOR;
    volatile uint32_t PTOR;
    volatile uint32_t PDIR;
    volatile uint32_t PDDR;
    volatile uint32_t PIDR;
} GPIO_Type;

#define GPIOD   ((volatile GPIO_Type *)0x400FF0C0u)

// --- LED pins on S32K144EVB ---
#define LED_BLUE_IDX    0u
#define LED_RED_IDX     15u
#define LED_GREEN_IDX   16u

#define LED_BLUE_MASK   (1u << LED_BLUE_IDX)
#define LED_RED_MASK    (1u << LED_RED_IDX)
#define LED_GREEN_MASK  (1u << LED_GREEN_IDX)


static inline void delay(volatile uint32_t n)
{
	for(uint32_t i = 0 ; i < n ; i++){}
}
static inline void led_on(uint32_t m)
{
	GPIOD->PCOR = m;
}   // active-low
static inline void led_off(uint32_t m)
{ GPIOD->PSOR = m; }

int main(void)
{
    // 1) Enable clock for PORTD (pin mux block)
    PCC_PORTD |= PCC_CGC;

    // 2) Mux PTD0/15/16 to GPIO (ALT1)
    PORT_PCR(LED_BLUE_IDX)  = PCR_MUX(1);
    PORT_PCR(LED_RED_IDX)   = PCR_MUX(1);
    PORT_PCR(LED_GREEN_IDX) = PCR_MUX(1);

    // 3) Set direction output
    GPIOD->PDDR |= (LED_BLUE_MASK | LED_RED_MASK | LED_GREEN_MASK);

    // 4) Turn all OFF initially (active-low → write 1 to PSOR)
    led_off(LED_BLUE_MASK | LED_RED_MASK | LED_GREEN_MASK);

    while (1) {
        led_on(LED_BLUE_MASK);  delay(100000);
        led_on(LED_RED_MASK);   delay(100000);
        led_on(LED_GREEN_MASK); delay(100000);

        led_off(LED_BLUE_MASK);  delay(100000);
        led_off(LED_RED_MASK);   delay(100000);
        led_off(LED_GREEN_MASK); delay(100000);
    }
}
