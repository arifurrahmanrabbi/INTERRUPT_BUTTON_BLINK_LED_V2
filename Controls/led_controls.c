#include "main.h"
#include "led_controls.h"

void toggle_led(void)
{
    HAL_GPIO_TogglePin(RED_LED_GPIO_Port, RED_LED_Pin);
    HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin);
}

void led_reinit(uint8_t PinState)
{
  /*
    Red LED is ON/OFF depending on current program state
    Green LED is always OFF
  */
  HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, PinState == ON ? GPIO_PIN_SET : GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, GPIO_PIN_RESET);
}

void StartStopTimer(uint8_t TimerState, TIM_HandleTypeDef *htim6)
{
  if (TimerState == ON)
  {
    //Clears interrupt, otherwise interrupt is triggered instantly
    __HAL_TIM_CLEAR_IT(htim6, TIM_IT_UPDATE);
    //Starts the interrupt
    HAL_TIM_Base_Start_IT(htim6);
    //Reset CNT, otherwise starts from previous CNT value causing early toggle for the first time
    htim6->Instance->CNT = 0;
  }
  else
  {
    //Stops the interrupt
    HAL_TIM_Base_Stop_IT(htim6);
  }
}