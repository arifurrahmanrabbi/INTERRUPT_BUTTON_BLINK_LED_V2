#include "main.h"
#include "interrupts.h"

extern PROGRAM_STATE CurState;
extern volatile PROGRAM_STATE NewState;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == BUTTON_Pin)
  {
    if (CurState == IDLE_OFF)
    {
      NewState = ON;
    }
    else if (CurState == IDLE_ON)
    {
      NewState = OFF;
    }
  }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM6 && CurState == IDLE_ON)
  {
    NewState = TOGGLE;
  }
}
