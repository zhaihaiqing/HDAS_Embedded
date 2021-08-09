/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "sdmmc.h"
#include "fatfs.h"
#include "sdmmc_test.h"
#include "sdmmc_fatfs.h"
//#include "usart.h"
//#include "gpio.h"


/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void HAL_Get_CPU_RCC_Clock(void);
void CPU_CACHE_Enable(void);
void MPU_Config( void );


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
Sys_Status_type Sys_Status;

uint8_t DMAdat_flag=0;//��������ǰ�����жϣ�����ȫ������ж�



void clc_watchdog(void)
{
	HAL_GPIO_TogglePin(WDI_GPIO_Port,WDI_Pin);
}


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
uint32_t file_number=0; //�ļ����
int main(void)
{
	
	
	uint32_t i=0,j=0;
	
//	uint32_t signal_file_write_count=0;
	
	//MPU_Config();
	//CPU_CACHE_Enable();

  //HAL_Init();
  //SystemClock_Config();

  //MX_GPIO_Init();
  //MX_ADC1_Init();
  //MX_UART8_Init();
	
	log_info("[HDAS]Base Hardware Init OK!\r\n");
	
  MX_SDMMC2_SD_Init();
	clc_watchdog();
	MX_FATFS_Init();
	clc_watchdog();
	
	MX_DMA_Init();
  MX_TIM2_Init(AD7606_SAMPLE_RATE,50);
  MX_FMC_Init();
	clc_watchdog();
	
	HAL_Get_CPU_RCC_Clock();
	
	rt_thread_mdelay(100);
	clc_watchdog();
	
	Get_CardInfo();
	clc_watchdog();
	
//SD_EraseTest(); 
//SD_Write_Read_Test();
	//Fatfa_GetFree();
	
		//Fatfs_RW_test();
		
		
		
		
	//Fatfs_RW_test2();
	//rt_thread_mdelay(5000);
		
	//�ڴ˴��жϸ����������Ƿ���������ӡ�����Ϣ
	
	clc_watchdog();
	hdas_test_thread_init();	//ִ�в��Գ���


	//hdas_thread_init();	//�����̣߳���ʼ����ϵͳ
//	rt_thread_mdelay(10);
		
		while(1)
		{
			rt_thread_mdelay(100);
		}
	
	
//  while (1)
//  {
//	  //HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
//		//�ȴ��洢�ź���
//		//DMA�����ʱ��������ռ��ǰ�벿�ֽ���sprintf�����б���
//		//DMA���ʱ��������ռ�ĺ�벿�ֽ���sprintf�����б���
//		
//		rt_sem_control(&storage_sem,RT_IPC_CMD_RESET,RT_NULL);//�ȴ��ź���
//		rt_sem_take(&storage_sem,RT_WAITING_FOREVER);
//		
//		if(DMAdat_flag==0)//DMA�������ɣ���ǰ�벿�ַ���SD������
//		{
//			sprintf_data_to_buf(0);//
//			
//		}
//		else if(DMAdat_flag==1)//DMA����ȫ��ɣ�����벿�ַ���SD��������ͬʱ�����ļ��洢
//		{
//			
//			sprintf_data_to_buf(1);
//			
//			retSD = f_write(&hdas_fil, FsWriteBuf, sizeof(FsWriteBuf), &byteswritten);	
//			f_lseek(&hdas_fil, hdas_fil.fptr);											 
//			
//			signal_file_write_count++;
//			if(signal_file_write_count==FS_WRITE_NUM)//д��������ˣ������ļ���С������328MB�����ȹر�ԭ�ļ������½��ļ�
//			{
//				signal_file_write_count=0;
//				retSD = f_close(&hdas_fil);
//				if(retSD){log_info("close error : %d\r\n",retSD);}
//				//else{log_info("close sucess!!! \r\n");}
//	
//	
//				if(Fatfa_GetFree_2()>=500)//1����ȡʣ������,��������������ļ�������1�����½�һ���ļ�
//				{
//					uint32_t len=0;
//					
//					file_number++;
//					
//					len=sprintf(hdas_filename,"hdas_data%d.txt",file_number);
//					retSD = f_open(&hdas_fil, hdas_filename, FA_CREATE_ALWAYS | FA_WRITE);
//					if(retSD) {log_info("open file error : %d\r\n",retSD);}		
//					else {log_info("Creat file:hdas_data%d.txt",file_number);}
//				}
//				else											//2�����ʣ��������������ֹͣ������ͬʱ�ر��ļ���ж��SD��
//				{
//					log_info("SD Card Available space <500MB,AD7606 Sampling has stopped,Please replace the SD card and Reset Device!!!\r\n");
//					AD7606_Stop();
//					hdas_sample_flag=0;
//				
//				
//					retSD = f_close(&hdas_fil);
//					if(retSD){log_info("close error : %d\r\n",retSD);}
//					else{log_info("close sucess!!! \r\n");}
//	
//					f_mount(NULL, "", 1);
//				}
//			}
//			
//			log_info(".");
//		}
//  }
  /* USER CODE END 3 */
}





/**
  * @brief System Clock Configuration
  * @retval None
  */
RCC_OscInitTypeDef RCC_OscInitStruct = {0};
void SystemClock_Config(void)
{
  
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);
  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
  /** Macro to configure the PLL clock source
  */
  __HAL_RCC_PLL_PLLSOURCE_CONFIG(RCC_PLLSOURCE_HSE);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 5;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void MPU_Config( void )
{
	MPU_Region_InitTypeDef MPU_InitStruct;

	/* ��ֹ MPU */
	HAL_MPU_Disable();

	/* ����AXI SRAM��MPU����ΪWrite through, read allocate��no write allocate */
	MPU_InitStruct.Enable           = MPU_REGION_ENABLE;
	MPU_InitStruct.BaseAddress      = 0x24000000;
	MPU_InitStruct.Size             = MPU_REGION_SIZE_512KB;
	MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
	MPU_InitStruct.IsBufferable     = MPU_ACCESS_NOT_BUFFERABLE;
	MPU_InitStruct.IsCacheable      = MPU_ACCESS_CACHEABLE;
	MPU_InitStruct.IsShareable      = MPU_ACCESS_NOT_SHAREABLE;
	MPU_InitStruct.Number           = MPU_REGION_NUMBER0;
	MPU_InitStruct.TypeExtField     = MPU_TEX_LEVEL0;
	MPU_InitStruct.SubRegionDisable = 0x00;
	MPU_InitStruct.DisableExec      = MPU_INSTRUCTION_ACCESS_ENABLE;

	HAL_MPU_ConfigRegion(&MPU_InitStruct);
	
	
//	/* ����FMC��չIO��MPU����ΪDevice����Strongly Ordered */
//	MPU_InitStruct.Enable           = MPU_REGION_ENABLE;
//	MPU_InitStruct.BaseAddress      = 0x60000000;
//	MPU_InitStruct.Size             = ARM_MPU_REGION_SIZE_64KB;	
//	MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
//	MPU_InitStruct.IsBufferable     = MPU_ACCESS_BUFFERABLE;
//	MPU_InitStruct.IsCacheable      = MPU_ACCESS_NOT_CACHEABLE;	/* ������MPU_ACCESS_CACHEABLE;�����2��CS��WE�ź� */
//	MPU_InitStruct.IsShareable      = MPU_ACCESS_NOT_SHAREABLE;
//	MPU_InitStruct.Number           = MPU_REGION_NUMBER1;
//	MPU_InitStruct.TypeExtField     = MPU_TEX_LEVEL0;
//	MPU_InitStruct.SubRegionDisable = 0x00;
//	MPU_InitStruct.DisableExec      = MPU_INSTRUCTION_ACCESS_ENABLE;
//	
//	HAL_MPU_ConfigRegion(&MPU_InitStruct);
	
	/* ����SRAM3������ΪWrite through, read allocate��no write allocate */
//    MPU_InitStruct.Enable           = MPU_REGION_ENABLE;
//    MPU_InitStruct.BaseAddress      = 0x38000000;
//    MPU_InitStruct.Size             = ARM_MPU_REGION_SIZE_64KB;	
//    MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
//    MPU_InitStruct.IsBufferable     = MPU_ACCESS_NOT_BUFFERABLE;
//    MPU_InitStruct.IsCacheable      = MPU_ACCESS_CACHEABLE;
//    MPU_InitStruct.IsShareable      = MPU_ACCESS_NOT_SHAREABLE;
//    MPU_InitStruct.Number           = MPU_REGION_NUMBER2;
//    MPU_InitStruct.TypeExtField     = MPU_TEX_LEVEL0;
//    MPU_InitStruct.SubRegionDisable = 0x00;
//    MPU_InitStruct.DisableExec      = MPU_INSTRUCTION_ACCESS_ENABLE;

//    HAL_MPU_ConfigRegion(&MPU_InitStruct);

	/*ʹ�� MPU */
	HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}

void CPU_CACHE_Enable(void)
{
  /* Enable I-Cache */
  SCB_EnableICache();

  /* Enable D-Cache */
  SCB_EnableDCache();
}

//void HAL_Get_CPU_RCC_Clock(void)
//{
//	log_info("[HAL_Get_CPU_RCC_Clock]HAL_RCC_SysClockFreq:%fMHz\r\n",1.0*HAL_RCC_GetSysClockFreq()/1000000);
//	log_info("[HAL_Get_CPU_RCC_Clock]HAL_RCC_HCLKFreq:%fMHz\r\n",1.0*HAL_RCC_GetHCLKFreq()/1000000);
//	log_info("[HAL_Get_CPU_RCC_Clock]HAL_RCC_PCLK1Freq:%fMHz\r\n",1.0*HAL_RCC_GetPCLK1Freq()/1000000);
//	log_info("[HAL_Get_CPU_RCC_Clock]HAL_RCC_PCLK2Freq:%fMHz\r\n",1.0*HAL_RCC_GetPCLK2Freq()/1000000);	
//}

void HAL_Get_CPU_RCC_Clock(void)
{
	log_info("[HAL_Get_CPU_RCC_Clock]HAL_RCC_SysClockFreq:%dMHz\r\n",HAL_RCC_GetSysClockFreq()/1000000);
	log_info("[HAL_Get_CPU_RCC_Clock]HAL_RCC_HCLKFreq:%dMHz\r\n",HAL_RCC_GetHCLKFreq()/1000000);
	log_info("[HAL_Get_CPU_RCC_Clock]HAL_RCC_PCLK1Freq:%dMHz\r\n",HAL_RCC_GetPCLK1Freq()/1000000);
	log_info("[HAL_Get_CPU_RCC_Clock]HAL_RCC_PCLK2Freq:%dMHz\r\n",HAL_RCC_GetPCLK2Freq()/1000000);	
}



/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  //__disable_irq();
  //while (1)
  //{
  //}
	return;
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
