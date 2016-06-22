#!/usr/bin/python2.7

# FLORIPASAT 
# Parser and data converter of fsat frames
# Created by Mario Baldini <mario.baldini@gmail.com>
# 2016-06-22
import sys


if len(sys.argv) <= 1:
    print 'Insuficient arguments! Usage: python2.7', sys.argv[0], ' frames_file.txt'
    quit()

file = open(str(sys.argv[1]), "r")

file_content = file.read()
lines = file_content.split('\n\r')

print "------------------------------------------------------------------"
print "obdh_clock  obdh_temp  obdh_status  imu_acc_x,y,z  imu_gyr_x,y,z  radio_counter1,2"
print "------------------------------------------------------------------"

for line in lines: 
    # print line.split(' ')

    line_tokens = line.split(' ')
    # print line_tokens, len(line_tokens)
    # print line_tokens[-1]

    if (line_tokens[0] == "{{{") and ( line_tokens[-1] == "}"):
        
        obdh_sysclock_s_H           = int( line_tokens[1], 16)
        obdh_sysclock_s_L           = int( line_tokens[2], 16)
        obdh_sysclock_ms_H          = int( line_tokens[3], 16)
        obdh_sysclock_ms_L          = int( line_tokens[4], 16)
        obdh_internal_temperature_H = int( line_tokens[5], 16)
        obdh_internal_temperature_L = int( line_tokens[6], 16)
        obdh_statuscode             = int( line_tokens[7], 16)

        imu_acc_x_H = int( line_tokens[8] , 16)
        imu_acc_x_L = int( line_tokens[9] , 16)
        imu_acc_y_H = int( line_tokens[10], 16)
        imu_acc_y_L = int( line_tokens[11], 16)
        imu_acc_z_H = int( line_tokens[12], 16)
        imu_acc_z_L = int( line_tokens[13], 16)
        imu_gyr_x_H = int( line_tokens[14], 16)
        imu_gyr_x_L = int( line_tokens[15], 16)
        imu_gyr_y_H = int( line_tokens[16], 16)
        imu_gyr_y_L = int( line_tokens[17], 16)
        imu_gyr_z_H = int( line_tokens[18], 16)
        imu_gyr_z_L = int( line_tokens[19], 16)

        radio_counter1_H = int( line_tokens[20], 16)
        radio_counter1_L = int( line_tokens[21], 16)
        radio_counter2_H = int( line_tokens[22], 16)
        radio_counter2_L = int( line_tokens[23], 16)

        eps_current_H      = int( line_tokens[24], 16)
        eps_current_L      = int( line_tokens[25], 16)
        eps_voltage_bat1_H = int( line_tokens[26], 16)
        eps_voltage_bat1_L = int( line_tokens[27], 16)
        eps_voltage_bat2_H = int( line_tokens[28], 16)
        eps_voltage_bat2_L = int( line_tokens[29], 16)
        eps_temperature_H  = int( line_tokens[30], 16)
        eps_temperature_L  = int( line_tokens[31], 16)
        eps_current_acc_H  = int( line_tokens[32], 16)
        eps_current_acc_L  = int( line_tokens[33], 16)
        eps_batmon_reg     = int( line_tokens[34], 16)

        crc = int( line_tokens[35], 16)




        ## OBDH Data convertion formulas

        obdh_sysclock_s  = (obdh_sysclock_s_H << 8)  + obdh_sysclock_s_L
        obdh_sysclock_ms = (obdh_sysclock_ms_H << 8) + obdh_sysclock_ms_L
        
        obdh_internal_temperature = (obdh_internal_temperature_H << 8)  + obdh_internal_temperature_L
        if (obdh_internal_temperature != 0):
            obdh_internal_temperature = (obdh_internal_temperature*55.0 - 107895) / 358.0

        IMU_ACC_RANGE = 16.0
        IMU_GYR_RANGE =  2.0

        imu_acc_x = (((imu_acc_x_H << 8 | imu_acc_x_L) * IMU_ACC_RANGE) / 32768.0)
        imu_acc_y = (((imu_acc_y_H << 8 | imu_acc_y_L) * IMU_ACC_RANGE) / 32768.0)
        imu_acc_z = (((imu_acc_z_H << 8 | imu_acc_z_L) * IMU_ACC_RANGE) / 32768.0)
        imu_gyr_x = (((imu_acc_x_H << 8 | imu_acc_x_L) * IMU_GYR_RANGE) / 32768.0)
        imu_gyr_y = (((imu_acc_y_H << 8 | imu_acc_y_L) * IMU_GYR_RANGE) / 32768.0)
        imu_gyr_z = (((imu_acc_z_H << 8 | imu_acc_z_L) * IMU_GYR_RANGE) / 32768.0)

        radio_counter1 = (radio_counter1_H << 8)  + radio_counter1_L
        radio_counter2 = (radio_counter2_H << 8)  + radio_counter2_L






        print "%.05d" % obdh_sysclock_s + "." + "%.03d" % obdh_sysclock_ms,
        print "\t%.02f" % obdh_internal_temperature,
        print "   " + str(obdh_statuscode),

        print "\t%.03f %.03f %.03f" % (imu_acc_x, imu_acc_y, imu_acc_z),
        print "\t%.03f %.03f %.03f" % (imu_gyr_x, imu_gyr_y, imu_gyr_z),


        print "\t",radio_counter1,radio_counter2,

        print

    # else: 
        # print ">>> INVALID FRAME:", line


    # print line_tokens[-1]

    # for token in line.split(' '):
        # tokens.append( token )




file.close()

