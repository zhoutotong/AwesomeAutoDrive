#!/usr/bin/env python

import sys
sys.path.append('/home/tong/Documents/AwesomeAutoDrive/AwesomeViewer/ros_tools/devel/lib/python2.7/dist-packages')

import rospy
import time
from std_msgs.msg import Header
from rostopic import ROSTopicHz
from hmi_msgs.msg import node_state
from hmi_msgs.msg import all_state


from nox_msgs.msg import DrivingCommand

from nox_msgs.msg import Chassis



hz_checker = ROSTopicHz(10, use_wtime=True)

msg_dict = {}
topic_keys = ['hz', 'hz_state', 'params']
param_keys = ['value', 'state']

pub = rospy.Publisher('vehicle_info_node', all_state, queue_size = 10)

def func_checking_value(param, min, max):
	return param <= max and param >= min

def timer_callback(event):
	global hz_checker
	global pub

	node_msg = list()


	ret = hz_checker.get_hz('/driving_command')
	if(ret):
		if isinstance(ret, tuple) and len(ret) == 5:
			msg_dict['/driving_command']['hz'] = ret[0]
		else:
			msg_dict['/driving_command']['hz'] = -1
		msg_dict['/driving_command']['hz_state'] = func_checking_value(msg_dict['/driving_command']['hz'], 35.00, 40.00)

	ret = hz_checker.get_hz('/chassis')
	if(ret):
		if isinstance(ret, tuple) and len(ret) == 5:
			msg_dict['/chassis']['hz'] = ret[0]
		else:
			msg_dict['/chassis']['hz'] = -1
		msg_dict['/chassis']['hz_state'] = func_checking_value(msg_dict['/chassis']['hz'], 49.00, 51.00)




	node_msg.append(node_state('/driving_command', 
					msg_dict['/driving_command']['hz'], 
					msg_dict['/driving_command']['hz_state'], 
					'target_steering', 
					msg_dict['/driving_command']['params']['target_steering']['value'], 
					msg_dict['/driving_command']['params']['target_steering']['state']))

	node_msg.append(node_state('/driving_command', 
					msg_dict['/driving_command']['hz'], 
					msg_dict['/driving_command']['hz_state'], 
					'target_speed', 
					msg_dict['/driving_command']['params']['target_speed']['value'], 
					msg_dict['/driving_command']['params']['target_speed']['state']))

	node_msg.append(node_state('/chassis', 
					msg_dict['/chassis']['hz'], 
					msg_dict['/chassis']['hz_state'], 
					'speed', 
					msg_dict['/chassis']['params']['speed']['value'], 
					msg_dict['/chassis']['params']['speed']['state']))

	node_msg.append(node_state('/chassis', 
					msg_dict['/chassis']['hz'], 
					msg_dict['/chassis']['hz_state'], 
					'steering', 
					msg_dict['/chassis']['params']['steering']['value'], 
					msg_dict['/chassis']['params']['steering']['state']))



	header = Header(stamp=rospy.Time.now())
	pub_msg = all_state(header, node_msg)
	pub.publish(pub_msg)



def nox_msgs_DrivingCommand_callback(msg):
	global hz_checker
	hz_checker.callback_hz(msg, '/driving_command')
	msg_dict['/driving_command']['params']['target_steering']['value'] = msg.target_steering
	msg_dict['/driving_command']['params']['target_steering']['state'] = func_checking_value(msg.target_steering, 
						-720.00, 720.00)
	msg_dict['/driving_command']['params']['target_speed']['value'] = msg.target_speed
	msg_dict['/driving_command']['params']['target_speed']['state'] = func_checking_value(msg.target_speed, 
						0.00, 30.00)
def nox_msgs_Chassis_callback(msg):
	global hz_checker
	hz_checker.callback_hz(msg, '/chassis')
	msg_dict['/chassis']['params']['speed']['value'] = msg.speed
	msg_dict['/chassis']['params']['speed']['state'] = func_checking_value(msg.speed, 
						0.00, 30.00)
	msg_dict['/chassis']['params']['steering']['value'] = msg.steering
	msg_dict['/chassis']['params']['steering']['state'] = func_checking_value(msg.steering, 
						-720.00, 720.00)





def main():
	rospy.init_node('vehicle_info_node', anonymous=False)
	curr = rospy.get_rostime().to_sec()


	msg_dict['/driving_command'] = dict.fromkeys(topic_keys)
	msg_dict['/driving_command']['hz'] = 0
	msg_dict['/driving_command']['hz_state'] = 0
	msg_dict['/driving_command']['params'] = dict()

	msg_dict['/driving_command']['params']['target_steering'] = dict.fromkeys(param_keys)

	msg_dict['/driving_command']['params']['target_speed'] = dict.fromkeys(param_keys)

	msg_dict['/chassis'] = dict.fromkeys(topic_keys)
	msg_dict['/chassis']['hz'] = 0
	msg_dict['/chassis']['hz_state'] = 0
	msg_dict['/chassis']['params'] = dict()

	msg_dict['/chassis']['params']['speed'] = dict.fromkeys(param_keys)

	msg_dict['/chassis']['params']['steering'] = dict.fromkeys(param_keys)





	hz_checker.set_msg_t0(curr, topic = '/driving_command')
	hz_checker.set_msg_t0(curr, topic = '/chassis')



	rospy.Subscriber('/driving_command', DrivingCommand, nox_msgs_DrivingCommand_callback)
	rospy.Subscriber('/chassis', Chassis, nox_msgs_Chassis_callback)


	rospy.Timer(rospy.Duration(1), timer_callback)

	rospy.spin()

if __name__ == '__main__':
	main()
