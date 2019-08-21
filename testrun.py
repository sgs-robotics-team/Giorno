import smart_thruster as thrusters
import threading
import time
import math

N_motors = 8
port = '/dev/ttyS3'

print("Starting motors...")
m = thrusters.start(N_motors, port)


try:
    while True:
        for id in m.motors:
            #amplitude = (len(m.motors)+1-id)*300 # RPM
            #frequency = (id+1)/20. # Hz
            #m.target_rpm[id] = int(amplitude*math.sin(2*math.pi*(id+1)*frequency*time.time()))
            m.target_rpm[id] = 500
            motor_feedback = 'Motor {:2d}: '.format(id)
            motor_feedback += "ON" if m.is_on[id] else "OFF"
            motor_feedback += '{:5d}R'.format(m.rpm[id])
            motor_feedback += '{:5.2f}A'.format(m.current[id])
            motor_feedback += '{:5.2f}V'.format(m.voltage[id])
            motor_feedback += '{:5.2f}C'.format(m.driver_temperature[id])
            motor_feedback += 'Alarm: ' + m.get_alarm_description(id)
            print(motor_feedback)
            if m.has_alarm[id]:
                print("Auto-resetting motor alarm")
                m.reset_alarm(id)
        time.sleep(0.01)
except KeyboardInterrupt: # Program can be stopped pressing CTRL+C
    for id in m.motors:
        m.target_rpm[id] = 0
    print("Shutting down smart thruster library...")

m.stop()
