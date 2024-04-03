#ifndef _AIR_GRADIENT_H_
#define _AIR_GRADIENT_H_

#include "Display/Display.h"
#include "Main/BoardDef.h"
#include "Main/HardwareWatchdog.h"
#include "Main/LedBar.h"
#include "Main/PushButton.h"
#include "Main/StatusLed.h"
#include "PMS/PMS5003.h"
#include "PMS/PMS5003T.h"
#include "S8/S8.h"
#include "Sgp41/Sgp41.h"
#include "Sht/Sht.h"

/**
 * @brief RGB LED bar mode for ONE_INDOOR board
 */
enum LedBarMode {
  /** Don't use LED bar */
  LedBarModeOff,

  /** Use LED bar for show PM2.5 value level */
  LedBarModePm,

  /** Use LED bar for show CO2 value level */
  LedBarModeCO2,
};

enum ConfigurationControl {
  /** Allow set configuration from local over device HTTP server */
  ConfigurationControlLocal,

  /** Allow set configuration from Airgradient cloud */
  ConfigurationControlCloud,

  /** Allow set configuration from Local and Cloud */
  ConfigurationControlBoth
};

enum AgFirmwareMode {
  FW_MODE_I_9PSL, /** ONE_INDOOR */
  FW_MODE_O_1PST, /** PMS5003T, S8 and SGP41 */
  FW_MODE_O_1PPT, /** PMS5003T_1, PMS5003T_2, SGP41 */
  FW_MODE_O_1PP,  /** PMS5003T_1, PMS5003T_2 */
  FW_MDOE_O_1PS   /** PMS5003T, S8 */
};
const char* AgFirmwareModeName(AgFirmwareMode mode);

/**
 * @brief Class with define all the sensor has supported by Airgradient. Each
 * sensor usage must be init before use.
 */
class AirGradient {
public:
  AirGradient(BoardType type);

  /**
   * @brief Plantower PMS5003 sensor
   */
  PMS5003 pms5003;
  /**
   * @brief Plantower PMS5003T sensor: connect to PM1 connector on
   * OPEN_AIR_OUTDOOR.
   */
  PMS5003T pms5003t_1;
  /**
   * @brief Plantower PMS5003T sensor: connect to PM2 connector on
   * OPEN_AIR_OUTDOOR.
   */
  PMS5003T pms5003t_2;

  /**
   * @brief SenseAirS8 CO2 sensor
   */
  S8 s8;

  /**
   * @brief Temperature and humidity sensor supported SHT3x and SHT4x
   *
   */
  Sht sht;

  /**
   * @brief  SGP41 TVOC and NOx sensor
   *
   */
  Sgp41 sgp41;

  /**
   * @brief OLED Display
   *
   */
  Display display;

  /**
   * @brief Push Button
   */
  PushButton button;

  /**
   * @brief LED
   */
  StatusLed statusLed;

  /**
   * @brief RGB LED array
   *
   */
  LedBar ledBar;

  /**
   * @brief External hardware watchdog
   */
  HardwareWatchdog watchdog;

  /**
   * @brief Get I2C SDA pin has of board supported
   *
   * @return int Pin number if -1 invalid
   */
  int getI2cSdaPin(void);
  /**
   * @brief Get I2C SCL pin has of board supported
   *
   * @return int Pin number if -1 invalid
   */
  int getI2cSclPin(void);

  /**
   * @brief Get the Board Type
   *
   * @return BoardType @ref BoardType
   */
  BoardType getBoardType(void);

  /**
   * @brief Get the library version string
   *
   * @return String
   */
  String getVersion(void);

  /**
   * @brief Get the Board Name object
   *
   * @return String
   */
  String getBoardName(void);

  /**
   * @brief Round double value with for 2 decimal
   *
   * @param valuem Round value
   * @return double
   */
  double round2(double value);

private:
  BoardType boardType;
};

#include "AgConfigure.h"
#include "AgApiClient.h"
#include "AgSchedule.h"
#include "MqttClient.h"
#include "AgStateMachine.h"

#endif /** _AIR_GRADIENT_H_ */
