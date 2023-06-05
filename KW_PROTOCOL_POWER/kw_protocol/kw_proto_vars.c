#include "kw_proto_vars.h"
#include <math.h>

kw_proto_vars_interface_t *p_vars;


typedef struct
{
  float     resolution;
  float     offset;
  float     low_level;
  float     hi_level;  
  uint32_t  packed_mask;
}
vars_param_metadata_t;


const vars_param_metadata_t setpoints_metadata[ SETPOINT_MAX ] =
{ 
  {   0.5,    0.0,    0.0,    500.0, 0x03FF },//	01h SETPOINT_OUT_VOLTAGE  = 0x01,   // Уставка номинального значения выходного напряжения
  {   0.5,    0.0,    0.0,    500.0, 0x03FF },//	02h SETPOINT_MEASURED_OUT_VOLTAGE,  //  Измеренное значение выходного напря жения для расчета калибровочных коэффициентов
  { 0.001,    0.0,    0.0,      2.0, 0x07FF },//	03h SETPOINT_CALIBRATION_FACTOR_OUT_VOLTAGE,            // Калибровочный коэффициент выходного напряжения
  {   0.1,    0.0,    0.0,     10.0, 0x007F },//	04h SETPOINT_DEVIATION_OUT_VOLTAGE,                     // Допустимое отклонение выходного напряжения от номинального значения
  {  0.01,    0.0,    0.0,    100.0, 0x3FFF },//	05h SETPOINT_OUT_CURRENT,                               // Уставка номинального значения выходного тока
  {  0.01,    0.0,    0.0,    100.0, 0x3FFF },//	06h SETPOINT_MEASURED_OUT_CURRENT_PHASE_A,              // Измеренное значение выходного тока в фазе А для расчета калибровочного коэффициента
  {  0.01,    0.0,    0.0,    100.0, 0x03FF },//	07h SETPOINT_MEASURED_OUT_CURRENT_PHASE_B,              // Измеренное значение выходного тока в фазе B для расчета калибровочного коэффициента
  {  0.01,    0.0,    0.0,    100.0, 0x03FF },//	08h SETPOINT_MEASURED_OUT_CURRENT_PHASE_C,              // Измеренное значение выходного тока в фазе C для расчета калибровочного коэффициента
  { 0.001,    0.0,    0.0,    100.0, 0x07FF },//  09h SETPOINT_CALIBRATION_FACTOR_OUT_CURRENT_PHASE_A,    // Калибровочный коэффициент выходного тока в фазе А
  { 0.001,    0.0,    0.0,    100.0, 0x07FF },//  0Ah SETPOINT_CALIBRATION_FACTOR_OUT_CURRENT_PHASE_B,    // Калибровочный коэффициент выходного тока в фазе B
  { 0.001,    0.0,    0.0,    100.0, 0x07FF },//  0Bh SETPOINT_CALIBRATION_FACTOR_OUT_CURRENT_PHASE_C,    // Калибровочный коэффициент выходного тока в фазе C
  {   0.1,    0.0,    0.0,  10000.0, 0x3FFF },//  0Ch SETPOINT_OUT_FREQUENCY,                             // Уставка номинального значения частоты выходного напряжения
  {   0.1,    0.0,    0.0,      3.0, 0x003F },//  0Dh SETPOINT_DEVIATION_OUT_FREQUENCY,                   // Допустимое отклонение частоты выходного напряжения от номинального значения
  { 0.001,    0.0,    0.0,      1.0, 0x03FF },//	0Eh SETPOINT_OUT_COS_MAX,                               // Уставка максимального значения cosφ на выходе ИБП
  {   1.0,    0.0,    0.0,  65000.0, 0xFFFF },//	0Fh SETPOINT_OUT_POWER,                                 // Уставка номинального значения выходной мощности
  {   1.0,    0.0,    0.0,  60000.0, 0xFFFF },//  10h SETPOINT_TIME_EXCEED_100_PERCENT_OUT_POWER,         // Допустимое время превышения 100% выходной мощности
  {   1.0,    0.0,  100.0,    200.0, 0x00FF },//	+11h SETPOINT_FIRST_THRESHHOLD_OUT_POWER,                // Первый порог превышения выходной мощности в %
  {   1.0,    0.0,    0.0,  60000.0, 0xFFFF },//	12h SETPOINT_TIME_EXCEED_FIRST_THRESHHOLD_OUT_POWER,    // Допустимое время превышения первого порога выходной мощности
  {   1.0,    0.0,  100.0,    200.0, 0x00FF },//  +13h SETPOINT_SECOND_THRESHHOLD_OUT_POWER,               // Второй порог превышения выходной мощности в %
  {   1.0,    0.0,    0.0,  60000.0, 0xFFFF },//  14h SETPOINT_TIME_EXCEED_SECOND_THRESHHOLD_OUT_POWER,   // Допустимое время превышения второго порога выходной мощности
  {  0.01,    0.0,    0.0,    300.0, 0x7FFF },//  15h SETPOINT_OUT_PEAK_CURRENT,                          // Уставка максимального пикового выходного тока
  {   0.1,    0.0,    0.0,    100.0, 0x03FF },//  16h SETPOINT_OUT_SHORT_CIRCUT_CURRENT,                  // Уставка тока короткого замыкания в режиме BYPASS (по умолчанию 16 А)
  {   1.0,    0.0,    0.0,    150.0, 0x00FF },//  +17h SETPOINT_COOLER_KKM_MAX_TEMP,                       // Уставка максимальной температуры охладителя ККМ
  {   1.0,    0.0,    0.0,    150.0, 0x00FF },//  +18h SETPOINT_COOLER_INVERTER_MAX_TEMP,                  // Уставка максимальной температуры охладителя инвертора
  {   1.0,    0.0,    0.0,    150.0, 0x00FF },//  +19h SETPOINT_BATTERY_MAX_TEMP,                          // Уставка максимальной температуры батареи
  {   1.0,    0.0,    0.0,    150.0, 0x00FF },//  +1Ah SETPOINT_INBOX_AIR_MAX_TEMP,                        // Уставка максимальной температуры воздуха внутри корпуса ИБП
  { 0.025,    0.0,    0.0,    500.0, 0x7FFF },//  1Bh SETPOINT_BATTERY_MIN_VOLTAGE,                       // Уставка минимального допустимого напряжения АКБ
  { 0.025,    0.0,    0.0,    500.0, 0x7FFF },//  1Ch SETPOINT_BATTERY_MAX_VOLTAGE,                       // Уставка максимального допустимого напряжения АКБ
  { 0.025,    0.0,    0.0,    500.0, 0x7FFF },//  1Dh SETPOINT_MEASURED_VOLTAGE_BATTERY,                  // Измеренное значение напряжения АКБ для расчета калибровочных коэффициентов
  {  0.01,    0.0,    0.0,     10.0, 0x03FF },//  1Eh SETPOINT_TEMP_COEFFICIENT_BATTERY,                  // Температурный коэффициент АКБ
  { 0.025,    0.0,    0.0,    100.0, 0x0FFF },//  1Fh SETPOINT_MAX_DISCHARGE_CURRENT_BATTERY,             // Уставка максимального тока разряда АКБ
  { 0.025,    0.0,    0.0,    100.0, 0x0FFF },//  20h SETPOINT_MAX_CHARGE_CURRENT_BATTERY,                // Уставка максимального тока заряда АКБ
  { 0.025,    0.0,    0.0,    100.0, 0x0FFF },//  21h SETPOINT_MIN_CHARGE_CURRENT_BATTERY,                //Уставка минимального тока заряда АКБ
  { 0.025,    0.0,    0.0,    500.0, 0x7FFF },//  22h SETPOINT_VOLTAGE_CHARGE_BATTERY_CYCLIC_MODE,        // Уставка напряжения заряда АКБ в циклическом режиме 
  { 0.025,    0.0,    0.0,    500.0, 0x7FFF },//  23h SETPOINT_VOLTAGE_CHARGE_BATTERY_BUFFER_MODE,        // Уставка напряжения заряда АКБ в буферном режиме 	
  { 0.025,    0.0,    0.0,    100.0, 0x0FFF },//  24h SETPOINT_MEASURED_CHARGE_CURRENT_BATTERY,           // Измеренное значение тока заряда АКБ для расчета калибровочных коэффициентов
  { 0.001,    0.0,    0.0,      2.0, 0x07FF },//  25h SETPOINT_CALIBRATION_FACTOR_CHARGE_CURRENT_BATTERY, // Калибровочный коэффициент тока заряда АКБ
  { 0.025,    0.0,    0.0,    500.0, 0x7FFF },//  26h SETPOINT_MEASURED_CHARGE_VOLTAGE_BATTERY,           // Измеренное значение напряжения заряда АКБ для расчета калибровочных коэффициентов
  { 0.001,    0.0,    0.0,      2.0, 0x07FF },//  27h SETPOINT_CALIBRATION_FACTOR_CHARGE_VOLTAGE_BATTERY, // Калибровочный коэффициент напряжения заряда АКБ
  {   0.1,    0.0,    0.0,   2000.0, 0x7FFF },//  28h SETPOINT_CAPACITY_BATTERY,                          // Номинальная ёмкость АКБ
  {   0.5,    0.0,    0.0,    500.0, 0x03FF },//  29h SETPOINT_IN_VOLTAGE_HI_THRESHHOLD,                  // Уставка верхней границы допустимого входного напряжения ИБП
  {   0.5,    0.0,    0.0,    500.0, 0x03FF },//  2Ah SETPOINT_IN_VOLTAGE_LOW_THRESHHOLD,                 // Уставка нижней границы допустимого входного напряжения ИБП
  {   1.0,    0.0,    0.0,     10.0, 0x000F },//  2Bh SETPOINT_IN_VOLTAGE_UNBALANCE_COEFFICIENT,          // Коэффициент несимметрии по входному напряжению
  {   0.1,    0.0,    0.0,    100.0, 0x03FF },//  2Ch SETPOINT_IN_CURRENT_MAX,                            // Уставка максимального значения входного тока ИБП
  {   1.0,    0.0,    0.0,     10.0, 0x000F },//  2Dh SETPOINT_IN_CURRENT_UNBALANCE_COEFFICIENT,          // Коэффициент несимметрии по входному току
  {   1.0,    0.0,    0.0,    200.0, 0x00FF },//  +2Eh SETPOINT_IN_FREQUENCY_HI_THRESHHOLD,                // Уставка верхней границы допустимой частоты входного напряжения, % от номинального значения
  {   1.0,    0.0,    0.0,    200.0, 0x00FF },//  +2Fh SETPOINT_IN_FREQUENCY_LOW_THRESHHOLD,               // Уставка нижней границы допустимой частоты входного напряжения, % от номинального значения
  {   0.5,    0.0,    0.0,    500.0, 0x03FF },//  30h SETPOINT_MIDDLE_VOLTAGE,                            // Уставка номинального значения напряжения промежуточной шины постоянного тока
  {   1.0,    0.0,    0.0,  20000.0, 0x7FFF },//  31h SETPOINT_FUN_1_MAX_SPEED,                           // Максимальная скорость вентилятора 1
  {   1.0,    0.0,    0.0,  20000.0, 0x7FFF },//  32h SETPOINT_FUN_2_MAX_SPEED,                           // Максимальная скорость вентилятора 2
  {   1.0,    0.0,    0.0,    150.0, 0x00FF },//  +33h SETPOINT_RES_1_MAX_TEMP,                            // Уставка максимальной температуры резерв 1
  {   1.0,    0.0,    0.0,    150.0, 0x00FF },//  +34h SETPOINT_RES_2_MAX_TEMP,                            // Уставка максимальной температуры резерв 2
  {   1.0,    0.0,    0.0,    150.0, 0x00FF },//  +35h SETPOINT_RES_3_MAX_TEMP,                            // Уставка максимальной температуры резерв 3
  {   1.0,    0.0,    0.0,  20000.0, 0x7FFF },//  36h SETPOINT_FUN_RES_1_MAX_SPEED,                       // Максимальная скорость резерв 1
  {   1.0,    0.0,    0.0,  20000.0, 0x7FFF },//  37h SETPOINT_FUN_RES_2_MAX_SPEED,                       // Максимальная скорость резерв 2
  {   1.0,    0.0,    0.0,  20000.0, 0x7FFF },//  38h SETPOINT_FUN_RES_3_MAX_SPEED,                       // Максимальная скорость резерв 3
  {   1.0,    0.0,    0.0,      1.0, 0x0001 },//  39h SETPOINT_WORKING_MODE_AFTER_POWER_UP,               // Режим работы модуля ИБП после включения
  {   1.0,    0.0,    0.0,      1.0, 0x0001 },//  3Ah SETPOINT_SWITCHING_MODES_WHEN_ALARM_EVENT,          // Переход между режимами работы модуля ИБП при возникновении аварийного события 	
  {   1.0,    0.0,    0.0,      2.0, 0x0003 },//  3Bh SETPOINT_POWER_LINE_SYNC,                           // Синхронизация с входной сетью
  {   1.0,    0.0,    0.0,  60000.0, 0xFFFF },//	3Ch SETPOINT_BATTERY_RUNTIME_AS_LOW_CHARGE,             // Уставка времени работы от батареи, ниже которой уровень заряда батареи считается низким
};

const vars_param_metadata_t values_metadata[ VALUE_MAX ] =
{
  {   0.5,    0.0,    0.0,    500.0, 0x03FF },   //  VALUE_IN_1_VOLTAGE_RMS_PHASE_A   = 0,
  {   0.5,    0.0,    0.0,    500.0, 0x03FF },   //  VALUE_IN_1_VOLTAGE_RMS_PHASE_B,
  {   0.5,    0.0,    0.0,    500.0, 0x03FF },   //  VALUE_IN_1_VOLTAGE_RMS_PHASE_C,
  {   1.0,    0.0,    0.0,    360.0, 0x01FF },   //  VALUE_IN_1_VOLTAGE_PHASE_SHIFT_PHASE_A,
  {   1.0,    0.0,    0.0,    360.0, 0x01FF },   //  VALUE_IN_1_VOLTAGE_PHASE_SHIFT_PHASE_B,
  {   1.0,    0.0,    0.0,    360.0, 0x01FF },   //  VALUE_IN_1_VOLTAGE_PHASE_SHIFT_PHASE_C,
  {   1.0,    0.0,    1.0,      7.0, 0x000F },   //  VALUE_UPS_WORKING_MODE,
  {   1.0,    0.0,    0.0,      1.0, 0x0001 },   //  VALUE_ON_OFF_BUTTON_STATE,
  {   0.5,    0.0,    0.0,    500.0, 0x03FF },   //  VALUE_IN_2_VOLTAGE_RMS_PHASE_A,
  {   0.5,    0.0,    0.0,    500.0, 0x03FF },   //  VALUE_IN_2_VOLTAGE_RMS_PHASE_B,
  {   0.5,    0.0,    0.0,    500.0, 0x03FF },   //  VALUE_IN_2_VOLTAGE_RMS_PHASE_C,
  {   1.0,    0.0,    0.0,    360.0, 0x00FF },   //  VALUE_IN_2_VOLTAGE_PHASE_SHIFT_PHASE_A,
  {   1.0,    0.0,    0.0,    360.0, 0x00FF },   //  VALUE_IN_2_VOLTAGE_PHASE_SHIFT_PHASE_B,
  {   1.0,    0.0,    0.0,    360.0, 0x01FF },   //  VALUE_IN_2_VOLTAGE_PHASE_SHIFT_PHASE_C,
  {   0.5,    0.0,    0.0,    500.0, 0x03FF },   //  VALUE_IN_3_VOLTAGE_RMS_PHASE_A,
  {   0.5,    0.0,    0.0,    500.0, 0x03FF },   //  VALUE_IN_3_VOLTAGE_RMS_PHASE_B,
  {   0.5,    0.0,    0.0,    500.0, 0x03FF },   //  VALUE_IN_3_VOLTAGE_RMS_PHASE_C,
  {   1.0,    0.0,    0.0,    360.0, 0x01FF },   //  VALUE_IN_3_VOLTAGE_PHASE_SHIFT_PHASE_A,
  {   1.0,    0.0,    0.0,    360.0, 0x01FF },   //  VALUE_IN_3_VOLTAGE_PHASE_SHIFT_PHASE_B,
  {   1.0,    0.0,    0.0,    360.0, 0x01FF },   //  VALUE_IN_3_VOLTAGE_PHASE_SHIFT_PHASE_C,
  {  0.01,    0.0,    0.0,    100.0, 0x3FFF },   //  VALUE_IN_1_CURRENT_RMS_PHASE_A,
  {  0.01,    0.0,    0.0,    100.0, 0x3FFF },   //  VALUE_IN_1_CURRENT_RMS_PHASE_B,
  {  0.01,    0.0,    0.0,    100.0, 0x3FFF },   //  VALUE_IN_1_CURRENT_RMS_PHASE_C,
  {   1.0,    0.0,    0.0,  60000.0, 0xFFFF },   //  VALUE_IN_1_POWER,
  {  0.01,    0.0,    0.0,    100.0, 0x3FFF },   //  VALUE_IN_2_CURRENT_RMS_PHASE_A,
  {  0.01,    0.0,    0.0,    100.0, 0x3FFF },   //  VALUE_IN_2_CURRENT_RMS_PHASE_B,
  {  0.01,    0.0,    0.0,    100.0, 0x3FFF },   //  VALUE_IN_2_CURRENT_RMS_PHASE_C,
  {   1.0,    0.0,    0.0,  60000.0, 0xFFFF },   //  VALUE_IN_2_POWER,
  {  0.01,    0.0,    0.0,    100.0, 0x3FFF },   //  VALUE_IN_3_CURRENT_RMS_PHASE_A,
  {  0.01,    0.0,    0.0,    100.0, 0x3FFF },   //  VALUE_IN_3_CURRENT_RMS_PHASE_B,
  {  0.01,    0.0,    0.0,    100.0, 0x3FFF },   //  VALUE_IN_3_CURRENT_RMS_PHASE_C,
  {   1.0,    0.0,    0.0,  60000.0, 0xFFFF },   //  VALUE_IN_3_POWER,
  {   0.1,    0.0,    0.0,   1000.0, 0x3FFF },   //  VALUE_IN_1_FREQUENCY_PHASE_A,
  {   0.1,    0.0,    0.0,   1000.0, 0x3FFF },   //  VALUE_IN_1_FREQUENCY_PHASE_B,
  {   0.1,    0.0,    0.0,   1000.0, 0x3FFF },   //  VALUE_IN_1_FREQUENCY_PHASE_C,
  {   0.1,    0.0,    0.0,   1000.0, 0x3FFF },   //  VALUE_IN_2_FREQUENCY_PHASE_A,
  {   0.1,    0.0,    0.0,   1000.0, 0x3FFF },   //  VALUE_IN_2_FREQUENCY_PHASE_B,
  {   0.1,    0.0,    0.0,   1000.0, 0x3FFF },   //  VALUE_IN_2_FREQUENCY_PHASE_C,
  {   0.1,    0.0,    0.0,   1000.0, 0x3FFF },   //  VALUE_IN_3_FREQUENCY_PHASE_A,
  {   0.1,    0.0,    0.0,   1000.0, 0x3FFF },   //  VALUE_IN_3_FREQUENCY_PHASE_B,
  {   0.1,    0.0,    0.0,   1000.0, 0x3FFF },   //  VALUE_IN_3_FREQUENCY_PHASE_C,
  {   1.0,    0.0,    0.0, 4000000000.0, 0xFFFFFFFF },   //  VALUE_IN_LINES_BAD_STATES_COUNT,
  {   1.0,    0.0,    1.0,      3.0, 0x0003 },   //  VALUE_IN_LINES_NUMBERS,
  {   0.5,    0.0,    0.0,    500.0, 0x03FF },   //  VALUE_OUT_1_VOLTAGE_RMS_PHASE_A,
  {   0.5,    0.0,    0.0,    500.0, 0x03FF },   //  VALUE_OUT_1_VOLTAGE_RMS_PHASE_B,
  {   0.5,    0.0,    0.0,    500.0, 0x03FF },   //  VALUE_OUT_1_VOLTAGE_RMS_PHASE_C,
  {   1.0,    0.0,    0.0,  60000.0, 0xFFFF },   //  VALUE_OUT_1_POWER,
  {   1.0,    0.0,    0.0,    200.0, 0x00FF },   //  VALUE_OUT_1_PERCENT,
  {   0.5,    0.0,    0.0,    500.0, 0x03FF },   //  VALUE_OUT_2_VOLTAGE_RMS_PHASE_A,
  {   0.5,    0.0,    0.0,    500.0, 0x03FF },   //  VALUE_OUT_2_VOLTAGE_RMS_PHASE_B,
  {   0.5,    0.0,    0.0,    500.0, 0x03FF },   //  VALUE_OUT_2_VOLTAGE_RMS_PHASE_C,
  {   1.0,    0.0,    0.0,  60000.0, 0xFFFF },   //  VALUE_OUT_2_POWER,
  {   1.0,    0.0,    0.0,    200.0, 0x00FF },   //  VALUE_OUT_2_PERCENT,
  {   0.5,    0.0,    0.0,    500.0, 0x03FF },   //  VALUE_OUT_3_VOLTAGE_RMS_PHASE_A,
  {   0.5,    0.0,    0.0,    500.0, 0x03FF },   //  VALUE_OUT_3_VOLTAGE_RMS_PHASE_B,
  {   0.5,    0.0,    0.0,    500.0, 0x03FF },   //  VALUE_OUT_3_VOLTAGE_RMS_PHASE_C,
  {   1.0,    0.0,    0.0,  60000.0, 0xFFFF },   //  VALUE_OUT_3_POWER,
  {   1.0,    0.0,    0.0,    200.0, 0x00FF },   //  VALUE_OUT_3_PERCENT,
  {  0.01,    0.0,    0.0,    100.0, 0x3FFF },   //  VALUE_OUT_1_CURRENT_RMS_PHASE_A,
  {  0.01,    0.0,    0.0,    100.0, 0x3FFF },   //  VALUE_OUT_1_CURRENT_RMS_PHASE_B,
  {  0.01,    0.0,    0.0,    100.0, 0x3FFF },   //  VALUE_OUT_1_CURRENT_RMS_PHASE_C,
  {  0.01,    0.0,    0.0,    100.0, 0x3FFF },   //  VALUE_OUT_2_CURRENT_RMS_PHASE_A,
  {  0.01,    0.0,    0.0,    100.0, 0x3FFF },   //  VALUE_OUT_2_CURRENT_RMS_PHASE_B,
  {  0.01,    0.0,    0.0,    100.0, 0x3FFF },   //  VALUE_OUT_2_CURRENT_RMS_PHASE_C,
  {  0.01,    0.0,    0.0,    100.0, 0x3FFF },   //  VALUE_OUT_3_CURRENT_RMS_PHASE_A,
  {  0.01,    0.0,    0.0,    100.0, 0x3FFF },   //  VALUE_OUT_3_CURRENT_RMS_PHASE_B,
  {  0.01,    0.0,    0.0,    100.0, 0x3FFF },   //  VALUE_OUT_3_CURRENT_RMS_PHASE_C,
  {   0.1,    0.0,    0.0,   1000.0, 0x3FFF },   //  VALUE_OUT_FREQUENCY_PHASE_A,
  {   0.1,    0.0,    0.0,   1000.0, 0x3FFF },   //  VALUE_OUT_FREQUENCY_PHASE_B,
  {   0.1,    0.0,    0.0,   1000.0, 0x3FFF },   //  VALUE_OUT_FREQUENCY_PHASE_C,
  {   1.0,    0.0,    1.0,      7.0, 0x0007 },   //  VALUE_OUT_POWER_SOURCE,
  {   1.0,    0.0,    1.0,      3.0, 0x0003 },   //  VALUE_OUT_LINES_NUMBER,
  {   1.0,    0.0,    1.0,      6.0, 0x0007 },   //  VALUE_TEST_RESULT,
  {   1.0,    0.0,    0.0,    360.0, 0x01FF },   //  VALUE_OUT_VOLTAGE_PHASE_SHIFT_PHASE_A,
  {   1.0,    0.0,    0.0,    360.0, 0x01FF },   //  VALUE_OUT_VOLTAGE_PHASE_SHIFT_PHASE_B,
  {   1.0,    0.0,    0.0,    360.0, 0x01FF },   //  VALUE_OUT_VOLTAGE_PHASE_SHIFT_PHASE_C,
  {   0.5,    0.0,    0.0,    500.0, 0x03FF },   //  VALUE_BYPASS_1_VOLTAGE_RMS_PHASE_A,
  {   0.5,    0.0,    0.0,    500.0, 0x03FF },   //  VALUE_BYPASS_1_VOLTAGE_RMS_PHASE_B,
  {   0.5,    0.0,    0.0,    500.0, 0x03FF },   //  VALUE_BYPASS_1_VOLTAGE_RMS_PHASE_C,
  {   1.0,    0.0,    0.0,  60000.0, 0xFFFF },   //  VALUE_BYPASS_1_POWER,
  {   0.5,    0.0,    0.0,    500.0, 0x03FF },   //  VALUE_BYPASS_2_VOLTAGE_RMS_PHASE_A,
  {   0.5,    0.0,    0.0,    500.0, 0x03FF },   //  VALUE_BYPASS_2_VOLTAGE_RMS_PHASE_B,
  {   0.5,    0.0,    0.0,    500.0, 0x03FF },   //  VALUE_BYPASS_2_VOLTAGE_RMS_PHASE_C,
  {   1.0,    0.0,    0.0,  60000.0, 0xFFFF },   //  VALUE_BYPASS_2_POWER,
  {   0.5,    0.0,    0.0,    500.0, 0x03FF },   //  VALUE_BYPASS_3_VOLTAGE_RMS_PHASE_A,
  {   0.5,    0.0,    0.0,    500.0, 0x03FF },   //  VALUE_BYPASS_3_VOLTAGE_RMS_PHASE_B,
  {   0.5,    0.0,    0.0,    500.0, 0x03FF },   //  VALUE_BYPASS_3_VOLTAGE_RMS_PHASE_C,
  {   1.0,    0.0,    0.0,  60000.0, 0xFFFF },   //  VALUE_BYPASS_3_POWER,
  {  0.01,    0.0,    0.0,    100.0, 0x3FFF },   //  VALUE_BYPASS_1_CURRENT_RMS_PHASE_A,
  {  0.01,    0.0,    0.0,    100.0, 0x3FFF },   //  VALUE_BYPASS_1_CURRENT_RMS_PHASE_B,
  {  0.01,    0.0,    0.0,    100.0, 0x3FFF },   //  VALUE_BYPASS_1_CURRENT_RMS_PHASE_C,
  {  0.01,    0.0,    0.0,    100.0, 0x3FFF },   //  VALUE_BYPASS_2_CURRENT_RMS_PHASE_A,
  {  0.01,    0.0,    0.0,    100.0, 0x3FFF },   //  VALUE_BYPASS_2_CURRENT_RMS_PHASE_B,
  {  0.01,    0.0,    0.0,    100.0, 0x3FFF },   //  VALUE_BYPASS_2_CURRENT_RMS_PHASE_C,
  {  0.01,    0.0,    0.0,    100.0, 0x3FFF },   //  VALUE_BYPASS_3_CURRENT_RMS_PHASE_A,
  {  0.01,    0.0,    0.0,    100.0, 0x3FFF },   //  VALUE_BYPASS_3_CURRENT_RMS_PHASE_B,
  {  0.01,    0.0,    0.0,    100.0, 0x3FFF },   //  VALUE_BYPASS_3_CURRENT_RMS_PHASE_C,
  {  0.1,    0.0,    0.0,   1000.0, 0x3FFF },   //  VALUE_BYPASS_FREQUENCY_PHASE_A,
  {  0.1,    0.0,    0.0,   1000.0, 0x3FFF },   //  VALUE_BYPASS_FREQUENCY_PHASE_B,
  {  0.1,    0.0,    0.0,   1000.0, 0x3FFF },   //  VALUE_BYPASS_FREQUENCY_PHASE_C,
  {   1.0,    0.0,    1.0,      3.0, 0x0003 },   //  VALUE_BYPASS_LINES_NUMBER,
  {   1.0,    0.0,    0.0,    360.0, 0x01FF },   //  VALUE_BYPASS_VOLTAGE_PHASE_SHIFT_PHASE_A,
  {   1.0,    0.0,    0.0,    360.0, 0x01FF },   //  VALUE_BYPASS_VOLTAGE_PHASE_SHIFT_PHASE_B,
  {   1.0,    0.0,    0.0,    360.0, 0x01FF },   //  VALUE_BYPASS_VOLTAGE_PHASE_SHIFT_PHASE_C,
  {  0.01,    0.0,    0.0,    100.0, 0x3FFF },   //  VALUE_INVERTER_CURRENT_RMS_PHASE_A,
  {  0.01,    0.0,    0.0,    100.0, 0x3FFF },   //  VALUE_INVERTER_CURRENT_RMS_PHASE_B,
  {  0.01,    0.0,    0.0,    100.0, 0x3FFF },   //  VALUE_INVERTER_CURRENT_RMS_PHASE_C,
  {   0.5,    0.0,    0.0,    500.0, 0x03FF },   //  VALUE_MIDDLE_BUS_POSITIVE_VOLTAGE,
  {   0.5,    0.0,    0.0,    500.0, 0x03FF },   //  VALUE_MIDDLE_BUS_NEGATIVE_VOLTAGE,
  {   1.0,    0.0,    0.0,    360.0, 0x01FF },   //  VALUE_OUT_CURRENT_PHASE_SHIFT_PHASE_A,
  {   1.0,    0.0,    0.0,    360.0, 0x01FF },   //  VALUE_OUT_CURRENT_PHASE_SHIFT_PHASE_B,
  {   1.0,    0.0,    0.0,    360.0, 0x01FF },   //  VALUE_OUT_CURRENT_PHASE_SHIFT_PHASE_C,
  {   0.5,    0.0,    0.0,    500.0, 0x03FF },   //  VALUE_INVERTER_VOLTAGE_RMS_PHASE_A, +++++++++++++ нет в протоколе
  {   0.5,    0.0,    0.0,    500.0, 0x03FF },   //  VALUE_INVERTER_VOLTAGE_RMS_PHASE_B,+++++++++++++ нет в протоколе
  {   0.5,    0.0,    0.0,    500.0, 0x03FF },   //  VALUE_INVERTER_VOLTAGE_RMS_PHASE_C,+++++++++++++ нет в протоколе
  { 0.025,    0.0,    0.0,    500.0, 0x7FFF },   //  VALUE_BATTERY_VOLTAGE,
  {  0.01,  100.0, -100.0,    100.0, 0x7FFF },   //  VALUE_BATTERY_CURRENT,
  { 0.025,    0.0,    0.0,    500.0, 0x7FFF },   //  VALUE_CHARGER_VOLTAGE,
  {  0.01,    0.0,    0.0,    100.0, 0x7FFF },   //  VALUE_CHARGER_CURRENT,
  {   1.0,    0.0,    0.0,    100.0, 0x007F },   //  VALUE_BATTERY_CHARGE_PERCENT,
  {   1.0,    0.0,    0.0, 130000.0,0x1FFFF },   //  VALUE_BATTERY_REMAINING_TIME,
  {   1.0,    0.0,    0.0,  60000.0, 0xFFFF },   //  VALUE_BATTERY_WORKING_TIME,
  {   1.0,    0.0,    1.0,      4.0, 0x0007 },   //  VALUE_BATTERY_STATUS,
  {   1.0,   60.0,  -60.0,    150.0, 0x00FF },   //  VALUE_KKM_COOLER_TEMPERATURE,
  {   1.0,   60.0,  -60.0,    150.0, 0x00FF },   //  VALUE_INTO_UPS_AIR_TEMPERATURE,
  {   1.0,   60.0,  -60.0,    150.0, 0x00FF },   //  VALUE_BATTERY_TEMPERATURE,
  {   1.0,   60.0,  -60.0,    150.0, 0x00FF },   //  VALUE_INVERTER_COOLER_TEMPERATURE,
  {   1.0,   60.0,  -60.0,    150.0, 0x00FF },   //  VALUE_RESERVE_1_TEMPERATURE,
  {   1.0,   60.0,  -60.0,    150.0, 0x00FF },   //  VALUE_RESERVE_2_TEMPERATURE,
  {   1.0,   60.0,  -60.0,    150.0, 0x00FF },   //  VALUE_RESERVE_3_TEMPERATURE,
  {   1.0,    0.0,    0.0,  20000.0, 0x7FFF },   //  VALUE_FUN_1_SPEED,
  {   1.0,    0.0,    0.0,  20000.0, 0x7FFF },   //  VALUE_FUN_2_SPEED,
  {   1.0,    0.0,    0.0,  20000.0, 0x7FFF },   //  VALUE_FUN_RES1_SPEED,
  {   1.0,    0.0,    0.0,  20000.0, 0x7FFF },   //  VALUE_FUN_RES2_SPEED,
  {   1.0,    0.0,    0.0,  20000.0, 0x7FFF },   //  VALUE_FUN_RES3_SPEED,  
};



uint32_t kw_proto_vars_pack_setpoint( ENUM_SETPOINT_NAME setpoint_name )
{
  value_pack_t val;
  uint32_t result;

  const vars_param_metadata_t *p_param = &setpoints_metadata[ ( ( uint32_t )setpoint_name - 1 ) ];
  
  p_vars->vars_get_setpoint( setpoint_name, &val );

  if( p_param->resolution == 1.0F )
  {
    // целое
    result = ( uint32_t )( val.val_int );
  } 
  else
  { // float
    result = ( uint32_t )( round( val.val_float / p_param->resolution ) );    
  }
    
  return result; 
}

int32_t kw_proto_vars_unpack_setpoint( ENUM_SETPOINT_NAME setpoint_name, uint32_t packed_value )
{
  value_pack_t val;

  const vars_param_metadata_t *p_param = &setpoints_metadata[ ( ( uint32_t )setpoint_name - 1 ) ];


  packed_value &= p_param->packed_mask;
  val.val_float = ( packed_value * p_param->resolution );

  // проверка на диапазон
  if( ( val.val_float < p_param->low_level ) || ( val.val_float > p_param->hi_level ) )
  {
    return -1;
  }

  if( p_param->resolution == 1.0F )
  {
    // целое
    val.val_int = ( packed_value & p_param->packed_mask );
  }

  p_vars->vars_set_setpoint( setpoint_name, val );

  return 0;
}

uint32_t kw_proto_vars_pack_value( ENUM_VALUE_NAME value_name )
{
  value_pack_t val;
  uint32_t result;

  const vars_param_metadata_t *p_param = &values_metadata[ ( ( uint32_t )value_name ) ];
  
  p_vars->vars_get_value( value_name, &val );

  if( p_param->resolution == 1.0F )
  {
    // целое
    result = ( uint32_t )( val.val_int );
  } 
  else
  { // float
    result = ( uint32_t )( round( val.val_float / p_param->resolution ) );    
  }
    
  return result; 
}

int32_t kw_proto_vars_unpack_value( ENUM_VALUE_NAME value_name, uint32_t packed_value )
{
  value_pack_t val;

  const vars_param_metadata_t *p_param = &values_metadata[ ( uint32_t )value_name ];

  packed_value &= p_param->packed_mask;
  val.val_float = ( packed_value * p_param->resolution );

  if( p_param->offset != 0.0F )
  {
    val.val_float -= p_param->offset;    
  }

  // проверка на диапазон
  if( ( val.val_float < p_param->low_level ) || ( val.val_float > p_param->hi_level ) )
  {
    return -1;
  }


  if( p_param->resolution == 1.0F )
  {
    // целое
    val.val_int = (int)val.val_float;
  }

  p_vars->vars_set_value( value_name, val );

  return 0;
}


