#include "main.h"
#include "interrupts.h"

extern volatile PROGRAM_STATE CurState;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  //Checking if interrupt is triggered by the Button pin
  if (GPIO_Pin == BUTTON_Pin)
  {
    //We are idling at OFF state. So, we start blinking
    if (CurState == IDLE_OFF)
    {
      CurState = ON;
    }
    //We are idling at ON state. So, we stop blinking
    else if (CurState == IDLE_ON)
    {
      CurState = OFF;
    }
  }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /*
    Checking if interrupt is triggered by TIM6
    We don't toggle if we are not in the IDLE_ON state
    Checking CurState == IDLE_ON is not needed but we keep it just to be safe
  */
  if (htim->Instance == TIM6 && CurState == IDLE_ON)
  {
    CurState = TOGGLE;
  }
}
