#define PERIPH_BASE     0x40000000UL
#define APB2PERIPH_BASE (PERIPH_BASE + 0x10000UL)
#define AHBPERIPH_BASE  (PERIPH_BASE + 0x20000UL)

#define RCC_BASE        (AHBPERIPH_BASE + 0x1000UL)
#define GPIOA_BASE      (APB2PERIPH_BASE + 0x0800UL)

#define RCC_APB2ENR     (*(volatile unsigned int *)(RCC_BASE + 0x18))
#define GPIOA_CRL       (*(volatile unsigned int *)(GPIOA_BASE + 0x00))
#define GPIOA_CRH       (*(volatile unsigned int *)(GPIOA_BASE + 0x04))
#define GPIOA_ODR       (*(volatile unsigned int *)(GPIOA_BASE + 0x0C))

#define RCC_IOPAEN      (1 << 2)

void delay(volatile unsigned int time)
{
    while (time--)
    {
        __asm__("nop");
    }
}

int main(void)
{
    RCC_APB2ENR |= RCC_IOPAEN;
    GPIOA_CRH &= ~(0xF << 20);
    GPIOA_CRH |=  (0x2 << 20);

    while (1)
    {
        GPIOA_ODR ^= (1 << 13);
        delay(18000000);
    }
}
