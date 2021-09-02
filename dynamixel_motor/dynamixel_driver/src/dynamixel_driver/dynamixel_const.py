# -*- coding: utf-8 -*-
#
# Software License Agreement (BSD License)
#
# Copyright (c) 2010-2011, Cody Jorgensen, Antons Rebguns.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above
#    copyright notice, this list of conditions and the following
#    disclaimer in the documentation and/or other materials provided
#    with the distribution.
#  * Neither the name of University of Arizona nor the names of its
#    contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.


__author__ = 'Cody Jorgensen, Antons Rebguns'
__copyright__ = 'Copyright (c) 2010-2011 Cody Jorgensen, Antons Rebguns'

__license__ = 'BSD'
__maintainer__ = 'Antons Rebguns'
__email__ = 'anton@email.arizona.edu'


"""
Dynamixel Constants
"""
# Control Table Constants

DXL_MODEL_NUMBER_L = 0 
DXL_MODEL_NUMBER_H = 1
DXL_VERSION = 6 #2
DXL_ID = 7 #3
DXL_BAUD_RATE = 8 #4
DXL_RETURN_DELAY_TIME = 9 #5
DXL_CW_ANGLE_LIMIT_L = 2 #6           #Doesn't exist
DXL_CW_ANGLE_LIMIT_H = 2 #7           #Doesn't exist
DXL_CCW_ANGLE_LIMIT_L = 2 #8           #Doesn't exist
DXL_CCW_ANGLE_LIMIT_H = 2 #9           #Doesn't exist
DXL_DRIVE_MODE = 10 #10
DXL_LIMIT_TEMPERATURE = 31 #11
DXL_DOWN_LIMIT_VOLTAGE = 34 #12    Warn: two bytes, expecting one?
DXL_UP_LIMIT_VOLTAGE = 32 #13      Warn: two bytes, expecting one?
DXL_MAX_TORQUE_L = 2 #14           #Doesn't exist
DXL_MAX_TORQUE_H = 2 #15           #Doesn't exist
DXL_RETURN_LEVEL = 68 #16
DXL_ALARM_LED = 2 #17           #Doesn't exist
DXL_ALARM_SHUTDOWN = 2 #18           #Doesn't exist
DXL_OPERATING_MODE = 11 #19
DXL_DOWN_CALIBRATION_L = 2 #20           #Doesn't exist
DXL_DOWN_CALIBRATION_H = 2 #21           #Doesn't exist
DXL_UP_CALIBRATION_L = 2 #22           #Doesn't exist
DXL_UP_CALIBRATION_H = 2 #23           #Doesn't exist
DXL_TORQUE_ENABLE = 64 #24
DXL_LED = 65 #25
#DXL_CW_COMPLIANCE_MARGIN = 26           #Doesn't exist
#DXL_CCW_COMPLIANCE_MARGIN = 27           #Doesn't exist
#DXL_CW_COMPLIANCE_SLOPE = 28           #Doesn't exist
#DXL_CCW_COMPLIANCE_SLOPE = 29           #Doesn't exist
DXL_D_GAIN = 80 #26		Warn: two bytes, expecting one?
DXL_I_GAIN = 82 #27		Warn: two bytes, expecting one?
DXL_P_GAIN = 84 #28		Warn: two bytes, expecting one?
DXL_GOAL_POSITION_L = 116 #29
DXL_GOAL_POSITION_H = 117 #30 
DXL_GOAL_SPEED_L = 104 #32 	Warn: 4 bytes, expecting 2?
DXL_GOAL_SPEED_H = 105 #33 	Warn: 4 bytes, expecting 2?
DXL_TORQUE_LIMIT_L = 2 #34           #Doesn't exist
DXL_TORQUE_LIMIT_H = 2 #35           #Doesn't exist
DXL_PRESENT_POSITION_L = 132 #36 Warn: 4 bytes, expecting 2?
DXL_PRESENT_POSITION_H = 133 #37 Warn: 4 bytes, expecting 2?
DXL_PRESENT_SPEED_L = 128 #38  Warn: 4 bytes, expecting 2?
DXL_PRESENT_SPEED_H = 129 #39 
DXL_PRESENT_LOAD_L = 126 #40
DXL_PRESENT_LOAD_H = 127 #41
DXL_PRESENT_VOLTAGE = 144 #42  Warn: 2 bytes, expecting 1?
DXL_PRESENT_TEMPERATURE = 146 #43
DXL_REGISTERED_INSTRUCTION = 69 #44
DXL_PAUSE_TIME = 2 #45		#Doesn't exist	
DXL_MOVING = 122 #46
DXL_LOCK = 2 #47			#Doesn't exist
DXL_PUNCH_L = 2 #48		#Doesn't exist
DXL_PUNCH_H = 2 #49		#Doesn't exist
DXL_SENSED_CURRENT_L = 2 #56   # For EX-106 #Doesn't exist
DXL_SENSED_CURRENT_H = 2 #57   #Doesn't exist	
DXL_CURRENT_L = 2 #68    # For MX-64 and up; different unit than EX-106 #Doesn't exist
DXL_CURRENT_H = 2 #69    #Doesn't exist
DXL_TORQUE_CONTROL_MODE = 2 #70    #Doesn't exist 
DXL_GOAL_TORQUE_L = 2 #71		#Doesn't exist
DXL_GOAL_TORQUE_H = 2 #72		#Doesn't exist
DXL_GOAL_ACCELERATION = 2 #73	#Doesn't exist

# Status Return Levels
DXL_RETURN_NONE = 0
DXL_RETURN_READ = 1
DXL_RETURN_ALL = 2

# Instruction Set
DXL_PING = 1
DXL_READ_DATA = 2
DXL_WRITE_DATA = 3
DXL_REG_WRITE = 4
DXL_ACTION = 5
DXL_RESET = 6
DXL_SYNC_WRITE = 131 #131 originally, protocol 1 dynamixel says 83

# Broadcast Constant
DXL_BROADCAST = 254

# Error Codes 
DXL_INSTRUCTION_ERROR = 64 #different format for XL
DXL_OVERLOAD_ERROR = 32
DXL_CHECKSUM_ERROR = 16
DXL_RANGE_ERROR = 8
DXL_OVERHEATING_ERROR = 4
DXL_ANGLE_LIMIT_ERROR = 2
DXL_INPUT_VOLTAGE_ERROR = 1
DXL_NO_ERROR = 0

# Static parameters
DXL_MIN_COMPLIANCE_MARGIN = 0
DXL_MAX_COMPLIANCE_MARGIN = 255

DXL_MIN_COMPLIANCE_SLOPE = 1
DXL_MAX_COMPLIANCE_SLOPE = 254

# These are guesses as Dynamixel documentation doesn't have any info about it
DXL_MIN_PUNCH = 0
DXL_MAX_PUNCH = 255

DXL_MAX_SPEED_TICK = 1023                   # maximum speed in encoder units
DXL_MAX_TORQUE_TICK = 1023                  # maximum torque in encoder units

KGCM_TO_NM = 0.0980665                      # 1 kg-cm is that many N-m
RPM_TO_RADSEC = 0.104719755                 # 1 RPM is that many rad/sec

# maximum holding torque is in N-m per volt
# maximum velocity is in rad/sec per volt
DXL_MODEL_TO_PARAMS = \
{
    113: { 'name':               'DX-113',
           'encoder_resolution': 1024,
           'range_degrees':      300.0,
           'torque_per_volt':    1.0 / 12.0,                       #  1.0 NM @ 12V
           'velocity_per_volt':  (54 * RPM_TO_RADSEC) / 12.0,      #  54 RPM @ 12V
           'rpm_per_tick':       0.111,
           'features':           []
         },
    116: { 'name':               'DX-116',
           'encoder_resolution': 1024,
           'range_degrees':      300.0,
           'torque_per_volt':    2.1 / 12.0,                       #  2.1 NM @ 12V
           'velocity_per_volt':  (78 * RPM_TO_RADSEC) / 12.0,      #  78 RPM @ 12V
           'rpm_per_tick':       0.111,
           'features':           []
         },
    117: { 'name':               'DX-117',
           'encoder_resolution': 1024,
           'range_degrees':      300.0,
           'torque_per_volt':    3.7 / 18.5,                       #  3.7 NM @ 18.5V
           'velocity_per_volt':  (85 * RPM_TO_RADSEC) / 18.5,      #  85 RPM @ 18.5V
           'rpm_per_tick':       0.111,
           'features':           []
         },
     12: { 'name':               'AX-12',
           'encoder_resolution': 1024,
           'range_degrees':      300.0,
           'torque_per_volt':    1.5 / 12.0,                       #  1.5 NM @ 12V
           'velocity_per_volt':  (59 * RPM_TO_RADSEC) / 12.0,      #  59 RPM @ 12V
           'rpm_per_tick':       0.111,
           'features':           []
         },
    300: { 'name':               'AX-12W',
           'encoder_resolution': 1024,
           'range_degrees':      300.0,
           'torque_per_volt':    0.2 / 12.0,                       # 0.2 NM @ 12V
           'velocity_per_volt':  (470 * RPM_TO_RADSEC) / 12.0,     # 470 RPM @ 12V
           'rpm_per_tick':       0.111,
           'features':           []
         },
     18: { 'name':               'AX-18',
           'encoder_resolution': 1024,
           'range_degrees':      300.0,
           'torque_per_volt':    1.8 / 12.0,                       #  1.8 NM @ 12V
           'velocity_per_volt':  (97 * RPM_TO_RADSEC) / 12.0,      #  97 RPM @ 12V
           'rpm_per_tick':       0.111,
           'features':           []
         },
     10: { 'name':               'RX-10',
           'encoder_resolution': 1024,
           'range_degrees':      300.0,
           'torque_per_volt':    1.3 / 12.0,                       #  1.3 NM @ 12V
           'velocity_per_volt':  (54 * RPM_TO_RADSEC) / 12.0,      #  54 RPM @ 12V
           'rpm_per_tick':       0.111,
           'features':           []
         },
     24: { 'name':               'RX-24',
           'encoder_resolution': 1024,
           'range_degrees':      300.0,
           'torque_per_volt':    2.6 / 12.0,                       #  2.6 NM @ 12V
           'velocity_per_volt':  (126 * RPM_TO_RADSEC) / 12.0,     # 126 RPM @ 12V
           'rpm_per_tick':       0.111,
           'features':           []
         },
     28: { 'name':               'RX-28',
           'encoder_resolution': 1024,
           'range_degrees':      300.0,
           'torque_per_volt':    3.7 / 18.5,                       #  3.7 NM @ 18.5V
           'velocity_per_volt':  (85 * RPM_TO_RADSEC) / 18.5,      #  85 RPM @ 18.5V
           'rpm_per_tick':       0.111,
           'features':           []
         },
     64: { 'name':               'RX-64',
           'encoder_resolution': 1024,
           'range_degrees':      300.0,
           'torque_per_volt':    5.3 / 18.5,                       #  5.3 NM @ 18.5V
           'velocity_per_volt':  (64 * RPM_TO_RADSEC) / 18.5,      #  64 RPM @ 18.5V
           'rpm_per_tick':       0.111,
           'features':           []
         },
    106: { 'name':               'EX-106',
           'encoder_resolution': 4096,
           'range_degrees':      250.92,
           'torque_per_volt':    10.9 / 18.5,                      # 10.9 NM @ 18.5V
           'velocity_per_volt':  (91 * RPM_TO_RADSEC) / 18.5,      #  91 RPM @ 18.5V
           'rpm_per_tick':       0.111,
           'features':           [DXL_SENSED_CURRENT_L]
         },     
    107: { 'name':               'EX-106+',
           'encoder_resolution': 4096,
           'range_degrees':      250.92,
           'torque_per_volt':    10.9 / 18.5,                      # 10.9 NM @ 18.5V
           'velocity_per_volt':  (91 * RPM_TO_RADSEC) / 18.5,      #  91 RPM @ 18.5V
           'rpm_per_tick':       0.111,
           'features':           [DXL_SENSED_CURRENT_L]
         },
    360: { 'name':               'MX-12W',
           'encoder_resolution': 4096,
           'range_degrees':      360.0,
           'torque_per_volt':    0.2 / 12.0,                        #  torque not specified!
           'velocity_per_volt':  (470 * RPM_TO_RADSEC) / 12.0,      #  470 RPM @ 12.0V
           'rpm_per_tick':       0.114,
           'features':           [DXL_GOAL_ACCELERATION]
         },
     29: { 'name':               'MX-28',
           'encoder_resolution': 4096,
           'range_degrees':      360.0,
           'torque_per_volt':    2.5 / 12.0,                       #  2.5 NM @ 12V
           'velocity_per_volt':  (55 * RPM_TO_RADSEC) / 12.0,      #  54 RPM @ 12.0V
           'rpm_per_tick':       0.114,
           'features':           [DXL_GOAL_ACCELERATION]
         },
    310: { 'name':               'MX-64',
           'encoder_resolution': 4096,
           'range_degrees':      360.0,
           'torque_per_volt':    6.0 / 12.0,                       #  6 NM @ 12V
           'velocity_per_volt':  (63 * RPM_TO_RADSEC) / 12.0,      #  63 RPM @ 12.0V
           'rpm_per_tick':       0.114,
           'features':           [DXL_CURRENT_L, DXL_TORQUE_CONTROL_MODE, DXL_GOAL_ACCELERATION]
         },
    320: { 'name':               'MX-106',
           'encoder_resolution': 4096,
           'range_degrees':      360.0,
           'torque_per_volt':    8.4 / 12.0,                       #  8.4 NM @ 12V
           'velocity_per_volt':  (45 * RPM_TO_RADSEC) / 12.0,      #  45 RPM @ 12.0V
           'rpm_per_tick':       0.114,
           'features':           [DXL_CURRENT_L, DXL_TORQUE_CONTROL_MODE, DXL_GOAL_ACCELERATION]
         },

	#Adding our motors (1060 and 1090)

    1060: {'name':               'XL430-W250-T',
           'encoder_resolution': 4096,
           'range_degrees':      360.0,
           'torque_per_volt':    1.5 / 12.0,                       #  1.5 NM @ 12V
           'velocity_per_volt':  (61 * RPM_TO_RADSEC) / 12.0,      #  61 RPM @ 12V
           'rpm_per_tick':       0.229,
           'features':           []
         },
    1090: {'name':               '2XL430-W250-T',
           'encoder_resolution': 4096,
           'range_degrees':      360.0,
           'torque_per_volt':    1.5 / 12.0,                       #  1.5 NM @ 12V
           'velocity_per_volt':  (61 * RPM_TO_RADSEC) / 12.0,      #  61 RPM @ 12.0V
           'rpm_per_tick':       0.229,
           'features':           []
         },
}

