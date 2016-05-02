#ifndef NODE_SEWAGEPUMP_H
#define NODE_SEWAGEPUMP_H

#include "common.h"

/*
 * This class represents a module that controls a sewage pump with the following actions:
 *  - Measure distance to water with a microwave meter, report to mqtt
 *  - Measure power consumption of pump, report to mqtt
 *  - When pump is on for too long, turn it off, report on mqtt and turn it off after a set time
 *  - Report when power input is lost to mqtt (unit is battery backed)
 *
 * It is assumed that there are higher level functions that read the mqtt data
 * and alert the user with email/sms/etc.
 *
 * Accessories:
 * - ADS1115 I2C ADC on pins 0 (SCL) & 2 (SDA), comparator output on pin 12
 * - Button + Led for reset to default on pin 4
 * - Relay Normally Closed on pin 5
 * - SR04 sensor echo on pin 13
 * - SR04 sensor trigger on pin 14
 *
 * MQTT endpoints:
 * - Input:
 *   - <node>/pump_on_trigger_time (minutes)
 *   - <node>/pump_off_time (minutes)
 *   - <node>/pump_on_min_current (mA)
 * - Output:
 *   - <node>/pump_on (0/1)
 *   - <node>/pump_switched_off (0/1)
 *   - <node>/pump_current (integer mA)
 *   - <node>/input_power (0/1)
 *   - <node>/distance (int cm)
 *   - <node>/i2c_state (0 ok, non-zero i2c error)
 */

class NodeSewagePump : public NodeActuator {
  public:
    void setup(void);
    unsigned loop(void);
    void mqtt_connected_event(void);
  private:
    void mqtt_pump_on_trigger_time(char *data);
    void mqtt_pump_off_time(char *data);
    void mqtt_pump_on_min_current(char *data);

    int m_pump_on_trigger_time;
    int m_pump_off_time;
    int m_pump_on_min_current;
};

#endif
