#include "Thermistor.h"

class Heater
{    
    protected:
    enum HeaterStates { HEATER_HEATING, HEATER_IDLE };

    enum HeaterStatus {
        MachineOff = 1,
        InvalidResponse = 2,
        ThermistorDisconnected = 4
    };

    int temp_pv;
    int temp_sv;
    long next_manage_time;
    unsigned char status;
    unsigned char heater_pin;
    enum HeaterStates heater_state;

    virtual int read_thermistor() = 0;

    public:
    Heater(unsigned char _heater_pin)
    {
        heater_pin = _heater_pin;
        temp_pv = 0;
        temp_sv = 0;
        status = MachineOff;
        heater_state = HEATER_IDLE;
    }

    void manage()
    {
        if ((signed long) (millis() - next_manage_time) >= 0)
        {
            next_manage_time = millis() + 16; /* Manage temperature every 16ms, ~64Hz */
          
            /* Make sure we know what our temp is. */
            temp_pv = this->read_thermistor();
            
            if (status != 0) /* Machine off */
            {
                analogWrite(heater_pin, 0);
                heater_state = HEATER_IDLE;
                return;
            }

            if (temp_pv < temp_sv)
            {
                analogWrite(heater_pin, 255);
                heater_state = HEATER_HEATING;
            }
            else
            {
                analogWrite(heater_pin, 75);
                heater_state = HEATER_IDLE;
            }
        }
    }

    virtual void init()
    {
        /* Don't config Thermistor Pin. It's analog pin! */
        pinMode(heater_pin, OUTPUT);
        analogWrite(heater_pin, LOW);

        next_manage_time = millis();
    }

    virtual void turnOff()
    {
        digitalWrite(heater_pin, LOW);
        status |= MachineOff;
    }

    virtual void turnOn()
    {
        status = 0;
    }

    unsigned char isHeaterOn()
    {
        return heater_state == HEATER_HEATING;
    }

    int getPV()
    {
        return temp_pv;
    }

    int getSV()
    {
        return temp_sv;
    }

    void setSV(int t)
    {
        temp_sv = t;
    }
};

class ThermistorHeater : public Heater
{
    private:
    unsigned char thermistor_pin;

    static int sample_temperature(unsigned char pin)
    {
        int raw = 0;

        // read in a certain number of samples
        for (byte i=0; i<TEMPERATURE_SAMPLES; i++)
            raw += analogRead(pin);

        // average the samples
        raw = raw / TEMPERATURE_SAMPLES;

        // send it back.
        return raw;
    }

    protected:
    virtual int read_thermistor()
    {
      int raw = sample_temperature(thermistor_pin);
    
      int celsius = 0;
      char i;
    
      for (i=1; i<NUMTEMPS; i++)
      {
        if (temptable[i][0] > raw)
        {
          celsius  = temptable[i-1][1] + 
            (raw - temptable[i-1][0]) * 
            (temptable[i][1] - temptable[i-1][1]) /
            (temptable[i][0] - temptable[i-1][0]);
    
          if (celsius > 300)
            celsius = 300; 
    
          break;
        }
      }
    
      // Overflow: We just clamp to 0 degrees celsius
      if (i == NUMTEMPS)
        celsius = 0;
    
      return celsius;
    }

    public:
    ThermistorHeater(unsigned char _thermistor_pin, unsigned char _heater_pin) : Heater(_heater_pin)
    {
        thermistor_pin = _thermistor_pin;
    }
};

