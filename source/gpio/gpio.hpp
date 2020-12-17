// Just messing with meta programming :P

#pragma once

#include <stm32f10x.h>

namespace gpio
{
    enum class Port
    {
        A, B, C, D, E, F, G
    };

    enum class OutputSpeed
    {
        Max10MHZ,
        Max2MHZ,
        Max50MHZ
    };

    enum class OutputMode
    {
        GeneralPurposePushPull,
        GeneralPurposeOpenDrain,
        AlternateFunctionPushPull,
        AlternateFunctionOpenDrain
    };

    enum class InputMode
    {
        Analog,
        Floating,
        PullUp,
        PullDown
    };

    enum class Pin
    {
        Number0,
        Number1,
        Number2,
        Number3,
        Number4,
        Number5,
        Number6,
        Number7,
        Number8,
        Number9,
        Number10,
        Number11,
        Number12,
        Number13,
        Number14,
        Number15
    };

    enum class PinState
    {
        Reset,
        Set
    };

    namespace internal
    {
        constexpr GPIO_TypeDef * getBase(gpio::Port a_port)
        {
            switch (a_port)
            {
            case gpio::Port::A:
                return GPIOA;
            case gpio::Port::B:
                return GPIOB;
            case gpio::Port::C:
                return GPIOC;
            case gpio::Port::D:
                return GPIOD;
            case gpio::Port::E:
                return GPIOE;
            case gpio::Port::F:
                return GPIOF;
            case gpio::Port::G:
                return GPIOG;
            }
        }

        constexpr u32 getPinNumber( gpio::Pin a_pin)
        {
            return static_cast< int>( a_pin);
        }

        constexpr u32 getInputMode( gpio::InputMode a_mode)
        {
            constexpr u32 lookup[] = { 0x00U, 0x01U, 0x02U, 0x02U};

            return lookup[ static_cast< int>( a_mode)];
        }

        constexpr u32 getOutputMode( gpio::OutputMode a_mode)
        {
            constexpr u32 lookup[] = { 0x00U, 0x01U, 0x02U, 0x03U};

            return lookup[ static_cast< int>( a_mode)];
        }

        constexpr u32 getSpeed( gpio::OutputSpeed a_speed)
        {
            constexpr u32 lookup[] = { 0x01U, 0x02U, 0x03U};

            return lookup[ static_cast< int>( a_speed)];
        }

        constexpr void setPinMode(
            GPIO_TypeDef *  ap_gpio,
            u32             a_pin,
            u32             a_mode,
            u32             a_config
        )
        {
            constexpr u32 mask = 0x0FU; // Nibble mask.

            if ( a_pin < 8U) /* CRL register */
            {
                u32 temp = ap_gpio->CRL;
                temp &= ~( mask << ( a_pin * 4 ));      /* clear fields */
                temp |=  a_mode << ( a_pin * 4);        /* set MODE field */
                temp |=  a_config  << ( ( a_pin * 4) + 2); /* set CNF field */
                ap_gpio->CRL = temp;
            } 
            else /* CRH register */
            {
                a_pin -= 8U;
                u32 temp = ap_gpio->CRH;
                temp &= ~( mask << ( a_pin * 4 ));      /* clear fields */
                temp |=  a_mode << ( a_pin * 4);        /* set MODE field */
                temp |=  a_config  << ( ( a_pin * 4) + 2); /* set CNF field */
                ap_gpio->CRH = temp;
            }
        }
    }

    // Input Mode
    template <Port a_port, Pin a_pin, InputMode a_mode>
    void setPinAsInput()
    {
        GPIO_TypeDef * gpio = internal::getBase( a_port);
        u32 pin = internal::getPinNumber( a_pin);
        u32 mode = internal::getInputMode( a_mode);

        constexpr u32 InputMode = 0U;
        internal::setPinMode( gpio, pin, InputMode, mode);
    }

    template <Port a_port, Pin a_pin>
    bool getInputPinValue()
    {
        GPIO_TypeDef * gpio = internal::getBase( a_port);
        u32 pin = internal::getPinNumber( a_pin);

        u32 result = ( gpio->IDR  >> pin) & 0x1U;

        if ( result)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    // Output Mode
    template <Port a_port, Pin a_pin, OutputSpeed a_speed, OutputMode a_mode>
    void setPinAsOutput()
    {
        GPIO_TypeDef * gpio = internal::getBase( a_port);
        u32 pin = internal::getPinNumber( a_pin);
        u32 speed = internal::getSpeed( a_speed);
        u32 mode = internal::getOutputMode( a_mode);

        internal::setPinMode( gpio, pin, speed, mode);
    }

    template <Port a_port, Pin a_pin>
    void setOutputPin()
    {
        GPIO_TypeDef * gpio = internal::getBase( a_port);
        u32 pin = internal::getPinNumber( a_pin);

        gpio->BSRR = ( 1U << pin);
    }

    template <Port a_port, Pin a_pin>
    void clearOutputPin()
    {
        GPIO_TypeDef * gpio = internal::getBase( a_port);
        u32 pin = internal::getPinNumber( a_pin);

        gpio->BRR = ( 1U << pin);
    }

    template <Port a_port, Pin a_pin>
    bool getOutputPinValue()
    {
        GPIO_TypeDef * gpio = internal::getBase( a_port);
        u32 pin = internal::getPinNumber( a_pin);

        u32 result = ( gpio->ODR  >> pin) & 0x1U;

        if ( result)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}