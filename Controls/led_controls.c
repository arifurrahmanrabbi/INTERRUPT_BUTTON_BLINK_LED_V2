#include "main.h"
#include "led_controls.h"

void toggle_led(void)
{ 
    HAL_GPIO_TogglePin(RED_LED_GPIO_Port, RED_LED_Pin);
    HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin);
}

void led_reinit(uint8_t PinState)
{
  HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, PinState == ON ? GPIO_PIN_SET : GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, GPIO_PIN_RESET);
}

void StartStopTimer(uint8_t TimerState, TIM_HandleTypeDef *htim16)
{
  if (TimerState == ON)
  {
    __HAL_TIM_CLEAR_IT(htim16, TIM_IT_UPDATE);
    HAL_TIM_Base_Start_IT(htim16);
    htim16->Instance->CNT = 0;
  }
  else
  {
    HAL_TIM_Base_Stop_IT(htim16);
  }
}